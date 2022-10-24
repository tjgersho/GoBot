cmake_minimum_required(VERSION 3.12)

#set(CMAKE_GENERATOR_PLATFORM x64)
#set(CMAKE_GENERATOR_PLATFORM win32)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(UNIX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(WIN32)
    message("This is a Windows System")
endif()
# or use MATCHES to see if actual system name 
# Darwin is Apple's system name
if(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(${CMAKE_SYSTEM_NAME} MATCHES Windows)
    message("This is a Windows System")
endif()



set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

project(GenAI VERSION 0.1.0)

include(${PROJECT_SOURCE_DIR}/${CMAKE_MODULE_PATH}/PrintVariables.cmake)

print_variables()
 
include(CTest)
enable_testing()


#GET ALL INCLUDE SUBDIRECTORIES>>// ANd include them:)
file(GLOB DIR_GLOB LIST_DIRECTORIES true "includes/*")
message(STATUS "################################")
foreach(dir ${DIR_GLOB})
    IF(IS_DIRECTORY ${dir})
        message(STATUS ${dir})
        include_directories(${dir})
    ELSE()
        CONTINUE()
    ENDIF()
endforeach()
include_directories(includes)


message(STATUS "-------------------------")
 

message(STATUS "ROOT DIRECTORY")

add_subdirectory(sdl_gfx)

message(STATUS "BACK TO ROOT")
 
 
set(SDL2_INCLUDE_DIR "D:/SDL2-2.0.22/include")
set(SDL2_LIB_DIR "D:/SDL2-2.0.22/lib/x64")

include_directories(${SDL2_INCLUDE_DIR})


link_directories(${SDL2_LIB_DIR})
 
 
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        ON)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost REQUIRED COMPONENTS date_time filesystem system locale serialization)
include_directories(${Boost_INCLUDE_DIRS})
 

message(STATUS "Boost Libs DIR: ${Boost_LIBRARIES}")
 
 
file(GLOB_RECURSE  SOURCES "src/*.cpp" )

file(GLOB_RECURSE  SDL_GFX_SOURCES "sdl_gfx/*.c" )

message(STATUS "SRC Sources: ${SOURCES}")
message(STATUS "SDL_GFX Sources: ${SDL_GFX_SOURCES}")

message(STATUS )

add_executable(${PROJECT_NAME} ${SOURCES} ${SDL_GFX_SOURCES})
 
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_Image SDL2_ttf ${Boost_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

file(COPY "www" DESTINATION "Debug/")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
