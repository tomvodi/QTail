project(QTail CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package( Qt5Widgets REQUIRED )

set(Project_Sources
  main.cpp
  gui/MainWindow.cpp
  gui/FileListItemWidget.cpp
  gui/PlainTextEdit.cpp

  data/FileWatcher.cpp

  tools/Settings.cpp
)

qt5_wrap_ui(Project_Sources
    gui/MainWindow.ui
    gui/FileListItemWidget.ui
)

qt5_add_resources(Project_Sources
    gui/resources.qrc
)

add_executable(${PROJECT_NAME} ${Project_Sources})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
