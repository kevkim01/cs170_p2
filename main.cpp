#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include "limits.h"
#include "instance.h"
#include "problem.h"

using namespace std;


struct Feature_Set                                          //this struct holds the accuracy per feature set
{
    double accuracy;
    vector<int> feat_in;                                    //to print add 1 (stores indexes)
    
    const bool operator <(const Feature_Set& rhs) const     //comparator operator for p queue
    {
      return accuracy < rhs.accuracy;
    }
    
    
    const vector<int> inc_print(vector<int> b) const        //increments the features by 1 (stored as indexes)
    {
        vector <int> v = b;
        for(int i = 0; i < v.size(); ++i)
        {
            v.at(i) += 1;
        }
        return v;
    }
    
    const void print() const                                //prints out the features with corresponding accuracy
    {
        vector <int> v = inc_print(feat_in);
        ostringstream oss;
        
        if (!v.empty())
        {
            copy(v.begin(), v.end()-1, ostream_iterator<int>(oss, ","));
            oss << v.back();
        }
        cout << "features set {" << oss.str() <<"} with accuracy: " << accuracy << endl;
    }
};



vector<Instance> parse(string input_file)                   //handles the reading in of the file
{
    ifstream infile;
    infile.open(input_file.c_str());
    
    vector<Instance> v;                                     //vector of all data
    
    while(infile.good())
    {
        Instance inst;
        double type = INT_MAX;
        vector<double> features;
        double temp;
        
        string row;                                         //will hold entirety of one row
        getline(infile, row);                               //retreives info from file one line at a time
        
        istringstream parse(row);
        
        parse >> type;
        if(type == INT_MAX)
        {
            break;
        }
        
        inst.set_type(type);
        
        while(parse >> temp)
        {
            inst.append_feature(temp);                      //append features to object
        }
        
        v.push_back(inst);                                  //store a vector of all the rows
    }
    return v;
}


bool is_in(int index, vector<int> v)                        //returns if an index is in the vector of indexes
{
    for(int i = 0; i < v.size(); ++i)
    {
        if(index == v.at(i))
        {
            return true;
        }
    }
    return false;
}

void Forward(Problem prob, int size)                        //function to solve forward selection
{
    cout << "This dataset has " << size << " features with "
         << prob.dataset_size() << " Instances:" << endl << endl;
         
    priority_queue<Feature_Set> pri_que;                    //priority queue for the features set
    
    Feature_Set max;                                        //holds the value of the max accuracy per feature
    max.accuracy = 0;
    Feature_Set temp;
    vector<int> y;
    
    temp.feat_in = y;                                       //prints starting state of forward
    temp.accuracy = prob.Nearest_N(y);
    temp.print();
    
    bool warn = true;
    
    for(int j = 0; j < size; ++j)
    {
        for(int i = 0; i < size; ++i)
        {
            Feature_Set set;
            vector<int> sel_features = y;                   //selected features
            
            if(is_in(i,sel_features) == true)               //only push on featues if they arent in
            {
                continue;
            }
            sel_features.push_back(i);                      //push back on feature at a time onto selected features
            set.feat_in = sel_features;
            set.accuracy = prob.Nearest_N(sel_features);    //the set's accuracy set by NN(takes in features)
            pri_que.push(set);                              //push feature set onto the queue
        }
        temp = pri_que.top();
        if(temp.accuracy > max.accuracy)                    //keep track of the feature set with highest %
        {
            max = temp;
        }
        if(warn && temp.accuracy < max.accuracy)
        {
            warn = false;
            cout << endl<< "Warning: accuracy decreasing, continuing search..." << endl << endl;
        }
        temp.print();                                       //print
        y = temp.feat_in;
        
        while(!pri_que.empty())                             //clear entire queue, only concerned with highest %
        {
            pri_que.pop();
        }
    }
    cout <<endl<< "the best feature subset is "; max.print();
}


void Backward(Problem prob, int size)                        //function to solve forward selection
{
    cout << "This dataset has " << size << " features with "
         << prob.dataset_size() << " Instances:" << endl << endl;
         
    priority_queue<Feature_Set> pri_que;                    //priority queue for the features set
    
    Feature_Set max;                                        //holds the value of the max accuracy per feature
    max.accuracy = 0;
    Feature_Set temp;
    vector<int> y;
    
    for(int i = 0; i < size; ++i)
    {
        y.push_back(i);
    }
    temp.feat_in = y;                                       //prints out the starting state
    temp.accuracy = prob.Nearest_N(y);
    temp.print();
    
    bool warn = true;
    
    for(int j = 0; j < size; ++j)
    {
        for(int i = 0; i < size; ++i)
        {
            Feature_Set set;
            vector<int> sel_features = y;                   //selected features
            
            if(is_in(i,sel_features) == false)               //only push on featues if they arent in
            {
                continue;
            }
            sel_features.erase(remove(sel_features.begin(), sel_features.end(), i), sel_features.end());
            //sel_features.push_back(i);                      //push back on feature at a time onto selected features
            set.feat_in = sel_features;
            set.accuracy = prob.Nearest_N(sel_features);    //the set's accuracy set by NN(takes in features)
            pri_que.push(set);                              //push feature set onto the queue
        }
        temp = pri_que.top();
        if(temp.accuracy > max.accuracy)                    //keep track of the feature set with highest %
        {
            max = temp;
        }
        if(warn && temp.accuracy < max.accuracy)
        {
            warn = false;
            cout << endl<< "Warning: accuracy decreasing, continuing search..." << endl << endl;
        }
        temp.print();                                       //print
        y = temp.feat_in;
        
        while(!pri_que.empty())                             //clear entire queue, only concerned with highest %
        {
            pri_que.pop();
        }
    }
    cout <<endl<< "the best feature subset is "; max.print();
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
    int size = v.at(0).get_features().size();
    
    
    
    int input;
    cout << "Welcome to Kevin's Feature Selection Algorithm" << endl;
    cout << "Type the number of the selection algorithm you want" << endl;
    cout << "\t 1) Forward Selection" << endl;
    cout << "\t 2) Backward Elimination" << endl;
    cout << "\t 3) Kevin's Special Algorithm" << endl;
    
    cin >> input;

    if(input == 1)
    {
        Forward(prob, size);
    }
    else if(input == 2)
    {
        Backward(prob, size);
    }
    else
    {
        cout << "Kevins" << endl;
    }
    
    
    return 0;
}
