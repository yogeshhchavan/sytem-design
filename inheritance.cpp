// Inheritance in C++

#include<iostream>
#include<string>
using namespace std;

class Car {
    protected:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;
    
    public:
    
        Car(string b, string m) {
            this->brand = b;
            this->model = m;
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

        void accelarate() {
            if (!isEngineOn) {
                cout<< brand <<" "<< model <<" : Cannot Accelerate! Engine is Off!  "<<endl;
                return;
            } 

            currentSpeed += 20;
            cout<< brand <<" "<< model <<" : Accelerating to: "<<currentSpeed<<" km/h"<<endl;
        }
        
        void brake() {
            currentSpeed -= 20;
            if (currentSpeed < 0)  currentSpeed = 0;
            cout<< brand <<" "<< model <<" : Braking! Current Speed: "<<currentSpeed<<" km/h"<<endl;
        }

        virtual ~Car() {}   // Virtual Destructor
};

class ManualCar : public Car {  //inheritance from Car class
    protected:
        int currentGear; // specific to Manual Car

    public:
        ManualCar(string b, string m) : Car(b, m) {  // Constructor
            this->currentGear = 0;
        }

        // specialized method for Manual Car
        void shiftGear(int gear) { //unique method for ManualCar
            currentGear = gear;
            cout<< brand << " "<< model <<" : Shifted to Gear "<<currentGear<<endl;
        }
};

class ElectricCar : public Car {  //inheritance from Car class
    private:
        int batteryLevel; // specific to Electric Car
    public:
        ElectricCar(string b, string m) : Car(b, m) {  // Constructor
        batteryLevel = 100; // fully charged
        }

        // specialized method for Electric Car
        void chargeBattery() { // unique method for ElectricCar
            batteryLevel = 100;
            cout<< brand << " "<< model <<" : Battery fully charged!"<<endl;
        }
        
};

int main(){
    ManualCar* myManualCar = new ManualCar("SUZUKI", "WAGNOR");
    myManualCar->startEngine();
    myManualCar->shiftGear(1);
    myManualCar->accelarate();
    myManualCar->brake();
    myManualCar->stopEngine();

    delete myManualCar;

    cout<<"-----------------------------"<<endl;

    ElectricCar* myElectricCar = new ElectricCar("TESLA","MODEL S");
    myElectricCar->chargeBattery();
    myElectricCar->startEngine();
    myElectricCar->accelarate();
    myElectricCar->brake();
    myElectricCar->stopEngine();

    delete myElectricCar;

    return 0;
}


// ===========================================================================================
//                                   OUTPUT
// ============================================================================================

//                               SUZUKI WAGNOR : Engine started.
//                               SUZUKI WAGNOR : Shifted to Gear 1
//                               SUZUKI WAGNOR : Accelerating to: 20 km/h
//                               SUZUKI WAGNOR : Braking! Current Speed: 0 km/h
//                               SUZUKI WAGNOR : Engine turn Off.
//                               -----------------------------
//                               TESLA MODEL S : Battery fully charged!
//                               TESLA MODEL S : Engine started.
//                               TESLA MODEL S : Accelerating to: 20 km/h
//                               TESLA MODEL S : Braking! Current Speed: 0 km/h
//                               TESLA MODEL S : Engine turn Off.

// ================================================================================================
