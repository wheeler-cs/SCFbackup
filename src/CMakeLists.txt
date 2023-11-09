
add_executable (SCFserver server_main.c)

add_compile_options(-Wall -Wextra -Wpedantic -g)
target_include_directories (SCFserver PRIVATE ../inc)
target_sources (SCFserver PRIVATE
    config.c
    filesystem.c
    hash.c
    list.c
    server.c
)
