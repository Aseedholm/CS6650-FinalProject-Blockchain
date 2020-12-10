#include "Miner.hpp"
#include <stdlib.h>
#include <string>
#include <SFML/Network.hpp>

#include "Blockchain.hpp"

int main(int argc, char const *argv[])
{
    int port = std::atoi(argv[1]);
    int randomInt = rand();
    int difficulty = 5;
    /* code */


    //Client to Server connection ************************************************************************************
    sf::Socket::Status sendToServerStatus;
    sf::TcpSocket sendToServer;
    sf::IpAddress ipAddress;
    ipAddress.getLocalAddress();
    sendToServerStatus = sendToServer.connect(ipAddress, port);

    sf::Packet packetP;

    //receive information from server. 
    sendToServer.receive(packetP);
    sf::Uint32 index;
    std::string previousHash;
    std::string sender = "c";
    sf::Uint32 initialConnection = 1;

    packetP >> index >> previousHash;

    std::cout <<"FROM SERVER: \nIndex: " << index << "\nPrevious Hash: " << previousHash << std::endl;
    //Client to Server connection ************************************************************************************


    //(int blockIndexPassed, const std::string &blockDataPassed, const int blockMiningDifficultyPassed) 
    Miner miner(int(index), argv[1], difficulty);
    std::cout << "Printed Value: *****************************************************" << std::endl;
    std::cout <<"Previous Hash: " << previousHash << std::endl;
    std::cout << "Mining Block 1 ..." << std::endl; 
    miner.mineBlock(previousHash);
    std::cout << "Minning Done *****************************************************" << std::endl;       
    miner.printAll();
    std::cout << "Printed Value: *****************************************************\n" << std::endl;

    sf::Uint32 killCommand = 1;
    packetP.clear();
    packetP << miner.getHash() << killCommand << sender << initialConnection;
    sendToServer.send(packetP);


    

    // //MINE SECOND BLOCK ********************************************************************************************************
    // packetP.clear();
    // sendToServer.receive(packetP);  
    // packetP >> index >> previousHash;

    // std::cout <<"\n\nFROM SERVER 2: \nIndex: " << index << "\nPrevious Hash: " << previousHash << std::endl;
    // //Client to Server connection ************************************************************************************


    // //(int blockIndexPassed, const std::string &blockDataPassed, const int blockMiningDifficultyPassed) 
    // Miner miner1(int(index), argv[1], difficulty);
    // std::cout << "Printed Value: *****************************************************" << std::endl;
    // miner.printAll();
    // std::cout << "Printed Value: *****************************************************" << std::endl;
    // std::cout <<"\nPrevious Hash: " << previousHash << std::endl;
    // std::cout << "\nMining Block 1 ..." << std::endl; 
    // miner.mineBlock(previousHash);
    // std::cout << "\nMinning Done *****************************************************" << std::endl;       



    // killCommand = 0;
    // packetP.clear();
    // //MINE SECOND BLOCK ********************************************************************************************************



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
