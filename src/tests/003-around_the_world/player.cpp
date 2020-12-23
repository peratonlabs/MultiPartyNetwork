#include <iostream>
#include "../../mp_network.h"

#define DEALER 1

boost::promise <bool> async_promise;
int num_sends = 0;


int main(int argc, char ** argv) {

    int player_num;
    int num_players;
    int base_port;

    if (argc != 4) {
        std::cout << "usage: ./player <player_num> <num_players> <base_port>\n";
        exit(-1);
    }

    player_num = atoi(argv[1]);
    num_players = atoi(argv[2]);
    base_port = atoi(argv[3]);

    std::cout << "player " << player_num << "/" << num_players << std::endl;

    asio::io_context p_ctx;
    std::shared_ptr <mp_network> network = std::make_shared <mp_network> (player_num, num_players, 1, base_port, &p_ctx);
    network->connect().wait();
    std::cout << "connected!" << std::endl;
    boost::unique_future <bool> async_future = async_promise.get_future();

    if (player_num == 1) {

        std::string a = "rock";
        std::vector <unsigned char> hello_msg(a.begin(), a.end());

        network->send(2, hello_msg, [hello_msg, num_players, player_num, network]() {
            std::string s(hello_msg.begin(), hello_msg.end());
            std::cout << "player " << player_num << " sent: " << s << " to player " << 2 << std::endl;

            network->recv(num_players, [player_num, num_players](std::vector <unsigned char> data){
                std::string s(data.begin(), data.end());
                std::cout << "player " << player_num << " received: " << s << " from player " << num_players << std::endl;
                
                async_promise.set_value(true);
            });

        });
    } else {
        network->recv(player_num - 1, [num_players, player_num, network](std::vector <unsigned char> data){
            std::string s(data.begin(), data.end());
            std::cout << "player " << player_num << " received: " << s << " from player " << player_num -1 << std::endl;

            int next = player_num + 1;
            if (next > num_players)
                next = 1;
            
            network->send(next, data, [player_num, next, s]() {
                std::cout << "player " << player_num << " sent: " << s << " to player " << next << std::endl;
                async_promise.set_value(true);

            });
        });
    }
    async_future.wait();
    std::cout << "exiting!" << std::endl;
    return 1;
}