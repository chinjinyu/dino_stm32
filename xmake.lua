-- 设置工程名
set_project("stm32g030f6 projects")
-- 设置版本号
set_version("1.0.1")
-- 设置编程语言
set_languages("gnu99", "gnuxx11")

-- 定义交叉编译工具链
toolchain("arm-none-eabi-gcc")
    local sdkdir = "$(env HOME)/tools/xpack-arm-none-eabi-gcc-12.3.1-1.1"
    local includedir = path.join(sdkdir, "arm-none-eabi", "include")

    set_kind("standalone")
    set_sdkdir(sdkdir)
    -- 下面这行可以省略，这里主要是为了解决clangd无法找到系统头文件的问题
    add_includedirs(includedir)
toolchain_end()

-- 设置默认编译工具和平台（可被命令行覆盖）
set_config("toolchain", "arm-none-eabi-gcc")
set_defaultplat("cross")
set_defaultarchs("arm")
set_defaultmode("debug")

-- 添加debug和release模式
add_rules("mode.debug", "mode.release")

-- 链接脚本
local linkscript = path.join("misc", "STM32G030F6PX_FLASH.ld")
-- OpenOCD配置文件
local openocd_cfg = {
    path.join("misc", "cmsis-dap.cfg"),
    path.join("misc", "stm32g0x.cfg")
}
-- GCC中与MCU相关的选项
local mcu_flags = {
    "-mcpu=cortex-m0plus",
    "-mthumb",
    "-mfloat-abi=soft"
}

-- 添加C/C++编译选项
add_cxflags(
    table.unpack(mcu_flags),
    "-fdata-sections",
    "-ffunction-sections"
)

-- 添加汇编选项
add_asflags(
    table.unpack(mcu_flags),
    "-x assembler-with-cpp",
    "-fdata-sections",
    "-ffunction-sections"
)

-- 添加链接选项
add_ldflags(
    table.unpack(mcu_flags),
    "-T" .. linkscript,
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
        local cp = find_program(prefix .. "objcopy", {paths = bindir})
        local hex = cp .. " -O ihex"
        local bin = cp .. " -O binary -S"

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
    end)
task_end()

-- 定义编程目标任务
task("program target")
    on_run(function (target)
        import("lib.detect.find_program")

        local openocd = find_program("openocd")
        local command = string.format("program %s verify reset exit", target:targetfile())
        local openocd_flags = ""

        for _, v in ipairs(openocd_cfg) do
            openocd_flags = openocd_flags .. string.format("-f %s ", v)
        end
        openocd_flags = openocd_flags .. string.format("-c \"%s\"", command)

        os.exec("%s %s", openocd, openocd_flags)
    end)
task_end()
