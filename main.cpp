#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

std::string getUsername() {
    char username[256];
    DWORD username_len = 256;
    GetUserNameA(username, &username_len);
    return std::string(username);
}

std::string getMachineName() {
    char computerName[256];
    DWORD size = sizeof(computerName);
    GetComputerNameA(computerName, &size);
    return std::string(computerName);
}

DWORD getLastInputTime() {
    LASTINPUTINFO lii = {0};
    lii.cbSize = sizeof(LASTINPUTINFO);
    if (GetLastInputInfo(&lii)) {
        return GetTickCount() - lii.dwTime;
    }
    return 0;
}

void sendDataToServer(const std::string& data) {
    WSADATA wsa;
    SOCKET s;
    sockaddr_in server;

    WSAStartup(MAKEWORD(2, 2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP
    server.sin_family = AF_INET;
    server.sin_port = htons(5000); // Server Port

    if (connect(s, (struct sockaddr*)&server, sizeof(server)) == 0) {
        send(s, data.c_str(), data.size(), 0);
    }
    closesocket(s);
    WSACleanup();
}

int main() {
    std::string username = getUsername();
    std::string machineName = getMachineName();
    DWORD lastInputTime = getLastInputTime();

    std::string data = "Username: " + username + "\nMachine: " + machineName + "\nLast Active (ms): " + std::to_string(lastInputTime);
    sendDataToServer(data);

    return 0;
}