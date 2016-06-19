set( testname MainWindowTest )
set( testmodules Test Widgets )
set( testlibraries TestCommon TailEngine )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )

file(GLOB source_files  ${source_dir}/gui/*.cpp)
list(REMOVE_ITEM source_files ${source_dir}/gui/main.cpp)
file(GLOB source_files_tools ${source_dir}/gui/tools/*.cpp)
file(GLOB source_files_views ${source_dir}/gui/file_views/*.cpp)
file(GLOB source_files_highlighting ${source_dir}/gui/highlighting/*.cpp)
file(GLOB source_files_filter ${source_dir}/gui/filter/*.cpp)

file(GLOB ui_files_topmost ${source_dir}/gui/*.ui)
file(GLOB ui_files_views ${source_dir}/gui/file_views/*.ui)
file(GLOB ui_files_highlighting ${source_dir}/gui/highlighting/*.ui)
file(GLOB ui_files_filter ${source_dir}/gui/filter/*.ui)

set( Test_SOURCES
  tst_${testname}.cpp
  ${source_files}
  ${source_files_views}
  ${source_files_tools}
  ${source_files_highlighting}
  ${source_files_filter}
)

set( Test_UIs
  ${ui_files_topmost}
  ${ui_files_views}
  ${ui_files_highlighting}
  ${ui_files_filter}
)
qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

include_directories(
    ${CMAKE_BINARY_DIR}/src/gui
)

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )

if (WIN32)
    include(WinDeployQt)
    windeployqt(TARGET ${testname})
endif()
