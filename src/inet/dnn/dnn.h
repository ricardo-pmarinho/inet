//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef INET_DNN_DNN_H_
#define INET_DNN_DNN_H_
#include <omnetpp.h>


namespace inet {

class dnn {
private:
    std::string name;
    std::vector<dnn*> *connections; //connections to the next layer
    std::vector<float> *weights; //weights for the next layer
    std::vector<float> *recWeights; //weights received from the previous layer
    std::vector<float> *totalWeights; //weight vector for FL
    std::vector<float> *values; //function values from the previous layer
    float functionValue; //sigmoid function value
    float bestValue=0; //optimal value from RL algorithm
    bool decision; //0-> not send 1-> send
    std::vector<bool> *decisionVect;

public:
    /*constructors and initializers*/
    dnn(std::string neuronName);
    virtual ~dnn();
    dnn* createDnn(int numInputs, int hiddenLayers, int numNerons, int output);
    /*setters and getters*/
    std::string getNeuronName();
    std::vector<dnn*>* getNeuronConnections();
    std::vector<float>* getNeuronWeights();
    std::vector<float>* getTotalWeights();
    bool getDecision();
    void setNeuronTotalWeights(std::vector<float> *weightVector);
    /*updates*/
    std::vector<bool>* calculateDnn(double dist, double delay);
    void updateDnn(float result,std::vector<bool> *decision);
    void updateWeights(unsigned int weightCounter,bool isCh);
};

} /* namespace inet */

#endif /* INET_DNN_DNN_H_ */
