#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include "pack109.hpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
std::vector<u8> decrypt(std::vector<u8> target){
    vec ret;
    u8 shift = 0x70;
    for(int i = 0; i < target.size(); i++){
        u8 holder = target[i];
        u8 temp = (holder ^ shift);
        ret.push_back(temp);
    }
    return ret;
}

std::vector<u8> readFile(string filename){
    FILE *fp;
    u8 temp;
    vec bytes;
    fp = fopen(filename.c_str(), "r");
    if(fp == NULL){
        perror("Client: Error opening file.\n");
        exit(1);
    } else {
        printf("Client: File opened successfully.\n");
    }

    for(int i = 0; temp != (u8)EOF; i++){
        temp = fgetc(fp);
        if(temp == (u8)EOF)
            break;
        bytes.push_back(temp);
    }
    fclose(fp);
    return bytes;
}

std::vector<u8> encrypt(std::vector<u8> target){
    vec newVec;
    u8 shift = 0x70;
    
    for(int i = 0; i < target.size(); i++){
        u8 temp = target[i];
        u8 changed = (temp ^ shift);
        newVec.push_back(changed); //https://codeforwin.org/2018/05/10-cool-bitwise-operator-hacks-and-tricks.html
    }
    return newVec;
}

int main(int argc, char *argv[])
{
    printf("Server: Starting.\n");

    int sockfd, newsockfd, portno, clilen;
    u8 buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    vec received; vec decrypted;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Checking for socket error
    if (sockfd < 0)
    {
        perror("Server: Error opening socket.");
        exit(1);
    }
    else
    {
        printf("Server: Socket creating successful.\n");
    }

    // Erasing 'serv_addr' bytes starting from the address of the serv_addr
    bzero((char *)&serv_addr, sizeof(serv_addr));

    portno = 5003;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Binding socket to port & checking for bind error
    if (::bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Server: Error binding socket.");
        exit(1);
    }
    else
    {
        printf("Server: Binding Successful.\n");
    }

    // Listening for connection
    printf("Server: Starting To Listen.\n");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /*
         Sources used up to this point (Q1 - Part 1):
             1) https://www.tutorialspoint.com/unix_sockets/socket_quick_guide.htm
             2) Prof. Montella's message in Slack (#general - Posted on 12:31PM Wednesday, May 4th)
    */

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
    if(newsockfd < 0){
        perror("Server: Error accepting connection.\n");
        exit(1);
    } else {
        printf("Server: Connection accepted successfully.\n");
    }

    /*
        Connection is now established
    */

   bzero(buffer, 256);
   n = read(newsockfd, buffer, 255);

   if(n < 0){
       perror("Server: Error reading from socket.\n");
       exit(1);
   } else {
       printf("Server: Success reading from socket.\n");
   }

   u8 send_req = buffer[0];

   n = write(newsockfd, "Ok, send over the serialized vector.", 36);
  
   if(n < 0){
       perror("Server: Error writing to socket.\n");
       exit(1);
   } else {
       printf("Server: Success writing to socket.\n");
   }
   
   n = read(newsockfd, buffer, 255);
   if(n < 0){
       perror("Server: Error reading from socket.\n");
       exit(1);
   } else {
       printf("Server: Success reading from socket.\n");
   }
   
   for(int i = 0; i < n; i++){
       received.push_back(buffer[i]);
   }
   pack109::printVec(received);
   decrypted = decrypt(received);
   pack109::printVec(decrypted);


   if(send_req == 's'){
       struct File deFile = pack109::deserialize_file(decrypted);

       string path = "received/" + deFile.name;
       ofstream MyFile(path);

       for(int j = 0; j < deFile.bytes.size(); j++){
           MyFile << deFile.bytes[j];
       }

       MyFile.close();

   } else {
       struct Request deRequest = pack109::deserialize_request(decrypted);

       string path = "received/" + deRequest.name;
       vec existCheck = readFile(path);

       struct File sendBack = {deRequest.name, existCheck};

       vec serializedReturn = pack109::serialize(sendBack);
       vec encryptedSerializedReturn = encrypt(serializedReturn);

       bzero(buffer, 256);
       int k;
       for(k = 0; k < encryptedSerializedReturn.size(); k++){
           buffer[k] = encryptedSerializedReturn[k];
       }
       n = write(sockfd, buffer, k);
   }

   return 0;
}