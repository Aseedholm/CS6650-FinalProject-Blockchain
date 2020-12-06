#include "Miner.hpp"

Miner::Miner(int blockIndexPassed, const std::string &blockDataPassed, const int blockMiningDifficultyPassed) 
: blockIndex(blockIndexPassed), blockData(blockDataPassed), blockMiningDifficulity(blockMiningDifficultyPassed), creationTime(time(nullptr)), blockNOnce(-1)
{

}

void Miner::printAll() {
    std::cout << "Printed Value: *****************************************************" << std::endl;
    std::cout << "BLOCK INDEX: " << blockIndex << "\nBLOCK DATA: " << blockData << "\nBLOCK MINING DIFFICULTY: " << blockMiningDifficulity << "\nBLOCK CREATION TIME: " << creationTime << "\nBLOCK NONCE: " << blockNOnce << std::endl;
    std::cout << "Printed Value: *****************************************************\n" << std::endl;
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