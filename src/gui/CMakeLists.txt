set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package( Qt5Widgets REQUIRED )

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/file_views
    ${CMAKE_CURRENT_LIST_DIR}/highlighting
)

set(Project_Sources
  main.cpp
  MainWindow.cpp
  AboutDialog.cpp
  PreferencesDialog.cpp

  file_views/FileListItemView.cpp
  file_views/FileListItemWidget.cpp
  file_views/PlainTextView.cpp
  file_views/PlainTextViewWidget.cpp
  file_views/PlainTextEdit.cpp
  file_views/SyntaxHighlighter.cpp
  file_views/LineNumberArea.cpp

  tools/Settings.cpp

  highlighting/HighlightingDialog.cpp
  highlighting/ColorPicker.cpp
  highlighting/FontPicker.cpp
  highlighting/HighlightListItemDelegate.cpp

  filter/FilterDialog.cpp
  filter/FileFilterWidget.cpp
)

configure_file(${CMAKE_CURRENT_LIST_DIR}/../version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/QTail_version.h)


qt5_wrap_ui(Project_Sources
  MainWindow.ui
  AboutDialog.ui
  PreferencesDialog.ui

  file_views/FileListItemWidget.ui
  file_views/PlainTextViewWidget.ui

  highlighting/HighlightingDialog.ui
  highlighting/ColorPicker.ui
  highlighting/FontPicker.ui

  filter/FilterDialog.ui
  filter/FileFilterWidget.ui
)

qt5_add_resources(Project_Sources
    resources.qrc
)

add_executable(${PROJECT_NAME} WIN32 ${Project_Sources})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets TailEngine )

install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION bin)

if (WIN32)
    include(WinDeployQt)
    windeployqt(CREATE_INSTALLS TARGET ${PROJECT_NAME} OUTPUT_DIR ${CMAKE_INSTALL_PREFIX}/bin)
endif()

# Packaging

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A tail programm written in C++/Qt.")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
set(CPACK_GENERATOR "IFW")
set(CPACK_IFW_PACKAGE_NAME ${PROJECT_NAME})

include(CPack)
include(CPackIFW)
