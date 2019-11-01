

#ifndef __MERRYGOROUND_ENTRY_H_
#define __MERRYGOROUND_ENTRY_H_

#include <omnetpp.h>

using namespace omnetpp;


class Entry : public cSimpleModule
{
private:
    int createdChild;
    simsignal_t children_per_time;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void GenerateChild(cMessage *msg);
};

#endif

