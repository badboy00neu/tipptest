# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/tipptest_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/tipptest_autogen.dir/ParseCache.txt"
  "tipptest_autogen"
  )
endif()
