#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

/home/dora/VirtualBox VMs/test5/test5.vdi


int main() {
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	char buffer[1024];
	int port = 6667;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if  (server_fd < 0)
	{
		perror("socket");
		return 1;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		if (client_fd < 0)
		{
			perror("accept");
			close(server_fd);
			return 1;
		}
	}

	if (listen(server_fd, 5) < 0) {
		perror("listen");
		close(server_fd);
		return 1;
	}

	std::cout << "Server listening on port " << port << std::endl;
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
	if (client_fd < 0)
	{
		perror("accept");
		close(server_fd);
		return 1;
	}

    std::cout << "Client connected" << std::endl;

	ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
	buffer[bytes_read] = '\0';

	std::cout << "Received message: " << buffer << std::endl;

	close(client_fd);
    close(server_fd);

    return 0;
}