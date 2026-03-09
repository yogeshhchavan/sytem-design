#include<iostream>
using namespace std;

// ----Strategy interface for walk ----
class walkableRobot{
public:
    virtual void walk() = 0;
    virtual ~walkableRobot() {}
};

// ---- Concrete strategy for walk ----
class NormalWalk : public walkableRobot{
public:
    void walk() override {
        cout<<"Walking normally..."<<endl;
    }
};

class NoWalk : public walkableRobot{
public:
    void walk() override {
        cout<<"cannot walk...."<<endl;
    }
};

// ---- Strategy Interface  for talk ----
class TalkableRobot{
public:
    virtual void talk() = 0;
    virtual ~TalkableRobot() {}

};

// ---- Concrete strategy for talk ----
class NormalTalk : public TalkableRobot{
public:
    void talk() override {
        cout<<"Talking normally..."<<endl;
    }
};

class NoTalk : public TalkableRobot{
public:
    void talk() override{
        cout<<"cannot talk...."<<endl;
    }
};

// ---- Strategy Interface for fly ----
class FlyRobot{
public :
    virtual void fly() = 0;
    virtual ~FlyRobot() {};
};

// ---- Concrete strategy for fly ----
class NormalFly : public FlyRobot{
public:
    void fly() override{
        cout<<"Flying normally..."<<endl;
    }
};

class NoFly : public FlyRobot{
public:
    void fly() override{
        cout<<"cannot fly...."<<endl;
    }
};

// ---- Robot Base Class ----
class Robot{
protected:
    walkableRobot* walkStrategy;
    TalkableRobot* talkStrategy;
    FlyRobot* flyStrategy;
public:
    Robot(walkableRobot* w, TalkableRobot* t, FlyRobot* f){
        this->walkStrategy = w;
        this->talkStrategy = t;
        this->flyStrategy = f;
    }

    void walk(){
        walkStrategy->walk();
    }

    void talk(){
        talkStrategy->talk();
    }

    void fly(){
        flyStrategy->fly();
    }

    virtual void projection () = 0; // Abstract Method for Subclasses

};

// ---- Concrete Robot Classes ----
class CompanionRobot : public Robot{
public:
    CompanionRobot(walkableRobot* w, TalkableRobot* t, FlyRobot* f) : Robot(w,t,f) {}

    void projection() override {
        cout<<"Displaying friendly companion features...."<<endl;
    }
};

class WorkerRobot : public Robot{
public:
    WorkerRobot(walkableRobot* w, TalkableRobot* t, FlyRobot* f) : Robot(w,t,f) {}

    void projection() override {
        cout<<"Displaying worker robot efficiency states.........."<<endl;
    }
}; 

int main(){
    Robot *robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());
    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->projection();
    cout<<"-----------------------------"<<endl;

    Robot *robot2 = new WorkerRobot(new NormalWalk(), new NoTalk(),new NormalFly());
    robot2->walk();
    robot2->talk();
    robot2->fly();
    robot2->projection();

    return 0;
}



// ========================================================================================
//                                       OUTPUT
// ========================================================================================

//                                     Walking normally...
//                                     Talking normally...
//                                     cannot fly....
//                                     Displaying friendly companion features....
//                                     -----------------------------
//                                     Walking normally...
//                                     cannot talk....
//                                     Flying normally...
//                                     Displaying worker robot efficiency states..........

// ===========================================================================================
