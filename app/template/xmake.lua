target("template")
    set_kind("binary")
    set_suffixname(".elf")
    add_rules("app")
    add_files("**.c")
    add_includedirs(".")
    add_deps("board")
