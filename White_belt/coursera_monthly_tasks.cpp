#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    vector<int> months = {31, 28, 31, 30, 31, 30 ,31 , 31, 30, 31, 30, 31};
    int curr_month = 0;
    int num_commands;
    vector<vector<string>> tasks;
    tasks.resize(months[curr_month], vector<string>(0));

    cin >> num_commands;
    for(int i = 0; i < num_commands; i += 1){
        string command;
        cin >> command;
        if (command == "ADD"){
            int day;
            string task;
            cin >> day;
            day -= 1;
            cin >> task;
            tasks[day].push_back(task);
        } else if (command == "NEXT"){
            int nextmonth;
            if (curr_month == 11) nextmonth = 0;
            else nextmonth = curr_month + 1;
            if (months[nextmonth] > months[curr_month]){
                for(int i = 0; i< months[nextmonth] - months[curr_month]; i++){
                    tasks.push_back(vector<string>(0));
                }
            }
            else{
                int diff = months[curr_month] - months[nextmonth];

                for(int i = 1; i <= diff; i++){
                    tasks[tasks.size() - diff - 1].insert(tasks[tasks.size() - diff - 1].end(),
                                                          tasks[tasks.size() - diff + i - 1].begin(),
                                                          tasks[tasks.size() - diff + i - 1].end());
                }
                tasks.erase(tasks.end() - diff, tasks.end());
            }
            curr_month = nextmonth;
        } else if (command == "DUMP"){
            int day;
            cin >> day;
            day -= 1;
            cout << tasks[day].size() << " ";
            for (int i = 0; i < tasks[day].size(); i++){
                cout << tasks[day][i];
                if (i != tasks[day].size() - 1) cout << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
