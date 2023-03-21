CCXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic

all: ipkcpc

# Link object files to create the executable
ipkcpc: main.o tcp_client.o udp_client.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile main.cpp
main.o: main.cpp tcp_client.o udp_client.o
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile tcp_client.cpp
tcp_client.o: tcp_client.cpp tcp_client.h
	$(CXX) $(CXXFLAGS) -c tcp_client.cpp

# Compile udp_client.cpp
udp_client.o: udp_client.cpp udp_client.h
	$(CXX) $(CXXFLAGS) -c udp_client.cpp

# Clean build artifacts
clean:
	rm -f *.o ipkcpc