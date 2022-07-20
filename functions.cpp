#include "test.h"
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

int add(int x, int y){
    return x + y;
}

vector<int> gen_individual(int numGene, int length){
    vector<int> genome;
    for (int x = 0; x < numGene; x++){
        genome.push_back(0);
    }
    for(int i = 0; i < numGene; i++){
        genome[i] = rand() % (length+1) + 1;
    }
    return genome;

}

bool isBlackListedFunc(numRanks num){
    return num.isBlacklisted;

}

vector<int> gen_individual_smart(int numGene, vector<vector<int>> validNumbers, vector<vector<numRanks>> rankedNums, int LENGTH){
    vector<int> genome;
    for (int x = 0; x < numGene; x++){
        genome.push_back(0);
    }
    for(int i = 0; i < rankedNums.size(); i++){
        for(int x = 0; x < rankedNums[i].size()-1; x++){
            if(rankedNums[i].size() > 1){
                rankedNums[i].erase(std::remove_if(rankedNums[i].begin(), rankedNums[i].end(), isBlackListedFunc), rankedNums[i].end());
            }     
            
                        
        }
    }
    
    int randPer = rand() % 100;
    if(randPer > 35){

    for(int i = 0; i < numGene; i++){
        vector<int> numRanked;
        for(numRanks numR : rankedNums[i]){
            for(int u = 0; u < numR.rank+1; u++){
                int randDV = 0;
                if(numR.rank > 2){
                    randDV = rand() % numR.rank;
                }else{
                    randDV = 1;
                }
                if((double)randDV > (double)numR.rank*0.70){                
                    numRanked.push_back(numR.num);
                }
            }
        }
        if(numRanked.size()>1){
            genome[i] = numRanked[rand() % (numRanked.size())];
        }else{
            genome[i] = rand() % LENGTH;
        }
        numRanked.clear();
    }

    }else{
        genome = gen_individual(numGene, LENGTH);
    }
    return genome;
}


char* gen_board(int boardLength){
    char* str = (char*)malloc(boardLength * sizeof(char));
    for(int i = 0; i<sizeof(str); i++){
        str[i] = '-';
    }
    return str;
}

