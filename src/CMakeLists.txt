
add_executable (SCFserver server_main.c)
add_compile_options(-Wall -Wextra -Wpedantic -g)
target_include_directories (SCFserver PRIVATE ../inc)
target_link_libraries (SCFserver ssl)
target_sources (SCFserver PRIVATE
    config.c
    filesystem.c
    hash.c
    list.c
    server.c
)

add_custom_target (runserver
    COMMAND ./SCFserver
    DEPENDS ./SCFserver
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
