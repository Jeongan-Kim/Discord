#include <iostream>
#include "ChatServer.h"

int main() {
    ChatServer server;

    if (server.Start(9000)) {
        std::cout << "������ ���� ���Դϴ�.\n";
        std::cin.get();  // ���͸� ���� ���� ����
        server.Stop();
    }
    else {
        std::cerr << "���� ���� ����\n";
    }

    return 0;
}