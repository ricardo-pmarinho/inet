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

#include "dnn.h"

namespace inet {

/*constructors and initializers begin*/
dnn::dnn(std::string neuronName) {
    this->name=neuronName;
    this->connections=new std::vector<dnn*>();
    this->weights=new std::vector<float>();
    this->recWeights=new std::vector<float>();
    this->totalWeights=new std::vector<float>();
    this->values=new std::vector<float>();
    this->decisionVect=new std::vector<bool>();
    this->decisionVect->push_back(true);
    this->decisionVect->push_back(true);
}

dnn::~dnn() {
    // TODO Auto-generated destructor stub
}

dnn* dnn::createDnn(int numInputs, int hiddenLayers, int numNerons, int output){

    dnn* initial = new dnn("initial");

    for(int i = 0;  i< numInputs;i++){
        initial->connections->push_back(new dnn("I"+std::to_string(i)));
        initial->weights->push_back(1);
    }

    //hidden layer 1
    dnn* aux = initial;
    for(int i = 0; i < numNerons; i++){
        dnn* hNeuron = new dnn("H1"+std::to_string(i));
        for(int j = 0; j < aux->connections->size(); j++){
            dnn* neuron = aux->connections->operator [](j);
            neuron->connections->push_back(hNeuron);
            neuron->weights->push_back((float)rand()/((float)RAND_MAX)*2-1);
        }
    }

    //hidden layer 2
    aux = initial->connections->operator [](0);
    for(int i = 0; i < numNerons; i++){
        dnn* hNeuron = new dnn("H2"+std::to_string(i));
        for(int j = 0; j < aux->connections->size(); j++){
            dnn* neuron = aux->connections->operator [](j);
            neuron->connections->push_back(hNeuron);
            neuron->weights->push_back((float)rand()/((float)RAND_MAX)*2-1);
        }
    }

    //output
    aux = aux->connections->operator [](0);
    for(int i = 0; i < output; i++){
        dnn* hNeuron = new dnn("O"+std::to_string(i));
        for(int j = 0; j < aux->connections->size(); j++){
            dnn* neuron = aux->connections->operator [](j);
            neuron->connections->push_back(hNeuron);
            neuron->weights->push_back((float)rand()/((float)RAND_MAX)*2-1);
        }
    }

    return initial;
}

/*constructors and initializers end*/

/*setters and getters begin*/

std::string dnn::getNeuronName(){
    return this->name;
}

std::vector<dnn*>* dnn::getNeuronConnections(){
    return this->connections;
}

std::vector<float>* dnn::getNeuronWeights(){
    return this->weights;
}

bool dnn::getDecision(){
    return this->decisionVect->operator [](0);
}


std::vector<float>* dnn::getTotalWeights(){

    std::vector<float>* totalWeights = new std::vector<float>();
    dnn* aux = this;
    for(;aux->connections->size()>0;aux=aux->connections->operator [](0)){
        for(int i = 0; i < aux->connections->size();i++){
            dnn* neuron = aux->connections->operator [](i);
            for(int j = 0; j < neuron->connections->size();j++)
                totalWeights->push_back(neuron->weights->operator [](j));
        }
    }

    return totalWeights;

}
void dnn::setNeuronTotalWeights(std::vector<float> *weightVector){
    this->totalWeights=weightVector;
}
/*setters and getters end*/


/*updates begin*/
std::vector<bool>* dnn::calculateDnn(double dist, double delay){
    //this dnn is the initial one
    this->connections->operator [](0)->values->push_back(dist);
    this->connections->operator [](0)->recWeights->push_back(1);
    this->connections->operator [](0)->functionValue=dist;
    this->connections->operator [](1)->values->push_back(delay);
    this->connections->operator [](1)->recWeights->push_back(1);
    this->connections->operator [](1)->functionValue=delay;

    dnn* aux = this;
    for(;aux->connections->size()>0;aux=aux->connections->operator [](0)){
        for(int i = 0; i < aux->connections->size();i++){
            dnn* neuron = aux->connections->operator [](i);
            if(neuron->name != "I0" && neuron->name != "I1"){
                float weightedValues = 0;
                for(int j = 0; j < neuron->recWeights->size(); j++)
                    weightedValues+=(neuron->recWeights->operator [](j)*neuron->values->operator [](j));
                neuron->functionValue=1/(1+exp(-weightedValues));
            }
            for(int j = 0; j < neuron->connections->size();j++){
                neuron->connections->operator [](j)->recWeights->push_back(
                        neuron->weights->operator [](j)
                        );
                neuron->connections->operator [](j)->values->push_back(
                        neuron->functionValue
                        );
            }
        }
    }

    //updates the new decision for
    this->decisionVect->operator [](0)=this->decisionVect->operator [](1);
    if(aux->functionValue < 0.5)
        this->decisionVect->operator [](1)= false;
    else
        this->decisionVect->operator [](1)= true;
    return this->decisionVect;

}

void dnn::updateDnn(float result,std::vector<bool> *decision){
    if(result>bestValue){
        bestValue=result;
        this->decisionVect = decision;

        dnn* aux = this;
        for(;aux->connections->size()>0;aux=aux->connections->operator [](0)){
            for(int i = 0; i < aux->connections->size();i++){
                dnn* neuron = aux->connections->operator [](i);
                for(int j = 0; j < neuron->connections->size();j++)
                    neuron->weights->operator [](j)+=(float)rand()/((float)RAND_MAX)*1-0.5;
            }
        }
    }
}

void dnn::updateWeights(unsigned int weightCounter,bool isCh){
    /***
     * Walk into the weights from each neuron
     * updating them with the received weight
     * vector
     * */

    if(isCh){
        dnn* aux = this;
        int vectIndex=0;/*index to walk into the weight vector*/
        for(;aux->connections->size()>0;aux=aux->connections->operator [](0)){
            for(int i = 0; i < aux->connections->size();i++){
                dnn* neuron = aux->connections->operator [](i);
                for(int j = 0; j < neuron->connections->size();j++){
                    neuron->weights->operator [](j)*=weightCounter-1;
                    neuron->weights->operator [](j)+=this->totalWeights->operator [](vectIndex);
                    neuron->weights->operator [](j)/=weightCounter;
                    vectIndex++;
                }
            }
        }
    }else{
        dnn* aux = this;
        int vectIndex=0;/*index to walk into the weight vector*/
        for(;aux->connections->size()>0;aux=aux->connections->operator [](0)){
            for(int i = 0; i < aux->connections->size();i++){
                dnn* neuron = aux->connections->operator [](i);
                for(int j = 0; j < neuron->connections->size();j++){
                    neuron->weights->operator [](j)=this->totalWeights->operator [](vectIndex);
                    vectIndex++;
                }
            }
        }
    }
}

/*updates end*/
} /* namespace inet */
