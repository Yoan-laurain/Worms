project(WormsApp)

set(DLL_NAME "Spoon")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

file(GLOB_RECURSE SOURCES "*.h" "*.cpp")

macro(GroupSources curdir)
    file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
    ${PROJECT_SOURCE_DIR}/${curdir}/* ${PROJECT_SOURCE_DIR}/${curdir}/${curdir}/*)

    foreach(child ${children})

        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${curdir})
            source_group(${groupname} FILES
            ${PROJECT_SOURCE_DIR}/${curdir}/${child})
        endif()
    endforeach()
endmacro()

# Execute the macro
GroupSources(src)

include_directories(${CMAKE_SOURCE_DIR}/${DLL_NAME}/src)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)

find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)

target_link_libraries(${PROJECT_NAME} PRIVATE ${DLL_NAME} sfml-system sfml-graphics sfml-window  )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

set(TARGET_FILE ${CMAKE_BINARY_DIR}/${DLL_NAME}/$<CONFIG>/${DLL_NAME}.dll)
set(TARGET_FILE_DIR ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/$<CONFIG>)

message("Target file : ${TARGET_FILE}")
message("Target files dir : ${TARGET_FILE_DIR}")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy  ${TARGET_FILE}  ${TARGET_FILE_DIR} COMMAND_EXPAND_LISTS )