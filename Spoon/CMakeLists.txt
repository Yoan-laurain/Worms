project (Spoon)

set (SOURCE_FILES 
	src/snpch.h
	src/snpch.cpp
)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "*.h" "*.cpp")

include_directories(src)

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
GroupSources(src)


add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_FILES})

find_package(Threads REQUIRED)
find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics )
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

if (MSVC)
    # Set Multi-threaded DLL flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
endif()

add_compile_definitions(SN_BUILD_DLL)

#ajouté une compilation definition DEBUG pour la configuration debug
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-graphics sfml-window
	    imgui::imgui
	    ImGui-SFML::ImGui-SFML
        Threads::Threads
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})


