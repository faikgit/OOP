#include <cstring>
#include <iostream>

using namespace std;

enum Size {
    small, medium, large
};

class Pizza {
protected:
    string ingredients;
    float basePrice;
    string name;
public:
    Pizza(const string &name, const string &ingredients, float basePrice) : name(name), ingredients(ingredients),
    basePrice(basePrice) {}

    virtual float price() const{
        return basePrice;
    }
    bool operator<(const Pizza &other) const {
        return  price() < other.price();
    }
    virtual ~Pizza() = default;
};

class FlatPizza : public Pizza {
private:
    Size size;
public:
    FlatPizza(const string &name = "", const string &ingredients = "", float basePrice = 0, Size size = small)
            : Pizza(name, ingredients, basePrice), size(size) {}

    float price() const {
        float pr = basePrice;
        if (size == 0) {
            pr *= 1.10;
        } else if (size == 1) {
            pr *= 1.20;
        } else {
            pr *= 1.30;
        }
        return pr;
    }


    friend ostream &operator<<(ostream &os, const FlatPizza &print) {
        os << print.name << ": " << print.ingredients << ", ";
        if(print.size==0){
            os << "small";
        }
        else if(print.size == 1){
            os << "medium";
        }
        else{
            os << "family";
        }
        os<< " - " << print.price() << endl;
        return os;
    }


};

class FoldedPizza : public Pizza {
private:
    bool white = true;
public:
    FoldedPizza(const string &name, const string &ingredients, float basePrice) : Pizza(name, ingredients,basePrice){}


    float price() const {
        float pr = basePrice;
        if (white) {
            pr *= 1.10;
        } else {
            pr *= 1.30;
        }
        return pr;
    }


    void setWhiteFlour(bool b) {
        white = b;
    }

    friend ostream &operator<<(ostream &os, const FoldedPizza &print) {
        os << print.name << ": " << print.ingredients << ", ";
        if (print.white) {
            os << "wf";
        } else {
            os << "nwf";
        }
        os << " - " << print.price() << endl;
        return os;
    }

};
void expensivePizza(Pizza **pizza, int n) {
    if (n <= 0 || pizza == nullptr) {
        cout << "Invalid input." << endl;
        return;
    }

    Pizza *mostExpensivePizza = pizza[0];
    for (int i = 1; i < n; ++i) {
        if (*mostExpensivePizza < *pizza[i]) {
            mostExpensivePizza = pizza[i];
        }
    }

    //if  there is a simpler way tell me
    if (FlatPizza* flatPizza = dynamic_cast<FlatPizza*>(mostExpensivePizza)) {
        cout << *flatPizza << endl;
    } else if (FoldedPizza* foldedPizza = dynamic_cast<FoldedPizza*>(mostExpensivePizza)) {
        cout << *foldedPizza << endl;
    }
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}
