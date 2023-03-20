#include "udp_client.h"
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

// Create a request from the input expression
std::vector<uint8_t> UDPClient::create_request(const std::string &expr) {
    std::vector<uint8_t> request;
    request.push_back(0); // Opcode: Request
    uint8_t payload_length = static_cast<uint8_t>(expr.size());
    request.push_back(payload_length); // Payload Length
    request.insert(request.end(), expr.begin(), expr.end()); // Payload Data
    return request;
}

// Handle the response received from the server
void UDPClient::handle_response(const std::vector<uint8_t> &response) {
    if (response.size() < 3) {
        throw std::runtime_error("Invalid response received");
    }

    if (response[1] == 0) { // Status: OK
        std::string result(response.begin() + 3, response.end());
        std::cout << "OK:" << result << std::endl;
    } else { // Status: Error
        std::string error_msg(response.begin() + 3, response.end());
        std::cout << "ERR:" << error_msg << std::endl;
    }
}

// Constructor
UDPClient::UDPClient(const std::string &host, int port)
    : host_(host), port_(port), sockfd_(-1) {}

// Destructor
UDPClient::~UDPClient() {
    if (sockfd_ != -1) {
        close(sockfd_);
    }
}

// Run the UDP client
void UDPClient::run() {
    // Create a socket
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ == -1) {
        throw std::runtime_error("Error creating socket");
    }

    // Set up server address
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_);
    if (inet_pton(AF_INET, host_.c_str(), &serv_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address or address not supported");
    }

    std::string input;
    while (std::getline(std::cin, input)) {
        // Create request
        auto request = create_request(input);

        // Send request to server
        sendto(sockfd_, request.data(), request.size(), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        // Receive response from server
        std::vector<uint8_t> buffer(512);
        ssize_t recv_len = recvfrom(sockfd_, buffer.data(), buffer.size(), 0, nullptr, nullptr);
        if (recv_len == -1) {
            throw std::runtime_error("Error receiving data from server");
        }
        buffer.resize(recv_len);

        // Handle response from server
        handle_response(buffer);
    }

    // Close the socket
    close(sockfd_);
}