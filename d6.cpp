#include <iostream>
#include <cstring>

using namespace std;

class ExistingGame {
private:
    char msg[256];

public:
    ExistingGame(char msg_txt[]) {
        strncpy(this->msg, msg_txt, 255);
        this->msg[255] = '\0';
    }

    void message() {
        cout << this->msg << endl;
    }
};

class Game {
protected:
    char name[100];
    float price;
    bool buy;

public:
    Game(const char name[] = "", float price = 0, bool buy = false) : price(price), buy(buy) {
        strncpy(this->name, name, 99);
        this->name[99] = '\0';
    }

    friend istream& operator>>(istream& is, Game& input) {
        is.get();
        is.getline(input.name, 100);
        is >> input.price >> input.buy;
        return is;
    }

    friend ostream& operator<<(ostream& os, const Game& print) {
        os << "Game: " << print.name << ", regular price: $" << print.price;
        if (print.buy) {
            os << ", bought on sale";
        }
        return os;
    }

    bool operator==(const Game& other) {
        return strcmp(name, other.name) == 0;
    }

    virtual float get_price() {
        if (buy) {
            return price * 0.3F;
        }
        return price;
    }
};

class SubscriptionGame : public Game {
private:
    float fee;
    int month;
    int year;

public:
    SubscriptionGame(const char name[] = "", float price = 0, bool buy = false, float fee = 0, int month = 0, int year = 0) : Game(name, price, buy), fee(fee), month(month), year(year) {}

    friend istream& operator>>(istream& is, SubscriptionGame& input) {
        is.get();
        is.getline(input.name, 100);
        is >> input.price >> input.buy >> input.fee >> input.month >> input.year;
        return is;
    }

    friend ostream& operator<<(ostream& os, const SubscriptionGame& sg) {
        const Game& g = sg;
        os << g << ", monthly fee: $" << sg.fee << ", purchased: " << sg.month << "-" << sg.year << endl;
        return os;
    }

    float get_price() override {
        float total_price = Game::get_price();

        int months = 0;
        if (year < 2018) {
            months = (12 - month) + (2017 - year) * 12 + 5;
        } else {
            months = 5 - month;
        }

        total_price += months * fee;

        return total_price;
    }
};

class User {
private:
    char name[100];
    Game** games;
    int nr;

    void copy(const User& other) {
        strncpy(this->name, other.name, 99);
        this->name[99] = '\0';
        this->nr = other.nr;
        this->games = new Game*[other.nr];
        for (int i = 0; i < other.nr; ++i) {
            this->games[i] = new Game(*other.games[i]);
        }
    }

public:
    User(const char name[]) : nr(0) {
        strncpy(this->name, name, 99);
        this->name[99] = '\0';
        games = nullptr;
    }

    User(User& other) {
        copy(other);
    }

    ~User() {
        for (int i = 0; i < this->nr; ++i) {
            delete this->games[i];
        }
        delete[] games;
    }

    User& operator=(User& other) {
        if (this != &other) {
            for (int i = 0; i < this->nr; ++i) {
                delete this->games[i];
            }
            delete[] games;
            copy(other);
        }
        return *this;
    }

    User& operator+=(Game& other) {
        Game** temp = new Game*[this->nr + 1];
        for (int i = 0; i < (this->nr); ++i) {
            if (*(this->games[i]) == other) {
                throw ExistingGame("The game is already in the collection");
            }
            temp[i] = games[i];//not sure if needed but works
        }
        for (int i = 0; i < (this->nr); ++i) {
            temp[i] = games[i];
        }
        SubscriptionGame* sub = dynamic_cast<SubscriptionGame*>(&other);//polymorphism
        if (sub) {
            temp[nr] = new SubscriptionGame(*sub);
        } else {
            temp[nr] = new Game(other);
        }

        delete[] this->games;
        this->games = temp;
        this->nr++;
        return *this;
    }

    Game& get_game(int i) {
        return (*(this->games[i]));
    }

    float total_spent() {
        float sum = 0.0f;
        for (int i = 0; i < this->nr; ++i) {
            sum += games[i]->get_price();
        }
        return sum;
    }

    const char* getName() const {
        return name;
    }

    int get_games_number() {
        return this->nr;
    }
};

ostream& operator<<(ostream& o, User& u) {
    o << "\nUser: " << u.getName() << "\n";
    for (int i = 0; i < u.get_games_number(); ++i) {
        Game* g;
        SubscriptionGame* sg;
        g = &(u.get_game(i));
        sg = dynamic_cast<SubscriptionGame*>(g);
        if (sg) {
            o << "- " << (*sg);
        } else {
            o << "- " << (*g);
        }
        o << "\n";
    }
    return o;
}

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
