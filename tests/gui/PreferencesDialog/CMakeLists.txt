set( testname PreferencesDialogTest )
set( testmodules Test Widgets )
set( testlibraries TestCommon TailEngine )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )

set(source_files
   ${source_dir}/gui/PreferencesDialog.cpp
   ${source_dir}/gui/highlighting/FontPicker.cpp
   ${source_dir}/gui/tools/Settings.cpp
   ${source_dir}/gui/tools/OpenFileSettings.cpp
)

set(ui_files
   ${source_dir}/gui/PreferencesDialog.ui
   ${source_dir}/gui/highlighting/FontPicker.ui
)

set( Test_SOURCES
  tst_${testname}.cpp
  ${source_files}
)

set( Test_UIs
  ${ui_files}
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
