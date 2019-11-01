

#ifndef __PERFORMANCE_OWNER_H_
#define __PERFORMANCE_OWNER_H_
//#define ev (*cSimulation::getActiveEnvir())
#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Owner : public cSimpleModule
{
    int threshold; //minimum number of child for the start of the ride
    int children; //children in the queue waiting for a ride
    int money; //money earned in a day
    int childrenPlayed;
    bool started = false;
    int lastMoney;
    simsignal_t earningPerTime;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void sendStartMessage();
};

#endif
