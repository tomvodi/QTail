project(TailEngine CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )

set(Project_Sources
  FileWatcher.cpp
  TailEngine.cpp
  FileReadLogic.cpp
  HighlightingRule.cpp
  TextViewSettings.cpp
  FilterRule.cpp
  FilterGroup.cpp

  FileViewInterface.cpp
  FileWatcherInterface.cpp
  ApplicationInterface.cpp

  ColumnConfiguration.cpp
  DateTimeConfigurationHelper.cpp
  TextConfigurationHelper.cpp
  SelectionConfigurationHelper.cpp
  ColumnConfigurationHelper.cpp

  include/FileViewInterface.h
  include/FileWatcherInterface.h
  include/HighlightingRule.h
  include/FilterRule.h
  include/FilterGroup.h
  include/ApplicationInterface.h

  include/columnize/columnize_globals.h
  include/columnize/ColumnConfiguration.h
  include/columnize/DateTimeConfigurationHelper.h
  include/columnize/TextConfigurationHelper.h
  include/columnize/SelectionConfigurationHelper.h
  include/columnize/ColumnConfigurationHelper.h
)

add_library(${PROJECT_NAME} STATIC ${Project_Sources})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui)
