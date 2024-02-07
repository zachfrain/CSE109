#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include "pack109.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

std::vector<u8> readFile(string filename){
    FILE *fp;
    u8 temp;
    vec bytes;
    fp = fopen(filename.c_str(), "r");
    if(fp == NULL){
        perror("Client: Error opening file.\n");
        exit(1);
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

std::vector<u8> encrypt(std::vector<u8> target){ [source][0]
    vec newVec;
    u8 shift = 0x70;
    
    for(int i = 0; i < target.size(); i++){
        u8 temp = target[i];
        u8 changed = (temp ^ shift);
        newVec.push_back(changed);
    }
    return newVec;
}

int main(int argc, char *argv[])
{

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    struct File file;
    struct Request req;
    vec serialized; vec transferred;
    char *c1 = "--hostname";
    char *c2 = "--send";
    char *c3 = "--request";
    int intc1 = 0;
    int intc2 = 0;
    int intc3 = 0;
    int send_req;
    u8 buffer[256];
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], c1) == 0)
        {
            intc1++;
        }
        if (strcmp(argv[i], c2) == 0)
        {
            intc2++;
        }
        if (strcmp(argv[i], c3) == 0)
        {
            intc3++;
        }
    }
    if (argc != 5)
    {
        printf("Incorrect Usage.\n\nCorrect Usage:\n\tTo Send A File: './client --hostname address:port --send filename'\n\tTo Request A File: './client --hostname address:port --request filename'\n");
        exit(0);
    }
    else if (strcmp(argv[1], c1) != 0)
    {
        printf("Incorrect Usage.\n\nCorrect Usage:\n\tTo Send A File: './client --hostname address:port --send filename'\n\tTo Request A File: './client --hostname address:port --request filename'\n");
        exit(0);
    }
    else if (strcmp(argv[3], c2) == 0 && intc3 > 0)
    {
        printf("Incorrect Usage.\n\nCorrect Usage:\n\tTo Send A File: './client --hostname address:port --send filename'\n\tTo Request A File: './client --hostname address:port --request filename'\n");
        exit(0);
    }
    else if (strcmp(argv[3], c3) == 0 && intc2 > 0)
    {
        printf("Incorrect Usage.\n\nCorrect Usage:\n\tTo Send A File: './client --hostname address:port --send filename'\n\tTo Request A File: './client --hostname address:port --request filename'\n");
        exit(0);
    }
    else if (intc2 > 0 && intc3 > 0)
    {
        printf("Incorrect Usage.\n\nCorrect Usage:\n\tTo Send A File: './client --hostname address:port --send filename'\n\tTo Request A File: './client --hostname address:port --request filename'\n");
        exit(0);
    }

    if (intc2 > intc3) {
        send_req = 2;
    } else {
        send_req = 3;
    }

    if (send_req == 2) {
        file.name = argv[4];
        vec tempVec = readFile(file.name);
        file.bytes = tempVec;

        serialized = pack109::serialize(file);

        transferred = encrypt(serialized);
        
    } else if(send_req == 3){
        req.name = argv[4];

        serialized = pack109::serialize(req);
        

        transferred = encrypt(serialized);
        
    }

    portno = 5003;

    // Creating socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("Client: Error opening socket.\n");
        exit(1);
    }

    server = gethostbyname(argv[2]);

    if (server == NULL)
    {
        perror("Client: Error connecting to host\n");
        exit(0);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    int conn = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (conn < 0)
    {
        perror("Client: Error connecting to server.\n");
        exit(1);
    }

    bzero(buffer, 256);
    if(send_req == 2){
        buffer[0] = 's';
    } else {
        buffer[0] = 'r';
    }
    n = write(sockfd, buffer, 1);

    if(n < 0){
        perror("Client: Error writing to socket.\n");
        exit(1);
    }

    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if(n < 0){
        perror("Client: Error reading from socket.\n");
        exit(1);
    }

    bzero(buffer, 256);
    int i;
    for(i = 0; i < transferred.size(); i++){
        buffer[i] = transferred[i];
    }
    n = write(sockfd, buffer, i);
    if(n < 0){
        perror("Client: Error writing to socket.\n");
        exit(1);
    }

    n = read(sockfd, buffer, 255);
    if(n < 0){
        perror("Client: Error reading from socket.\n");
    }


    return 0;
}
    [0]: https://codeforwin.org/2018/05/10-cool-bitwise-operator-hacks-and-tricks.html
