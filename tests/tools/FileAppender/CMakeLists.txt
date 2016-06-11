project(FileAppender CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package( Qt5Widgets REQUIRED )

set(QTail_Source_Dir ${CMAKE_SOURCE_DIR}/src/gui)

include_directories( ${QTail_Source_Dir} )

set(Project_Sources
  main.cpp
  MainWindow.cpp

  views/FileListItemWidget.cpp
  views/FileConfigPage.cpp

  ${QTail_Source_Dir}/tools/Settings.cpp
)


qt5_wrap_ui(Project_Sources
    MainWindow.ui

    views/FileListItemWidget.ui
    views/FileConfigPage.ui
)

qt5_add_resources(Project_Sources
    ${QTail_Source_Dir}/resources.qrc
)

add_executable(${PROJECT_NAME} ${Project_Sources})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets TailEngine )

if (WIN32)
    include(WinDeployQt)
    windeployqt(TARGET ${PROJECT_NAME})
endif()
