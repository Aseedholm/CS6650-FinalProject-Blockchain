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


    //Client to Server connection
    sf::Socket::Status sendToServerStatus;
    sf::TcpSocket sendToServer;
    sf::IpAddress ipAddress;
    ipAddress.getLocalAddress();
    sendToServerStatus = sendToServer.connect(ipAddress, port);
    //Client to Server connection

    sf::Uint32 command = std::atoi(argv[2]);
    sf::Packet packetP;
    sf::Uint32 killCommand = 1;
    std::string sender = "c";

    //initial connection information
    sendToServer.receive(packetP);
    sf::Uint32 index;
    std::string previousHash;
    //initial connection information


    packetP >> index >> previousHash;

    //Change send order for packet.
    //command == 0 
    //packet << sender << command

    if(command == 0) {
        std::cout <<"FROM SERVER: \nIndex: " << index << "\nPrevious Hash: " << previousHash << std::endl;
        Miner miner(int(index), argv[1], difficulty, previousHash);
        std::cout << "Mining Block " << index << " ..." << std::endl; 
        miner.mineBlock();    
        miner.printAll();
        packetP.clear();
        // packetP << miner.getHash() << killCommand << sender << command;
        packetP << sender << command << miner.getHash() <<  miner.getBlockData() << miner.getCreationTimeAsString() << miner.getPreviousHash() << killCommand << sf::Uint32(miner.getBlockIndex());
        sendToServer.send(packetP);
    } else if(command == 1) {
        packetP.clear();
        packetP << sender << command;
        sendToServer.send(packetP);
        packetP.clear();
    }

    return 0;
}

//NOTES
        //to have a terminate signal. 
        //can have a shared variable that tells thread to terminate.
        //can use thread signalling maybe? 
        //store receive socket function here, make it non-blocking. 
        //or let them finish mining and then they can append the blcok and it'll fail. 
        //at worst client will finish mining and then it'll send out theblock. 
        //Depending on how block chain is implemeted server will just reject the block, 
        //saying your hash doesn't match the latest blcok or server will create a new branch on 
        //th chain and then we have two branches on the chain. Then we can let the users decide which branch wins -- 
        //one soltuion would be that longer branch wins. 
        //

        //Proof of work is just grabbing the proposal number in terms of Paxos. 
        //More complicated part is resolving conflicts so every node is in the same state. 