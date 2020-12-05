#include "Blockchain.hpp"
#include <iostream>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
    std::cout << "OUR PORT #: " << argv[1] << "\nOTHER SERVER's PORT #: " << argv[2] << std::endl;    
    Blockchain blockchain(std::atoi(argv[1]));
    int port = std::atoi(argv[2]);
    blockchain.receiveInformationFromClient(port);
    // std::cout << "PAST BLOCK CHAIN" << std::endl; 

}