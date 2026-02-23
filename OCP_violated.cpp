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

// a. ShoppingCart : only responsible for cart related business logic.
class ShoppingCart{
private:
    vector<Product*> products; // store heap-allocated products
public:
    void addProduct(Product* p){
        products.push_back(p);
    }

    const vector<Product*>& getProducts(){
        return products;
    }

    // calculates total price in cart.
    double calculateTotal(){
        double total = 0;
        for(auto p: products){
            total += p-> price;
        }
        return total;
    }
};

// 2. ShoppingCartPrinter: only responsible for printing Invoices
class ShoppingCartPrinter{
private:
    ShoppingCart* cart;
public:
    ShoppingCartPrinter(ShoppingCart* cart){
        this->cart = cart;
    }

    void printInvoice(){
        cout<<"Shopping Cart Invoice :\n";
        for(auto p : cart->getProducts()){
            cout<<p->name<<" - $"<<p->price<<endl;
        }
        cout<<"Total : $"<<cart->calculateTotal()<<endl;
    }
};

//3. ShoppingCartStorage: only responsible for saving cart to DB

class ShoppingCartStorage{
private:
    ShoppingCart* cart;
public:
    ShoppingCartStorage(ShoppingCart* cart){
        this->cart = cart;
    }

    void saveToSQLDatabase(){
        cout<<"Saving the shopping cart to SQL Database"<<endl;
    }

    void saveToMongoDB(){
        cout<<"Saving the Shopping Cart to MongoDB Database"<<endl;
    }

    void saveToFileDatabase(){
        cout<<"Saving the shopping cart to File Database"<<endl;
    }
}; 

int main(){
    ShoppingCart* cart = new ShoppingCart();

    cart->addProduct(new Product("Laptop", 15000));
    cart->addProduct(new Product("Mouse", 50));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
    db->saveToSQLDatabase();
    

    return 0;
}


// ======================================================================================================
//                                           OUTPUT
// ======================================================================================================

//                                       Shopping Cart Invoice :
//                                       Laptop - $15000
//                                       Mouse - $50
//                                       Total : $15050
//                                       Saving the shopping cart to SQL Database

// =======================================================================================================
