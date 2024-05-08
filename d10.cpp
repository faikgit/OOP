//ARBI'S CODE IS TRASH
#include <iostream>
#include <cstring>


using namespace std;

class NegativnaVrednost {
    char msg[100];
public:
    NegativnaVrednost(const char *msg = "") {
        strcpy(this->msg, msg);
    }

    void print() const {
        cout << msg << endl;
    }
};

class Oglas {
    char title[51];
    char category[31];
    char description[101];
    double price;

    void copy(const Oglas &other){
        strcpy(this->title, other.title);
        strcpy(this->description, other.description);
        strcpy(this->category, other.category);
        this->price = other.price;
    }

public:
    Oglas(const char *title = "", const char *category = "", const char *description = "", double price = 0) {
        this->price = price;
        strcpy(this->title, title);
        strcpy(this->description, description);
        strcpy(this->category, category);
    }

    Oglas &operator=(const Oglas &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    double getPrice() const {
        return price;
    }

    bool operator>(const Oglas &other) const {
        return price > other.price;
    }

    friend ostream &operator<<(ostream &os, const Oglas &print) {
       return os << print.title << "\n" << print.description << "\n" << print.price << " evra\n";
    }

    const char *getCategory() const {
        return category;
    }
};

class Oglasnik {
    char name[21];
    Oglas *ads;
    int nrAds;

    void copy(const Oglasnik &other) {
        strcpy(this->name, other.name);
        this->nrAds = other.nrAds;
        if (other.ads != nullptr) {
            this->ads = new Oglas[other.nrAds];
            for (int i = 0; i < other.nrAds; ++i) {
                this->ads[i] = other.ads[i];
            }
        } else {
            this->ads = nullptr;
        }
    }

public:
    Oglasnik(const char *name) : ads(nullptr), nrAds(0) {
        strcpy(this->name, name);
    }

    Oglasnik(const Oglasnik &other) {
        copy(other);
    }

    Oglasnik &operator=(const Oglasnik &other) {
        if (this != &other) {
            delete[] ads;
            copy(other);
        }
        return *this;
    }

    ~Oglasnik() {
        delete[] ads;
    }

    Oglasnik &operator+=(const Oglas &newListing) {
        try {
            if (newListing.getPrice() < 0) {
                throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
            }
            Oglas *temp = new Oglas[nrAds + 1];
            for (int i = 0; i < nrAds; ++i) {
                temp[i] = ads[i];
            }

            temp[nrAds++] = newListing;
            delete[] ads;
            ads = temp;
        }
        catch (NegativnaVrednost &other) {
            other.print();
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Oglasnik &print) {
        os << print.name << endl;
        for (int i = 0; i < print.nrAds; ++i) {
            os << print.ads[i] << endl;
        }
        return os;
    }

    void oglasiOdKategorija(const char *k) {
        for (int i = 0; i < nrAds; ++i) {
            if (strcmp(ads[i].getCategory(),k)==0) {
                cout << ads[i] << endl;
            }
        }
    }

    void najniskaCena() {
        if (nrAds == 0) {
            cout << "Nema dostapni oglasi." << endl;
            return;
        }
        double min = ads[0].getPrice();
        int minIndex = 0;
        for (int i = 1; i < nrAds; ++i) {
            if (ads[i].getPrice() < min) {
                min = ads[i].getPrice();
                minIndex = i;
            }
        }
        cout << ads[minIndex];
    }
};


int main() {

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;

    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl += o;
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    }

    return 0;
}
