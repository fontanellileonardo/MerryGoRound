#include "IN_MGR.h"
#include"Ctrl_M_m.h"
#include"child_m.h"
#include"childrenInQueue_m.h"

Define_Module(IN_MGR);

void IN_MGR::initialize() {
    ride_time = par("ride_time");
    seat_num = par("seat_num");
    occupiedSits = 0;
    childrenDropped = 0;
    cMessage *timer = new cMessage("Timer");
    scheduleAt(simTime()+1,timer);
}

void IN_MGR::handleMessage(cMessage *msg) {
    // children coming
    if (strcmp(msg->getName(), "kid") == 0) { //a new child arrives to the MGR
        queueUp(msg);
    }

    // Start the game/Ride
    else if (strcmp(msg->getName(), "start") == 0) { //received the start message from the Owner
        EV << "Owner ordered a start" << endl;
        startRide(msg);
    }

    //end the Ride
    else if (strcmp(msg->getName(),"EndRide")==0) {
        endRide(msg);
    }

    //do the drop out of children
    else if(strcmp(msg->getName(),"Timer")==0){
        checkThreshold();
        scheduleAt(simTime()+1,msg);
    }
}

void IN_MGR::queueUp(cMessage *msg) {
    ChildrenInQueue *childArrive = new ChildrenInQueue("C_arrive");
    childrenLine.insert(msg);
    childArrive->setNumber(childrenLine.getLength());
    send(childArrive,"notify");
    EV << childrenLine.getLength() << " child(ren) in the queue" << endl;
}

void IN_MGR::startRide(cMessage *msg) {
    Ctrl_M *starter = check_and_cast<Ctrl_M*>(msg);
    int children_on_ride = starter->getChil_num();

    //the (for) loop is safe to copy from "childrenLine" to "sits" only if queue is not empty and
    //there are at least "children_on_ride" number of children on the queue
        for (int i = 1; i <= children_on_ride && i <= seat_num && !childrenLine.isEmpty(); ++i) {
             //because there must be enough sits for the children.
                sits.insert(childrenLine.pop());    //kids taking their sit
        }

        EV << childrenLine.getLength() << " child(ren) in the queue\t"
                  << sits.getLength() << " sits occupied" << endl;
        cMessage *ride = new cMessage("EndRide"); // to notify the owner the end of message
        scheduleAt(simTime() + ride_time, ride);
        delete(msg);
        EV << "MRG started " << endl;
}

void IN_MGR::endRide(cMessage *msg) {
    //self message received, the ride is over. Send children out
    EV << "Start send out children on sits" << sits.getLength() << endl;
    occupiedSits = sits.getLength();
    for (int var = 1; var <= occupiedSits; var++) { //one after another, children comes out from the MGR
        EV << "sending out child #" << var << endl;
        send((cMessage *) sits.pop(), "out");
    }
    delete (msg);
    Ctrl_M *start = new Ctrl_M("done");
    start->setEnjoyed(occupiedSits);
    send(start, "notify");

}

void IN_MGR::checkThreshold(){
    int dropCount=0;
    for(cQueue::Iterator iter(childrenLine); !iter.end(); ++iter ){
        Child *child = (Child*)*iter;
        int temp = child->getWaitingThreshold();
        temp--;
        if(temp<=0){
            childrenLine.remove((Child*)*iter);
            dropCount++;
            childrenDropped++;
        }else{
            child->setWaitingThreshold(temp);
        }

    }
    if(dropCount > 0){
        ChildrenInQueue *childArrive = new ChildrenInQueue("C_arrive");
        childArrive->setNumber(childrenLine.getLength());
        send(childArrive,"notify");
    }
    EV << dropCount <<" child left the playground for expiry of the threshold" <<endl;
    EV << childrenDropped <<" total number of children dropped"<<endl;
}
