#include "Blockchain.hpp"

Blockchain::Blockchain(int port) {
    Block genesisBlock(0.0, 0, 0.0, "Genesis Block", "0", "1a2b3c4d5e6f7g8h9i", "Genesis Block");
    genesisBlock.printAll();
    addBlock(genesisBlock);
    informationToBroadcast.clear();
    // std::cout << blockChain.size() << std::endl;
    // blockChain[blockChain.size() - 1].printAll();
    // serverConnectionToClient;
    initialConnection = false;
    serverToServerSocket.setBlocking(false);
    serverStatus = clientListeningSocket.listen(port);
    
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
    
    // serverConnectionToClient.setBlocking(false);
    // while(serverStatus == sf::Socket::Done) {
        std::string passedString;
        sf::Uint32 killCommand = 0;
        std::string blockHash;
        std::string sender;
        
        while(true) {
            clientListeningSocket.accept(serverConnectionToClient);
            
            while(killCommand == 0) {

                if(initialConnection == false) {
                    sendInformationToClient();
                    initialConnection = true;
                }
                
                
                serverConnectionToClient.receive(informationToBroadcast);
                if(informationToBroadcast >> blockHash >> killCommand >> sender) {
                    
                    if (sender.compare("c") == 0) {
                        std::cout << "\nRECEIVED HASH FROM CLIENT: " << blockHash << "\nKillCommand: " << killCommand << "\nSENDER: " << sender << "\n" << std::endl;
                        // serverConnectionToClient.disconnect();
                        serverToServerSocket.connect(sf::IpAddress::getLocalAddress(), port);
                        informationToBroadcast.clear();
                        sender = "s";
                        informationToBroadcast << blockHash << killCommand << sender;
                        serverToServerSocket.send(informationToBroadcast);
                        informationToBroadcast.clear();
                        // serverToServerSocket.disconnect();
                        //NEW BLOCK TO ATTEMPT TO REPLICATE
                        //if new blocks index is already taken, then reject, if not then accept. 
                        Block block(1.1, blockChain.size(), 5.5, sender, blockChain[blockChain.size() -1].getBlockHash(), blockHash, sender);
                        addBlock(block);
                        blockChain[blockChain.size() - 1].printAll();
                        //NEW BLOCK TO ATTEMPT TO REPLICATE
                    } else if(sender.compare("s") == 0) {
                        std::cout << "\nRECEIVED HASH FROM SERVER: " << blockHash << "\nKillCommand: " << killCommand << "\nSENDER: " << sender << "\n" << std::endl;
                        Block block(1.1, blockChain.size(), 5.5, sender, blockChain[blockChain.size() -1].getBlockHash(), blockHash, sender);
                        addBlock(block);
                        //NEW BLOCK REPLICATED
                        blockChain[blockChain.size() - 1].printAll();
                        //NEW BLOCK REPLICATED
                        informationToBroadcast.clear();
                    }

                }
                // informationToBroadcast >> blockHash >> killCommand;

            }
            initialConnection = false;
            killCommand = 0;
            // clientListeningSocket.accept(serverToServerSocket);

        }
}