find_package(Catch2 CONFIG REQUIRED)

set(CMAKE_CXX_FLAGS "-fprofile-instr-generate -fcoverage-mapping ")

add_executable(ads-lab3-tests test.cpp)
target_link_libraries(ads-lab3-tests PRIVATE Catch2::Catch2 ads-lab3-rbst)