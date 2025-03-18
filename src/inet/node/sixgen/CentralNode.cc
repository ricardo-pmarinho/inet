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

#include "CentralNode.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

namespace inet {

Define_Module(CentralNode);

void CentralNode::initialize()
{
    EV << "Central node" << endl; // Inicializa o socket UDP
//    socket.setOutputGate(gate("socketIn"));
//    socket.bind(1234); // Porta local para receber mensagens
}

void CentralNode::handleMessage(cMessage *msg)
{
    EV << "Receiving message from antenna" << endl;

}

CentralNode::CentralNode() {
    // TODO Auto-generated constructor stub

}

CentralNode::~CentralNode() {
    // TODO Auto-generated destructor stub
}

} /* namespace inet */
