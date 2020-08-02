project(Kaleidoscope)
cmake_minimum_required(VERSION 3.16)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

file(GLOB_RECURSE Kaleidoscope_SRC src/*.cpp include/*.h)
add_library(Kaleidoscope STATIC ${Kaleidoscope_SRC})
target_include_directories(Kaleidoscope PUBLIC include/ ${LLVM_INCLUDE_DIRS})
target_link_libraries(Kaleidoscope ${LLVM_LIBRARIES})


set(main_project_dir "main/")
file(GLOB main_projects "${main_project_dir}/*.cpp")

foreach(main_project_path ${main_projects} )
    # I used a simple string replace, to cut off .cpp.
    get_filename_component(main_project_name ${main_project_path} NAME_WE )

    message("Main project path: ${main_project_path} and name: ${main_project_name}")
    set(${main_project_name} ON CACHE BOOL "")

    add_executable(${main_project_name} ${main_project_path})
    target_link_libraries(${main_project_name} Kaleidoscope)

endforeach()
