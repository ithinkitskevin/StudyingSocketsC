#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
//This header contains function for converting network addresses

int main(int argc, char *argv[]){
  char *address;
  address = argv[1];

  int client_socket;
  client_socket = socket(AF_INET, SOCK_STREAM, 0);

  //Now we have to get the address and the port number
  struct sockaddr_in remote_address;
  remote_address.sin_family = AF_INET; //Family of the address what type of address we are
  remote_address.sin_port = htons(80); //port. 9002 i
  //converts string address and converts it through address structures
  inet_aton(address, &remote_address.sin_addr.s_addr);
  //first is the address, second is where to put it (which is at the remote_address)

  //Then just connect
  connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));

  char request[] = "GET / HTTP/1.1\r\n\r\n";//the / is indicating the general page, and \r\n\n is indicating that we're done
  char response[4096];

  send(client_socket,request, sizeof(request),0);

  //Now let's receive from the server
  recv(client_socket, &response, sizeof(response), 0);

  //Now we're going to print out what we got back from the server
  printf("Response From the Server: %s\n",response);

  close(client_socket);

  return 0;

}
