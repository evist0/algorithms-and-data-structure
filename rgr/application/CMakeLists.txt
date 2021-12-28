project(ads-rgr-app)

set(CMAKE_CXX_FLAGS "")

add_executable(ads-rgr-app main.cpp)
target_link_libraries(ads-rgr-app PRIVATE ads-rgr-graph)
