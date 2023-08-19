#ifndef TESTFUNCTIONS_H_INCLUDED
#define TESTFUNCTIONS_H_INCLUDED

#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

float Beale(vector<float> position)
{
    float funcionB;
    float x = position.at(0);
    float y = position.at(1);
    funcionB= pow(1.5 - x + x*y,2) + pow(2.25 - x + x*(y*y),2) + pow(2.625 - x + x*(y*y*y),2);
    return funcionB;
}

float GoldsteinPrice(vector<float> position)
{
    float funcionG;
    float x = position.at(0);
    float y = position.at(1);
    funcionG= ((1 + ((pow(x + y + 1,2)) * (19 - 14*x + 3*x*x - 14*y + 6*x*y + 3*y*y)) )
            * (30 + ((pow(2*x - 3*y,2))*(18 - 32*x + 12*x*x + 48*y - 36*x*y + 27*x*y)) ) );
    return funcionG;
}

float McCormick(vector<float> position)
{
    float funcionM;
    float x = position.at(0);
    float y = position.at(1);
    funcionM= sin(x + y) + (pow(x - y,2)) - 1.5*x + 2.5*y +1;
    return funcionM;
}

float EggHolder(vector<float> position)
{
    float funcionE;
    float x = position.at(0);
    float y = position.at(1);
    funcionE= -(y + 47)*sin(sqrt(abs(x/2 + (y + 47) ))) - x*sin(sqrt(abs(x - (y + 47))));
    return funcionE;
}

float Sphere(vector<float> position)
{
    float funcionS;
    for(size_t i=0; i<position.size(); i++)
        funcionS = funcionS + pow(position.at(i),2);
    return funcionS;
}

#endif // TESTFUNCTIONS_H_INCLUDED
