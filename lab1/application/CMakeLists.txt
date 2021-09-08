project(ads-lab1-app)
add_executable(ads-lab1-app main.cpp)
target_link_libraries(ads-lab1-app PUBLIC ads-lab1-container)
target_include_directories(ads-lab1-app PRIVATE include)