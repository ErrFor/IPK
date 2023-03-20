#include "tcp_client.h"
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <signal.h>

static volatile bool keep_running = true;

// Signal handler function
void handle_sigint(int signum) {
    (void)signum; // Mark the parameter as unused
    keep_running = false;
}

// Constructor
TCPClient::TCPClient(const std::string &host, int port)
    : host_(host), port_(port), sockfd_(-1) {
        tcp_client_instance = this; // Set the global instance
    }

// Destructor
TCPClient::~TCPClient() {
    if (sockfd_ != -1) {
        close(sockfd_);
    }
    tcp_client_instance = nullptr; // Unset the global instance
}

// Send "BYE" message to the server
void TCPClient::send_bye() {
    if (sockfd_ != -1) {
        send(sockfd_, "BYE", strlen("BYE"), 0);
    }
}

// Run the TCP client
void TCPClient::run() {
    // Register the signal handler for SIGINT
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = handle_sigint;
    sigaction(SIGINT, &act, nullptr);

    // Create a socket
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ == -1) {
        throw std::runtime_error("Error creating socket");
    }

    // Set up the server address
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_);
    if (inet_pton(AF_INET, host_.c_str(), &serv_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address or address not supported");
    }

    // Connect to the server
    if (connect(sockfd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        throw std::runtime_error("Error connecting to server");
    }

    // Send and receive data
    std::string input;
    std::getline(std::cin, input); // HELLO
    send(sockfd_, input.c_str(), input.size(), 0);

    // Receive data from the server
    char buffer[512];
    ssize_t recv_len = recv(sockfd_, buffer, sizeof(buffer) - 1, 0);
    if (recv_len == -1) {
        throw std::runtime_error("Error receiving data from server");
    }
    buffer[recv_len] = '\0';
    std::cout << buffer << std::endl; // HELLO

    // Continue sending and receiving data
    while (std::getline(std::cin, input) || !keep_running) {
        if (!keep_running) {
            input = "BYE";
            std::cout << std::endl << input << std::endl;
        }

        if (input == "BYE") {
            send(sockfd_, input.c_str(), input.size(), 0);
            std::cout << input << std::endl;
            break;
        }

        // SOLVE ({+,-,*,/} a b)
        send(sockfd_, input.c_str(), input.size(), 0);

        recv_len = recv(sockfd_, buffer, sizeof(buffer) - 1, 0);
        if (recv_len == -1) {
            throw std::runtime_error("Error receiving data from server");
        }
        buffer[recv_len] = '\0';
        std::cout << buffer << std::endl;   // RESULT c
    }

    // Close the socket
    close(sockfd_);
}

TCPClient *tcp_client_instance = nullptr;

