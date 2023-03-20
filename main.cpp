#include <iostream>
#include <string>
#include "ipkcpc_client.h"

// Print usage instructions for the program
void print_usage() {
    std::cerr << "Usage: ipkcpc -h <host> -p <port> -m <mode> (tcp|udp)\n";
}

int main(int argc, char *argv[]) {
    std::string host, mode;
    int port = -1;

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" && i + 1 < argc) {
            host = argv[++i];
        } else if (arg == "-p" && i + 1 < argc) {
            port = std::stoi(argv[++i]);
        } else if (arg == "-m" && i + 1 < argc) {
            mode = argv[++i];
        } else {
            print_usage();
            return 1;
        }
    }

    // Check if required arguments are provided
    if (host.empty() || port == -1 || (mode != "tcp" && mode != "udp")) {
        print_usage();
        return 1;
    }

    // Create and run the IPKCPC client
    try {
        IPKCPCClient client(host, port, mode);
        client.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
