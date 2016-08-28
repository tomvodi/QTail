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
  ViewApplication.cpp

  file_views/FileListItemView.cpp
  file_views/FileListItemWidget.cpp
  file_views/PlainTextView.cpp
  file_views/PlainTextViewWidget.cpp
  file_views/PlainTextEdit.cpp
  file_views/SyntaxHighlighter.cpp
  file_views/LineNumberArea.cpp
  file_views/SearchBar.cpp

  tools/Settings.cpp
  tools/OpenFileSettings.cpp

  highlighting/HighlightingDialog.cpp
  highlighting/ColorPicker.cpp
  highlighting/FontPicker.cpp
  highlighting/HighlightListItemDelegate.cpp

  filter/FilterDialog.cpp
  filter/FileFilterWidget.cpp

  columnize/ColumnizeDialog.cpp
)

if (WIN32)
    list(APPEND Project_Sources windows_resources.rc)
endif()

configure_file(${CMAKE_CURRENT_LIST_DIR}/../version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/QTail_version.h)


set( Project_UIs
    MainWindow.ui
    AboutDialog.ui
    PreferencesDialog.ui

    file_views/FileListItemWidget.ui
    file_views/PlainTextViewWidget.ui
    file_views/SearchBar.ui

    highlighting/HighlightingDialog.ui
    highlighting/ColorPicker.ui
    highlighting/FontPicker.ui

    filter/FilterDialog.ui
    filter/FileFilterWidget.ui

    columnize/ColumnizeDialog.ui
)

qt5_wrap_ui(Project_Sources
  ${Project_UIs}
)

set(Project_RESOURCES
    resources.qrc
)

# Translations
set( Project_TRANSLATIONS
    ${CMAKE_CURRENT_LIST_DIR}/translations/QTail_en.ts
    ${CMAKE_CURRENT_LIST_DIR}/translations/QTail_de.ts
)
option(WITH_CREATE_TRANSLATIONS "Create translations. Runs lupdate on existing .ts files" OFF)
if (WITH_CREATE_TRANSLATIONS)
    find_package(Qt5LinguistTools REQUIRED)
    qt5_create_translation(QM_FILES ${Project_SOURCES} ${Project_UIs} ${Project_TRANSLATIONS})
else()
    find_package(Qt5LinguistTools)
    if (Qt5LinguistTools_DIR)
        qt5_add_translation(QM_FILES ${Project_TRANSLATIONS})
    endif()
endif()

# Pack all .qm files into a .qrc resource file
set(TRANSLATIONS_QRC "${CMAKE_CURRENT_BINARY_DIR}/translation.qrc")
file(WRITE ${TRANSLATIONS_QRC} "<RCC>\n\t<qresource prefix=\"/translations\">")
foreach(QM_FILE ${QM_FILES})
    get_filename_component(QM_FILE_NAME ${QM_FILE} NAME)
    file(APPEND ${TRANSLATIONS_QRC} "\n\t\t<file alias=\"${QM_FILE_NAME}\">${QM_FILE_NAME}</file>")
endforeach()
file(APPEND ${TRANSLATIONS_QRC} "\n\t</qresource>\n</RCC>")
list(APPEND Project_RESOURCES ${TRANSLATIONS_QRC})

qt5_add_resources(Project_Sources
    ${Project_RESOURCES}
)

add_executable(${PROJECT_NAME} WIN32 ${Project_Sources} ${QM_FILES})

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
