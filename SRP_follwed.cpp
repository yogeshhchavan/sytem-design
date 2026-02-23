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

//1. ShoppingCart: only responsible for cart related business logic.

class ShoppingCart{
private:
    vector<Product*> products;
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

// 2. ShoppingCartprinter : only resposible for printing Invoice

class ShoppingcartPrinter{
private:
    ShoppingCart* cart;
public:
    ShoppingcartPrinter(ShoppingCart* cart){
        this->cart = cart;
    }

    void printInvoice(){
        cout<<"Shopping cart Invoice :\n";
        for(auto p : cart->getProducts()){
            cout<<p->name<<" - $"<<p->price<<endl;
        }
        cout<<"Total : $"<<cart->calculateTotal()<<endl;
    }
};

    // 3. ShoppingcartStorage: Only responsible for saving cart to DB
    class ShoppingCartStorage{
    private:
        ShoppingCart* cart;
    public:
        ShoppingCartStorage(ShoppingCart* cart){
            this->cart = cart;
        }

        void saveToDatabase(){
            cout<<"Saving shopping cart to database..."<<endl;
            // Simulate DB save with a print statement
        }
    };


int main(){
    ShoppingCart* cart = new ShoppingCart();

    cart->addProduct(new Product("Laptop", 15000));
    cart->addProduct(new Product("Mouse", 50));

    ShoppingcartPrinter* printer = new ShoppingcartPrinter(cart);
    printer->printInvoice();

    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
    db->saveToDatabase();

    return 0;
}



// ============================================================================================================
//                                                   OUTPUT
// ============================================================================================================

//                                               Shopping cart Invoice :
//                                               Laptop - $15000
//                                               Mouse - $50
//                                               Total : $15050
//                                               Saving shopping cart to database...

// ============================================================================================================
