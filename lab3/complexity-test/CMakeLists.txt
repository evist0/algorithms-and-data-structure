project(ads-lab3-complexity-test)

set(CMAKE_CXX_FLAGS )

add_executable(ads-lab3-complexity-test main.cpp)
target_link_libraries(ads-lab3-complexity-test PRIVATE ads-lab3-rbst)
target_link_libraries(ads-lab3-complexity-test PRIVATE ads-lab2-bst)
