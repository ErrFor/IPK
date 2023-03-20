#include <string>
#include <vector>

class UDPClient {
public:
    // Constructor
    UDPClient(const std::string &host, int port);
    
    // Destructor
    ~UDPClient();
    
    // Run the UDP client
    void run();

private:
    std::string host_;
    int port_;
    int sockfd_;

    // Create a request from the input expression
    std::vector<uint8_t> create_request(const std::string &expr);
    
    // Handle the response received from the server
    void handle_response(const std::vector<uint8_t> &response);
};
