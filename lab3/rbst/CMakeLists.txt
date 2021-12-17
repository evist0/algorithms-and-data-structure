project(ads-lab3-rbst)

add_library(ads-lab3-rbst INTERFACE)

target_link_libraries(ads-lab3-rbst INTERFACE ads-lab2-bst)

target_include_directories(ads-lab3-rbst INTERFACE include)
target_compile_features(ads-lab3-rbst INTERFACE cxx_std_20)