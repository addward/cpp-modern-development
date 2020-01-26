#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    int n, length = 0;
    cin >> n;
    vector<string> commands = {"WORRY", "QUIET", "COME", "WORRY_COUNT"};
    vector<int> worry;
    int flag = -1;
    for(int i = 0; i < 2*n; i++){
        if (i%2 == 0){
            string command;
            cin >> command;
            flag = (int)(find(commands.begin(), commands.end(), command) - commands.begin());
            if (flag == 3){
                i++;
                cout << worry.size() << endl;
            }
            continue;
        }

        int parameter;
        cin >> parameter;
        vector<int>::iterator pos = find(worry.begin(), worry.end(), parameter);

        switch (flag){
        case 0: if (worry.end() == find(worry.begin(), worry.end(), parameter)){
                    worry.push_back(parameter);
                    break;
                }
        case 1: if (pos != worry.end()){
                    worry.erase(pos);
                    break;
                }
        case 2: if (parameter > 0){
                    length += parameter;
                }else{
                    length += parameter;
                    for (int i = worry.size() - 1; i >= 0; i--){
                        if (worry[i] > length - 1){
                            worry.erase(worry.begin() + i);
                        }
                    }
                }
                break;
        }
    }
    return 0;
}
