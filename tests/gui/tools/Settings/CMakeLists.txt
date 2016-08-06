set( testname SettingsTest )
set( testmodules Test Widgets )
set( testlibraries TestCommon TailEngine )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )

set( Test_SOURCES
  tst_${testname}.cpp
  ${source_dir}/gui/tools/Settings.cpp
  ${source_dir}/gui/tools/OpenFileSettings.cpp
)

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )

if (WIN32)
    include(WinDeployQt)
    windeployqt(TARGET ${testname})
endif()
