set( testname MainWindowTest )
set( testmodules Test Widgets )
set( testlibraries TestCommon TailEngine )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )

file(GLOB source_files  ${source_dir}/gui/*.cpp)
list(REMOVE_ITEM source_files ${source_dir}/gui/main.cpp)
file(GLOB source_files_tools ${source_dir}/gui/tools/*.cpp)
file(GLOB source_files_views ${source_dir}/gui/file_views/*.cpp)

file(GLOB ui_files_topmost ${source_dir}/gui/*.ui)
file(GLOB ui_files_views ${source_dir}/gui/file_views/*.ui)
set( Test_SOURCES
  tst_${testname}.cpp
  ${source_files}
  ${source_files_views}
  ${source_files_tools}
)

set( Test_UIs
  ${ui_files_topmost}
  ${ui_files_views}
)
qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

configure_file(${source_dir}/version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/QTail_version.h)

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
