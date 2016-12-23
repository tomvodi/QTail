set(source_dir ${CMAKE_SOURCE_DIR}/src)
set(binary_dir ${CMAKE_BINARY_DIR}/src)
include_directories(
    ${source_dir}
    ${source_dir}/engine
    ${source_dir}/gui/columnize
    ${binary_dir}/gui/columnize
    ${CMAKE_CURRENT_LIST_DIR}/common
)

add_subdirectory( common )
add_subdirectory( engine )
add_subdirectory( gui )
add_subdirectory( tools )
