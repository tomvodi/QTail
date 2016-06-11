# Call the windeployqt executable

find_package( Qt5Core REQUIRED )
set(QtBinDir ${Qt5Core_DIR}/../../../bin)
get_filename_component(QtBinDir ${QtBinDir} ABSOLUTE)

function(windeployqt)
   set(options COMPILER_RUNTIME)
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

   add_custom_target(windeployqt_${_windeploy_TARGET} ALL ${_windeploy_EXE} ${_ARGUMENTS}
      $<TARGET_FILE:${_windeploy_TARGET}>
      DEPENDS ${_windeploy_TARGET}
      COMMENT "Install Qt dependencies for target")
endfunction()
