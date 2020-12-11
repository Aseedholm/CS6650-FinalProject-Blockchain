#include "Blockchain.hpp"

Blockchain::Blockchain(int port) {
    Block genesisBlock(0.0, 0, "0.0", "Genesis Block", "0", "1a2b3c4d5e6f7g8h9i", "Genesis Block");
    // genesisBlock.printAll();
    addBlock(genesisBlock);
    informationToBroadcast.clear();
    serverResponsePacket.clear();
    initialConnection = false;
    serverPort = port;
    serverStatus = listeningSocket.listen(serverPort);
    // serverCommunicationSocket.setBlocking(false);
    // serverCommunicationSocket.listen(serverPort);
    
}

void Blockchain::setSocketVector() {
    int mapSize = (int)serverInfo.size();
    for (int i = 0; i < mapSize; i++) {
        std::unique_ptr<sf::TcpSocket> socketToAdd = std::unique_ptr<sf::TcpSocket>(new sf::TcpSocket);
        otherServerSockets.push_back(std::move(socketToAdd));
    }
}

void Blockchain::connectAndSend() {
    std::map<int , struct ServerData>::iterator it = serverInfo.begin();
    int iterator = 0;
    for (it; it != serverInfo.end(); it++) {
        otherServerSockets[iterator]->connect(it->second.ipAddress, it->second.portNumber);
        otherServerSockets[iterator]->send(informationToBroadcast);
        //may want to disconnect sockets after sending information.

        serverResponsePacket.clear();
        otherServerSockets[iterator]->receive(serverResponsePacket);
        std::string response;
        serverResponsePacket >> response;
        std::cout << "SERVER: " << it->second.portNumber << " RESPONSE: " << response << std::endl;

        iterator+=1;

    }
}
void Blockchain::addBlock(const Block& block){
    blockChain.push_back(block);
}

void Blockchain::setServerInfoData(sf::IpAddress ipAddressPassed, int portNumberPassed, int otherServerId) {
    ServerData data;
    data.ipAddress = ipAddressPassed;
    data.portNumber = portNumberPassed;
    serverInfo.insert({otherServerId, data});
}


void Blockchain::sendInformationToClient() {
    std::cout << "Sending to client: BLOCK CHAIN SIZE: " 
            << sf::Uint32(blockChain.size()) << "\nBLOCK CHAIN HASH: " 
            << blockChain[blockChain.size() - 1].getBlockHash() 
            << std::endl;
    informationToBroadcast.clear();
    informationToBroadcast << sf::Uint32(blockChain.size()) << blockChain[blockChain.size() - 1].getBlockHash();
    connectionSocket.send(informationToBroadcast);
    informationToBroadcast.clear();
}

void Blockchain::receiveRequestFromClient() {
    std::string sender;
    sf::Uint32 command;
    std::string minedHash;
    std::string clientData;
    std::string creationTime;
    std::string previousHashPassed;
    sf::Uint32 killCommand;
    sf::Uint32 blockIndex;

    if(informationToBroadcast >> command ) {

        if (command == 0) {
            if(informationToBroadcast >> minedHash 
                >> clientData >> creationTime 
                >> previousHashPassed >> killCommand >> blockIndex) 
            {
                std::cout << "RECEIVED HASH FROM CLIENT: " << minedHash 
                        << "\nKillCommand: " << killCommand 
                        << "\nSENDER: " << sender 
                        << "\nCommand: " << command 
                        << "\nClient Data: " <<clientData
                        << "\nCreation Time: " << creationTime
                        << "Previous Hash Passed: " << previousHashPassed
                        << "\nBlock Index: " << blockIndex
                        << std::endl;
                informationToBroadcast.clear();
                sender = "s";
                informationToBroadcast << sender << command << minedHash << clientData 
                << creationTime << previousHashPassed << killCommand << blockIndex << std::to_string(serverPort);
                connectAndSend();
                
                informationToBroadcast.clear();
                Block block(0.0, blockIndex, creationTime, clientData, previousHashPassed, minedHash, std::to_string(serverPort));
                if(blockChain.size() == blockIndex) {
                    addBlock(block);
                    std::cout << "\nBelow is block being sent to other servers." << std::endl;
                    blockChain[blockChain.size() - 1].printAll();
                }

                //Set up a receive call here. 
                //if server accepted request move on
                //if server rejected request remove the newly added block, then it will add other block.

            }           
        }
        else if (command == 1) {
            printBlockChain();
        }
    }
}


