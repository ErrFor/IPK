# IPKCPC Client

## Table of Contents

- [Overview](#overview)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Building](#building)
- [Usage](#usage)
- [Architecture](#architecture)
    - [Class Diagram](#class-diagram)
    - [Core Components](#core-components)
- [Testing](#testing)
- [Extra Features](#extra-features)
- [Bibliography](#bibliography)

## Overview

IPKCPC Client is a command-line utility that allows users to communicate with a remote server using either TCP or UDP protocols. The client can be used to send requests to the server and receive responses, making it suitable for testing server functionality or as part of a larger application that requires network communication.

## Getting Started

### Prerequisites

- A modern C++ compiler that supports C++11
- The make build tool

### Building

To build the IPKCPC Client, follow these steps:

1. Clone the repository or download the source code.
2. Open a terminal and navigate to the project directory.
3. Run `make` to build the client. This will generate the ipkcpc binary.

## Usage

To use the IPKCPC Client, you'll need to know the following:

- The remote server's hostname or IP address
- The port number on which the server is listening
- The mode of communication (TCP or UDP)

Run the client with the following command:

./ipkcpc -h `<host>` -p `<port>` -m `<mode>`


Replace `<host>` with the server's hostname or IP address, `<port>` with the server's port number, and `<mode>` with either `tcp` or `udp`, depending on the desired communication protocol.

For example, to connect to a server at example.com on port 1234 using TCP:

./ipkcpc -h example.com -p 1234 -m tcp


Once the client is connected, you can enter commands or expressions, which will be sent to the server. The server's responses will be displayed on the screen. To exit the client, enter the command `BYE`.

## Architecture

### Class Diagram

+------------------+
|   IPKCPCClient   |
+------------------+
| -host: string    |
| -port: int       |
| -mode: string    |
+------------------+
| +run(): void     |
+------------------+
            |
            +------------------------+
            |                        |
  +-----------------+     +----------------+
  |    TCPClient    |     |   UDPClient    |
  +-----------------+     +----------------+
  | -host: string   |     | -host: string  |
  | -port: int      |     | -port: int     |
  | -sockfd: int    |     | -sockfd: int   |
  +-----------------+     +----------------+
  | +run(): void    |     | +run(): void   |
  +-----------------+     +----------------+


### Core Components

- `main.cpp`: The entry point of the application, responsible for parsing command-line options and initializing the IPKCPCClient instance.
- `ipkcpc_client.h` and `ipkcpc_client.cpp`: The core IPKCPCClient class, responsible for managing the connection to the server and dispatching to the appropriate protocol-specific client (TCP or UDP).
- `tcp_client.h` and `tcp_client.cpp`: The TCPClient class, responsible for establishing a TCP connection, sending requests, and handling responses.
- `udp_client.h` and `udp_client.cpp`: The UDPClient class, responsible for creating and sending UDP packets, as well as handling server responses.

## Testing

To ensure the correct functionality of the IPKCPC Client, a series of tests were performed. The tests cover various aspects of the client, including:

- Connecting to a server using both TCP and UDP protocols.
- Sending requests to the server and receiving responses.
- Handling invalid input or unexpected server responses.
- Gracefully handling connection errors and other exceptions.

These tests were performed using a mock server designed to emulate various scenarios and edge cases. The mock server allowed us to verify that the IPKCPC Client operates as expected and can handle a variety of situations.

To further ensure the reliability of the client, it was tested with several real-world servers to verify compatibility and correct operation.

## Extra Features

The IPKCPC Client offers the following additional features beyond the standard requirements:

- Input validation: The client checks for valid hostname, port, and mode values, providing clear error messages in case of invalid input.
- Graceful error handling: The client handles errors and exceptions gracefully, such as invalid server addresses, unreachable servers, or closed connections.

## Bibliography

- Beej's Guide to Network Programming: https://beej.us/guide/bgnet/
- The C++ Programming Language by Bjarne Stroustrup
- The C++ Standard Library by Nicolai M. Josuttis
- C++ Primer (5th Edition) by Stanley B. Lippman, Josée Lajoie, and Barbara E. Moo
- Stack Overflow (Various threads for specific issues and examples)

# IPK
