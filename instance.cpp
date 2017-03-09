#include <iostream>
#include "instance.h"

using namespace std;

Instance::Instance()
{
    type = 0;
}

void Instance::append_feature(double f)
{
    features.push_back(f);
    return;
}

void Instance::set_type(double i)
{
    type = i;
    return;
}

void Instance::print()
{
    cout << "type: " << type << endl;
    
    for(int i = 0; i < features.size(); ++i)
    {
        cout << features.at(i) << " ";
    }cout << endl;
    
    return;
}