void Blockchain::receiveRequestFromServer() {
    std::string sender;
    sf::Uint32 command;
    std::string minedHash;
    std::string clientData;
    std::string creationTime;
    std::string previousHashPassed;
    sf::Uint32 killCommand;
    sf::Uint32 blockIndex;
    std::string sendingServerPort;

    if(informationToBroadcast >> command >> minedHash >> clientData >> creationTime >> previousHashPassed >> killCommand >> blockIndex >> sendingServerPort) {
        std::cout << "RECEIVED HASH FROM SERVER: " << minedHash 
        << "\nKillCommand: " << killCommand 
        << "\nSENDER: " << sender 
        << "\nCommand: " << command 
        << "\nClient Data: " <<clientData
        << "\nCreation Time: " << creationTime
        << "Previous Hash Passed: " << previousHashPassed
        << "Block Index: " << blockIndex 
        << "\nSending Server Port: " << sendingServerPort << std::endl;

        informationToBroadcast.clear();
        Block block(0.0, blockIndex, creationTime, clientData, previousHashPassed, minedHash, sendingServerPort);
        if(blockChain.size() == blockIndex) { 

            serverResponsePacket.clear();
            serverResponsePacket << "Accepted";
            // connectionSocket.send(serverResponsePacket);
            sendMessage(std::stoi(sendingServerPort));
            serverResponsePacket.clear();

            addBlock(block);
            std::cout << "**********************FROM OTHER SERVER**********************" << std::endl;
            blockChain[blockChain.size() - 1].printAll();
            std::cout << "**********************FROM OTHER SERVER**********************" << std::endl;
        } else {
            //send reject message to Server that sent message. 

            serverResponsePacket.clear();
            serverResponsePacket << "Rejected";
            sendMessage(std::stoi(sendingServerPort));
            // connectionSocket.send(serverResponsePacket);
            serverResponsePacket.clear();
        }
        

        //NEW BLOCK TO ATTEMPT TO REPLICATE
    }
}

void Blockchain::sendMessage(int portNumberPassed) {
    // std::map<int , struct ServerData>::iterator it = serverInfo.begin();
    // int iterator = 0;
    // for (it; it != serverInfo.end(); it++) {
    //     if(it->second.portNumber == portNumberPassed) {
    //         otherServerSockets[iterator]->connect(it->second.ipAddress, it->second.portNumber);
    //         otherServerSockets[iterator]->send(serverResponsePacket);
    //     }

    //     // //may want to disconnect sockets after sending information.

    //     // serverResponsePacket.clear();
    //     // otherServerSockets[iterator]->receive(serverResponsePacket);
    //     // std::string response;
    //     // serverResponsePacket >> response;
    //     // std::cout << "SERVER: " << it->second.portNumber << " RESPONSE: " << response << std::endl;

    //     iterator+=1;

    // }
    connectionSocket.send(serverResponsePacket);
}

void Blockchain::receiveInformation() {

        std::string passedString;
        sf::Uint32 killCommand = 0;
        sf::Uint32 command = 0;
        std::string blockHash;
        std::string sender;
        sf::Socket::Status status;
        while(true) {
            status = listeningSocket.accept(connectionSocket);
                if(status == 0) {
                    sendInformationToClient();
                    initialConnection = true;
                }
                connectionSocket.receive(informationToBroadcast);
                if(informationToBroadcast >> sender) {
                    std::cout << "**********************************************" << std::endl;
                    if (sender.compare("c") == 0) 
                    {
                        receiveRequestFromClient();
                    } 

                    else if(sender.compare("s") == 0) 
                    {
                        receiveRequestFromServer();
                    }
                    std::cout << "**********************************************" << std::endl;
                }
        }
}

void Blockchain::printBlockChain() {
    std::cout << "*Printing Blockchain*" << std::endl;
    std::vector<Block>::iterator itBegin = blockChain.begin();
    std::vector<Block>::iterator itEnd = blockChain.end();
    for(itBegin; itBegin != itEnd; itBegin++){
        itBegin->printAll();
        std::cout << "\n";
    }
    std::cout << "*Printing Blockchain*" << std::endl;
}