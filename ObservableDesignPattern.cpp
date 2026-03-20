#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

// Abstract Obserever interface : subscribers must implement update()
class ISubscriber {
public:
    virtual void update() = 0;
    virtual ~ISubscriber() {} // virtual destructer for interface

};

// Abstrct Observable interface : a YouTube channel interface
class IChannel{
public:
    virtual void subscribe(ISubscriber* subscriber) = 0;
    virtual void unsubscribe(ISubscriber* subscriber) = 0;
    virtual void notifySubscribers() = 0;
    virtual ~IChannel() {} // virtual destructer for interface
};

// Concreate Subject : A YouTube channel that observers can subscribe to 
class Channel : public IChannel {
private:
    vector<ISubscriber*> subscribers; // List of subscribers
    string name;
    string latestVideo;               // latest uploaded video title
public:
    Channel(const string& name){
        this->name = name;
    }

    // Add a subscriber (avoid duplicates)
    void subscribe(ISubscriber* subscriber) override {
        if (find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()){
            subscribers.push_back(subscriber);
        }
    }

    // Remove a subscriber if present
    void unsubscribe(ISubscriber* subscriber) override {
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if(it != subscribers.end()){
            subscribers.erase(it);
        }
    }

    // Notify all subscribers of the latest video
    void notifySubscribers() override {
        for(ISubscriber* sub : subscribers){
            sub->update();
        }
    }

    // Upload a new video and notify all subscribers
    void uploadVideo(const string& title){
        latestVideo = title;
        cout<<"\n[" << name <<"uploaded \""<< title <<"\"]\n";
        notifySubscribers();
    }
    
    // Read video data

    string getVideoData() {
        return "\nCheckout our new Video : "+ latestVideo + "\n";
    }
};

// Concreate Observer: represents a subscriber to the channel
class Subscriber : public ISubscriber {
private:
    string name;
    Channel* channel;
public:
    Subscriber(const string& name, Channel* channel){
        this->name = name;
        this-> channel = channel;
    }

    // Called by Channel : prints notification message

    void update() override {
        cout<< "Hey "<< name <<","<< this->channel->getVideoData();
    }
};

int main(){
    // create a channel and subscribers

    Channel* channel = new Channel("CoderArmy");

    Subscriber* sub1 = new Subscriber("Yogesh", channel);
    Subscriber* sub2 = new Subscriber("Varun", channel);

    // Yogesh and Varun subscribe to the CoderArmy
    channel->subscribe(sub1);
    channel->subscribe(sub2);   

    // upload a video : both Yogesh and Varun are notified
    channel->uploadVideo("Observer Pattern Tutorial");

    //Yogesh unsubscribes : Varun remains sunscribed
    channel->unsubscribe(sub1);

    // upload another video : only varun is notified
    channel->uploadVideo("Decorator Pattern Tutorial");

    return 0;
}


// ========================================================
//                         OUTPUT
// ========================================================

// [CoderArmyuploaded "Observer Pattern Tutorial"]
// Hey Yogesh,
// Checkout our new Video : Observer Pattern Tutorial
// Hey Varun,
// Checkout our new Video : Observer Pattern Tutorial

// [CoderArmyuploaded "Decorator Pattern Tutorial"]
// Hey Varun,
// Checkout our new Video : Decorator Pattern Tutorial

// =========================================================
