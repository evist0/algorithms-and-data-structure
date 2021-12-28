project(ads-lab3-app)

set(CMAKE_CXX_FLAGS )

add_executable(ads-lab3-app main.cpp)
target_link_libraries(ads-lab3-app PRIVATE ads-lab3-rbst)
