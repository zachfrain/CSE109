#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "pack109.hpp"
#include <iostream>

using std::begin, std::end;

void pack109::printVec(vec &bytes){
    printf("[ ");
    for(int i = 0; i < bytes.size(); i++){
        printf("%x ", bytes[i]);
    }
    printf("]\n");
}

vec slice(vec& bytes, int vbegin, int vend){
    auto start = bytes.begin() + vbegin;
    auto end = bytes.begin() + vend + 1;
    vec result(vend - vbegin + 1);
    copy(start, end, result.begin());
    return result;
}

vec pack109::serialize(u8 item){
    vec bytes;
    bytes.push_back(PACK109_U8);
    bytes.push_back(item);
    return bytes;
}

u8 pack109::deserialize_u8(vec bytes){
    if(bytes.size() < 2){
        throw;
    }
    if(bytes[0] == PACK109_U8){
        return bytes[1];
    } else {
        throw;
    }
}

vec pack109::serialize(string item){
    vec bytes;
    if(item.size() < 256){
        bytes.push_back(PACK109_S8);
        bytes.push_back((u8)item.size());
        for(int i = 0; i < item.size(); i++){
            bytes.push_back(item[i]);
        }
    } else if(item.size() < 65536){
        bytes.push_back(PACK109_S16);
        u32 string_length = (u32)item.size();
        bytes.push_back((u8)(string_length >> 8));
        bytes.push_back((u8)(string_length));
        for(int i = 0; i < item.size(); i++){
            bytes.push_back((u8)item[i]);
        }
    } else {
        throw;
    }
    return bytes;
}

string pack109::deserialize_string(vec bytes) {
  if(bytes.size() < 3) {
    throw;
  }
  string deserialized_string = "";
  if(bytes[0] == PACK109_S8) {
    int string_length = bytes[1];
    for(int i = 2; i < (string_length + 2); i++) {
      deserialized_string += bytes[i];
    }
  }
  else if(bytes[0]==PACK109_S16) {
    int string_length = (bytes[1]<<8) | bytes[2];
    for(int i = 3; i < (string_length + 3); i++) {
      deserialized_string += bytes[i];
    }
  }
  return deserialized_string;
}

vec pack109::serialize(std::vector<u8> item) {
  vec bytes;
  if (item.size() < 256) {
    bytes.push_back(PACK109_A8);
    u8 size = (u8)item.size();
    bytes.push_back(size);
    for (int i = 0; i < item.size(); i++) {
      vec temp = serialize(item[i]);
      for (int j = 0; j < temp.size(); j++) {
        bytes.push_back(temp[j]);
      }
    }
  } else if (item.size() < 65536) {
    bytes.push_back(PACK109_A16);
    u32 item_length = (u32)item.size();
    bytes.push_back((u8)(item_length >> 8));
    bytes.push_back((u8)(item_length));
    for (int i = 0; i < item.size(); i++) {
      vec elem = serialize(item[i]);
      bytes.insert(end(bytes), begin(elem), end(elem));
    }
  } else {
    throw;
  }
  return bytes;
}

std::vector<u8> pack109::deserialize_vec_u8(vec bytes) {
  if(bytes.size() < 3) {
    throw;
  }
  int el_size = 2;
  std::vector<u8> result;
  if(bytes[0] == PACK109_A8) {
    int size = el_size * bytes[1];
    for (int i = 2; i < (size + 2); i += el_size) {
      vec sub_vec = slice(bytes, i, i + el_size);
      u64 element = deserialize_u8(sub_vec);
      result.push_back(element);
    }
  } else if(bytes[0] == PACK109_A16) {
    int size = el_size * (((int)bytes[1])<<8 | (int)bytes[2]);
    for(int i = 2; i < (size + 2); i += el_size) {
      vec sub_vec = slice(bytes, i + 1, i + el_size);
      u64 element = deserialize_u8(sub_vec);
      result.push_back(element);
    }
  }
  return result;
}

vec pack109::serialize(struct File item){ 
    vec bytes;
    bytes.push_back(PACK109_M8);
    bytes.push_back(0x1);

    vec file = serialize((string)"File");
    bytes.insert(end(bytes), begin(file), end(file));

    bytes.push_back(PACK109_M8);
    bytes.push_back(0x2);

    vec namek = serialize((string)"name");
    bytes.insert(end(bytes), begin(namek), end(namek));

    vec namev = serialize(item.name);
    bytes.insert(end(bytes), begin(namev), end(namev));

    vec bytesk = serialize((string)"bytes");
    bytes.insert(end(bytes), begin(bytesk), end(bytesk));

    vec bytesv = serialize(item.bytes);
    bytes.insert(end(bytes), begin(bytesv), end(bytesv));

    return bytes;
}

struct File pack109::deserialize_file(vec bytes){ 
   if(bytes.size() < 10)
        throw;
    
    vec file_slice = slice(bytes, 2, 7);
    string file_string = deserialize_string(file_slice);
    if(file_string != (string)"File")
        throw;

    u8 name_length = bytes[17];
    u8 start_name = 16;
    u8 end_name = start_name + name_length + 1;
    vec namev = slice(bytes, start_name, end_name);
    string name = deserialize_string(namev);

    u8 start_bytes = end_name + 8;
    u8 end_bytes = bytes.size();
    vec bytesv = slice(bytes, start_bytes, end_bytes);
    vec file_bytes = deserialize_vec_u8(bytesv);

    struct File deserialized_file = {name, file_bytes};

    return deserialized_file;
}


vec pack109::serialize(struct Request item){ 
    vec bytes;
    bytes.push_back(PACK109_M8);
    bytes.push_back(0x1);

    vec req = serialize((string)"Request");
    bytes.insert(end(bytes), begin(req), end(req));

    bytes.push_back(PACK109_M8);
    bytes.push_back(0x1);

    vec namek = serialize((string)"name");
    bytes.insert(end(bytes), begin(namek), end(namek));

    vec namev = serialize(item.name);
    bytes.insert(end(bytes), begin(namev), end(namev));

    return bytes;
}

struct Request pack109::deserialize_request(vec bytes){
    vec request_slice = slice(bytes, 2, 10);
    string request_string = deserialize_string(request_slice);
    if(request_string != (string)"Request")
      throw;

    vec request_na = slice(bytes, 13, 18);
    string request_name = deserialize_string(request_na);
    if(request_name != (string)"name")
      throw;

    u8 filename_length = bytes[20];
    u8 start_filename = 19;
    u8 end_filename = start_filename + filename_length + 1;
    vec bytes_filename = slice(bytes, start_filename, end_filename);
    string filename = deserialize_string(bytes_filename);

    struct Request deserialized_request = {filename};

    return deserialized_request;
}