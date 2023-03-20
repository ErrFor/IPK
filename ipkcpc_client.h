#ifndef IPKCPC_CLIENT_H
#define IPKCPC_CLIENT_H

#include <string>

class IPKCPCClient {
public:
    // Constructor
    IPKCPCClient(const std::string &host, int port, const std::string &mode);
    
    // Destructor
    ~IPKCPCClient();

    // Run the appropriate client based on the specified mode
    void run();

private:
    std::string host_;
    int port_;
    std::string mode_;
};

#endif  // IPKCPC_CLIENT_H
