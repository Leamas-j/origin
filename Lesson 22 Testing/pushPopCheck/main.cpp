#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include "my_list.h"

List list;
TEST_CASE("test list", "[list]") {
  SECTION("PushBack") {
    CHECK(list.Empty() == true);
    list.PushBack(5);
    CHECK(list.Size() == 1);
  }  
  SECTION("PushFront") {
    list.PushFront(1);
    CHECK(list.Size() == 2);
  }
   
  SECTION("PopBack"){ 
    list.Clear();
    CHECK_THROWS(list.PopBack());
  } 
  SECTION("PopFront") {
    CHECK_THROWS(list.PopFront());
  }
}