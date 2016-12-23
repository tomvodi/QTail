project(ColumnizeLib CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories( ${CMAKE_CURRENT_LIST_DIR} )

find_package( Qt5Widgets REQUIRED )

set(Project_Sources
    ColumnGlobals.h
    ColumnizeDialog.cpp
    ColumnDefinitionDialog.cpp
    ColumnDefinitionInterface.cpp
    ColumnDefinitionFactory.cpp
    ColumnDefinitionDelegate.cpp

    app/AppColumnDefinitionFactory.cpp

    app/text/TextDefinition.cpp

    app/datetime/DateTimeDefinition.cpp
    app/datetime/DateTimeConfigWidget.cpp
    app/datetime/DateTimeHelpWidget.cpp

    app/selection/SelectionDefinition.cpp

    # .uis
    ColumnizeDialog.ui
    ColumnDefinitionDialog.ui

    app/datetime/DateTimeConfigWidget.ui
    app/datetime/DateTimeHelpWidget.ui
)

add_library(${PROJECT_NAME} STATIC ${Project_Sources})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
