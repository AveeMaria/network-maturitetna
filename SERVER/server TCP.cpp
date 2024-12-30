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
    TCPsocket server, client;
    bool running = true;
    auto startTime = std::chrono::steady_clock::now();

    if (SDLNet_ResolveHost(&ip, NULL, 12345) == -1) {
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        SDLNet_Quit();
        SDL_Quit();
        return -1;
    }

    server = SDLNet_TCP_Open(&ip);
    if (!server) {
        std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;        SDLNet_Quit();
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

        client = SDLNet_TCP_Accept(server);
        if (client) {
            std::cout << "Client connected." << std::endl;

            char message[512];
            int result = SDLNet_TCP_Recv(client, message, 512);
            if (result > 0) {
                message[result] = '\0';
                std::cout << "Received message: " << message << std::endl;

                const char* response = "Hello from server!";
                if (SDLNet_TCP_Send(client, response, strlen(response) + 1) < strlen(response) + 1) {
                    std::cerr << "SDLNet_TCP_Send: " << SDLNet_GetError() << std::endl;
                }
            }
            else {
                std::cerr << "SDLNet_TCP_Recv: " << SDLNet_GetError() << std::endl;
            }

            SDLNet_TCP_Close(client);
            std::cout << "Client disconnected." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    SDLNet_TCP_Close(server);
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}