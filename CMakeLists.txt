cmake_minimum_required (VERSION 3.10)

# Activez Rechargement � chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT 
      "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(PROJECT_NAME "WormsApp")

project(${PROJECT_NAME})
add_subdirectory(Spoon)
add_subdirectory(${PROJECT_NAME})


include("${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")