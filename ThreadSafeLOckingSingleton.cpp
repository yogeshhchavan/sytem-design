#include<iostream>
#include<mutex>
using namespace std;

class Singleton {
private:
    static Singleton* instance;
    static mutex mtx;

    Singleton(){
        cout<<"Singleton Constructor called, New Object created"<<endl;
    }
public:
    static Singleton* getInstance(){
        if(instance == nullptr){
            lock_guard<mutex> lock(mtx); // Lock the mutex to ensure thread safety
            if(instance == nullptr){
                instance = new Singleton();
            }
        }
        return instance;
    }
        
};

// Initialize static members
Singleton* Singleton::instance = nullptr; // Initialize the static member variable
mutex Singleton::mtx;

int main(){
    Singleton* st1 = Singleton::getInstance(); 
    Singleton* st2 = Singleton::getInstance();

    cout<<(st1 == st2)<<endl;
} 
