project(ads-lab2-complexity-test)

set(CMAKE_CXX_FLAGS "-EHsc")

add_executable(ads-lab2-complexity-test main.cpp)
target_link_libraries(ads-lab2-complexity-test PRIVATE ads-lab2-bst)
