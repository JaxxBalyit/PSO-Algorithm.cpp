#ifndef TOOLFUNCTIONS_H_INCLUDED
#define TOOLFUNCTIONS_H_INCLUDED

#include "Particle.h"
#include "testFunctions.h"

using namespace std;

vector<float> randGen(float lbj,float ubj, int N, int D, long seed) //Vectores de flotantes
{
    random_device rd;
    default_random_engine eng(seed);
    uniform_real_distribution<float> distribution(lbj,ubj);

    vector<float> componentes;
    for(int n=0; n<D*N; n++)
        componentes.push_back(distribution(eng));

  return componentes;
}

float randNumber(float lbj, float ubj, long seed)
{
    random_device rd;
    default_random_engine eng(seed);
    uniform_real_distribution<float> distribution(lbj,ubj);

    float randNum = distribution(eng);

    return randNum;
}

void printIteration(int Iteration, string functionName)
{
    string file_name = "Bitacora_"+functionName+".txt";
    ofstream fout;
    fout.open(file_name,fstream::app);
    fout<< "\n\n******* ITERACION #" << Iteration << " *******" <<endl;
    fout.close();
}

void printPopulation(vector<Particle> population,string functionName, string extra) //Checar la impresión de los datos
{
    string file_name = "Bitacora_"+functionName+".txt";
    ofstream fout;
    fout.open(file_name,fstream::app); //agregar para que no se borre cada una de las veces que se corre el archivo

    fout<<endl<< "Imprimiendo las primeras 3 líneas y las últimas 3 líneas" <<endl;

    for(size_t i=0; i<3; i++)
        fout<< population.at(i).imprimirDatos() <<endl;

    fout<< "...líneas omitidas..." <<endl;
    for(size_t i=population.size()-3; i<population.size(); i++)
        fout<< population.at(i).imprimirDatos() <<endl;
    fout.close();
}

/****************************Aux Functions****************************/
vector<float> suma(vector<float> u,vector<float> v)
{
    vector<float> r;
    for(size_t i=0; i<u.size(); i++)
        r.push_back(u.at(i) + v.at(i));

    return r;
}

vector<float> resta(vector<float> u,vector<float> v)
{
    vector<float> r;
    for(size_t i=0; i<u.size(); i++)
        r.push_back(u.at(i) - v.at(i));

    return r;
}

vector<float> escalar(float k,vector<float> u)
{
    vector<float> r;
    for(size_t i=0; i<u.size(); i++)
        r.push_back(k * u.at(i));

    return r;
}
/***********************************************************************/

/*************************Función de separación*************************/
//Esta parte es de la práctica 7, y es reciclado
template<typename Out>
void split(const string &s,char delim, Out result)
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string & s, char delim)
{
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}
/**********************************************************************/
#endif // TOOLFUNCTIONS_H_INCLUDED
