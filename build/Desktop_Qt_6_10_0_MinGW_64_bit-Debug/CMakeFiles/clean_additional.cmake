# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Library_Management_And_Routing_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Library_Management_And_Routing_autogen.dir\\ParseCache.txt"
  "Library_Management_And_Routing_autogen"
  )
endif()
