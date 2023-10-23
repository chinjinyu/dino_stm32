target("stm32g0xx")
    set_kind("static")
    add_defines(
        "STM32G030xx",
        "USE_HAL_DRIVER",
        "USE_FULL_LL_DRIVER",
        "ARM_MATH_CM0PLUS",
        {public = true}
    )
    add_files(
        "CMSIS/Device/ST/STM32G0xx/Source/Templates/gcc/startup_stm32g030xx.s",
        "CMSIS/Device/ST/STM32G0xx/Source/Templates/*.c",
        "STM32G0xx_HAL_Driver/Src/*.c|*_template.c"
    )
    add_includedirs(
        ".",
        "CMSIS/Core/Include",
        "CMSIS/Device/ST/STM32G0xx/Include",
        "CMSIS/DSP/Include",
        "STM32G0xx_HAL_Driver/Inc",
        {public = true}
    )
    add_linkdirs("CMSIS/DSP/Lib/GCC")
    add_links("arm_cortexM0l_math")

    if is_mode("debug") then
        add_defines(
            "USE_FULL_ASSERT",
            {public = true}
        )
    end
