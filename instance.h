#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <vector>

using namespace std;

class Instance
{
    private:
        double type;                    //type of instance (1 or 2)
        vector<double> features;        //holds all of the features per row
        
    public:
        Instance();                     //constructor
        void append_feature(double);    //appends features to vector
        void set_type(double);          //set function for class type
        void print();
        
};

#endif
