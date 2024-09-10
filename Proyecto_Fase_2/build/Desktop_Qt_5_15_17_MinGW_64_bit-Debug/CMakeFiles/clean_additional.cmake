# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Proyecto_Fase_2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Proyecto_Fase_2_autogen.dir\\ParseCache.txt"
  "Proyecto_Fase_2_autogen"
  )
endif()
