#include <iostream>

#ifdef _WIN32 || _WIN64
  // Windows UDP by Sloan Kelly (Thank you!)
  #include <WS2tcpip.h>
  #pragma comment (lib, "ws2_32.lib") 
  using namespace std;
  // Main entry point into the server
  bool UDP_functional(){
    return true;
  }

  // void UDP_init(){  
  //   WSADATA data;
	 //  WORD version = MAKEWORD(2, 2);
	 //  int wsOk = WSAStartup(version, &data);
	 //  if (wsOk != 0){ // Not ok! Get out quickly
  // 		cout << "Can't start Winsock! " << wsOk;
  // 		return;
  // 	}

  // }

  void UDP_Recive()
  {
	  // INITIALIZE WINSOCK and check if working
    // UDP_init();
	  WSADATA data;
	  WORD version = MAKEWORD(2, 2);
	  int wsOk = WSAStartup(version, &data);
	  if (wsOk != 0){ // Not ok! Get out quickly
  		cout << "Can't start Winsock! " << wsOk;
  		return;
  	}

  	// SOCKET CREATION AND BINDING
  
  	// Create a socket, notice that it is a user datagram socket (UDP)
  	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
  
  	// Create a server hint structure for the server
  	sockaddr_in serverHint;
  	serverHint.sin_addr.S_un.S_addr = ADDR_ANY; // Us any IP address available on the machine
  	serverHint.sin_family = AF_INET; // Address format is IPv4
  	serverHint.sin_port = htons(54000); // Convert from little to big endian
  
  	// Try and bind the socket to the IP and port
  	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
  	{
  		cout << "Can't bind socket! " << WSAGetLastError() << endl;
  		return;
  	}
  	
  	sockaddr_in client; // Use to hold the client information (port / ip address)
  	int clientLength = sizeof(client); // The size of the client information
  
  	char buf[1024];

    ZeroMemory(&client, clientLength); // Clear the client structure
    ZeroMemory(buf, 1024); // Clear the receive buffer

    // Wait for message
    int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
    if (bytesIn == SOCKET_ERROR)
    {
      cout << "Error receiving from client " << WSAGetLastError() << endl;
      continue;
    }

    // Display message and client info
    char clientIp[256]; // Create enough space to convert the address byte array
    ZeroMemory(clientIp, 256); // to string of characters

    // Convert from byte array to chars
    inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

    // Display the message / who sent it
    cout << "Message recv from " << clientIp << " : " << buf << endl;
  	
  	// Close socket
  	closesocket(in);
  
  	// Shutdown winsock
  	WSACleanup();
  }

  void UDP_Send(int argc, char* argv[])
  {

	  WSADATA data;
	  WORD version = MAKEWORD(2, 2);
  	int wsOk = WSAStartup(version, &data);
  	if (wsOk != 0)
  	{
  		// Not ok! Get out quickly
  		cout << "Can't start Winsock! " << wsOk;
  		return;
  	}
	  // Create a hint structure for the server
  	sockaddr_in server;
    string sever_IP = "127.0.0.1"
  	server.sin_family = AF_INET; // AF_INET = IPv4 addresses
  	server.sin_port = htons(54000); // Little to big endian conversion
  	inet_pton(AF_INET, sever_IP, &server.sin_addr); // Convert from string to byte array
  
  	// Socket creation, note that the socket type is datagram
  	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
  
  	// Write out to that socket
  	string s(argv[1]);
  	int sendOk = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));
  
  	if (sendOk == SOCKET_ERROR)
  	{
  		cout << "That didn't work! " << WSAGetLastError() << endl;
  	}
  
  	// Close the socket
  	closesocket(out);
  
  	// Close down Winsock
  	WSACleanup();
  }
  




#elif __linux__
  //linux
  #include <iostream>
  bool UDP_functional(){
    std::cout << "linux" << std::endl; 
    return false;
  }
#elif __unix || __unix__
  //unix
  bool UDP_functional(){
    std::cout << "unix\n";
    return false;
  }
#else 
  bool UDP_functional(){
    std::cout << "error \n";
    return false; 
  }
#endif