#include<iostream>
using namespace std;


// Product 1 ------> Burger
class Burger {
public:
    virtual void prepare() =0; // Pure virtual function for preparing the burger
    
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout<<"Preparing Basic Burger with bun, patty, and ketchup!"<<endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout<<"Preparing Standard Burger with bun, patty, cheese, and lettuce!"<<endl;
    }
};

class PremimumBurger : public Burger {
public:
    void prepare() override {
        cout<<"Preparing Premium Burger with bun, patty, cheese, lettuce, tomato, and special sauce!"<<endl;
    }
};

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout<<"Preparing Basic Wheat Burger with wheat bun, patty, and ketchup!"<<endl;
    }
};

class StandardWheatBurger : public Burger {
public:
    void prepare() override {
        cout<<"Preparing Standard Wheat Burger with wheat bun, patty, cheese, and lettuce!"<<endl;
    }
};

class PremiumWheatBurger : public Burger {
public:
    void prepare() override {
        cout<<"Preparing Premium Wheat Burger with wheat bun, patty, cheese, lettuce, tomato, and special sauce!"<<endl;
    }
}; 


// Product 2 ------> Garlic Bread
class GarlicBread {
public:
    virtual void prepare() = 0; // Pure virtual function for preparing garlic bread
};

class BasicGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout<<"Preparing Basic Garlic Bread with butter and garlic! \n";
    }
};

class StandardGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout<<"Preparing Cheese Garlic Bread with extra cheese and butter \n";
    }
};

class BasicWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout<<"Preparing Basic Wheat Garlic Bread with butter and Garlic! \n";
    }
};

class CheeseWheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout<<"Preparing Cheese Wheat Garlic Bread with extra Cheaase and butter \n";
    }
};

// FACTORY and CONCRETIONS
class MealFactory {
public:
    virtual Burger* createBurger(string& type) = 0; // Pure virtual function for creating burgers
    virtual GarlicBread* createGarlicBread(string& type) = 0; // Pure virtual function for creating garlic bread
};

class SinghBurger : public MealFactory {
public:
    Burger* createBurger(string& type){
        if(type == "basic"){
            return new BasicBurger();
        }
        else if(type == "standard"){
            return new StandardBurger();
        }
        else if(type == "premium"){
            return new PremimumBurger();
        }
        else{
            cout<<"Invalid Burger type........!"<<endl;
            return nullptr;
        }
    }

    GarlicBread* createGarlicBread(string& type){
        if(type == "basic"){
            return new BasicWheatGarlicBread();
        }
        else if(type == "cheese"){
            return new CheeseWheatGarlicBread();
        }
        else{
            cout<<"Invalid Garlic Bread type........!"<<endl;
            return nullptr;
        }
    }
};


class KingBurger : public MealFactory {
public:
    Burger* createBurger(string& type){
        if(type == "basic"){
            return new BasicWheatBurger();
        }
        else if(type == "standard"){
            return new StandardWheatBurger();
        }
        else if(type == "premium"){
            return new PremiumWheatBurger();
        }
        else{
            cout<<"Invalid Burger type........!"<<endl;
            return nullptr;
        }
    }
    
    GarlicBread* createGarlicBread(string& type){
        if(type == "basic"){
            return new BasicWheatGarlicBread();
        }
        else if(type == "cheese"){
            return new CheeseWheatGarlicBread();
        }
        else{
            cout<<"Invalid Garlic Bread type........!"<<endl;
            return nullptr;
        }
    }
};

int main() {
    string burgerType = "basic";
    string garlicBreadType = "cheese";

    MealFactory* mealFactory = new KingBurger();

    Burger* burger = mealFactory->createBurger(burgerType);
    GarlicBread* garlicBread = mealFactory->createGarlicBread(garlicBreadType);

    burger->prepare();
    garlicBread->prepare();
    
    return 0;
}



// ============================================================================
//                                   OUTPUT

// ============================================================================

//   Preparing Basic Wheat Burger with wheat bun, patty, and ketchup!
//   Preparing Cheese Wheat Garlic Bread with extra Cheaase and butter 

// =============================================================================  
