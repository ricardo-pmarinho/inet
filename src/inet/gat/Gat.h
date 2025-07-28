/*
 * Gat.h
 *
 *  Created on: 25 de fev de 2025
 *      Author: ricar
 */

#ifndef INET_GAT_GAT_H_
#define INET_GAT_GAT_H_

#include "inet/networklayer/contract/IL3AddressType.h"

using namespace std;
namespace inet {

class INET_API Gat : public cSimpleModule{
private:
    vector<double>* w; //gat w random vector (h_i=x_i*w_i)
    vector<double>* a; //gat a random vector (a^T[Wh_i||Wh_m])
    vector<L3Address>* neighAdrrs; //neighobors address to match 'w' and 'a' indexes
    vector<double>* neighDists; //distance to the neighbors. index match with neighAddrs. it is the 'x' feature vector
    vector<double>* alpha; //neighbors softmax vector
    double selfA;
    double selfW;
public:
    Gat();
    virtual ~Gat();

    void insertGatNeighbor(L3Address neighAddr, double dist);
    void cleanGatNeighbors();
    void printGat();
    void calcAttention();
    double getAttention(L3Address cainDest);
};

} /* namespace inet */

#endif /* INET_GAT_GAT_H_ */
