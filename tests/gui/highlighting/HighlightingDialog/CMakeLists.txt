set( testname HighlightingDialogTest )
set( testmodules Test Widgets )
set( testlibraries TestCommon TailEngine )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )

file(GLOB source_files  ${source_dir}/gui/highlighting/*.cpp)

file(GLOB ui_files_topmost ${source_dir}/gui/highlighting/*.ui)

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

if (WIN32)
    include(WinDeployQt)
    windeployqt(TARGET ${testname})
endif()
