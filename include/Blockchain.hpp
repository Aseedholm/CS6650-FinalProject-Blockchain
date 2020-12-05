#ifndef __BLOCKCHAIN_HPP__
#define __BLOCKCHAIN_HPP__

#include <SFML/Network.hpp>
#include <vector>
#include <map>

#include "Block.hpp"

struct ServerData {
    sf::IpAddress ipAddress;
    int portNumber;
};

class Blockchain {
    private:
        int serverId;
        sf::TcpListener clientListeningSocket; 
        sf::TcpSocket serverConnectionToClient;
        sf::Socket::Status serverStatus;
        std::unique_ptr<sf::TcpSocket> otherServerSockets;
        std::map<int , struct ServerData> serverInfo;
        int portListeningAtNumber;

        std::vector<Block> blockChain; //log of blocks
        sf::Packet informationToBroadcast;

        bool initialConnection; 

        //vector of ips
        //vector of ports 
    public:
        Blockchain();
        // ~Blockchain();
        void addBlock(const Block& blockToBeAdded); //Method to add a block to the Server. 
        void sendBlock(); //This is the method to broadcast a block to other servers. 
        void sendInformationToClient(); //Method will send the client the index of the block they are to mine and the previous hash. 
        void receiveInformationFromClient(int port); //While loop of receiving information. 
        void setServerInfoData(sf::IpAddress ipAddressPassed, int portNumberPassed, int otherServerId);

    //one socket for client - server listening for client.

    //vector of sockets for connecting to other servers
    //5 servesr - all have one static boolean - primary - false

    //sockets non blocking 
    //server wilkl accept blcok based on first sent or timestamp. 

    //DESIGN
    //1 client socket in server for the client to connect to, this is server's listening socket. 
    //When a connection is established server will send client length of blockchain (index they'll be adding at), 
    //and previous hash for last node added to blcok chain. 

    //client will start mining after they receive info from server.

    //Once client is done mining it'll send block information to server including 

    //block creation time (time that mining started)
    //completion time (total time it took to mine.)
    //index we expect to add block at (this is the received value from server)
    //data that block shoudl contain. 
    //send previous block hash (this is the received value from server) compare it against the last expected block in the chain for 
    //  addition security. 
    //this blocks hash to prove that proof of work in complete
    //client name 

 

    //Blockchain that receives block information attempts to become primary. 
    //IT will try to broadcast information right away.
    //Once it has conesus from other Blockchains that it can add it to its log, it will append. 


    
};


#endif

//ServerMain -> Thread -> Blockchain 