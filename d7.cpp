#include<iostream>
#include <cstring>

using namespace std;

class OutOfBoundException {
private:
    char message[101];

public:
    OutOfBoundException(const char* message = "") {
        strcpy(this->message, message);
    }
    void print() const {
        cout << "Exception: " << message << endl;
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;

public:
    Karticka(const char* smetka, int pin) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    virtual ~Karticka() {}

    int tezinaProbivanje() const {
        int counter(0);
        int pass = pin;
        while (pass != 0) {
            counter++;
            pass /= 10;
        }
        return counter;
    }

    const char* getSmetka() const {
        return smetka;
    }

    bool getDopolnitelenPin() const {
        return povekjePin;
    }

    friend ostream& operator<<(ostream& os, const Karticka& karticka) {
        os << karticka.smetka << ": " << karticka.tezinaProbivanje();
        return os;
    }
};

class SpecijalnaKarticka : public Karticka {
private:
    int* array;
    int nr;

public:
    SpecijalnaKarticka(const char* smetka, int pin) : Karticka(smetka, pin) {
        this->array = nullptr;
        this->nr = 0;
    }

    SpecijalnaKarticka(const SpecijalnaKarticka& other) : Karticka(other) {
        copy(other);
    }

    SpecijalnaKarticka& operator=(const SpecijalnaKarticka& other) {
        if (this != &other) {
            Karticka::operator=(other);
            delete[] array;
            copy(other);
        }
        return *this;
    }

    ~SpecijalnaKarticka() {
        delete[] array;
    }

    SpecijalnaKarticka operator+=(const int &other) {
        if (nr >= p) {
            throw OutOfBoundException();
        }

        int *temp = new int[nr + 1];

        for (int i = 0; i < nr; ++i) {
            temp[i] = array[i];
        }
        temp[nr++] = other;
        delete[] array;
        array = temp;
        return *this;
    }

    int getNr() const {
        return nr;
    }

    static int getP() {
        return p;
    }

private:
    static int p;

    void copy(const SpecijalnaKarticka& other) {
        if (other.nr > 0) {
            array = new int[other.nr];
            for (int i = 0; i < other.nr; ++i) {
                array[i] = other.array[i];
            }
        } else {
            array = nullptr;
        }
        nr = other.nr;
    }
};

int SpecijalnaKarticka::p = 4;

class Banka {
private:
    char naziv[30];
    Karticka* karticki[20];
    int broj;
    static int LIMIT;

public:
    Banka(const char* naziv, Karticka** karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            } else {
                this->karticki[i] = new Karticka(*karticki[i]);
            }
        }
        this->broj = broj;
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) {
            delete karticki[i];
        }
    }

    void pecatiKarticki() const {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < broj; ++i) {
            cout << *karticki[i] << endl;
        }
    }

    static void setLIMIT(int newLimit) {
        LIMIT = newLimit;
    }

    void dodadiDopolnitelenPin(const char* smetka, int novPin) {
        for (int i = 0; i < broj; ++i) {
            if (strcmp(karticki[i]->getSmetka(), smetka) == 0) {
                SpecijalnaKarticka* specijalnaKarticka = dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if (specijalnaKarticka && specijalnaKarticka->getNr() < SpecijalnaKarticka::getP()) {
                    try {
                        *specijalnaKarticka += novPin;
                    } catch (const OutOfBoundException& e) {
                        e.print();
                    }
                    return;
                }
            }
        }
    }
};

int Banka::LIMIT = 7;

int main() {
    Karticka** niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka*[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) {
        delete niza[i];
    }
    delete[] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;

        komercijalna.dodadiDopolnitelenPin(smetka, pin);
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

    return 0;
}
