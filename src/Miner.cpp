#include "Miner.hpp"

Miner::Miner(int blockIndexPassed, const std::string &blockDataPassed, const int blockMiningDifficultyPassed, const std::string previousBlockHashPassed) 
: blockIndex(blockIndexPassed), blockData(blockDataPassed), previousBlockHash(previousBlockHashPassed),
 blockMiningDifficulity(blockMiningDifficultyPassed), 
 creationTime(time(nullptr)), blockNOnce(-1), creationTimeAsString(ctime(&creationTime)), blockHash(" ")
{

}

void Miner::printAll() {
    std::cout << "Printed Value: *****************************************************" << std::endl;
    std::cout 
                << "BLOCK INDEX: " << blockIndex 
                << "\nBLOCK DATA: " << blockData 
                << "\nBLOCK MINING DIFFICULTY: " << blockMiningDifficulity 
                << "\nBLOCK CREATION TIME AS STRING: " << creationTimeAsString 
                << "BLOCK NONCE: " << blockNOnce 
                << "\nTHIS BLOCK HASH: " << blockHash
                << "\nPREVIOUS BLOCK HASH: " << previousBlockHash
                << 
    std::endl;
    std::cout << "Printed Value: *****************************************************\n" << std::endl;
}

void Miner::mineBlock() {
    
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
        blockHash = calculateHash();
    } while (blockHash.substr(0, blockMiningDifficulity) != stringOfZereos);

    std::cout << "Block mined: " << blockHash << std::endl;
} //end minerBlock

//declared inline for efficiency
inline std::string Miner::calculateHash() const {
    std::stringstream stringStream;
    stringStream << blockIndex << creationTimeAsString << blockData << blockNOnce << previousBlockHash;
    return sha256(stringStream.str());
}

std::string Miner::getHash() {
    return blockHash;
}

std::string Miner::getPreviousHash() {
    return previousBlockHash;
}

std::string Miner::getBlockData() {
    return blockData;
}

std::string Miner::getCreationTimeAsString() {
    return creationTimeAsString;
}

int Miner::getBlockIndex() {
    return blockIndex;
}