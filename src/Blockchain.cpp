#include "Blockchain.hpp"

Blockchain::Blockchain() {
    Block genesisBlock(0.0, 0, 0.0, "Genesis Block", "0", "1a2b3c4d5e6f7g8h9i", "Genesis Block");
    genesisBlock.printAll();
    addBlock(genesisBlock);
    informationToBroadcast.clear();
    // std::cout << blockChain.size() << std::endl;
    // blockChain[blockChain.size() - 1].printAll();
    // serverConnectionToClient;
    initialConnection = false;
    serverToServerSocket.setBlocking(false);
    
}


void Blockchain::addBlock(const Block& block){
    blockChain.push_back(block);
}

void Blockchain::setServerInfoData(sf::IpAddress ipAddressPassed, int portNumberPassed, int otherServerId){
    ServerData data;
    data.ipAddress = ipAddressPassed;
    data.portNumber = portNumberPassed;
    serverInfo.insert({otherServerId, data});
}


void Blockchain::sendInformationToClient() {
    std::cout << "BLOCK CHAIN SIZE: " << sf::Uint32(blockChain.size()) << "\nBLOCK CHAIN HASH: " << blockChain[blockChain.size() - 1].getBlockHash() << std::endl;
    informationToBroadcast << sf::Uint32(blockChain.size()) << blockChain[blockChain.size() - 1].getBlockHash();
    serverConnectionToClient.send(informationToBroadcast);
    informationToBroadcast.clear();
}

void Blockchain::receiveInformationFromClient(int port) {
    serverStatus = clientListeningSocket.listen(port);
    // serverConnectionToClient.setBlocking(false);
    // while(serverStatus == sf::Socket::Done) {
        std::string passedString;
        sf::Uint32 killCommand = 0;
        std::string blockHash;
        
        while(true) {
            clientListeningSocket.accept(serverConnectionToClient);
            
            while(killCommand == 0) {

                if(initialConnection == false) {
                    sendInformationToClient();
                    initialConnection = true;
                }
                
                
                serverConnectionToClient.receive(informationToBroadcast);
                if(informationToBroadcast >> blockHash >> killCommand) {
                    std::cout << "RECEIVED HASH FROM CLIENT: " << blockHash << "\nKillCommand: " << killCommand << std::endl;
                    serverConnectionToClient.disconnect();
                    serverToServerSocket.connect(sf::IpAddress::getLocalAddress(), 8080);
                    serverToServerSocket.send(informationToBroadcast);
                    informationToBroadcast.clear();
                }
                // informationToBroadcast >> blockHash >> killCommand;

            }
            initialConnection = false;
            killCommand = 0;
            // clientListeningSocket.accept(serverToServerSocket);

        }
}