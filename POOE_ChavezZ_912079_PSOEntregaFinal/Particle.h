#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

class Particle
{
private:
    float m_fitness,m_bestFitness;
    vector<float> m_position;
    vector<float> m_velocity;
    vector<float> m_bestPosition;
public:
    int m_id;
    //Constructor default
    Particle(){}
    //Constructor personalizado
    Particle(int id)
    {
        m_id=id;
        m_fitness=0;
        m_bestFitness=0;
        m_position = {0.0,0.0};
        m_velocity = {0.0,0.0};
        m_bestPosition = {0.0,0.0};

    }

    //Destructor default
    ~Particle(){}

    //Setters
    void setFitness(float fitness) {m_fitness=fitness;}
    void setBestFitness (float bestFitness) {m_bestFitness=bestFitness;}
    void setPosition(vector<float> position)
    {
        m_position.clear();
        for(size_t i=0; i<position.size(); i++)
            m_position.push_back(position.at(i));
    }
    void setVelocity(vector<float> velocity)
    {
        m_velocity.clear();
        for(size_t i=0; i<velocity.size(); i++)
            m_velocity.push_back(velocity.at(i));
    }
    void setBestPosition(vector<float> bestPosition)
    {
        m_bestPosition.clear();
        for(size_t i=0; i<bestPosition.size(); i++)
            m_bestPosition.push_back(bestPosition.at(i));
    }
    //Getters
    float getFitness() {return m_fitness;}
    float getBestFitness () {return m_bestFitness;}
    vector<float> getPosition() {return m_position;}
    vector<float> getVelocity() {return m_velocity;}
    vector<float> getBestPosition() {return m_bestPosition;}

    //Recorrer los vectores (cambiarlo a string)
    string vectorRecorrer(vector<float> x)
    {
        string s;
        for(size_t i=0; i<x.size(); i++)
            s.append(to_string(x.at(i))).append(" ");
        return s;
    }
    //Mostrar los datos
    string imprimirDatos()
    {
       string datos;

    datos="(" + to_string(m_id) + ") \t (" + to_string(m_fitness) + ") \t (" + to_string(m_bestFitness) + ") \t [";

    for(size_t i=0; i<m_position.size(); i++)
        datos+= to_string(m_position.at(i)) + ", ";
    datos += "] \t [";

    for(size_t j=0; j<m_bestPosition.size(); j++)
        datos += to_string(m_bestPosition.at(j)) + ", ";
    datos +="] \t [";

    for(size_t k=0; k<m_velocity.size(); k++)
        datos+= to_string(m_velocity.at(k)) + ", ";
    datos += "]";

    return datos;
    }

    //Ordenación de objetos
    bool operator < (const Particle &particula2) const {return m_fitness < particula2.m_fitness;}
};

#endif // PARTICLE_H_INCLUDED
