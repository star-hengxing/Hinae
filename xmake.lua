set_project("Hinae")

target("test")
    add_includedirs("include")
    add_files("test/test.cpp")

    set_kind("binary")
    set_languages("c++20")
    
    add_cxxflags("-Wall")
    set_warnings("all", "error")
