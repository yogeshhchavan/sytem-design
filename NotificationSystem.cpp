#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

/*==============================
    Notification & Decoraotors
================================*/

class INotification {
public:
    virtual string getContent() const = 0;
    virtual ~INotification() {}
};

// Concrete Notification: simple text notification.
class SimpleNotification : public INotification {
private:
    string text;
public:
    SimpleNotification(const string& msg){
        text = msg;
    }
    string getContent() const override {
        return text;
    }
};

// Anstract Decorator : wraps a Notification object.
class INotificationDecorator : public INotification{
protected:
    INotification* notification;
    INotificationDecorator(INotification* n){
        notification = n;
    }
    virtual ~INotificationDecorator() {
        delete notification; // prevent memory leaks
    }
};

// Decorator to add a timestamp to the content.
class TimestampDecorator: public INotificationDecorator{
public:
    TimestampDecorator(INotification* n): INotificationDecorator(n) { }
    string getContent() const override {
        return "[2026-03-27 16:00:15] " + notification->getContent();
    }
};

//Decorator to appen a signature to the content.
class SignatureDecorator : public INotificationDecorator {
private:
    string signature;
public:
    SignatureDecorator(INotification* n, const string& sig) : INotificationDecorator(n) {
        signature = sig;
    }
    string getContent() const override {
        return notification->getContent() + "\n-- " + signature + "\n\n";
    }
};

/*=======================================================
    Observer Pattern Componnet
========================================================*/

// Observerver interface: each observer gets an update with a Notification pointer.
class IObserver {
public:
    virtual void update() = 0;
    virtual ~IObserver() {}
};

class IObservable {
public:
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

// Concrete Observerable
class NotificationObservable : public IObservable {
private:
    vector<IObserver*> observers;
    INotification* currentNotification;
public:
    NotificationObservable() {
        currentNotification = nullptr;
    }

    void addObserver(IObserver* obs) override {
        observers.push_back(obs);
    }

    void removeObserver(IObserver* obs) override {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObservers() override {
        for(unsigned int i = 0; i < observers.size(); i++) {
            observers[i]->update();
        }
    }

    void setNotification(INotification*notification){
        if(currentNotification != nullptr){
            delete currentNotification;
        }
        currentNotification = notification;
        notifyObservers();
    }

    INotification* getNotification() {
        return currentNotification;
    }
    string getNotificationContent() {
        return currentNotification->getContent(); 
    }

    ~NotificationObservable() {
        if (currentNotification != NULL) {
            delete currentNotification;
        }
    }
};

// Concrete Observer 1
class Logger : public IObserver {
private:
    NotificationObservable* notificationObservable;
public:
    Logger(NotificationObservable* observable){
        this->notificationObservable = observable;
    }

    void update() {
        cout<<"Logging New Notification ; \n"<< notificationObservable->getNotificationContent();
    }
};

/*========================================================
    Strategy Pattern Component (concrete Observer 2)
========================================================*/

// Abstract class for different Notification Strategies.
class INotificationStrategy {
public:
    virtual void sendNotification(string content) = 0;
};

class EmailStrategy : public INotificationStrategy {
private:
    string emailId;
public:
    EmailStrategy(string emailId){
        this->emailId = emailId;
    }

    void sendNotification(string content) override {
        // Simulate tthe process of sending aan email notification,
        //representing the dispatch of messages to users via email.

        cout<<"Sending Email Notification to: "<< emailId << "\n" << content;
    }
};

class SMSStrategy : public INotificationStrategy {
private:
    string phoneNumber; 
public:
    SMSStrategy(string phoneNumber){
        this->phoneNumber = phoneNumber;
    }

    void sendNotification(string content) override {
        // Simulate the process of sending an SMS notification,
         // representing the dispatch of messages to users via SMS.

        cout<<"Sending SMS Notification to: "<< phoneNumber << "\n" << content;
    }
};

class PopUpStrategy : public INotificationStrategy {
public:
    void sendNotification(string content) override {
        // Simulate the process of displaying a pop-up notification,
        
        cout<<"Sending Pop-Up Notification: \n"<< content;
    }
};

class NotificationEngine : public IObserver {
private:
    NotificationObservable* notificationObservable;
    vector<INotificationStrategy*> notificationStrategies;
public:
    NotificationEngine(NotificationObservable* observable){
        this->notificationObservable = observable;
    }

    void addNotificationStrategy(INotificationStrategy* ns) {
        this->notificationStrategies.push_back(ns);
    }

    // can have RemoveNotificationStrategy as well.

    void update() {
        string notificationContent = notificationObservable->getNotificationContent();
        for(const auto notificationStrategy : notificationStrategies) {
            notificationStrategy->sendNotification(notificationContent);
        }
    }
};

/*================================
    NotificationServices
==================================*/

// The NotificationService manages notification. It keeps track of notifications.
// Any client code will interact with this service.

// Singleton class
class NotificationService {
private:
    NotificationObservable* observable;
    static NotificationService* instance;
    vector<INotification*> notifications;

    NotificationService() {
        // private constructor
        observable = new NotificationObservable();
    }
public:
    static NotificationService* getInstance() {
        if (instance == nullptr) {
            instance = new NotificationService();
        }
        return instance;
    }

    // Expose the observable so observers can attach.
    NotificationObservable* getObservable() {
        return observable;
    }

    // create a new Notification and notifies observers.
    void sendNotification(INotification* notification){
        notifications.push_back(notification);
        observable->setNotification(notification);
    } 
    
    ~NotificationService() {
        delete observable;
    }
};

NotificationService* NotificationService::instance = nullptr;

int main() {
    // create NotificationServices.
    NotificationService* notificationService = NotificationService::getInstance();

    // Get Observable
    NotificationObservable* notificationObservable = notificationService->getObservable();

    // Create Logger Observer
    Logger* logger = new Logger(notificationObservable);

    // Create NotificationEngine observers
    NotificationEngine* notificationEngine = new NotificationEngine(notificationObservable);

    notificationEngine->addNotificationStrategy(new EmailStrategy("random.person@gmail.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("+91 9876543210"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());

    // Attach this observers
    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    //  Create a notification with decorators.
    INotification* notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimestampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");
    
    notificationService->sendNotification(notification);

    delete logger;
    delete notificationEngine;
    return 0;
}   


// ======================================================================================
//                                   OUTPUT
// ======================================================================================

//                     Logging New Notification :
//                     [2026-03-27 16:00:15] Your order has been shipped!
//                     -- Customer Care
                    
//                     Sending Email Notification to: random.person@gmail.com
//                     [2026-03-27 16:00:15] Your order has been shipped!
//                     -- Customer Care
                    
//                     Sending SMS Notification to: +91 9876543210
//                     [2026-03-27 16:00:15] Your order has been shipped!
//                     -- Customer Care
                    
//                     Sending Pop-Up Notification:
//                     [2026-03-27 16:00:15] Your order has been shipped!
//                     -- Customer Care

// =========================================================================================
