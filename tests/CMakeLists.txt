set(source_dir ${CMAKE_SOURCE_DIR}/src)
include_directories(
    ${source_dir}
    ${source_dir}/engine
    ${CMAKE_CURRENT_LIST_DIR}/common
)

add_subdirectory( common )
add_subdirectory( engine )
add_subdirectory( gui )
