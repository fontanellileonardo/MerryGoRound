#include "Entry.h"
#include "child_m.h"

Define_Module(Entry);

void Entry::initialize() {
    cMessage *msg = new cMessage("starter");
    createdChild = 0;
    scheduleAt(simTime(), msg); //start sending child to the MGR
    children_per_time = registerSignal("generated"); // signal for observing the number of children arrive at an instant
}

void Entry::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        GenerateChild(msg);
    }
}

void Entry::GenerateChild(cMessage *msg) {

    if(par("burstArrival")){ //Burst arrival scenario. Children geometrically distributed, and exponential arrival
        int burst = geometric(0.5, 3);
        emit(children_per_time, burst); // comment(uncomment) this line to check the mean number of children arrived at an instant
        EV<<"burst number: "<< burst<< endl;
        for (int i = 0; i < burst; i++){
            Child *childA = new Child("kid");
            double Qtime = par("Q");
            childA->setWaitingThreshold(Qtime + exponential(1, 2)); // set the threshold waiting time of each child
            createdChild++;
            send(childA, "out");
        }
    }
    else{ //Single child, exponential arrival
        Child *childA = new Child("kid");
        double Qtime = par("Q");
        childA->setWaitingThreshold(Qtime + exponential(1, 2)); // set the threshold waiting time of each child
        createdChild++;
        send(childA, "out");
    }
    EV << createdChild << " children created during simulation"<<endl;
    double temp = par("meanInterArrival");
    scheduleAt(simTime() + exponential(temp,1), msg); //child generated with an exponential distribution
}
