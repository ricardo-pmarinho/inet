/*
 * Gat.cpp
 *
 *  Created on: 25 de fev de 2025
 *      Author: ricar
 */

#include "Gat.h"
#include <random>
#include <algorithm>

using namespace std;

namespace inet {

Define_Module(Gat);

Gat::Gat()
{
    // TODO Auto-generated constructor stub
    neighAdrrs = new vector<L3Address>();
    neighDists = new vector<double>();
    alpha = new vector<double>();
    a = new vector<double>();
    w = new vector<double>();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-1.0, 1.0);
    selfW = dis(gen);
    uniform_real_distribution<> dis2(0.0, 1.0);
    selfA = dis2(gen);
}

Gat::~Gat() {
    // TODO Auto-generated destructor stub
}

void Gat::insertGatNeighbor(L3Address neighAddr, double dist)
{
    vector<L3Address>::iterator it = find(neighAdrrs->begin(),neighAdrrs->end(), neighAddr);
    if(it == neighAdrrs->end()){
        neighAdrrs->push_back(neighAddr);
        neighDists->push_back(dist);
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(-1.0, 1.0);
        w->push_back(dis(gen));
        uniform_real_distribution<> dis2(0.0, 1.0);
        a->push_back(dis2(gen));
    }
}

void Gat::calcAttention()
{
    if(!this->alpha->empty())
        this->alpha->clear(); //restart alpha for new computations
    vector<double>::iterator it;
    double distMean = 0.0; // value to be uses as the x_1 feature
    for(it = neighDists->begin(); it != neighDists->end(); it++)
        distMean+=*it;
    distMean/=neighDists->size();

    vector<double>* e = new vector<double>();
    double h1 = distMean*selfW;
    double tempE = selfA*h1;
    double h = 0.0;
    it = w->begin();
    for(int i = 0;it != w->end();i++,it++){
        h = neighDists->at(i)*(*it);
        double leakrelu = tempE + (a->at(i)*h);
        if(leakrelu < 0)
            leakrelu*=0.9;//default alpha argument for activation function
        leakrelu*=1.5;
        e->push_back(leakrelu);
    }

    vector<double>::iterator itSoft;
    for(itSoft = e->begin(); itSoft != e->end();itSoft++){
        double tempSoft = 0.0;
        for(it = e->begin(); it != e->end();it++){
            tempSoft += *it;
        }
        this->alpha->push_back(*itSoft/tempSoft);
    }
}

double Gat::getAttention(L3Address cainDest)
{
    int index=0;
    vector<L3Address>::iterator it  = neighAdrrs->begin();
    for(it = neighAdrrs->begin(); it != neighAdrrs->end();it++){
        if(*it == cainDest)
            break;
        index++;
    }

    return this->alpha->at(index);
}

void Gat::printGat() {
    EV << "Imprimindo dados do GAT: " << endl;
    vector<L3Address>::iterator it = this->neighAdrrs->begin();
    int i = 0;
    for (; it != this->neighAdrrs->end(); it++) {
        EV << "Index " << i << ": " << it->str() << endl;
        EV << "W vector: " << w->at(i) << endl;
        EV << "A vector: " << a->at(i) << endl;
        i++;
    }
}





} /* namespace inet */
