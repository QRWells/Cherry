add_defines("SRC")

add_requires("fmt", "openmp")
add_requires("nlohmann_json", {alias = "json"})
add_requires("magic_enum")

target("Cherry")
    set_default(true)
    set_kind("binary")
    set_languages("c17", "gnu++20")

    add_vectorexts("mmx")
    add_vectorexts("neon")
    add_vectorexts("avx", "avx2")
    add_vectorexts("sse", "sse2", "sse3", "ssse3")

    add_includedirs("$(curdir)/include")

    add_files("$(curdir)/src/**.cc")
    remove_files("$(curdir)/src/object/mesh.cc", "$(curdir)/src/utility/sampler.cc")

    add_packages("fmt", "openmp", "json", "magic_enum")
target_end()