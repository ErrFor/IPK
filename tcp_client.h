#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>

class TCPClient {
public:
    // Constructor
    TCPClient(const std::string &host, int port);
    
    // Destructor
    ~TCPClient();

    // Run the TCP client
    void run();
    void send_bye();

private:
    std::string host_;
    int port_;
    int sockfd_ = -1;
};

extern TCPClient *tcp_client_instance;
#endif  // TCP_CLIENT_H
