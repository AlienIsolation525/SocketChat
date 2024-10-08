#if defined(__linux__)
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h> // Библиотека для работы с сокетами
#include <arpa/inet.h>

using namespace std;
 
// Максимальный размер буфера для приема и передачи
#define MESSAGE_BUFFER 4096
#define PORT 7777 // номер порта, который будем использовать для приема и передачи 
 
string sep = " ^^ ", username;

char buffer[MESSAGE_BUFFER];
char message[MESSAGE_BUFFER];
int socket_descriptor;
struct sockaddr_in serveraddress;
 
void sendRequest(){
    // Укажем адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта для соединения с сервером
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Создадим сокет 
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    // Установим соединение с сервером
    if(connect(socket_descriptor, (struct sockaddr*) &serveraddress, sizeof(serveraddress)) < 0) {
        cout << endl << " Something went wrong Connection Failed" << endl;
        exit(1);
    }
    while(1){
        cout << "Enter a message you want to send to the server: " << endl;
        cin >> message;
        if (strcmp(message, "end") == 0)  {
        sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
        cout << "Client work is done.!" << endl;
        close(socket_descriptor);
        exit(0);
        }   
        else {
            sendto(socket_descriptor, message, MESSAGE_BUFFER, 0, nullptr, sizeof(serveraddress));
            cout << "Message sent successfully to the server: " <<  message << endl;
            cout << "Waiting for the Response from Server..." << endl;
        }
    cout << "Message Received From Server: " << endl;
    recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr);
    cout <<  buffer << endl;
    }
    // закрываем сокет, завершаем соединение
    close(socket_descriptor);
}
#endif