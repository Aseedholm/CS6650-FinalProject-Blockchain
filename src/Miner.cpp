#include "Miner.hpp"

Miner::Miner(int blockIndexPassed, const std::string &blockDataPassed, const int blockMiningDifficultyPassed) 
: blockIndex(blockIndexPassed), blockData(blockDataPassed), blockMiningDifficulity(blockMiningDifficultyPassed), creationTime(time(nullptr)), blockNOnce(-1)
{

}

void Miner::printAll() {
    std::cout << "BLOCK INDEX: " << blockIndex << "\nBLOCK DATA: " << blockData << "\nBLOCK MINING DIFFICULTY: " << blockMiningDifficulity << "\nBLOCK CREATION TIME: " << creationTime << "\nBLOCK NONCE: " << blockNOnce << std::endl;
}

void Miner::mineBlock(const std::string previousHash) {
    char zeroArray[blockMiningDifficulity + 1]; //will contain the number of zeroes according to the difficulty contained in the class that a miner must figure out to properly mine a block.
    for (int i = 0; i < blockMiningDifficulity; i++) {
        zeroArray[i] = '0';
    }

    zeroArray[blockMiningDifficulity] = '\0'; //set the escape character for a string contained in an array.  This is a NUL character. 

    std::string stringOfZereos(zeroArray);

    //while the calculated has doesn't have the proper number of zereos preceeding it, continue trying to solve this math problem.
    //This is the proof of work. 
    do {
        blockNOnce++;
        blockHash = calculateHash(previousHash);
    } while (blockHash.substr(0, blockMiningDifficulity) != stringOfZereos);

    std::cout << "Block mined: " << blockHash << std::endl;
} //end minerBlock

//declared inline for efficiency
inline std::string Miner::calculateHash(const std::string previousHash) const {
    std::stringstream stringStream;
    stringStream << blockIndex << creationTime << blockData << blockNOnce << previousHash;
    return sha256(stringStream.str());
}

std::string Miner::getHash() {
    return blockHash;
}