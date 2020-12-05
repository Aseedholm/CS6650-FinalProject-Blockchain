#include "Blockchain.hpp"
#include <iostream>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
    Blockchain blockchain;
    int port = std::atoi(argv[1]);
    blockchain.receiveInformationFromClient(port);
    // std::cout << "PAST BLOCK CHAIN" << std::endl; 

}