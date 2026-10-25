// INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


// MAIN FUNCTION

int main(int argc, char* argv[]) {

	// If statment to prevent future errors...
	if (argc < 2) {
		printf("Usage: %s <msg> <port>\n", argv[0]);
		return 1;
	}

	// Server message.
	char *server_message = argv[1];

	// Create the server socket.
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Define the addr struct (its like the client :/)
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);


	// Binding time, (finally)
	bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	// Listen only two connections at a time (chill ladies B))
	listen(server_socket, 2);

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// Send call
	send(client_socket, server_message, strlen(server_message), 0);
	
	send(client_socket, "\n", 1, 0);


	// close the socket
	close(client_socket);
	close(server_socket);
	return 0;
}
		
