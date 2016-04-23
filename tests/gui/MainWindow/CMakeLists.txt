set( testname MainWindowTest )
set( testmodules Test Widgets )
set( testlibraries TestCommon )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )

set( Test_SOURCES
        tst_${testname}.cpp
        ${source_dir}/gui/MainWindow.cpp
        ${source_dir}/gui/PlainTextEdit.cpp
        ${source_dir}/tools/Settings.cpp
        )

set( Test_UIs
      ${source_dir}/gui/MainWindow.ui
)
qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
