#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    // Get IP address and port number from user input
    char ip_address[16];
    printf("Enter IP address to bind to: ");
    fgets(ip_address, 16, stdin);
    ip_address[strcspn(ip_address, "\n")] = 0; // Remove trailing newline character

    int port_number;
    printf("Enter port number to bind to: ");
    scanf("%d", &port_number);

    // Create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    // Bind socket to IP address and port number
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip_address);
    server_address.sin_port = htons(port_number);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s:%d\n", ip_address, port_number);

    // Accept incoming connections
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
    if (client_socket < 0) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    printf("Client connected: %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // Receive data from client
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    printf("Received %zd bytes: %s\n", bytes_received, buffer);

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}

