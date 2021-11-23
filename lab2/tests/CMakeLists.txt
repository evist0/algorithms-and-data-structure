find_package(Catch2 CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "-fprofile-instr-generate -fcoverage-mapping")

add_executable(ads-lab2-tests test.cpp)
target_link_libraries(ads-lab2-tests PRIVATE Catch2::Catch2 ads-lab2-bst)