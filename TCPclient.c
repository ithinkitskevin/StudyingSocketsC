//So a socket is an endpoint of a two way communications link between two programs running on a network
//  +--> The socket will be bound to a port number so that TCP layer can identify the application  data is getting sent to

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

//Like the file name, this is the client TCP. So the workflow will be a little like this
/*
socket() -> connect() -> recv()
socket will be created
connect will connect the socket
recv will retrieve any data
*/

int main(){
  //This variable will contain information about the network socket, hence called network_socket
  int network_socket;
  //first parameter is the domain of the socket, since it's the internet, it'll be AF_INET
  //Second parameter is the type of the socket, which is TCP (instead of datagram, UDP)
  //Third parameter is the protocol, it's zero sicne we're already calling on TCP, so it's default
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  //Now we have to get the address and the port number
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET; //Family of the address what type of address we are
  server_address.sin_port = htons(9002); //port. 9002 is a number that is highly unlikely for another port to have
  //htons is host to online network short
  server_address.sin_addr.s_addr = INADDR_ANY; //sin_addr is a struct itself, and we're trying to get the Actual Address. trying to connect to 0.0.0

  //Now that we're done with the socket, we nw have to connect the socket
  int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
  //Also, we can get the connect variable to do error handling.

  //So now let's check for errors
  if(connection_status == -1){
    printf("\nThere was an error making a connection to the remote socket\n");
  }

  //Now that we're done with connect, we're doing recv
  //We'll need a string to hold the server response
  char server_response[256];
  recv(network_socket, &server_response, sizeof(server_response), 0);
  //First parameter is, like connect, socket
  //Second and third parameter is for the server response.
  //Fourth parameter is a flagparameter, but leaving it since we're not doing anything fancy.

  //Now let's print out the data we get back
  printf("Server_response: %s\n",server_response);

  //now let's close the socket.
  close(network_socket);

  //That's it, this is a basic TCP client. To test it, we need to make a TCP server and test it out there.

  return 0;
}
