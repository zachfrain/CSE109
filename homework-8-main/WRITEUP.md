Write Up

In a file called WRITEUP.md, provide a detailed account of how your client was constructed. First and foremost, tell me how to build it. What steps do I need to take to run it? Then, tell me how your program works. Go through the entire program and tell me what everything does. Explain your design decisions. Explain any code that is not straightforward. Note: If you would rather record a video walkthrough of your code, you can do this as well. Upload the video to your repository or google drive and add a link here (make sure to grant me viewing permissions).


Creating the client.cpp class was the easier part of this process. The client program starts with validating the input coming from the user. My program checks if there is a '--hostname' flag to start the program call, checks if there is either a '--send' or '--request' following the hostname. If the program call was invalid, the program will exit and display the correct usage. Once the program call is validated, the arguments will be sorted and stored. If the call was to send, my program will serialize the File struct, and if the call was to request my program will serialize the request struct. Additionally, I created a char to store whether the call was a send or request, that I will use later in my program. Once the program call is validated, the file or request struct will be serialized then encrypted. Then, I create a socket, get the host from argv, and connect the socket to the server. After each step, I checked for errors in the connection.

As for the server.cpp class, there isn't as much to do before the connection is established. I started the program by declaring various variables that I will use, and then created my socket. After checking for the socket creating erorr, I binded the socket to the server, checked for the error, then began listening. After the listening, I accepted the connection from the client, and the conversation between the client and server began.

Once the connection was established, the first thing that I did was send the character I declared for the send or request to the server, in order to make things easier for the deserialization. I wrote the character to the buffer, and the server read the buffer. Next, I transferred the serialized & encrypted vector from the client.cpp class to the buffer. The server.cpp class read the vector and stored it in it's own vector. Then, depending on the char symbolizing send or request, the vector sent over will be decrypted & deserialized. Once the struct is deserialized and back to original form, there are two things that can happen.

1) If the call was to send a file, the File struct would be transformed into an actual file and stored in a folder named 'received/'

2) If the call was to request a file, the Request struct would be accessed and the filename would be searched for in the received folder. If the file doesn't exist, nothing will happen, but if it does, the file requested will be turned into a File struct, serialized and decrypted then sent to the client.

In order to build my program, I made a Makefile. The Makefile creates an object file for the server and client classes. I created a library using the lib.cpp class and pack109.hpp header and named is libpack109.a. Then, I created executables of server and client which included that library. To run my program, you would need two command prompt windows open.

1) The first cmd window will be used to run the server. The command needed in order to run the server is:

./build/bin/release/server

Once that is called, the server class will begin and start listening for a connection from the client.

2) The second cmd window will be used to run the client. 
The command needed in order to run the command is:

./build/bin/release/client --hostname 'YOUR_ADDRESS' (--send / --request) 'FILENAME'

Once that command is called with the server listening, the two will connect and the communication between the client and server will begin.