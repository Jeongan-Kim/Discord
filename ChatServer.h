#pragma once
#include <winsock2.h>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <map>

class ChatServer {
public:
    ChatServer();
    ~ChatServer();

    bool Start(int port); // ���� ä�� ������ �̷������ TCP ��Ʈ ��ȣ�� �Ű��� ����
    void Stop();

private:
    void AcceptClients();
    void HandleClient(SOCKET clientSocket);
    void Broadcast(const std::string& message, SOCKET excludeSocket = INVALID_SOCKET);
    void BroadcastUserList();

    SOCKET listenSocket;
    std::vector<SOCKET> clients;
    std::mutex clientMutex;
    bool isRunning = false;
    bool isShuttingDown = false;

    std::map<SOCKET, std::string> clientNames;
};
