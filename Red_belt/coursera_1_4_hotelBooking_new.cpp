#include <iostream>
#include <tuple>
#include <deque>
#include <map>
#include <vector>
#include <set>

using namespace std;

class BookingDatabase{
private:
    map<int64_t, vector<tuple<string, uint32_t, uint16_t>>> query_;
public:
    void addGuest(int64_t time, const string& hotelName, uint32_t guestId, uint16_t roomCount);
    void clearOldBookings(int64_t time);
    int uniqueClientsNumber(const string& hotel_name) const ;
    int bookedRoomsNumber(const string& hotel_name) const ;
    void printDb();
};

void BookingDatabase::addGuest(int64_t time, const string& hotelName, uint32_t guestId, uint16_t roomCount){
    clearOldBookings(time);
    query_[time].push_back(tie(hotelName, guestId, roomCount));
    //printDb();
}

void BookingDatabase::clearOldBookings(int64_t time){
    if (query_.empty()) return;
    auto it = query_.upper_bound(time - 86400);
    query_.erase(begin(query_), it);
}

int BookingDatabase::uniqueClientsNumber(const string& hotel_name) const {
    set<uint32_t> guests;
    for (const auto& elem: query_){
        for (const auto& vecElem: elem.second){
            if (get<0>(vecElem) == hotel_name){
                guests.insert(get<1>(vecElem));
            }
        }
    }
    return guests.size();
}

void BookingDatabase::printDb(){
    cout << "\n--------------------" << endl;
    for(auto t: query_){
        for (auto g: t.second){
            cout << "t = " << t.first << ": " << get<0>(g) << " - " << get<1>(g) << " - " << get<2>(g) << endl;
        }
    }
    cout << "--------------------\n" << endl;
}

int BookingDatabase::bookedRoomsNumber(const string& hotel_name) const {
    int result = 0;
    for (const auto& elem: query_){
        for (const auto& vecElem: elem.second){
            if (get<0>(vecElem) == hotel_name){
                result += get<2>(vecElem);
            }
        }
    }
    return result;
}

int main(){
    //cin.tie(nullptr);
    //ios_base :: sync_with_stdio (false);

    int querySize;
    cin >> querySize;

    BookingDatabase db;

    for (size_t i = 0; i < querySize; ++i){
        string queryCommand;
        cin >> queryCommand;
        if (queryCommand == "BOOK"){
            int64_t time;
            uint32_t client_id;
            uint16_t room_count;
            string hotel_name;

            cin >> time >> hotel_name >> client_id >> room_count;

            db.addGuest(time, hotel_name, client_id, room_count);

        } else {
            string hotel_name;
            cin >> hotel_name;

            if (queryCommand == "CLIENTS") {
                cout << db.uniqueClientsNumber(hotel_name) << '\n';
            } else {
                cout << db.bookedRoomsNumber(hotel_name)   << '\n';
            }
        }
    }
}
