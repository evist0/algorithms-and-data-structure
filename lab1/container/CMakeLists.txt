project(ads-lab1-container)

add_library(ads-lab1-container
        include/container.hpp
        )

set_target_properties(ads-lab1-container PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(ads-lab1-container PUBLIC include)

target_compile_features(ads-lab1-container PUBLIC cxx_std_20)