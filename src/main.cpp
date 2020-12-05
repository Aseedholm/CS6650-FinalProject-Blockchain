#include "Miner.hpp"
#include <stdlib.h>
#include <string>
#include <SFML/Network.hpp>

#include "Blockchain.hpp"

int main(int argc, char const *argv[])
{
    int randomInt = rand();
    int difficulty = 2;
    /* code */
    //(int blockIndexPassed, const std::string &blockDataPassed, const int blockMiningDifficultyPassed) 
    Miner miner(0, "Andrew sends bitcoins to someone else1", difficulty);
    miner.printAll();
    std::cout << "Printed Value: " << std::endl;
    std::cout <<"\nPrevious Hash: " << randomInt << std::endl;
    std::cout << "\nMining Block 1 ..." << std::endl; 
    miner.mineBlock(std::to_string(randomInt));


    sf::Socket::Status sendToServerStatus;
    sf::TcpSocket sendToServer;
    sf::IpAddress ipAddress;
    ipAddress.getLocalAddress();
    sendToServerStatus = sendToServer.connect(ipAddress, 8081);

    sf::Packet packetP;

    sendToServer.receive(packetP);

    sf::Uint32 index;
    std::string previousHash;

    packetP >> index >> previousHash;

    std::cout <<"FROM SERVER: \nIndex: " << index << "\nPrevious Hash: " << previousHash << std::endl;

    packetP.clear();
    // packetP << miner.getHash();
    // sendToServer.send(packetP);


    
    //statusInApp = clientSocketInApp.connect(ipAddress, port);

    // //////
    // Miner miner1(1, "Andrew sends bitcoins to someone else 2", difficulty);
    // miner.printAll();
    // std::cout << "Printed Value: " << std::endl;
    // std::cout <<"\nPrevious Hash: " << miner.getHash() << std::endl;
    // std::cout << "\nMining Block 2 ..." << std::endl; 
    // miner.mineBlock(miner.getHash());

    // ////
    // Miner miner2(2, "Andrew sends bitcoins to someone else3", difficulty);
    // miner.printAll();
    // std::cout << "Printed Value: " << std::endl;
    // std::cout <<"\nPrevious Hash: " << miner1.getHash() << std::endl;
    // std::cout << "\nMining Block 3 ..." << std::endl; 
    // miner.mineBlock(miner1.getHash());
    return 0;
}
