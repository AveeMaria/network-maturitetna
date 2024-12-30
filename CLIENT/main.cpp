#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
    if (SDL_Init(0) == -1 || SDLNet_Init() == -1) {
        std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
        return -1;
    }

    IPaddress ip;
    UDPsocket sock;
    UDPpacket packet;

    if (SDLNet_ResolveHost(&ip, "192.168.0.10", 12345) == -1) {
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        return -1;
    }

    sock = SDLNet_UDP_Open(0); // 0 to let SDL choose an available port
    if (!sock) {
        std::cerr << "SDLNet_UDP_Open: " << SDLNet_GetError() << std::endl;
        return -1;
    }

    const char* message = "Hello from client!";
    packet.address = ip;
    packet.len = strlen(message) + 1;
    packet.data = (Uint8*)message;

    if (SDLNet_UDP_Send(sock, -1, &packet) < 1) {
        std::cerr << "SDLNet_UDP_Send: " << SDLNet_GetError() << std::endl;
        SDLNet_UDP_Close(sock);
        return -1;
    }

    char response[512];
    packet.data = (Uint8*)response;
    packet.len = 512;

    if (SDLNet_UDP_Recv(sock, &packet)) {
        std::cout << "Received response: " << response << std::endl;
    } else {
        std::cerr << "SDLNet_UDP_Recv: " << SDLNet_GetError() << std::endl;
    }

    SDLNet_UDP_Close(sock);
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}
