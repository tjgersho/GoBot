cmake_minimum_required(VERSION 3.12)

#set(CMAKE_GENERATOR_PLATFORM x64)
#set(CMAKE_GENERATOR_PLATFORM win32)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GenAI VERSION 0.1.0)

include(PrintVariables.cmake)
print_variables()

include(CTest)
enable_testing()

include_directories("includes")
 
set(SDL2_INCLUDE_DIR "D:/SDL2-2.0.22/include")
set(SDL2_LIB_DIR "D:/SDL2-2.0.22/lib/x64")

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})


file(GLOB  SOURCES "src/*.cpp" )

add_executable(${PROJECT_NAME} ${SOURCES})
 
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_Image SDL2_ttf)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
