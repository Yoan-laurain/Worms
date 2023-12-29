project (Spoon)

set(dir Sources)

set (SOURCE_FILES
	${dir}/snpch.h
	${dir}/snpch.cpp
)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "*.h" "*.cpp" "*.inl")

include_directories(
    ${dir}/Spoon
    ${dir}
)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

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
GroupSources(Sources)


add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_FILES})

find_package(Threads REQUIRED)
find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics )
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

if (MSVC)
    # Set Multi-threaded DLL flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    # target_compile_options(${PROJECT_NAME} PRIVATE /wd4244 /wd4251 /wd4311)
endif()

add_compile_definitions(SN_BUILD_DLL)

#ajouté une compilation definition DEBUG pour la configuration debug
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-graphics sfml-window
	    imgui::imgui
	    ImGui-SFML::ImGui-SFML
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})

set(TARGET_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/$<CONFIG>/${PROJECT_NAME}.dll)
set(TARGET_FILE_DIR ${CMAKE_BINARY_DIR}/WormsApp/$<CONFIG>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory  ${TARGET_FILE_DIR} COMMAND_EXPAND_LISTS )

message("Target file : ${TARGET_FILE}")
message("Target files dir : ${TARGET_FILE_DIR}")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy  ${TARGET_FILE}  ${TARGET_FILE_DIR} COMMAND_EXPAND_LISTS )
