#include "f_demo.h"

f_demo::f_demo(mp_network * _network){
    network = _network;
    num_players = network->num_players;
    player_num = network->player_num;
}

void f_demo::on_dealer_send(std::vector <unsigned char> hello_msg, int send_player) {
    std::string s(hello_msg.begin(), hello_msg.end());
    std::cout << "player " << DEALER << " sent " << s << " to player " << send_player << std::endl;

    num_sends++;
    if (num_sends == num_players - 1)
        on_pi_return_handler(hello_msg);
}

void f_demo::pi(std::function <void(std::vector <unsigned char>)> _on_pi_return_handler){

    on_pi_return_handler = _on_pi_return_handler;
    auto self = shared_from_this();

    if (player_num == DEALER) {
        for (int i = 1; i <= num_players; i++) {
            if (i != DEALER) {
                std::string a = "hello";
                std::vector <unsigned char> hello_msg(a.begin(), a.end());
                num_sends = 0;
                network->send(i, hello_msg, [this, i, hello_msg]() {
                    on_dealer_send(hello_msg, i);
                });
            }
        }
    } else {
        network->recv(DEALER, [this](std::vector <unsigned char> data){
            std::string s(data.begin(), data.end());
            std::cout << "player " << player_num << " received " << s << " from player " << DEALER << std::endl;
            on_pi_return_handler(data);
        });
    }    

}
