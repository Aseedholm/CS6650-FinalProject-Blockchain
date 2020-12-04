#include "Block.hpp"

Block::Block(double timeSpentMiningPassed, int blockIndexPassed, double creationTimePassed,
     std::string dataPassed, std::string previousHashPassed, std::string blockHashPassed, std::string clientNamePassed) {
    double timeSpentMining = timeSpentMiningPassed; //total time spent mining. 
    int blockIndex = blockIndexPassed; //index of block in blockchain. 
    double creationTime = creationTimePassed; //creation time of block determined by when mining started. 
    std::string data = dataPassed; //Data client sent to the blockchain to store in a block.
    std::string previousHash = previousHashPassed; //previousHash of last block in the blockchain. 
    std::string blockHash = blockHashPassed; //current hash of this block 
    std::string clientName = clientNamePassed; //name of the client who this block belongs to.

}

const std::string Block::getBlockHash() {
    return blockHash;
}