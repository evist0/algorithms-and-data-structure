project(ads-rgr-graph)

add_library(ads-rgr-graph INTERFACE)

target_include_directories(ads-rgr-graph INTERFACE include)
target_compile_features(ads-rgr-graph INTERFACE cxx_std_20)