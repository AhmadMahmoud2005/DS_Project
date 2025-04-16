# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/DS_Project_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/DS_Project_autogen.dir/ParseCache.txt"
  "DS_Project_autogen"
  )
endif()
