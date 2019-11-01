
#include "Owner.h"
#include"Ctrl_M_m.h"
#include"childrenInQueue_m.h"

Define_Module(Owner);

void Owner::initialize() {
    threshold = par("threshold");
    children = 0;
    money = 0;
    lastMoney = 0;
    earningPerTime = registerSignal("earning");
    cMessage *msg = new cMessage("takeStat");
    scheduleAt(simTime() + 10, msg);
}

void Owner::handleMessage(cMessage *msg) {
    if (strcmp(msg->getName(), "C_arrive") == 0) { //notification of the arrival of a new child
        ChildrenInQueue *arrived = (ChildrenInQueue*) msg;
        children = arrived->getNumber();    //update the number the children waiting for the ride
        EV << "Owner sees " << children << " children in the queue as they come" << endl;
        sendStartMessage();
        delete (msg);
    }

    //the IN_MGR sends a notification to the owner that it has finished the ride.
    //the the OWNER can start the next ride.
    else if (strcmp(msg->getName(), "done") == 0) {
        started = false;
        Ctrl_M *ms = check_and_cast<Ctrl_M*>(msg);
        money += ms->getEnjoyed();
        childrenPlayed = ms -> getEnjoyed();
        EV<<money<<" coins collected"<<endl;

        //@Bruk inserted this line and remove the periodic chechup
        sendStartMessage();
        delete(msg);
    }
    else if(strcmp(msg->getName(),"takeStat")==0){
        EV<<money<<"statistics is collected"<<endl;
        double earning = (money - lastMoney) / 10.0;
        emit(earningPerTime, earning);
        lastMoney = money;
        WATCH(lastMoney);
        WATCH(money);
        scheduleAt(simTime() + 10, msg);
    }
}
void Owner::sendStartMessage(){
         if (children >= threshold && started == false) {
             started = true;
             Ctrl_M *starter = new Ctrl_M("start");
             starter->setChil_num(children);
             send(starter, "out"); //sends the star command to the MGR
             children = 0; //reset the number of the children in the queue
         }
}
