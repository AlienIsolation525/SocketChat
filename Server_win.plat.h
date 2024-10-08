#if defined(_WIN64)
#include "Client_win.plat.h"

class UDPServer {
public:
    UDPServer() {
        // initialise winsock
        std::cout << "Initialising Winsock...\n";
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            std::cout << "Failed. Error Code: " << WSAGetLastError() << "\n";
            exit(0);
        }
        std::cout << "Initialised.\n";

        // create a socket
        if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
            std::cout << "Could not create socket: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }

        // prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(PORT);

        // bind
        if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
            std::cout << "Bind failed with error code: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }
    }

    ~UDPServer() {
        closesocket(server_socket);
        WSACleanup();
    }

    void start() {
        while (!exitRequested) {
            char message[BUFLEN] = {};

            // try to receive some data, this is a blocking call
            int message_len;
            int slen = sizeof(sockaddr_in);
            if ((message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen)) == SOCKET_ERROR) {
                std::cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
                exit(0);
            }

            // print details of the client/peer and the data received
            std::cout << "Message Received from Client: " << message << "\n";

            std::cout << "Enter response (exit to stop server process): ";
            std::cin.getline(message, BUFLEN);

            // reply to the client with the same data
            if (sendto(server_socket, message, strlen(message), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR) {
                std::cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
                exit(EXIT_FAILURE);
            }

            if (strcmp(message, "exit") == 0) {
                std::cout << "Exiting server...\n";
                exitRequested = true;
                break;
            }
        }
    }

private:
    WSADATA wsa{};
    SOCKET server_socket = 0;
    sockaddr_in server{}, client{};
    bool exitRequested = false;
};

#endif