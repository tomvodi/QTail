set( testname PlainTextViewTest )
set( testmodules Test Widgets )
set( testlibraries TestCommon TailEngine )

find_package( Qt5Widgets REQUIRED )
find_package( Qt5Test REQUIRED )

set( Test_SOURCES
        tst_${testname}.cpp
        ${source_dir}/gui/file_views/PlainTextView.cpp
        ${source_dir}/gui/file_views/PlainTextViewWidget.cpp
        ${source_dir}/gui/file_views/PlainTextEdit.cpp
        )

set( Test_UIs
    ${source_dir}/gui/file_views/PlainTextViewWidget.ui
)
qt5_wrap_ui( Test_SOURCES ${Test_UIs} )

set( Test_Resources
)
qt5_add_resources(Test_SOURCES
      ${Test_Resources}
)

add_executable( ${testname} ${Test_SOURCES} )
qt5_use_modules( ${testname} ${testmodules} )
target_link_libraries( ${testname} ${testlibraries} )

add_test( NAME ${testname} COMMAND ${testname} )
