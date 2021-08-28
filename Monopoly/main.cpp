#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>

#define MaxField 24

using namespace std;

class Company{
public:
    Company(string new_name, int new_number, int new_cost, int new_deposit,
            int new_buyback, int new_branch_cost, vector<int> new_rents){
        name = new_name;
        number = new_number;
        cost = new_cost;
        deposit = new_deposit;
        buyback = new_buyback;
        branch_cost = new_branch_cost;
        rents = new_rents;
    }

    Company(string new_name, int new_number, int new_cost,
             int new_branch_cost, vector<int> new_rents){
        name = new_name;
        number = new_number;
        cost = new_cost;
        deposit = cost / 2;
        buyback = buyback * 6 / 5;
        branch_cost = new_branch_cost;
        rents = new_rents;
    }

    string GetName() const{
        return name;
    }
    int GetNumber() const{
        return number;
    }
    int GetCost() const{
        return cost;
    }
    int GetDeposit() const{
        return deposit;
    }
    int GetBuyback() const{
        return buyback;
    }
    int GetBranch_cost() const{
        return branch_cost;
    }
    vector<int> GetRents() const{
        return rents;
    }

public:
    string master;
    int status;

private:
    string name;
    int number;
    int cost; // стоимость
    int deposit; // залог
    int buyback; // выкуп
    int branch_cost; // стоимость филиала
    vector<int> rents; // базовая рента
};

class Category{
private:
    vector<Company> companies;
};

class Player{
public:
    Player(string new_name){
        name = new_name;
        capital = 10000;
        field_now = 0;
    }

    int field_now = 0;
    string name;
    int capital = 10000;
};

Company chanel("Perfumery", 1, 600, 300,
               360, 500, {20, 40, 80, 160, 320, 640});
Company boss("Hugo Boss", 3, 600, 300,
             360, 500, {40, 80, 160, 320, 640, 1280});
Company adidas("Adidas", 6, 1000, 500,
               600, 500, {60, 120, 240, 480, 960, 1920});
Company puma("Puma", 8, 1000, 500,
             600, 500, {60, 120, 240, 480, 960, 1920});
Company lacoste("Lacoste", 9, 1000, 500,
                600, 500, {60, 120, 240, 480, 960, 1920});
Company vk("VK", 11, 1400, 700,
           840, 750, {100, 200, 400, 800, 1600});
Company facebook("Facebook", 13, 1400, 700,
                 840, 750, {110, 220, 440, 880, 1760, 3520});
Company twitter("Twitter", 14, 1400, 700,
                840, 750, {120, 240, 480, 960, 1920, 3840});
Company cola("Coca-Cola", 16, 1800, 900,
             1080, 100, {140, 280, 560, 1120, 2240, 4480});
Company pepsi("Pepsi-Cola", 18, 1800, 900,
              1080, 100, {140, 280, 560, 1120, 2240, 4480});
Company fanta("Fanta", 19, 2000, 1000,
              1200, 1000, {160, 320, 640, 1280, 2560, 5120});
Company american("American Airlines", 21, 2200, 1250,
                 {180, 360, 720, 1440, 2880, 5760});
Company lufthansa("Lufthansa", 23, 2200, 1250,
                  {180, 360, 720, 1440, 2880, 5760});
Company british("British Airlines", 24, 2400, 1250,
                {200, 400, 800, 1600, 3200, 6400});


map<int, Company> fields2Company{
        {chanel.GetNumber(),    chanel},
        {boss.GetNumber(),      boss},
        {adidas.GetNumber(),    adidas},
        {puma.GetNumber(),      puma},
        {lacoste.GetNumber(),   lacoste},
        {vk.GetNumber(),        vk},
        {facebook.GetNumber(),  facebook},
        {twitter.GetNumber(),   twitter},
        {cola.GetNumber(),      cola},
        {pepsi.GetNumber(),     pepsi},
        {fanta.GetNumber(),     fanta},
        {american.GetNumber(),  american},
        {lufthansa.GetNumber(), lufthansa},
        {british.GetNumber(),   british}
}; //  Словарь полей и компаний на них.

int rollDice(){
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

void printGameBoard(const vector<Player>& players){
    ostream& os = cout;
    //system("start output.txt");
    os << "Game board:" << endl;
    for (int i = 0; i < MaxField; ++i) {
        os << "Field " << setw(2) << right << setfill('0') << i <<": " << setw(18) << setfill(' ');

        if (fields2Company.count(i) == 0)
            os << left << "empty";
        else{
            os << left << fields2Company.at(i).GetName();
        }
        os << '|';
        for (const Player& item: players){
            if (item.field_now == i){
                os << ' ' << item.name;
            }
        }
        os << endl;
    }
    os << endl;
    //os.close();
    //system("start output.txt");

}

vector<Player> readPlayers (istream& is, ostream& os){
    setlocale(LC_ALL, "Russian");
    os << "Enter number of players (not more than 6):";
    int N;
    is >> N;
    cout << "N is: " << N << endl;
    if (N < 1 || N > 6)
        throw invalid_argument("Wrong number of players");

    vector<Player> players;
    os << "Enter names separated by a space:";

    for (int i = 0; i < N; ++i) {
        string name;
        is >> name;
        Player player(name);
        players.push_back(player);
        }

    return players;
}

string getCommand(string line){
    stringstream stream(line);
    string command;
    string word;
    stream >> word;
    command += word;
    if (word == "roll" || word == "finish"){
        stream >> word;
        command += ' ';
        command += word;
    }
    //cout << "Command was:" << command << endl;
    return command;
}

bool verifyCommand(string command){
    if (command == "roll dices" ||
        command == "finish game" ||
        command.empty())
        return true;
    return false;
}

int main() {
    srand(time(0));

    vector<Player> players = readPlayers(cin, cout);
    string l;
    getline(cin, l);

    while (players.size() > 0){
        for (int i = 0; i < players.size(); ++i) {
            printGameBoard(players);

            //cout << players[i].name << ", Enter command (roll dice, finish game) ";
            string line;
            cout << players[i].name << ", Enter command (roll dices, finish game)" << endl;
            getline(std::cin, line); // полностью извлекаем строку в переменную myName
            string command = getCommand(line);

            if (verifyCommand(command)) {
                if (command == "finish game")
                    players.clear();
                else if (command == "roll dices" || command.empty()){
                    int rand_num1 = rand() % 6 + 1;
                    int rand_num2 = rand() % 6 + 1;
                    cout << "Oh, there are " << rand_num1 << " + "<< rand_num2 << endl;
                    int rand_num = rand_num1 + rand_num2;
                    players[i].field_now = (players[i].field_now + rand_num) % MaxField;
                    cout << "Now field is: " << players[i].field_now << endl;

                    printGameBoard(players);
                    if (fields2Company.count(players[i].field_now) > 0){ //Если поле- компания
                        string master;
                        master = fields2Company.at(players[i].field_now).master;
                        if (master != players[i].name){
                            ;
                        }
                        else{
                            ;
                        }
                    }

                    if (rand_num1 == rand_num2)
                        i--;

                }

            } else {
                cout << "O, no! Invalid cum :(" << endl;
                i--;
            }

        }
    }

    //PrintGameBoard(cout, fields2Company);

    //system("start output.txt");
    //system("taskkill /im notepad.exe");

    return 0;
}
