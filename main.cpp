#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "limits.h"
#include "instance.h"
#include "problem.h"

using namespace std;

vector<Instance> parse(string input_file)
{
    ifstream infile;
    infile.open(input_file.c_str());
    
    vector<Instance> v;                 //vector of all data
    
    while(infile.good())
    {
        Instance inst;
        double type = INT_MAX;
        vector<double> features;
        double temp;
        
        string row;                         //will hold entirety of one row
        getline(infile, row);               //retreives info from file one line at a time
        
        istringstream parse(row);
        
        parse >> type;
        if(type == INT_MAX)
        {
            break;
        }
        
        inst.set_type(type);
        
        while(parse >> temp)
        {
            inst.append_feature(temp);      //append features to object
        }
        
        v.push_back(inst);                  //store a vector of all the rows
    }
    
    return v;
}


int main(int argc, char*argv[])
{
    if(argc != 2)
    {
        cout << "Error: Invalid program call" << endl;
        return 1;
    }
    string file_name(argv[0]);
    string input_file(argv[1]);
    
    vector<Instance> v = parse(input_file);
    
    Problem prob(v);
    int input;
    cout << "Welcome to Kevin's Feature Selection Algorithm" << endl;
    cout << "Type the number of the selection algorithm you want" << endl;
    cout << "\t 1) Forward Selection" << endl;
    cout << "\t 2) Backward Elimination" << endl;
    cout << "\t 3) Kevin's Special Algorithm" << endl;
    
    cin >> input;

    if(input == 1)
    {
        cout << "forward" << endl;
    }
    else if(input == 2)
    {
        cout << "backard" << endl;
    }
    else
    {
        cout << "Kevins" << endl;
    }


    return 0;
}
