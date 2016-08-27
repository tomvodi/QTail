project( TestCommon )

find_package( Qt5Widgets REQUIRED )

set( Project_Sources
  TestCommon.cpp
  MocFileView.cpp
  MocFileWatcher.cpp
  MocApplicationInterface.cpp
)

add_library( ${PROJECT_NAME} ${Project_Sources} )

target_link_libraries(${PROJECT_NAME} TailEngine)

qt5_use_modules( ${PROJECT_NAME} Widgets)
