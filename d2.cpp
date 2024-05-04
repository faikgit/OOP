#include <iostream>
#include <string>

using namespace std;

class Vozac{
protected:
    string name;
    int age;
    int nrRaces;
    bool veteran;
public:
    Vozac(const string &name, int age, int nrRaces, bool veteran) : name(name), age(age), nrRaces(nrRaces),
    veteran(veteran) {}

    friend ostream& operator<<( ostream& os,const Vozac &print){
        os << print.name << "\n" << print.age << "\n" << print.nrRaces << "\n";
        if(print.veteran){
            os << "VETERAN " << endl;
        }
        return os;
    }
    virtual float danok() {
        return danok();
    }
    virtual float earn() const = 0;
    
    bool operator==(const Vozac& driver) {
        return (this->earn() == driver.earn());
    }

};
class Avtomobilist:public Vozac{
private:
    float price;
public:
    Avtomobilist(const string &name, int age, int nrRaces, bool veteran, float price) : Vozac(name, age, nrRaces,veteran), price(price) {}

    float earn() const{
        float earning = price / 5;
        return earning;
    }
    float danok(){
        float tax = earn();
        if(nrRaces > 10){
            tax *= 0.15;
        }else{
            tax *= 0.10;
        }
        return tax;
    }
};

class Motociklist:public Vozac{
private:
    int power;
public:
    Motociklist(const string &name, int age, int nrRaces, bool veteran, int power) : Vozac(name, age, nrRaces, veteran),
    power(power) {}

    float earn() const{
        float earning = power * 20;
        return earning;
    }
    float danok(){
        float tax = earn();
        if(veteran){
            tax *= 0.25;
        }else{
            tax *= 0.20;
        }
        return tax;
    }
};

int soIstaZarabotuvachka(Vozac** vozaci, int n, Vozac* driver) {
    float driverEarnings = driver->earn();
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (vozaci[i]->earn() == driverEarnings) {
            count++;
        }
    }
    return count;
}


int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
