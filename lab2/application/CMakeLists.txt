project(ads-lab2-app)

set(CMAKE_CXX_FLAGS)

add_executable(ads-lab2-app main.cpp)
target_link_libraries(ads-lab2-app PRIVATE ads-lab2-bst)
