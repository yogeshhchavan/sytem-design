#include<iostream>


using namespace std;

class Singleton {
private:
    static Singleton* instance;

    Singleton(){
        cout<<"Singleton Constructor Called!"<<endl;
    }
public:
    static Singleton* getInstance(){
    return instance;
    }
};

// Initialize the static member
Singleton* Singleton::instance = new Singleton();

int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    cout<<(s1 == s2)<<endl;
}




// ==========================================================================
//                               OUTPUT
// ==========================================================================


//                         Singleton Constructor Called!
//                         1

// ========================================================================
