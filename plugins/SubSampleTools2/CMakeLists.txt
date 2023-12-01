# CloudCompare example for standard plugins

# REPLACE ALL 'SubSampleTools2' OCCURENCES BY YOUR PLUGIN NAME
# AND ADAPT THE CODE BELOW TO YOUR OWN NEEDS!

# Add an option to CMake to control whether we build this plugin or not
option( PLUGIN_SubSampleTools2 "Install SubSampleTools2" ON )

if ( PLUGIN_SubSampleTools2 )
	project( SubSampleTools2 )
	 
	AddPlugin( NAME ${PROJECT_NAME} )
		
	add_subdirectory( include )
	add_subdirectory( src )
	
	# set dependencies to necessary libraries
	# target_link_libraries( ${PROJECT_NAME} LIB1 )
endif()
