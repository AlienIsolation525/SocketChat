
#if defined(_WIN64)
#define PLATFORM_NAME "windows 64-bit" // Windows 64-bit
#include "Server_win.plat.h"
int main() {
    using namespace std;
    string username;
    int q;
    //Options
    cout << "Greetings!" << endl << "Enter your name: ";
    cin >> username;
    cout << endl << "Would you like to go client or like server?" << endl << "SERVER - 1   " << "CLIENT - 2" << endl;
    cin >> q;
    if (q == 1) {
        system("title UDP Server");
         
        MoveWindow(GetConsoleWindow(), 50, 50, 500, 500, true);

        UDPServer udpServer;
        udpServer.start();
    }
    if (q == 2) {
        system("title UDP Client");

        MoveWindow(GetConsoleWindow(), 50, 50, 500, 500, true);

        UDPClient udpClient;
        udpClient.start();
    }
}

#elif defined(__linux__)
#define PLATFORM_NAME "linux" // Linux
#include "Server_lin.plat.h"
int main() {
    using namespace std;
    string username;
    int q;
    //Options
    cout << "Greetings!" << endl << "Enter your name: ";
    cin >> username;
    cout << endl << "Would you like to go client or like server?" << endl << "SERVER - 1   " << "CLIENT - 2" << endl;
    cin >> q;
    if (q == 1) {
        cout << "SERVER IS LISTENING THROUGH THE PORT: " << PORT << " WITHIN A LOCAL SYSTEM" << endl;
        processRequest();
    }
    if (q == 2) {
        cout << "CLIENT IS ESTABLISHING A CONNECTION WITH SERVER THROUGH PORT: " << PORT << endl;
        sendRequest();
    }
}
#endif
;

