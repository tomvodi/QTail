project(QTail CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package( Qt5Widgets REQUIRED )

set(Project_Sources
  main.cpp
  MainWindow.cpp
  FileListItemWidget.cpp
  PlainTextEdit.cpp
  AboutDialog.cpp

  tools/Settings.cpp
)

configure_file(${CMAKE_CURRENT_LIST_DIR}/../version.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/QTail_version.h)


qt5_wrap_ui(Project_Sources
    MainWindow.ui
    AboutDialog.ui
    FileListItemWidget.ui
)

qt5_add_resources(Project_Sources
    resources.qrc
)

add_executable(${PROJECT_NAME} ${Project_Sources})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)