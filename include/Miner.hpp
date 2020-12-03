#ifndef __MINER__
#define __MINER__

#include "sha256.h"
#include <iostream>
#include <sstream>

class Miner {
    public:
        Miner(int blockIndexPassed, const std::string &blockDataPassed, const int blockMiningDifficulityPassed);
        void mineBlock(const std::string previousHash);
        void printAll(); // This method is just for testing. 
        std::string getHash(); //for testing purposes. 
    private:
        int blockIndex; //index of block being mined. Can be acquired by client from server. Will contribute to block's unique hash.
        time_t creationTime; //time of node creation. Will contribute to block's unique hash. 
        std::string blockData; //simple representation of data to be stored in block. 
        int blockNOnce; //keeps track of number of unique values tested against the block's hash, until the correct hash is found. 
        std::string blockHash; //hash that will be returned identify that the Proof of Work is complete. 
        int blockMiningDifficulity; //The number of zeros prior to the has that'll determine the difficulity to mine the block.  

        std::string calculateHash(const std::string previousHash) const; //function used to calculate private hash. This will be used by the mining function to determine if the block has been mined (Proof of Work).
        
};

#endif