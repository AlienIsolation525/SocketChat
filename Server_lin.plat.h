#if defined(__linux__)
#include"Client_lin.plat.h"
//#define MESSAGE_BUFFER 4096 // Максимальный размер буфера для приема и передачи
//#define PORT 7777 // Номер порта, который будем использовать для приема и передачи 
int socket_file_descriptor, message_size;
socklen_t length;
const char *end_string = "end";
struct sockaddr_in client;
 
void processRequest()  {
    // Создадим UDP сокет 
    socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим порт для соединения
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет 
    bind(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    while(1)  {
        // Длина сообщения от клиента
        length = sizeof(client);
        message_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &length);
        buffer[message_size] = '\0';
        if(strcmp(buffer, end_string) == 0)  {
            cout << "Server is Quitting" << endl;
            close(socket_file_descriptor);
            exit(0);
        }
        cout << "Message Received from Client: " << buffer << endl;
        // ответим клиенту
        cout << "Enter reply message to the client: " << endl;
        cin >> message;
        sendto(socket_file_descriptor, message, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
        cout << "Message Sent Successfully to the client: " << message << endl;
        cout << "Waiting for the Reply from Client..!" << endl;
    }
 
    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
}
#endif