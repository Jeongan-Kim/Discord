#include "ChatClient.h"
#include <iostream>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

ChatClient::ChatClient() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}

ChatClient::~ChatClient() {
    closesocket(sock);
    WSACleanup();
}

bool ChatClient::Connect(const std::string& ip, int port) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) return false;

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) != 1) {
        std::cerr << "IP �ּ� ��ȯ ����\n";
        return false;
    }

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        return false;
    }

    isConnected = true;

	// �г��� �Է�
    std::cout << "�г����� �Է��ϼ���: ";
    std::getline(std::cin, nickname);

    // ������ �г��� ���� ����
    send(sock, nickname.c_str(), nickname.length(), 0);


    StartReceiving();
    return true;
}

void ChatClient::Send(const std::string& message) {
    if (isConnected) {
        send(sock, message.c_str(), message.size(), 0);
    }
}

void ChatClient::StartReceiving() {
    std::thread([this]() {
        char buffer[1024];
        int bytes;

        while ((bytes = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
            buffer[bytes] = '\0';

            // ���� �Է� �� ����� + �޽��� ���
            std::cout << "\r\33[K " << buffer << std::endl;

            // �Է� ������Ʈ �ٽ� ���
            std::cout << "> ";
            std::cout.flush();  // ��� ��� �ݿ�
        }
        }).detach();
}
