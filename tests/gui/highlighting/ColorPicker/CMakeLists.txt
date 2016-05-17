set( testname ColorPickerTest )
set( testmodules Test Widgets )
set( testlibraries TestCommon )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )

file(GLOB source_files  ${source_dir}/gui/highlighting/ColorPicker.cpp)

file(GLOB ui_files_topmost ${source_dir}/gui/highlighting/ColorPicker.ui)

set( Test_SOURCES
  tst_${testname}.cpp
  ${source_files}
)

set( Test_UIs
  ${ui_files_topmost}
)
qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
