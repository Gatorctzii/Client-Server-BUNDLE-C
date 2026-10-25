// INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>

#include <arpa/inet.h>


// MAIN FUNCTION

int main(int argc, char* argv[]) {

	if (argc < 3) {
		fprintf(stderr, "Usage %s <ip_addr> <port>\n", argv[0]);
		return 1;
	}
	
	// Initalize the socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_addr.s_addr = inet_addr(argv[1]);

	if (server_address.sin_addr.s_addr == INADDR_NONE) {
		fprintf(stderr, "Invalid IP Provided.\n");
		close(network_socket);
		return 1;
	}
	
	// Connect function time :D
	// Expected return value : 0
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	if (connection_status == -1) {
		perror("There was an error making a connection to the remote socket\n\n");
	}
	
	// Recieve data from the server
	char server_response[4096];
	recv(network_socket, &server_response, sizeof(server_response), 0); // 0 is for flags param
	
	// Now that we recieved, we just print the data!
	
	// print response
	printf("+===================+\n");
	printf("|   DATA_RECIEVED!  |\n");
	printf("+===================+\n\n");

	printf("%s\n", server_response);

	close(network_socket); // idk why you just say sock but whatever..

	return 0;
}
