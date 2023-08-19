#ifndef AUXFUNCTIONS_H_INCLUDED
#define AUXFUNCTIONS_H_INCLUDED

vector<float> randGen(int N)
{
    random_device rd;
    default_random_engine generator(rd());
    normal_distribution<float> distribution(-15,15);

    vector<float> num_aleat(N);
    for(int i=0; i<N; i++)
        num_aleat.at(i)=distribution(generator);

    return num_aleat;
}

#endif // AUXFUNCTIONS_H_INCLUDED
