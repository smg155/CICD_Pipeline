#include <stdio.h>

static struct addrinfo* result = NULL;

int main(int argc, char** argv) {
	run_server(argv[1], argv[2]);
}

void run_server(char* host, char* port) {
	int fd = setup(host, port);

	while(1) {
		int client = accept(fd, result->ai_addr, result->ai_addrlen);

		// Read 200 bytes from the client
		char buffer[200];
		read_all(client, buffer, 200);

		// Echo those 200 bytes back to the client
		write_all(client, buffer, 200);
	}
}

int setup(char* host, char* port) {
	int nfd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct addrinfo hints;

	memset(&hints, 0, sizeof(hints));
	bind(host, port, &hints, &result);

	listen(nd, 128);

	return nfd;
}
