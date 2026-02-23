#include<iostream>
#include<vector>

using namespace std;

// Product Class representing any item of any Ecommerce.

class Product {
public:
    string name;
    double price;

    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

// Violating SRP: Shopping handling more respocibilities.

class ShoppingCart {
private:
    vector<Product*> products;
public:
    void addProduct(Product* p){
        products.push_back(p);
    }

    const vector<Product*>& getProducts() {
        return products;
    }

    // 1. Calculate total price in cart.

    double calculateTotal(){
        double total = 0;
        for(auto p : products){
            total += p->price;
        }
        return total;
    }

    // 2. Violating SRP - Prints invoice (Should be in separate class)

    void printInvoice(){
        cout<<"Shopping Cart Invoice:\n";
        for(auto p : products){
            cout<< p->name <<" - $"<<p->price<<endl;
        }
        cout<<"Total : $"<<calculateTotal()<<endl;
    }

    // 3. Violating SRP - Saved to DB (should in seperate Class)

    void saveToDatabase(){
        cout<<"Saving shopping cart to database..."<<endl;
        // Simulate DB save with a print statement
    }
};

int main(){
    ShoppingCart* cart = new ShoppingCart();

    cart->addProduct(new Product("Laptop", 15000));
    cart->addProduct(new Product("Mouse", 50));

    cart->printInvoice();
    cart->saveToDatabase();

    return 0;
}



// ============================================================================================================
//                                                 OUTPUT
// ============================================================================================================

//                                             Shopping Cart Invoice:
//                                             Laptop - $15000
//                                             Mouse - $50
//                                             Total : $15050
//                                             Saving shopping cart to database...

// ============================================================================================================
