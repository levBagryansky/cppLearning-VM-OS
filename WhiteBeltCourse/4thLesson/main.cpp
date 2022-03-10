#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <system_error>

using namespace std;

string AskTimeServer();

class TimeServer {
public:
    string GetCurrentTime(){
        try{
            last_fetched_time = AskTimeServer();
            return last_fetched_time;
        }
        catch (system_error&) {
            return last_fetched_time;
        }

    }
private:
    string last_fetched_time = "00:00:00";
};

int main(){
    return 0;
}