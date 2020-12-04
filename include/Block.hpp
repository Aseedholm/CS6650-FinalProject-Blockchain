#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__
#include <chrono>
#include <string>

class Block{
private:
    //std::chrono duration<double>; 
    double timeSpentMining; //total time spent mining. 
    int blockIndex; //index of block in blockchain. 
    double creationTime; //creation time of block determined by when mining started. 
    std::string data; //Data client sent to the blockchain to store in a block.
    std::string previousHash; //previousHash of last block in the blockchain. 
    std::string blockHash; //current hash of this block 
    std::string clientName; //name of the client who this block belongs to.

public:
    Block(double timeSpentMiningPassed, int blockIndexPassed, double creationTimePassed,
     std::string dataPassed, std::string previousHashPassed, std::string blockHashPassed, std::string clientNamePassed);

    // ~Block();

    //getters
    const double getTimeSpentMining();
    const int getBlockIndex();
    const double getCreationTime();
    const std::string getDataPassed();
    const std::string getPreviousHash();
    const std::string getBlockHash();
    const std::string getClientName();

    //no setters since block is immutable, but it is supposed to be public. So information is accessible, but not changeable. 

};

#endif

//block creation time (time that mining started)
//completion time (total time it took to mine.)
//index we expect to add block at (this is the received value from server)
//data that block shoudl contain.
//send previous block hash (this is the received value from server) compare it against the last expected block in the chain for
//  addition security.
//this blocks hash to prove that proof of work in complete
//client name 