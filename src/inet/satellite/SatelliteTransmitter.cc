#include <omnetpp.h>
#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"

using namespace omnetpp;
using namespace inet;

class SatelliteTransmitter : public ApplicationBase
{
protected:
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    void sendSatelliteMessage();
    void handleSatelliteMessage(cPacket *pkt);

    cMessage *sendEvent = nullptr;
};

Define_Module(SatelliteTransmitter);

void SatelliteTransmitter::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        sendEvent = new cMessage("sendSatelliteMessage");
        scheduleAt(simTime() + par("startTime"), sendEvent);
    }
}

void SatelliteTransmitter::handleMessageWhenUp(cMessage *msg)
{
    if (msg == sendEvent) {
        sendSatelliteMessage();
        scheduleAt(simTime() + par("sendInterval"), sendEvent);
    } else {
        cPacket *pkt = check_and_cast<cPacket *>(msg);
        handleSatelliteMessage(pkt);
    }
}

void SatelliteTransmitter::sendSatelliteMessage()
{
    // Create and send a satellite message to the next node
    EV << "Sending satellite message" << endl;
    Packet *pkt = new Packet("SatelliteMessage");
    pkt->setByteLength(par("messageSize"));
    send(pkt, "lowerLayerOut");
}

void SatelliteTransmitter::handleSatelliteMessage(cPacket *pkt)
{
    // Handle received satellite message
    EV << "Received satellite message: " << pkt->getName() << endl;
    delete pkt;
}

void SatelliteTransmitter::handleStartOperation(LifecycleOperation *operation)
{
    // Implementação mínima para inicialização
}

void SatelliteTransmitter::handleStopOperation(LifecycleOperation *operation)
{
    // Implementação mínima para parar a operação
}

void SatelliteTransmitter::handleCrashOperation(LifecycleOperation *operation)
{
    // Implementação mínima para lidar com um "crash"
}
