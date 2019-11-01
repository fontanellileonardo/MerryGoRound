
#ifndef __MERRYGOROUND_IN_MGR_H_
#define __MERRYGOROUND_IN_MGR_H_

#include <omnetpp.h>

using namespace omnetpp;

class IN_MGR: public cSimpleModule {
    double ride_time;
    int seat_num;            //The number of chairs of the MRG
    int occupiedSits;
    int childrenDropped;
    cQueue sits;            //DS that to represent the children on the ride.
    cQueue childrenLine; //The queue where children wait until they get a place on the MRG sits
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void queueUp(cMessage *msg);
    void startRide(cMessage *msg);
    void endRide(cMessage *msg);
    void checkThreshold(); // check and drop out children according to their threshold time
};

#endif
