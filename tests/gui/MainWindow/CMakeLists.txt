set( testname MainWindowTest )
set( testmodules Test Widgets )
set( testlibraries TestCommon TailEngine )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )

set( Test_SOURCES
        tst_${testname}.cpp
        ${source_dir}/gui/MainWindow.cpp
        ${source_dir}/gui/AboutDialog.cpp
        ${source_dir}/gui/PlainTextEdit.cpp
        ${source_dir}/gui/FileListItemWidget.cpp
        ${source_dir}/gui/tools/Settings.cpp
        )

set( Test_UIs
      ${source_dir}/gui/MainWindow.ui
      ${source_dir}/gui/AboutDialog.ui
      ${source_dir}/gui/FileListItemWidget.ui
)
qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

configure_file(${source_dir}/version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/QTail_version.h)

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
