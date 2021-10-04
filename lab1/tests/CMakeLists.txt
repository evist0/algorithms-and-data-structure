find_package(Catch2 CONFIG REQUIRED)

add_executable(ads-lab1-tests test.cpp)
target_link_libraries(ads-lab1-tests PRIVATE Catch2::Catch2 ads-lab1-container)