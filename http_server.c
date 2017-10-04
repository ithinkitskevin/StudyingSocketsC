#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(){
  FILE *html_data;

  html_data = fopen("index.html","r");
  //first parameter is the html, and the second parameter is what we do with the html

  char response_data[1024];
  fgets(response_data,1024,html_data);
  //Your basic fgets function, that gets the char[],how much data, and what file

  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
  strcat(http_header,response_data);

  //Now it's your basic TCP client/server
  int server_socket;
  /*
  Again, AF_INET is the type of address your socket communicates with (family)
  SOCK_STREAM is two way connection, connection-based byte stream
    -This is for TCP, you'll need SOCK_DGRAM for UDP
  */
  server_socket = socket(AF_INET,SOCK_STREAM,0);

  //Now we're defining the address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8001);
  server_address.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY is any address

  //Now time to bind it (bind port and ip, and I guess the family, to socket).
  bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  //Now let's just listen/
  listen(server_socket, 5);

  //Now to accept
  int client_socket;
  //We now need make this go into a forever while loop, so that we can keep serving and getting request
  while(1){
    client_socket = accept(server_socket,NULL,NULL);
    //then we're going to send the http stuff
    send(client_socket, http_header, sizeof(http_header),0);
    close(client_socket);
  }

  return 0;
}
