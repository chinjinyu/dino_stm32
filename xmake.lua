-- 设置工程名
set_project("dino")
-- 设置版本号
set_version("1.0.4")
-- 设置编程语言
set_languages("gnu99", "gnuxx11")

-- 编译工具链路径
option("gcc-dir")
    set_default(path.join("$(env HOME)", "tools", "xpack-arm-none-eabi-gcc-13.2.1-1.1"))
    set_description("GNU C Cross Compiler Toolchain")
option_end()

-- Cortex内核类型
option("cortex-arch")
    set_default("cortex-m0plus")
    set_values("cortex-m0", "cortex-m0plus", "cortex-m3", "cortex-m4", "cortex-m7", "cortex-m23", "cortex-m33")
    set_description("Cortex Architecture",
                    "    - cortex-m0",
                    "    - cortex-m0plus",
                    "    - cortex-m3",
                    "    - cortex-m4",
                    "    - cortex-m7",
                    "    - cortex-m23",
                    "    - cortex-m33")
    set_category("MCU")
option_end()

-- 启用FPU
option("enable-fpu")
    set_default(false)
    set_description("Enable FPU")
    set_category("MCU")
option_end()

-- FPU类型
option("fpu-type")
    set_default("none")
    set_values("none", "fpv4-sp-d16", "fpv4-d16", "fpv5-sp-d16", "fpv5-d16")
    set_description("FPU Type")
    set_category("MCU")
option_end()

-- 链接脚本路径
option("linkscript")
    set_default(path.join("misc", "STM32G030F6PX_FLASH.ld"))
    set_description("Linkscript")
    set_category("MCU")
option_end()

-- 编程器类型
option("programmer")
    set_default("pyOCD")
    set_values("OpenOCD", "pyOCD")
    set_description("Programmer",
                    "    - OpenOCD",
                    "    - pyOCD")
option_end()

-- OpenOCD接口配置文件
option("openocd-interface")
    set_default(path.join("misc", "cmsis-dap.cfg"))
    set_description("Interface Config File")
    set_category("OpenOCD")
option_end()

-- OpenOCD目标配置文件
option("openocd-target")
    set_default(path.join("misc", "stm32g0x.cfg"))
    set_description("Target Config File")
    set_category("OpenOCD")
option_end()

-- MCU型号
option("mcu-part")
    set_default("STM32G030F6Px")
    set_description("MCU Part")
    set_category("pyOCD")
option_end()

-- 定义交叉编译工具链
toolchain("arm-none-eabi-gcc")
    set_kind("standalone")
    set_sdkdir("$(gcc-dir)")
    -- 下面这行可以省略，这里主要是为了解决clangd无法找到系统头文件的问题
    add_includedirs(path.join("$(gcc-dir)", "arm-none-eabi", "include"))
toolchain_end()

-- 设置默认编译工具和平台（可被命令行覆盖）
set_config("toolchain", "arm-none-eabi-gcc")
set_defaultplat("cross")
set_defaultarchs("arm")
set_defaultmode("debug")

-- 添加debug和release模式
add_rules("mode.debug", "mode.release")

-- GCC中与MCU相关的选项
local mcu_flags = {
    "-mcpu=$(cortex-arch)",
    "-mthumb",
}
if has_config("enable-fpu") then
    table.insert(mcu_flags, "-mfloat-abi=hard")
    if not is_config("fpu-type", "none") then
        table.insert(mcu_flags, "-mfpu=$(fpu-type)")
    end
else
    table.insert(mcu_flags, "-mfloat-abi=soft")
end

-- 添加C/C++编译选项
add_cxflags(
    mcu_flags,
    "-fdata-sections",
    "-ffunction-sections",
    {force = true}
)

-- 添加汇编选项
add_asflags(
    mcu_flags,
    "-x assembler-with-cpp",
    "-fdata-sections",
    "-ffunction-sections",
    {force = true}
)

-- 添加链接选项
add_ldflags(
    mcu_flags,
    "-T$(linkscript)",
    "-Wl,--gc-sections",
    "-Wl,--no-warn-rwx-segments",
    "-specs=nano.specs",
    {force = true}
)

-- 添加系统链接库
add_syslinks("c", "m", "nosys")
-- 设置警告级别
set_warnings("allextra")
-- 包含子目录
includes("**/xmake.lua")

-- 定义app规则
rule("app")
    -- 设置build之后执行的任务
    after_build(function (target)
        import("core.base.task")
        task.run("convert target", {}, target)
    end)

    -- 设置clean之后执行的任务
    after_clean(function (target)
        import("core.base.task")
        task.run("clean target", {}, target)
    end)

    -- 设置run时执行的任务
    on_run(function (target)
        import("core.base.task")
        task.run("program target", {}, target)
    end)
rule_end()

-- 定义转换目标任务
task("convert target")
    on_run(function (target)
        import("lib.detect.find_program")

        local toolchain = target:toolchains()[1]
        local bindir = toolchain:bindir()
        local prefix = toolchain:cross()
        local size = find_program(prefix .. "size", {paths = bindir})
        local copy = find_program(prefix .. "objcopy", {paths = bindir})
        local dump = find_program(prefix .. "objdump", {paths = bindir})
        local hex = copy .. " -O ihex"
        local bin = copy .. " -O binary -S"

        os.execv(dump, {"-h", "-S", target:targetfile()}, {stdout = path.join(target:targetdir(), target:basename() .. ".list")})
        os.exec("%s %s", size, target:targetfile())
        os.exec("%s %s %s", hex, target:targetfile(), path.join(target:targetdir(), target:basename() .. ".hex"))
        os.exec("%s %s %s", bin, target:targetfile(), path.join(target:targetdir(), target:basename() .. ".bin"))
    end)
task_end()

-- 定义清理目标任务
task("clean target")
    on_run(function (target)
        os.rm(path.join(target:targetdir(), target:basename() .. ".hex"))
        os.rm(path.join(target:targetdir(), target:basename() .. ".bin"))
        os.rm(path.join(target:targetdir(), target:basename() .. ".list"))
    end)
task_end()

-- 定义编程目标任务
task("program target")
    on_run(function (target)
        import("lib.detect.find_program")
        local command = nil

        if is_config("programmer", "OpenOCD") then
            local openocd = find_program("openocd")
            local operation = string.format("program %s verify reset exit", target:targetfile())
            command = string.format("%s -f $(openocd-interface) -f $(openocd-target) -c \"%s\"", openocd, operation)
        elseif is_config("programmer", "pyOCD") then
            local pyocd = find_program("pyocd")
            command = string.format("%s load --erase=auto --target=$(mcu-part) %s", pyocd, target:targetfile())
        end
        
        print(string.format("use programmer \"%s\"", "$(programmer)"))
        print(command)
        os.exec(command)
    end)
task_end()
