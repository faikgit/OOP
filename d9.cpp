#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Exception {
    char sms[50];
public:
    Exception(const char *sms = "") {
        strcpy(this->sms, sms);
    }

    void print() const {
        cout << sms << endl;
    }
};

class Trud {
    char paper;
    int year;

    void copy(const Trud &other) {
        this->paper = other.paper;
        this->year = other.year;
    }

public:
    Trud(char paper = 'c', int year = 0) {
        this->paper = paper;
        this->year = year;
    }

    Trud(const Trud &other) {
        copy(other);
    }

    Trud operator=(const Trud &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    char getPaper() const {
        return paper;
    }

    int getYear() const {
        return year;
    }

    friend istream &operator>>(istream &is, Trud &input) {
        is.get();
        return is >> input.paper >> input.year;
    }
};

class Student {
    char name[31];
    int index;
    int yearEnrollment;
    int grades[100];
    int n;

    void copy(const Student &other) {
        this->index = other.index;
        this->yearEnrollment = other.yearEnrollment;
        this->n = other.n;
        for (int i = 0; i < other.n; i++) {
            this->grades[i] = other.grades[i];
        }
        strcpy(this->name, other.name);
    }

public:
    Student(const char *name = "", int index = 0, int yearEnrollment = 0, const int *grades = nullptr, int n = 0) {
        this->index = index;
        this->yearEnrollment = yearEnrollment;
        this->n = n;
        for (int i = 0; i < n; i++) {
            this->grades[i] = grades[i];
        }
        strcpy(this->name, name);
    }

    Student(const Student &other) {
        copy(other);
    }

    Student &operator=(const Student &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    virtual ~Student() {}

    virtual float rang() const {
        float sum(0);
        for (int i = 0; i < n; i++) {
            sum += (float) grades[i];
        }
        return sum / (float) n;
    }

    friend ostream &operator<<(ostream &os, const Student &print) {
        return os << print.index << " " << print.name << " " << print.yearEnrollment << " " << print.rang() << endl;
    }


    int getEnroll() const {
        return yearEnrollment;
    }

    const char *getName() const {
        return name;
    }

    int getIndex() const {
        return index;
    }

    const int *getGrades() const {
        return grades;
    }

    int getN() const {
        return n;
    }
};

class PhDStudent : public Student {
    Trud *papers;
    int nrPapers;
    static int c;
    static int j;
    
    void copy(const PhDStudent &other){
        this->nrPapers = other.nrPapers;
        if (nrPapers == 0) {
            this->papers = nullptr;
        } else {
            this->papers = new Trud[other.nrPapers];
            for (int i = 0; i < other.nrPapers; i++) {
                this->operator+=(papers[i]);
            }
        }
    }
public:
    PhDStudent(const char *name = "", int index = 0, int enroll = 0, const int *grades = nullptr, int n = 0,const Trud *ts = nullptr, int nrPapers = 0) :
            Student(name, index, enroll, grades, n), nrPapers(0) {
        if (nrPapers == 0) {
            this->papers = nullptr;
        } else {
            this->papers = new Trud[nrPapers];
            for (int i = 0; i < nrPapers; i++) {
                this->operator+=(ts[i]);
            }
        }
    }

    PhDStudent(const PhDStudent &other) : Student(other) {
        copy(other);
    }

    PhDStudent &operator=(const PhDStudent &other) {
        if (this != &other) {
            Student::operator=(other);
            copy(other);
        }
        return *this;
    }

    ~PhDStudent() {
        delete[] papers;
    }

    float rang() const {
        float sum = Student::rang();
        for (int i = 0; i < nrPapers; i++) {
            if (tolower(papers[i].getPaper()) == 'c') {
                sum +=(float) c;
            } else {
                sum +=(float) j;
            }
        }
        return sum;
    }

    PhDStudent &operator+=(const Trud &other) {
        try {
            if (other.getYear() < this->getEnroll()) {
                throw Exception("Ne moze da se vnese dadeniot trud");
            }
        } catch (Exception &ex) {
            ex.print();
            return *this;
        }
        Trud *temp = new Trud[nrPapers + 1];
        for (int i = 0; i < nrPapers; i++) {
            temp[i] = papers[i];
        }
        temp[nrPapers++] = other;
        delete[] papers;
        papers = temp;
        return *this;
    }

    static void setC(int c) {
        PhDStudent::c = c;
    }

    static void setJ(int j) {
        PhDStudent::j = j;
    }
};

int PhDStudent::c = 1;
int PhDStudent::j = 3;

int main() {
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool pri(true);
        for (int i = 0; i < m; i++) {
            PhDStudent *p = dynamic_cast<PhDStudent *>(niza[i]);
            if (p && p->getIndex() == indeks) {
                *p += t;
                pri = false;
            }
        }
        if (pri) {
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        bool pri(true);
        for (int i = 0; i < m; i++) {
            PhDStudent *p = dynamic_cast<PhDStudent *>(niza[i]);
            if (p && p->getIndex() == indeks) {
                *p += t;
                pri = false;
            }
        }
        if (pri) {
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setC(conf);
        PhDStudent::setJ(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}
