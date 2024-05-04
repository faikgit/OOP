#include <iostream>
#include <cstring>

using namespace std;

class Book {
protected:
    string isbn;
    string title;
    string author;
    float basePrice;
public:
    Book(const string &isbn, const string &title, const string &author, int basePrice) : isbn(isbn), title(title),
    author(author),basePrice(basePrice) {}

    virtual float bookPrice() const {
        return basePrice;
    }

    bool operator>(const Book &other) const {
        return bookPrice() > other.bookPrice();
    }

    friend ostream &operator<<(ostream &os, const Book &book) {
        os << book.isbn << ": " << book.title << ", " << book.author << " "
           << book.bookPrice() << endl;
        return os;
    }

    void setIsbn(const string &isbn) {
        Book::isbn = isbn;
    }
};

class OnlineBook : public Book {
private:
    char *url;
    int mb;

    void copy(const OnlineBook &other) {
        isbn = other.isbn;
        title = other.title;
        author = other.author;
        this->basePrice = other.basePrice;
        this->url = new char[other.mb];
        strcpy(this->url, other.url);
        this->mb = other.mb;
    }

public:
    OnlineBook(const string &isbn = "", const string &title = "", const string &author = "", int basePrice = 0,const char *url = nullptr, int mb = 0) :
    Book(isbn, title, author, basePrice) {
        this->url = new char[mb];
        strcpy(this->url, url);
        this->mb = mb;
    }

    OnlineBook(const OnlineBook &other) : Book(other), url(nullptr), mb(other.mb) {
        copy(other);
    }

    OnlineBook &operator=(const OnlineBook &other) {
        if (this != &other) {
            Book::operator=(other);
            delete[] url;
            copy(other);
        }
        return *this;
    }

    ~OnlineBook() {
        delete[] url;
    }

    float bookPrice() const {

        float price = basePrice;
        if (mb > 20) {
            price *= 1.20;
        }
        return price;
    }

    void setISBN(const string &isbn) {
        this->isbn = isbn;
    }
};

class PrintBook : public Book {
private:
    int weight;
    bool stock;
public:
    PrintBook(const string &isbn, const string &title, const string &author, int basePrice, int weight, bool stock)
            : Book(isbn, title, author, basePrice) {
        this->weight = weight;
        this->stock = stock;
    }

    PrintBook(const PrintBook &other) : Book(other), weight(other.weight), stock(other.stock) {}

    PrintBook &operator=(const PrintBook &other) {
        if (this != &other) {
            Book::operator=(other);
            weight = other.weight;
            stock = other.stock;
        }
        return *this;
    }

    float bookPrice() const {
        float price = basePrice;
        if (weight > 0.7) {
            price *= 1.15;
        }
        return price;
    }

};

void mostExpensiveBook(Book **books, int n) {
    float maxOprice = 0, maxPprice = 0;
    OnlineBook *mostexpesiveO = nullptr;
    PrintBook *mostexpensiveP = nullptr;

    cout << "FINKI-Education" << endl;

    for (int i = 0; i < n; i++) {
        OnlineBook *onlineBook = dynamic_cast<OnlineBook *>(books[i]);
        if (onlineBook) {
            float price = onlineBook->bookPrice();
            if (price > maxOprice) {
                maxOprice = price;
                mostexpesiveO = onlineBook;
            }
        } else {
            PrintBook *printBook = dynamic_cast<PrintBook *>(books[i]);
            if (printBook) {
                float price = printBook->bookPrice();
                if (price > maxPprice) {
                    maxPprice = price;
                    mostexpensiveP = printBook;
                }
            }
        }
    }
    int count(0), count1(0);
    cout << "Total number of online books: ";
    for (int i = 0; i < n; i++) {
        OnlineBook *onlineBook = dynamic_cast<OnlineBook *>(books[i]);
        if (onlineBook) {
            count++;
        }
    }
    cout << count << endl;

    cout << "Total number of print books: ";
    for (int i = 0; i < n; i++) {
        PrintBook *printBook = dynamic_cast<PrintBook *>(books[i]);
        if (printBook) {
            count1++;
        }
    }
    cout << count1 << endl;

    cout << "The most expensive book is:" << endl;
    if (maxOprice > maxPprice)
        cout << *mostexpesiveO << endl;
    else
        cout << *mostexpensiveP << endl;
}

int main() {

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}
