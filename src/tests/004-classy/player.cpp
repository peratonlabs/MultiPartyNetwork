#include <iostream>
#include "../../mp_network.h"

#include "f_demo.h"

#define DEALER 1

boost::promise <bool> async_promise;
int num_sends = 0;


void on_pi_demo(std::vector <unsigned char> demo_msg, mp_network * network) {    
    std::string s(demo_msg.begin(), demo_msg.end());
    std::cout << "demo_msg: " << s << std::endl;
    std::cout << "exiting." << std::endl;
    async_promise.set_value(true);
}


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
    std::shared_ptr <f_demo> demoImpl = std::make_shared <f_demo> (network.get());

    demoImpl->pi([network](std::vector <unsigned char> demo_msg){ on_pi_demo(demo_msg, network.get()); });

    async_future.wait();
    return 1;
}