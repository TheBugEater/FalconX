file(GLOB_RECURSE  source_files "../FalconX/Source/*.cpp")

idf_component_register(
        SRCS ${source_files} "FalconX.cpp"
        INCLUDE_DIRS ".")
