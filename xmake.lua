set_project("Hinae")

if is_os("linux") then
    set_toolchains("clang")
end

add_includedirs("include")
set_languages("c++20")
set_warnings("all", "error")

target("test")
    set_kind("binary")
    add_files("test/test.cpp")
