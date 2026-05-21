cmake_minimum_required(VERSION 3.20)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SearchEngine
    main.cpp  
    indexer.cpp
    dirReader.cpp
    database.cpp
    ini.cpp
    thread_pool.cpp
    safe_queue.cpp
)
set(PostgreSQL_ADDITIONAL_VERSIONS "17")
add_subdirectory(C:/Users/Leamas/Desktop/cMake/libpqxx-7.10.0 libpqxx-build) 

target_include_directories(SearchEngine PRIVATE C:/Boost/include/boost-1_86)
target_link_directories(SearchEngine PRIVATE C:/Boost/lib)

find_package(Boost REQUIRED COMPONENTS system)
target_compile_features(SearchEngine PRIVATE cxx_std_17)

target_link_libraries(SearchEngine 
    pqxx 
    Boost::system
)


if(MSVC)
    add_compile_options("/utf-8")
    add_compile_options("/wd4828")
endif()
