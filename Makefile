CCXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic

all: ipkcpc

# Link object files to create the executable
ipkcpc: main.o ipkcpc_client.o tcp_client.o udp_client.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile main.cpp
main.o: main.cpp ipkcpc_client.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile ipkcpc_client.cpp
ipkcpc_client.o: ipkcpc_client.cpp ipkcpc_client.h tcp_client.h udp_client.h
	$(CXX) $(CXXFLAGS) -c ipkcpc_client.cpp

# Compile tcp_client.cpp
tcp_client.o: tcp_client.cpp tcp_client.h
	$(CXX) $(CXXFLAGS) -c tcp_client.cpp

# Compile udp_client.cpp
udp_client.o: udp_client.cpp udp_client.h
	$(CXX) $(CXXFLAGS) -c udp_client.cpp

# Clean build artifacts
clean:
	rm -f *.o ipkcpc