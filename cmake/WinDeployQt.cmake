# Call the windeployqt executable

find_package( Qt5Core REQUIRED )
set(QtDir ${Qt5Core_DIR}/../../..)
get_filename_component(QtDir ${QtDir} ABSOLUTE)
set(QtBinDir ${Qt5Core_DIR}/../../../bin)
get_filename_component(QtBinDir ${QtBinDir} ABSOLUTE)

function(windeployqt)
   set(options WITH_WITH_COMPILER_RUNTIME CREATE_INSTALLS)
   set(oneValueArgs TARGET OUTPUT_DIR)
   set(multiValieArgs )

   cmake_parse_arguments(_windeploy
      "${options}"
      "${oneValueArgs}"
      "${multiValieArgs}"
      ${ARGN}
      )

   if (NOT _windeploy_TARGET)
      message(FATAL_ERROR "No target specified")
   endif()

   if (_windeploy_OUTPUT_DIR)
      list(APPEND _ARGUMENTS "--dir" ${_windeploy_OUTPUT_DIR})
   endif()

   find_program(_windeploy_EXE windeployqt
      PATHS ${QtBinDir} $ENV{QTDIR}/bin
      )

   if (NOT _windeploy_EXE)
      message(FATAL_ERROR "Failed finding windeployqt.exe")
   endif()

   if (NOT _windeploy_WITH_COMPILER_RUNTIME)
      list(APPEND _ARGUMENTS "--no-compiler-runtime")
   endif()

   if (NOT _windeploy_CREATE_INSTALLS)
       message(STATUS "Normal deploy qt")
      add_custom_target(windeployqt_${_windeploy_TARGET} ALL ${_windeploy_EXE} ${_ARGUMENTS}
         $<TARGET_FILE:${_windeploy_TARGET}>
         DEPENDS ${_windeploy_TARGET}
         COMMENT "Install Qt dependencies for target")
   endif()

  if (_windeploy_CREATE_INSTALLS)
      message(STATUS "QtDir: " ${QtDir})
      list(APPEND _ARGUMENTS "--list" "source")
      get_property(target_location TARGET ${_windeploy_TARGET} PROPERTY LOCATION)
      execute_process( COMMAND ${_windeploy_EXE} ${_ARGUMENTS} ${target_location}
          OUTPUT_VARIABLE install_files_list
      )

      # make every line in command output to a list element
      string(REGEX REPLACE ";" "\\\\;" install_files_list "${install_files_list}")
      string(REGEX REPLACE "\n" ";" install_files_list "${install_files_list}")

      foreach(install_file_path ${install_files_list})
          # First make possible backslashes to forward slashes to have a path similar to
          # QtDir path
          get_filename_component( install_file_path ${install_file_path} ABSOLUTE)

          set(file_path ${install_file_path})

          # Now check, if the file is in the QtDir path.
          string(FIND ${file_path} ${QtDir} find_pos)
          if (find_pos EQUAL 0)
              # If the file is in the QtDir, remove the QtDir path and create install for the file
              # and keep its relative position in the QtDir
              string(REPLACE "${QtDir}/" "" file_path ${file_path})

              # If the file for deployment doesn't start with bin, prepend its path with bin
              string(FIND ${file_path} "bin/" find_pos)
              if (find_pos EQUAL -1)
                  set(file_path "bin/${file_path}")
              endif()

              # Get the relative path of the file for the install command
              get_filename_component(file_rel_path ${file_path} DIRECTORY)

              # Empty install destinations aren't allowed, so make it at least the install
              # directory itself with a dot
              if ("${file_rel_path}" STREQUAL "")
                  set(file_rel_path ".")
              endif()

#              message(STATUS "Install file " ${install_file_path} " to directory " ${file_rel_path})
              install(FILES ${install_file_path} DESTINATION ${file_rel_path})
          else()
              # If the file has not the path prefix, create install for the file in the
              # install root
#              message(STATUS "Install file " ${install_file_path} " to directory " ${_windeploy_OUTPUT_DIR})
              install(FILES ${file_path} DESTINATION bin)
          endif()
      endforeach()
  endif()
endfunction()
