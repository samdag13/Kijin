add_executable(main_example main_example.cpp)
target_link_libraries(main_example ${PROJECT_NAME})

add_executable(basic_window window_example.cpp)
target_link_libraries(basic_window  ${PROJECT_NAME})