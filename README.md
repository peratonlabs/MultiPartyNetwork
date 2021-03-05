# MultiPartyNetwork (mp_network)

The multi-party network class is a c++ header and source file used to establish a fully-connected network with an arbitrary number of tcp channels between every party. Once the network is fully-connected, the class provides synchronous and asynchronous networking functionality to send and recieve data. mp_network depends on libBoost.

Examples | Description
------------- | -------------
Connect | establish a fully-connected network with a single channel.
Hello Async | player 1 is the dealer and sends "hello" asynchonously to every other player 
Around the World | player 1 sends to player 2, then player 2 sends to player 3,..., player n finally sends to player 1
Classy | demonstrates hello async example using mp_network within a class
Large Scale MPC | project uses mp_network for MPC with complex communication patterns tested up to 512 parties

## Dependencies
* libboost-1.71.0 https://www.boost.org/users/history/version_1_71_0.html

### Ubuntu 20.04
```sudo apt install cmake g++ libboost-all-dev```
