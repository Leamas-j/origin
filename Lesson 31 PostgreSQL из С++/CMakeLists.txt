cmake_minimum_required(VERSION 3.20)
project(MyProject1)
add_executable(MyProject1 main.cpp)
set(PostgreSQL_ADDITIONAL_VERSIONS "17")
add_subdirectory(C:/Users/Leamas/Desktop/cMake/libpqxx-7.10.0 libpqxx-build) # ������� ���� � libpq++
target_compile_features(MyProject1 PRIVATE cxx_std_17) # �������� C++17
target_link_libraries(MyProject1 pqxx) # ��������� libpq++ � �������
if(MSVC)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()