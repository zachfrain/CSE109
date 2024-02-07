#include <vector>
#include <stdio.h>
#include "pack109.hpp"
#include <iostream>

using namespace std;

void pack109::printVec(vec &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}

// Boolean

vec pack109::serialize(bool item) {
  vec bytes;
  if (item == true) {
    bytes.push_back(PACK109_TRUE);
  } else {
    bytes.push_back(PACK109_FALSE);
  }
  return bytes;
}

bool pack109::deserialize_bool(vec bytes) {
  if (bytes.size() < 1) {
     throw;
  }

  if (bytes[0] == PACK109_TRUE) {
    return true;
  } else if (bytes[0] == PACK109_FALSE) {
    return false;
  } else {
    throw;
  }

}

// Integers

vec pack109::serialize(u8 item) {
  vec bytes;
  bytes.push_back(PACK109_U8);
  bytes.push_back(item);
  return bytes;
}

u8 pack109::deserialize_u8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_U8) {
    return bytes[1];
  } else {
    throw;
  }
}

//u32
vec pack109::serialize(u32 item){
  vec bytes;
  bytes.push_back(PACK109_U32);
  int i = (sizeof(u32) * 2) - 2;
  for(i; i >= 0; i-=2){
    int shift = (item >> i * 4);
    u8 byte = shift & 0x000000FF;
    bytes.push_back((u8)byte);
  }
  return bytes;
}

u32 pack109::deserialize_u32(vec bytes){
  if(bytes.size() < 5){
    throw;
  }
  u32 result = 0;
  if(bytes[0] == PACK109_U32){
    int j = (sizeof(u32) * 2) - 2;
    for(int i = 1; i <= sizeof(u32); i++){
      u32 shifted = (u32)bytes[i] << j * 4;
      result = result | shifted;
      j -= 2;
    }
    return result;
  } else {
    throw;
  }
}
//u64
vec pack109::serialize(u64 item){
  vec bytes;
  bytes.push_back(PACK109_U64);
  int i = (sizeof(u64)*2) - 2;
  for(i; i >= 0; i -= 2){
    int shift = (item >> i * 4);
    u8 byte = shift & 0x000000FF;
    bytes.push_back((u8)byte);
  }
  return bytes;
}

u64 pack109::deserialize_u64(vec bytes){
  if(bytes.size() < 9){
    throw;
  }
  u64 result = 0;
  if(bytes[0] == PACK109_U64){
    int j = (sizeof(u64)*2) - 2;
    for(int i = 1; i <= sizeof(u64); i++){
      u64 shifted = (u64)bytes[i] << j * 4;
      result = result | shifted;
      j -= 2;
    }
    return result;
  } else {
    throw;
  }
}
//i8
vec pack109::serialize(i8 item){
  vec bytes;
  bytes.push_back(PACK109_I8);
  bytes.push_back(item);
  return bytes;
}

i8 pack109::deserialize_i8(vec bytes){
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_I8) {
    return bytes[1];
  } else {
    throw;
  }
}
//i32
vec pack109::serialize(i32 item){
  vec bytes;
  bytes.push_back(PACK109_I32);
  int i = (sizeof(i32) * 2) - 2;
  for(i; i >= 0; i-=2){
    int shift = (item >> i * 4);
    i8 byte = shift & 0x000000FF;
    bytes.push_back((i8)byte);
  }
  return bytes;
}

i32 pack109::deserialize_i32(vec bytes){
  if(bytes.size() < 5){
    throw;
  }
  i32 result = 0;
  if(bytes[0] == PACK109_I32){
    int j = (sizeof(i32) * 2) - 2;
    for(int i = 1; i <= sizeof(i32); i++){
      i32 shifted = (i32)bytes[i] << j * 4;
      result = result | shifted;
      j -= 2;
    }
    return result;
  } else {
    throw;
  }
}
//i64
vec pack109::serialize(i64 item){
  vec bytes;
  bytes.push_back(PACK109_I64);
  int i = (sizeof(i64)*2) - 2;
  for(i; i >= 0; i -= 2){
    int shift = (item >> i * 4);
    i8 byte = shift & 0x000000FF;
    bytes.push_back((i8)byte);
  }
  return bytes;
}

i64 pack109::deserialize_i64(vec bytes){
  if(bytes.size() < 9){
    throw;
  }
  i64 result = 0;
  if(bytes[0] == PACK109_I64){
    int j = (sizeof(i64)*2) - 2;
    for(int i = 1; i <= sizeof(i64); i++){
      i64 shifted = (i64)bytes[i] << j * 4;
      result = result | shifted;
      j -= 2;
    }
    return result;
  } else {
    throw;
  }
}

