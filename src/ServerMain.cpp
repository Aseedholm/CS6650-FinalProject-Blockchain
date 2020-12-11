#include "Blockchain.hpp"
#include <iostream>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
    //Input order will be
    //this servers port #
    //# of other servers
    //ip address of other servers // port of other server 
    //do line 10 times the input for line 9. (if # of other servers = 3, there should be 3 ip address and 3 ports entered) ip address port // ip address port // ip address port
    int thisPort = std::atoi(argv[1]);
    Blockchain blockchain(thisPort);
    std::cout << "OUR PORT #: " << argv[1];
    int otherServersNumber = std::atoi(argv[2]);
    for (int i = 3; i < (otherServersNumber * 2) + 2; i+=2) {
        //void setServerInfoData(sf::IpAddress ipAddressPassed, int portNumberPassed, int otherServerId);
        sf::IpAddress ipAddress(argv[i]);
        blockchain.setServerInfoData(ipAddress, std::atoi(argv[i+1]), std::atoi(argv[i+1]));
        std::cout << "\nOTHER SERVER's Ip Address: " << argv[i] << "\nOTHER SERVER's PORT #: " << argv[i+1] << std::endl;  
    }
    std::cout <<"\n"<<std::endl;
    blockchain.setSocketVector();

    // int port = std::atoi(argv[2]);
    blockchain.receiveInformation();
    // std::cout << "PAST BLOCK CHAIN" << std::endl; 

}