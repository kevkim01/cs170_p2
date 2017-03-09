#include <iostream>
#include <vector>
#include "instance.h"

using namespace std;

class Problem
{
    private:
        vector<Instance> dataset;        //vector that holds the dataset
        
    public:
        Problem(vector<Instance>);
};
