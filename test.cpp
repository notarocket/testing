#include "test.h"
#include<stdio.h>
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

const int NUM_INDIVIDUAL = 90;
const int LENGTH = 100;
const int NUM_GENE = 100;



int main(){
    int times = 0;
    vector< int > arr;
    vector<testStruct> population;
    for(int i = 0; i < NUM_INDIVIDUAL; i++){
        arr = gen_individual(NUM_GENE, LENGTH);
        float num = 1.0f;
        population.push_back({i, arr, 1});
    }

    population[12].fitness+= 0.1;
    for (char i: population[52].genome){
        cout << i << ' ';
    }
    float lowestFitness = 1;
    float highestFitness = 0;
    testStruct bestIndividual;
    vector<vector<numRanks>> rankedNums; 
    while(lowestFitness > 0){
        for (int i = 0; i< NUM_INDIVIDUAL; i++){
            population[i].fitness = game(population[i].genome);

            if(population[i].fitness > highestFitness){
                highestFitness = population[i].fitness;
            }

            if(population[i].fitness < lowestFitness){
                lowestFitness = population[i].fitness;
                bestIndividual = population[i];
            }
        

        }
        if(lowestFitness != 0){
            times++;
            vector<int> popsToBeReplaced;
            for (int i = 0; i < NUM_INDIVIDUAL; i++){
                if(population[i].fitness >= highestFitness){
                    popsToBeReplaced.push_back(population[i].id);
                }
            }
            pair<vector<testStruct>, vector<vector<numRanks>>> population_ranked_nums = randomizeandreplace(population, popsToBeReplaced,rankedNums);
            population.clear();
            population = get<vector<testStruct>>(population_ranked_nums);
            rankedNums = get<vector<vector<numRanks>>>(population_ranked_nums);
            cout << lowestFitness;
            
        }

    }
    cout << "test";
}



float game(vector< int > genome){
    int numbers[NUM_GENE]; 
    int first = 1;
    int second = 1;
    int result = 0;
    float fitness = 1;
    for(int i = 0; i<NUM_GENE; i++){ 
        result = first + second;
        first = second;
        second = result;
        numbers[i] = result;
    }
    for(int i = 0; i<NUM_GENE; i++){
        if(genome[i] == numbers[i]){
            fitness = fitness -  (1/(double)NUM_GENE);         
        }
    }
    return fitness;
}   

std::pair<vector<testStruct>, vector<vector<numRanks>>> randomizeandreplace(vector<testStruct> population, vector<int> replacePops, vector<vector<numRanks>> rankedNums){
    vector<vector<int>> newGenomes ;
    vector<vector<testStruct>> rankedPops;
    float fitness = 1;
    for(int i=0; i < NUM_GENE; i++){
        rankedPops.push_back({});
        for(int x = 0; x < NUM_INDIVIDUAL; x++){
            if(population[x].fitness == fitness){
                rankedPops[i].push_back(population[x]);
            } 
        
        }
        fitness = fitness - (1/(double)NUM_GENE);
        
    }
    vector<vector<int>> nums;
    vector<int> blNums;
    for(int i=0; i < NUM_GENE; i++){
        if(rankedNums.size() < NUM_GENE){
            rankedNums.push_back({});
        }
        for(testStruct badNum : rankedPops[0]){
            rankedNums[i].push_back({badNum.genome[i],0,true});    
            blNums.push_back(badNum.genome[i]);
        }
       
        nums.push_back({});
        for(int x = NUM_GENE-1; x > 0; x--){
            for(testStruct pop : rankedPops[x]){
                if(find(blNums.begin(), blNums.end(), pop.genome[i])==blNums.end()){
                    nums[i].push_back(pop.genome[i]);
                } 
                
                
            }
        }
        blNums.clear();
        
    }
    for(int lvl = 0; lvl < nums.size(); lvl++){
        for(int c = 0; c<nums[lvl].size(); c++){
            bool isFound = false;
            for(int lol = 0; lol < rankedNums[lvl].size(); lol++){
                if(nums[lvl][c] == rankedNums[lvl][lol].num){
                    rankedNums[lvl][lol].rank++;
                    isFound = true;
                }
            }
            if(!isFound){
                rankedNums[lvl].push_back({nums[lvl][c],0,false});
            }
        }
    }
    vector<vector<int>> corrNums;
    for(int i = 0; i<NUM_GENE;i++){
        corrNums.push_back({});
        for(numRanks nr : rankedNums[i]){
            if(nr.isBlacklisted == false && find(corrNums[i].begin(), corrNums[i].end(), nr.num)==corrNums[i].end()){
                corrNums[i].push_back(nr.num);
            }
        }
    }
    vector<testStruct> new_pops;
    for(int i = 0; i < NUM_INDIVIDUAL; i++){
        new_pops.push_back({i,gen_individual_smart(NUM_GENE, corrNums, rankedNums, LENGTH),1});
    }
    std::pair<vector<testStruct>, vector<vector<numRanks>>> pair = make_pair(new_pops,rankedNums);
    return pair;


}


