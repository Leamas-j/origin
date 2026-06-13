cmake_minimum_required(VERSION 3.20)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PostgreSQL_ADDITIONAL_VERSIONS "17")
add_subdirectory(C:/Users/Leamas/Desktop/cMake/libpqxx-7.10.0 libpqxx-build) 

find_package(Boost REQUIRED COMPONENTS system)

set(COMMON_INCLUDE_DIR C:/Boost/include/boost-1_86)
set(COMMON_LINK_DIR C:/Boost/lib)
set(LINK_LIBRARIES pqxx Boost::system)
set(COMMON_SOURCES  Shared/ini_parser.cpp Shared/database.cpp Shared/string_modify.cpp)

add_executable(Indexer
    ${COMMON_SOURCES}
    Indexer/main.cpp  
    Indexer/indexer.cpp
    Indexer/dirReader.cpp
    Indexer/thread_pool.cpp
    Indexer/safe_queue.cpp)

target_include_directories(Indexer PRIVATE ${COMMON_INCLUDE_DIR})
target_link_directories(Indexer PRIVATE ${COMMON_LINK_DIR})
target_link_libraries(Indexer PRIVATE ${LINK_LIBRARIES}) 
target_compile_features(Indexer PRIVATE cxx_std_17)

add_executable(Searcher
    ${COMMON_SOURCES}
    Searcher/main.cpp    
)

target_include_directories(Searcher PRIVATE ${COMMON_INCLUDE_DIR})
target_link_directories(Searcher PRIVATE ${COMMON_LINK_DIR})
target_link_libraries(Searcher PRIVATE ${LINK_LIBRARIES})
target_compile_features(Searcher PRIVATE cxx_std_17)

if(MSVC)
    add_compile_options("/utf-8")
    add_compile_options("/wd4828")
endif()
