project( TestCommon )

find_package( Qt5Core REQUIRED )

set( Project_Sources
  TestCommon.cpp
  MocFileView.cpp
  MocFileWatcher.cpp
)

add_library( ${PROJECT_NAME} ${Project_Sources} )

qt5_use_modules( ${PROJECT_NAME} Core )
