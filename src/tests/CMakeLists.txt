
set(NAME nlib-test)

add_executable(${NAME} main.cpp)

target_link_libraries(${NAME} nbase nmemory)
