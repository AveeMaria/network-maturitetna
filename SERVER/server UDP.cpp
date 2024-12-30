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
    bool running = true;
    auto startTime = std::chrono::steady_clock::now();

    if (SDLNet_ResolveHost(&ip, NULL, 12345) == -1) {
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        SDLNet_Quit();
        SDL_Quit();
        return -1;
    }

    sock = SDLNet_UDP_Open(12345);  // Open socket on port 12345
    if (!sock) {
        std::cerr << "SDLNet_UDP_Open: " << SDLNet_GetError() << std::endl;
        SDLNet_Quit();
        SDL_Quit();
        return -1;
    }

    std::cout << "Server is listening on port 12345..." << std::endl;

    while (running) {
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count() >= 60) {
            running = false;
            std::cout << "Server has been running for 1 minute. Shutting down." << std::endl;
            break;
        }

        char message[512];
        packet.data = (Uint8*)message;
        packet.len = 512;

        if (SDLNet_UDP_Recv(sock, &packet)) {
            std::cout << "Received message: " << message << std::endl;

            const char* response = "Hello from server!";
            packet.data = (Uint8*)response;
            packet.len = strlen(response) + 1;
            if (SDLNet_UDP_Send(sock, -1, &packet) < 1) {
                std::cerr << "SDLNet_UDP_Send: " << SDLNet_GetError() << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    SDLNet_UDP_Close(sock);
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}
