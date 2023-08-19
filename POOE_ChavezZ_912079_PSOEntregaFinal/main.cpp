/*
Autor: Ch�vez Zepeda Jos� Emmanuel
Fecha: 18.05.2022
Tema: Algoritmo Metaheur�stico de PSO Entrega Final

En esta pr�ctica se har� el cuarto avance de la implementaci�n de la clase 'Part�cula',
las funciones solicitadas (5), y la impresi�n en archivo de los estados de la part�cula,
las actualizaciones de las part�culas y la impresi�n de las actualizaciones.
A su vez, cada una de las funciones tendr� su propia bit�cora, y los datos ser�n le�dos
desde un archivo de texto llamado 'configPSO.txt'.
*/

#include "testFunctions.h"
#include "Particle.h"
#include "toolFunctions.h"

int main()
{
    //Implementaci�n del PSO
    int N; //N�mero de part�culas
    int D=2; //Dimensiones (Dominio en R^D)
    int maxIter; //N�mero m�ximo de iteraciones
    string functionName;  //Sirve para los apuntadores a funci�n
    vector<float> lb;  //Cota inferior
    vector<float> ub;  //Cota superior

    //Lectura del archivo "configPso.txt"
    ifstream fin("configPSO.txt");
    string line;
    vector<string> tokens, shortTokens;

    //Lectura de cada l�nea del archivo
    while(getline(fin, line))
    {
        //Separaci�n por tokens
        tokens = split(line, '=' );

        //Dependiendo del par�metro, se asignan los valores
        if(tokens.at(0)=="N")
            N=stof(tokens.at(1));
        if(tokens.at(0)=="maxIt")
            maxIter=stof(tokens.at(1));
        if(tokens.at(0)=="fitnessFunction")
            functionName=tokens.at(1);
        if(tokens.at(0)=="lowerBound")  //asignaci�n de las cotas
            {
                shortTokens = split(tokens.at(1),',');
                for(size_t i=0; i<shortTokens.size(); i++)
                    lb.push_back(stof(shortTokens.at(i)));
                shortTokens.clear();
            }
        if(tokens.at(0)=="upperBound")  //asignaci�n de las cotas
            {
                shortTokens = split(tokens.at(1),',');
                for(size_t i=0; i<shortTokens.size(); i++)
                    ub.push_back(stof(shortTokens.at(i)));
                shortTokens.clear();
            }
    }

    //Asignaci�n de la funci�n fitness
    float(*functionFitness)(vector<float> position) = Sphere;  //funci�n por defecto

    if(functionName=="sphere")
        functionFitness = Sphere;
    else if(functionName=="beale")
        functionFitness = Beale;
    else if(functionName=="goldsteinprice")
        functionFitness = GoldsteinPrice;
    else if(functionName=="mccormick")
        functionFitness = McCormick;
    else if(functionName=="eggholder")
        functionFitness = EggHolder;

    //Bienvenida al programa
    cout<< "Bienvenido, usuario. \nEste codigo nos servira para implementar el algoritmo" <<endl
        << "metaheuristico del PSO (Particle Swarm Optimization)." <<endl<<endl;
    cout<< "Para poder cambiar los parametros de numero de particulas, funcion, cantidad" <<endl
        << "de iteraciones, cotas de evaluacion, etc., es necesario que se acceda al archivo" <<endl
        << "llamado 'configPSO.txt', y desde ahi se cambien los valores deseados." <<endl<<endl;
    system("pause");
    system("cls");

    cout<< "Generando archivo de Bitacora, el cual tiene la informacion de las particulas." <<endl;

//Paso1. CREANDO POBLACI�N INICIAL
    vector<Particle> population;

    vector<float> componentes = randGen(lb.at(0),ub.at(0),N,D,123L);

    vector<float> posTemp;
    for(int i=0; i<N; i++)
    {
        Particle pTemp = Particle(i);

        //Asignaci�n de aleatorios a las part�culas
        for(int j=0; j<D; j++)
            posTemp.push_back(componentes.at(j));

        pTemp.setPosition(posTemp);
        pTemp.setBestPosition(posTemp);

        //Asignaci�n de las part�culas a la poblaci�n
        population.push_back(pTemp);
        posTemp.clear();
    }

//Paso 2. ITERACIONES DEL PSO
    for(int i=1; i<=maxIter; i++)
    {
        printIteration(i,functionName);

    //Paso 3.  EVALUACIONES CON LAS FUNCIONES DE TESTEO PARA LAS PART�CULAS
        for(size_t i=0; i<population.size(); i++)
        {
            population.at(i).setFitness(Sphere(population.at(i).getPosition() ));

            if(population.at(i).getBestFitness() == 0)
                population.at(i).setBestFitness(population.at(i).getFitness() );

    //Paso 4. COMPARACION DEL FITNESS VS BESTFITNESS (ACTUALIZACIONES)
            if(population.at(i).getFitness() < population.at(i).getBestFitness() )
            {
                population.at(i).setBestFitness(population.at(i).getFitness());
                population.at(i).setBestPosition(population.at(i).getPosition());
            }
        }

    printPopulation(population, functionName, " Valores sin ordenar.");

    //Paso 5. IDENTIFICACI�N DE LA PART�CULA CON EL MEJOR FITNESS Y DARLE LOS ATRIBUTOS A BESTPARTICLE
        sort(population.begin(), population.end());

        Particle bestParticle = Particle();

        bestParticle.m_id = population.at(0).m_id;
        bestParticle.setFitness(population.at(0).getFitness());
        bestParticle.setBestFitness(population.at(0).getBestFitness());
        bestParticle.setPosition(population.at(0).getPosition());
        bestParticle.setBestPosition(population.at(0).getBestPosition());
        bestParticle.setVelocity(population.at(0).getVelocity());

        //Impresi�n de la bit�cora con su respectiva ordenaci�n (fitness)
        printPopulation(population, functionName, " Valores ordenados por fitness");

    //Paso 6. ASIGNACI�N DE VELOCIDADES Y POSICIONES
      //Phi_1 y Phi_2 deben de ser iguales a 2.0

      vector<float> vTemp_1, vTemp_2;
      vector<float> res1, res2;
      vector<float> mult1, mult2;
      float random1, random2;
      float Phi_1=2.0, Phi_2=2.0;

      for(size_t i=0; i<population.size(); i++)
      {
          random1 = randNumber(0,Phi_1, 123L);
          random2 = randNumber(0, Phi_2, 123L);

          res1 = resta(population.at(i).getBestPosition(), population.at(i).getPosition());
          res2 = resta(bestParticle.getPosition(), population.at(i).getPosition());

          mult1 = escalar(random1, res1);
          mult2 = escalar(random2, res2);

          vTemp_1 = suma(mult1, mult2);

          //Asignaci�n de velocidad a las part�culas
          population.at(i).setVelocity( suma(population.at(i).getVelocity(), vTemp_1) );

          //Asignaci�n de posici�n a las part�culas
          population.at(i).setPosition( suma(population.at(i).getPosition(), population.at(i).getVelocity()) );
      } //Finalizaci�n del Paso 6

      printPopulation(population, functionName, " Poblacion Actualizada");

      //Acotamiento para que las part�culas no salgan del espacio de b�squeda
      for(size_t i=0; i<population.size(); i++)
      {
          posTemp = population.at(i).getPosition();
          for(int j=0; j<D; j++)
          {
              if(posTemp.at(j) < lb.at(j))
                posTemp.at(j) = lb.at(j);
              if(posTemp.at(j) > ub.at(j))
                posTemp.at(j) = ub.at(j);
          }
          population.at(i).setPosition(posTemp);
      }
    } //Finalizaci�n del Paso 2

    //Finalizaci�n del PSO

    return 0;
}
