#ifndef _F_DEMO_H_
#define _F_DEMO_H_

#define DEALER 1

#include "../../mp_network.h"


class f_demo : public std::enable_shared_from_this <f_demo> {

public:

    f_demo(mp_network * _network);
    void pi(std::function <void(std::vector <unsigned char>)> _on_pi_return_handler);
    void on_dealer_send(std::vector <unsigned char> hello_msg, int send_player);


private:

    int player_num;
    int num_players;

    int num_sends;

    mp_network * network;

    std::function <void(std::vector <unsigned char>)> on_pi_return_handler;
};

#endif