#include "Blockchain.hpp"

Blockchain::Blockchain() {
    Block genesisBlock(0.0, 0, 0.0, "Genesis Block", "0", "1a2b3c4d5e6f7g8h9i", "Genesis Block");
    initialConnection = false;
    
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
    informationToBroadcast << sf::Uint32(blockChain.size()) << blockChain[blockChain.size() - 1].getBlockHash();
    serverConnectionToClient.send(informationToBroadcast);
    informationToBroadcast.clear();
}

void Blockchain::receiveInformationFromClient(int port) {
    serverStatus = clientListeningSocket.listen(port);
    serverConnectionToClient.setBlocking(false);
    // while(serverStatus == sf::Socket::Done) {
        std::string passedString;
        clientListeningSocket.accept(serverConnectionToClient);
        // sendInformationToClient();
        // serverConnectionToClient.receive(informationToBroadcast);
        // informationToBroadcast << passedString;
        // if(serverStatus == sf::Socket::Done) {
        //     while(true) {
                
        //         clientListeningSocket.
        //     }
        // }
    // }

}