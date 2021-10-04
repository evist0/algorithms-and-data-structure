project(ads-lab2-bst)

add_library(ads-lab2-bst INTERFACE)

target_include_directories(ads-lab2-bst INTERFACE include)
target_compile_features(ads-lab2-bst INTERFACE cxx_std_20)