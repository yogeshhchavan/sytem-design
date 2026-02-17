// Dynamic Polymorphism 

#include<iostream>
#include<string>
using namespace std;

// Base class
class Car {
protected:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;
    
public:
    Car(string brand, string model) {
            this->brand = brand;
            this->model = model;
            this->isEngineOn = false;
            this->currentSpeed = 0;
        }

    // common method for All Cars.
    void startEngine() {
            isEngineOn = true;
            cout<< brand <<" "<<model<<" : Engine started."<<endl;
        }
    void stopEngine() {
            isEngineOn = false;
            currentSpeed = 0;
            cout<< brand <<" "<<model<<" : Engine turn Off."<<endl;
        }

    virtual void accelarate() = 0; //Abstract method for dynamic Polymorphism
    virtual void brake() = 0; //Abstract method for dynamic Polymorphism
    virtual ~Car() {}   // Virtual Destructor
};

class ManualCar : public Car {
private:
    int currentGear; // specific to Manual Car

public:
    ManualCar(string brand, string model) : Car(brand, model) {  // Constructor
            this->currentGear = 0;
        }

    //specialized method for Manual Car
    void shiftGear(int gear){
        currentGear = gear;
        cout<< brand <<" "<< model <<" : Shifted to Gear "<<currentGear<<endl;
    }

    //overriding accelarate - dynamic Polymorphism
    void accelarate() {
        if(!isEngineOn){
            cout<< brand <<" "<< model <<" : Cannot Accelerate! Engine is Off!  "<<endl;
            return;
        }
        currentSpeed += 20;
        cout<< brand <<" "<< model <<" : Accelerating to: "<<currentSpeed<<" km/h"<<endl;        
        } 

    //overriding brake - dynamic Polymorphism
    void brake() {
        currentSpeed -= 20;
        if (currentSpeed < 0)  currentSpeed = 0;
        cout<< brand <<" "<< model <<" : Braking! Current Speed: "<<currentSpeed<<" km/h"<<endl;
    }
};

class ElectricCar : public Car {
private:
    
    int batteryLevel; // specific to Electric Car

public:
    ElectricCar(string brand, string model) : Car(brand, model) {  // Constructor
            this->batteryLevel = 100;
        }
    
    //specialized method for Electric Car
    void chargeBattery() {
        batteryLevel = 100;
        cout<< brand <<" "<< model <<" : Charging Battery..."<<endl;
    }

    //overriding accelarate - dynamic Polymorphism
    void accelarate() {
        if(!isEngineOn){
            cout<< brand <<" "<< model <<" : Cannot Accelerate! Engine is Off!  "<<endl;
            return;
        }
        if(batteryLevel <= 0){
            cout<< brand <<" "<< model <<" : Cannot Accelerate! Battery is Dead!  "<<endl;
            return;
        }
        batteryLevel -= 10; // Decrease battery level on acceleration
        currentSpeed += 15; // Electric cars can accelerate faster
        cout<< brand <<" "<< model <<" : Accelerating to: "<<currentSpeed<<" km/h. Battery Level: "<<batteryLevel<<"%"<<endl;        
        }

    //overriding brake - dynamic Polymorphism
    void brake() {
        currentSpeed -= 15; // Electric cars can decelerate faster
        if (currentSpeed < 0)  currentSpeed = 0;
        cout<< brand <<" "<< model <<" : Braking! Current Speed: "<<currentSpeed<<" km/h"<<endl;
    }
};

 
// Main function
int main() {
    Car* myManualCar = new ManualCar("SUZUKI", "WAGNOR");
    myManualCar->startEngine();
    myManualCar->accelarate();
    myManualCar->accelarate();
    myManualCar->brake();
    myManualCar->stopEngine();

    cout<<"-----------------------------"<<endl;

    Car* myElectricCar = new ElectricCar("TESLA", "MODEL S");
    myElectricCar->startEngine();
    myElectricCar->accelarate();
    myElectricCar->accelarate();
    myElectricCar->brake();
    myElectricCar->stopEngine();

    //cleanup 
    delete myManualCar;
    delete myElectricCar;

    return 0;
}

// ==================================================================================================================================
//                                                           OUTPUT
// ==================================================================================================================================


//                                                         SUZUKI WAGNOR : Engine started.
//                                                         SUZUKI WAGNOR : Accelerating to: 20 km/h
//                                                         SUZUKI WAGNOR : Accelerating to: 40 km/h
//                                                         SUZUKI WAGNOR : Braking! Current Speed: 20 km/h
//                                                         SUZUKI WAGNOR : Engine turn Off.
//                                                         -----------------------------
//                                                         TESLA MODEL S : Engine started.
//                                                         TESLA MODEL S : Accelerating to: 15 km/h. Battery Level: 90%
//                                                         TESLA MODEL S : Accelerating to: 30 km/h. Battery Level: 80%
//                                                         TESLA MODEL S : Braking! Current Speed: 15 km/h
//                                                         TESLA MODEL S : Engine turn Off.

// ==================================================================================================================================
  
