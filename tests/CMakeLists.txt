set(source_dir ${CMAKE_SOURCE_DIR}/src)
include_directories(
    ${source_dir}
    ${CMAKE_CURRENT_LIST_DIR}/common
)

add_subdirectory( common )
add_subdirectory( data )
add_subdirectory( gui )
