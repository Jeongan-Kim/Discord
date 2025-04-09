#pragma once
#include <winsock2.h>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <unordered_map>

class ChatServer {
public:
    ChatServer();
    ~ChatServer();

    bool Start(int port); // ���� ä�� ������ �̷������ TCP ��Ʈ ��ȣ�� �Ű��� ����
    void Stop();

private:
    void AcceptClients();
    void HandleClient(SOCKET clientSocket);
    void Broadcast(const std::string& message, SOCKET excludeSocket = INVALID_SOCKET); // ��ü �������� ���� ��
    void BroadcastUserList(const std::string& roomName); // ä�ù� �̸��� ���ڷ� �޾� �ش� �濡�� ����Ʈ�� ������ �Լ�
    void BroadcastToRoom(const std::string& roomId, const std::string& message, SOCKET exclude); // �� ���� ä�� �޽����� �ý��� �޽��� ���� ��

    SOCKET listenSocket;
    std::vector<SOCKET> clients;
    std::mutex clientMutex;
    bool isRunning = false;
    bool isShuttingDown = false;

    //std::map<SOCKET, std::string> clientNames;
    //std::map<std::string, std::vector<SOCKET>> roomList;

    std::unordered_map<SOCKET, std::string> clientNames;            //���� -> �г���
    std::unordered_map<SOCKET, std::set<std::string>> clientRooms;  //���� -> �������� ���   
    std::unordered_map<std::string, std::set<SOCKET>> roomList;     //�� �̸� -> �������� ���ϵ�
};
