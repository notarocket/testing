#include <vector>

#ifndef TEST_H
#define TEST_H

using namespace std;

struct testStruct {
    int id;
    vector<int> genome;
    float fitness;
};

struct numRanks {
    int num;
    int rank;
    bool isBlacklisted;
};

struct numExists{
    int pos;
    bool exists;
};

int add(int,int);
std::vector<int> gen_individual(int, int);
char* gen_board(int);
float game(std::vector<int>);
std::pair<vector<testStruct>, vector<vector<numRanks>>> randomizeandreplace(vector<testStruct>, vector<int>,  vector<vector<numRanks>>);
vector<int> gen_individual_smart(int, vector<vector<int>>, vector<vector<numRanks>>, int);
bool isBlackListedFunc(numRanks);
#endif