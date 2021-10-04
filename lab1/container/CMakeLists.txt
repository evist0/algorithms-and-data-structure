project(ads-lab1-container)

add_library(ads-lab1-container INTERFACE)

target_include_directories(ads-lab1-container INTERFACE include)
target_compile_features(ads-lab1-container INTERFACE cxx_std_20)