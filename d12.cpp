#include <iostream>
#include <cstring>

using namespace std;

enum tip {
    smartphone, computer
};

class InvalidProductionDate {
private:
    char sms[101];
public:
    InvalidProductionDate(const char *sms = "") {
        strcpy(this->sms, sms);
    }

    void print() {
        cout << sms << endl;
    }
};

class Device {
private:
    char name[101];
    tip type;
    static double inspection;
    int year;

    void copy(const Device &other) {
        strcpy(this->name, other.name);
        this->type = other.type;
        this->year = other.year;
    }

public:
    Device(const char *name = "", tip type = computer, int year = 0) {
        strcpy(this->name, name);
        this->type = type;
        this->year = year;
    }

    Device(const Device &other) {
        copy(other);
    }

    Device& operator=(const Device &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    static void setPocetniCasovi(int insp) {
        Device::inspection = insp;
    }

    double time() const {
        double sum(0);
        if (year > 2015) {
            sum += 2;
        }
        if (type == computer) {
            sum += 2;
        }
        return inspection + sum;
    }

    friend ostream &operator<<(ostream &os, const Device &print) {
        os << print.name << "\n";
        if (print.type == computer) {
            os << "Laptop ";
        } else {
            os << "Mobilen ";
        }
        os << print.time() << "\n";
        return os;
    }

    int getYear() const {
        return year;
    }

};

double Device::inspection = 1;


class MobileServis {
private:
    char address[101];
    Device *devices;
    int nr;

public:
    MobileServis(const char *address = "") {
        strcpy(this->address, address);
        this->devices = nullptr;
        this->nr = 0;
    }

    MobileServis& operator+=(const Device &newDev) {
        try {
            if (newDev.getYear() > 2019 || newDev.getYear() < 2000) {
                throw InvalidProductionDate("Невалидна година на производство");
            }
        } catch (InvalidProductionDate &print) {
            print.print();
            return *this;
        }
        Device *temp = new Device[nr + 1];
        for (int i = 0; i < nr; ++i) {
            temp[i] = devices[i];
        }
        temp[nr++] = newDev;
        delete[] devices;
        devices = temp;
        return *this;
    }

    void pecatiCasovi() {
        cout << "Ime: " << address << endl;
        for (int i = 0; i < nr; ++i) {
            cout << devices[i];
        }
    }

    
};
int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            t += tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            t += tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            t += tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);

            t += tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            t += tmp;
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

