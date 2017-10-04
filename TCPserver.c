#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

/*
server workflow

socket() -> Bind() -> listen() -> send()

*/

int main(){
  //create a string that we're going to send to all clients
  char server_message[256]= "Welcome to the server!";

  //All these will be just like the TCP client
  //Now we're creating the server_socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  //Define the server address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY;

  //Now that we're done with creating a socket, we'll have to bind it
  bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address));
  //Now our socket is bind to the IP and port

  //Let's start listening for connection
  listen(server_socket, 5);
  //second parameter is how many connectsions can be waiting (backlog). So just make it greater than 1.

  //Now let's start accepting
  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);
  //second&third parameter is struct and size.

  //Now we can send stuff
  send(client_socket, server_message, sizeof(server_message), 0);

  close(server_socket);
  return 0;
}

/*
Now that we have finished both C program, we can now send basic information through TCP protocol between two sockets.
So now let's try and make this code a little bit more complicated.
*/
