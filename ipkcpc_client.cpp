#include "ipkcpc_client.h"
#include "tcp_client.h"
#include "udp_client.h"
#include <iostream>
#include <stdexcept>

// Constructor
IPKCPCClient::IPKCPCClient(const std::string &host, int port, const std::string &mode)
    : host_(host), port_(port), mode_(mode) {}

// Destructor
IPKCPCClient::~IPKCPCClient() {}

// Run the appropriate client based on the specified mode
void IPKCPCClient::run() {
    if (mode_ == "tcp") {
        TCPClient client(host_, port_);
        client.run();
    } else if (mode_ == "udp") {
        UDPClient client(host_, port_);
        client.run();
    } else {
        throw std::runtime_error("Invalid mode specified");
    }
}
