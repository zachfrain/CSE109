#include <stdexcept>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include"pack109.hpp"

template <class T>
int test(const char* label, T lhs, T rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs=%x\n", lhs);
    printf("  rhs=%x\n", rhs);
    exit(1);
  }
}

int testvec(const char* label, vec lhs, vec rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs="); pack109::printVec(lhs); printf("\n");
    printf("  rhs="); pack109::printVec(rhs); printf("\n");
    exit(1);
  }
}


int main() {

  // Test bool

  // True
  vec v1{0xa0};
  vec bytes1 = pack109::serialize(true);
  testvec("Test 1 - true ser", bytes1, v1);

  bool bool_true = pack109::deserialize_bool(bytes1);
  test("Test 2 - true de", bool_true, true);
 

  // False
  vec v2{0xa1};
  vec bytes2 = pack109::serialize(false);
  testvec("Test 3 - false ser", bytes2, v2);

  bool bool_false = pack109::deserialize_bool(bytes2); 
  test("Test 4 - false de", bool_false, false);

  // Test Integers

  // u8
  u8 item1 = 0x42;
  vec v3{0xa2, 0x42};
  vec bytes3 = pack109::serialize(item1);
  testvec("Test 5 - u8 ser", bytes3, v3);
  
  u8 int_u8 = pack109::deserialize_u8(bytes3);  
  test("Test 6 - u8 de", int_u8, item1);

  // u32
  u32 item2 = 0xABCDEF12;
  vec v4{0xa3, 0xAB, 0xCD, 0xEF, 0x12};
  vec bytes4 = pack109::serialize(item2);
  testvec("Test 7 - u32 ser", bytes4, v4);

  u32 int_u32 = pack109::deserialize_u32(bytes4);
  test("Test 8 - u32 de", int_u32, item2);
  // u64
  u64 item3 = 0xAABBCCDDEEFF1122;
  vec v5{0xa4, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22};
  vec bytes5 = pack109::serialize(item3);
  testvec("Test 9 - u64 ser", bytes5, v5);

  u64 int_u64 = pack109::deserialize_u64(bytes5);
  test("Test 10 - u64 de", int_u64, item3);
  // i8
  i8 item4 = 0x42;
  vec v6{0xa5, 0x42};
  vec bytes6 = pack109::serialize(item4);
  testvec("Test 11 - i8 ser", bytes6, v6);

  i8 int_i8 = pack109::deserialize_i8(bytes6);
  test("Test 12 - i8 de", int_i8, item4);
  // i32
  i32 item5 = 0xABCDEF12;
  vec v7{0xa6, 0xAB, 0xCD, 0xEF, 0x12};
  vec bytes7 = pack109::serialize(item5);
  testvec("Test 13 - i32 ser", bytes7, v7);

  i32 int_i32 = pack109::deserialize_i32(bytes7);
  test("Test 14 - i32 de", int_i32, item5);
  // i64
  i64 item6 = 0xAABBCCDDEEFF1122;
  vec v8{0xa7, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22};
  vec bytes8 = pack109::serialize(item6);
  testvec("Test 15 - i64 ser", bytes8, v8);

  i64 int_i64 = pack109::deserialize_i64(bytes8);
  test("Test 16 - i64 de", int_i64, item6);
  // Test Float
  
  // f32
  f32 item7 = 12.5;
  vec v9{0xa8, 0x41, 0x48, 0x00, 0x00};
  vec bytes9 = pack109::serialize(item7);
  testvec("Test 17 - f32 ser", bytes9, v9);

  // f64
  f64 item8 = 12.5;
  vec v10{0xa9, 0x40, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  vec bytes10 = pack109::serialize(item8);
  testvec("Test 18 - f64 ser", bytes10, v10);

  // Test Strings

  // s8
  string item9 = "Hello";
  vec v11{0xaa, 5,'H', 'e', 'l', 'l', 'o'};
  vec bytes11 = pack109::serialize(item9);
  testvec("Test 19 - s8 ser", bytes11, v11);

  // s16
  
  // Test Arrays

  // a8
std::vector<u8> u8vec = {0xAA, 0xBB, 0xCC, 0xDD};
vec u8vec2{0xac, 0x04, 0xa2, 0xAA, 0xa2, 0xBB, 0xa2, 0xCC, 0xa2, 0xDD};
vec u8vec3 = pack109::serialize(u8vec);
testvec("Test 20 - a8 ser (u8)", u8vec3, u8vec2);

std::vector<u64> u64vec = {0xAABBAABBAABBAABB , 0xAABBCCDDEEFF1122};
vec u64vec2{0xac, 0x02, 0xa4, 0xAA, 0xBB, 0xAA, 0xBB, 0xAA, 0xBB, 0xAA, 0xBB, 0xa4, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22};
vec u64vec3 = pack109::serialize(u64vec);
testvec("Test 21 - a8 ser (u64)", u64vec3, u64vec2);

std::vector<f64> f64vec = {12.5, 13.5, 14.5};
vec f64vec2{0xac, 0x03, 0xa9, 0x40, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa9, 0x40, 0x2B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa9, 0x40, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
vec f64vec3 = pack109::serialize(f64vec);
testvec("Test 22 - a8 ser (f64)", f64vec3, f64vec2);

std::vector<string> strvec = {"Hello", "Bye"};
vec strvec2{0xac, 0x02, 0xaa, 5, 'H', 'e', 'l', 'l', 'o', 0xaa, 3, 'B', 'y', 'e'};
vec strvec3 = pack109::serialize(strvec);
testvec("Test 23 - a8 ser (str)", strvec3, strvec2);
  // a16

  // Test Maps

  // m8

  // m16 

  return 0;
}