// Floats
//f32
vec pack109::serialize(f32 item){
  vec bytes;
  bytes.push_back(PACK109_F32);
  u32* temp = (u32*)&item;
  int i = (sizeof(u32) * 2) - 2;
  for(i; i >= 0; i-=2){
    int shift = (*temp >> i * 4);
    u8 byte = shift & 0x000000FF;
    bytes.push_back((u8)byte);
  }
  return bytes;
}

f32 pack109::deserialize_f32(vec bytes){
  
}
//f64
vec pack109::serialize(f64 item){
  vec bytes;
  bytes.push_back(PACK109_F64);
  u64* temp = (u64*)&item;
  int i = (sizeof(u64) * 2) - 2;
  for(i; i >= 0; i-=2){
    int shift = (*temp >> i * 4);
    u8 byte = shift & 0x000000FF;
    bytes.push_back((u8)byte);
  }
  return bytes;
}

f64 pack109::deserialize_f64(vec bytes){

}

// Strings
vec pack109::serialize(string item){
  vec bytes;
  int item_length;
  if(item.size() > 0 && item.size() < (1 << 8) - 1){
    bytes.push_back(PACK109_S8);
  } else if(item.size() > 255 && item.size() < (1 << 16)-1){
    bytes.push_back(PACK109_S16);
  } else {
    throw;
  }
  if(item.size() > 0){
    item_length = item.size();
    u8 charInItem = (u8)(item_length);
    bytes.push_back(charInItem);
  } else {
    throw;
  }
  u8 bytes2[item_length];
  for(int i = 0; i < item_length; i++){
    bytes2[i] = (u8)(item.at(i));
    bytes.push_back(bytes2[i]);
  }
  return bytes;
}

string pack109::deserialize_string(vec bytes){
  
}

// Arrays
vec pack109::serialize(std::vector<u8> item){
  vec bytes;
  bytes.push_back(PACK109_A8);
  u8 item_size = item.size();
  bytes.push_back(item_size);
  for(int i = 0; i < item.size(); i++){
    bytes.push_back(PACK109_U8);
    bytes.push_back(item[i]);
  }
  return bytes;
}

vec pack109::serialize(std::vector<u64> item){
  vec bytes;
  bytes.push_back(PACK109_A8);
  u8 item_size = item.size();
  u64 temp;
  bytes.push_back(item_size);
  for(int i = 0; i < item.size(); i++){
    bytes.push_back(PACK109_U64);
    temp = item[i];
    int j = (sizeof(u64)*2) - 2;
      for(j; j >= 0; j -= 2){
        int shift = (temp >> j * 4);
        u8 byte = shift & 0x000000FF;
        bytes.push_back((u8)byte);
      }
  }
  return bytes;
}

vec pack109::serialize(std::vector<f64> item){
  vec bytes;
  bytes.push_back(PACK109_A8);
  u8 item_size = item.size();
  bytes.push_back(item_size);
  for(int i = 0; i < item.size(); i++){
    bytes.push_back(PACK109_F64);
    u64* temp = (u64*)&item[i];
    int j = (sizeof(u64) * 2) - 2;
    for(j; j >= 0; j-=2){
      int shift = (*temp >> j * 4);
      u8 byte = shift & 0x000000FF;
      bytes.push_back((u8)byte);
    }
  }
  return bytes;
}

vec pack109::serialize(std::vector<string> item){
  vec bytes;
  bytes.push_back(PACK109_A8);
  u8 item_size = item.size();
  bytes.push_back(item_size);
  string temp;
  for(int i = 0; i < item.size(); i++){
    bytes.push_back(PACK109_S8);
    temp = item[i];
    int str_length = temp.size();
    if(str_length > 0){
      u8 charInItem = (u8)(str_length);
      bytes.push_back(charInItem);
    } else {
      throw;
    }
      u8 bytes2[str_length];
      for(int j = 0; j < str_length; j++){
        bytes2[j] = (u8)(temp.at(j));
        bytes.push_back(bytes2[j]);
      }
  }
  return bytes;
  
}
//          deserialize
std::vector<u8> pack109::deserialize_vec_u8(vec bytes){

}

std::vector<u64> pack109::deserialize_vec_u64(vec bytes){

}

std::vector<f64> pack109::deserialize_vec_f64(vec bytes){

}

std::vector<string> pack109::deserialize_vec_string(vec bytes){

}

// Maps
vec pack109::serialize(struct Person item){

}

struct Person pack109::deserialize_person(vec bytes){

}