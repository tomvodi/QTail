project(TailEngine CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package( Qt5Core REQUIRED )

set(Project_Sources
  FileWatcher.cpp
  TailEngine.cpp
  FileReadLogic.cpp

  FileViewInterface.cpp
  FileWatcherInterface.cpp

  include/FileViewInterface.h
  include/FileWatcherInterface.h
)

add_library(${PROJECT_NAME} STATIC ${Project_Sources})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
