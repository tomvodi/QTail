include_directories(
   ${source_dir}/gui/file_views
   ${source_dir}/gui
)

add_subdirectory( MainWindow )
add_subdirectory( PreferencesDialog )
add_subdirectory( file_views )
add_subdirectory( filter )
add_subdirectory( highlighting )
add_subdirectory( tools )
add_subdirectory( columnize )
