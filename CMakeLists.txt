# CMakeList.txt: projekt CMake dla elementu RoboBeat, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("RoboBeat")

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (RoboBeat "main_file.cpp" "Collisions.cpp" "Collisions.h" "constants.h" "Drawing.cpp" "Drawing.h" "Entity.cpp" "Entity.h" "lodepng.cpp" "lodepng.h" "Logic.cpp" "Logic.h" "Physics.cpp" "Physics.h" "Pipeline.cpp" "Pipeline.h" "shaderprogram.cpp" "shaderprogram.h" "TextureLoader.h")

add_subdirectory(glfw)
add_subdirectory(glew)
add_subdirectory(glm)

target_link_libraries(RoboBeat glm::glm)

target_include_directories(RoboBeat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories(RoboBeat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)

target_link_libraries(RoboBeat glm::glm glfw libglew_static)

add_custom_command(TARGET RoboBeat PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources/
                       $<TARGET_FILE_DIR:RoboBeat>)
#target_include_directories(RoboBeat glm)

#include_directories(${PATH_GLM})
# target_include_directories(RoboBeat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glm/glm)


# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
