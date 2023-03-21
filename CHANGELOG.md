# Changelog

[v1.0.0] - 2023-03-21

2023-03-17

Started project setup:

- Created new directory structure, including src and include folders for source files and headers.
- Began working on the main.cpp file with basic argument parsing and error checking.

2023-03-18

Implemented IPKCPCClient class in ipkcpc_client.cpp and ipkcpc_client.h:

- Constructors and destructors for IPKCPCClient: Initializes the host, port, and mode.
- run() function to instantiate and run the appropriate client (TCP or UDP) based on the specified mode. Throws an exception if an invalid mode is provided.

Updated main.cpp:

- Improved command line argument parsing using a loop and conditional checks.
- Checking if required arguments are provided and valid; printing usage instructions otherwise.
- Instantiating and running the IPKCPC client with the provided arguments, and handling exceptions.

2023-03-19

Created Makefile for building the project:

- Compiling and linking object files to create the 'ipkcpc' executable using the C++11 standard, along with specific compiler flags for warnings and pedantic checks.
- Rules for compiling main.cpp, ipkcpc_client.cpp, tcp_client.cpp, and udp_client.cpp with their corresponding header files as dependencies.
- 'clean' rule for removing build artifacts (*.o files and 'ipkcpc' executable).

Implemented TCPClient class in tcp_client.cpp and tcp_client.h:

- Constructors and destructors for TCPClient: Initializes the host, port, and sockfd (socket file descriptor). Closes the sockfd in the destructor.
- Function to send "BYE" message to the server using the send() function.
- run() function to:
    - Register the signal handler for SIGINT (Ctrl+C) using a struct sigaction.
    - Create a socket and set up the server address.
    - Connect to the server using the connect() function.
    - Send and receive data using send() and recv() functions in a loop until receiving a "BYE" message or a SIGINT signal.

2023-03-20

Implemented UDPClient class in udp_client.cpp and udp_client.h:

- Constructors and destructors for UDPClient: Initializes the host, port, and sockfd (socket file descriptor). Closes the sockfd in the destructor.
- create_request() function to create a request with proper formatting (opcode, payload length, and payload data) based on the input expression.
- handle_response() function to handle responses from the server by checking the status (OK or Error) and printing the result or error message accordingly.
- run() function to:
    - Create a socket and set up the server address.
    - Use a loop to read input, create requests, send requests to the server, and receive responses.
    - Handle responses received from the server.

2023-03-21

- Merged separate source files into a single main.cpp file as per the request.
- Updated the Makefile to reflect the changes made to the source files:
    - Removed rules for compiling ipkcpc_client.cpp,
    - Updated the rule for compiling main.cpp, removing the dependency on the individual header files.
    - Updated the rule for linking object files to create the 'ipkcpc' executable, as only main.o is required now.
- Removed the ipkcpc_client.cpp, ipkcpc_client.h files, since their content has been merged into main.cpp.

- Refactored code, making small improvements and adding comments for better readability.
- Conducted thorough testing of the application, ensuring proper functionality and error handling.
- Created a Git repository for version control and collaboration.
- Finalized documentation and created the detailed changelog.