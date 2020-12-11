#include "Block.hpp"

Block::Block(double timeSpentMiningPassed, int blockIndexPassed, std::string creationTimePassed,
     std::string dataPassed, std::string previousHashPassed, std::string blockHashPassed, std::string clientNamePassed) {
    timeSpentMining = timeSpentMiningPassed; //total time spent mining. 
    blockIndex = blockIndexPassed; //index of block in blockchain. 
    creationTime = creationTimePassed; //creation time of block determined by when mining started. 
    data = dataPassed; //Data client sent to the blockchain to store in a block.
    previousHash = previousHashPassed; //previousHash of last block in the blockchain. 
    blockHash = blockHashPassed; //current hash of this block 
    clientName = clientNamePassed; //name of the client who this block belongs to.

}

std::string Block::getBlockHash() {
    return blockHash;
}

void Block::printAll() {
    std::cout << "Time Spent Minning: " << timeSpentMining  
            << "\nBlock Index: " << blockIndex 
            << "\nCreation Time: " << creationTime 
            << "Data: " << data 
            << "\nPrevious Hash: " << previousHash 
            << "\nThis hash: " << blockHash 
            << "\nClient Name: " << clientName << std::endl;
}