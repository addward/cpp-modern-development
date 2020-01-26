#include <iostream>
#include <tuple>
#include <deque>
#include <map>

using namespace std;

class BookingDatabase{
private:
    map<string, map<uint32_t, uint16_t>> hotel_guests_;
    map<string, uint64_t> hotel_rooms_;
    map<int64_t, deque<tuple<uint32_t, string, uint16_t>>> time_bookings_;
public:
    void addGuest(int64_t time, const string& hotelName, uint32_t guestId, uint16_t roomCount);
    void clearOldBookings(int64_t time);
    int uniqueClientsNumber(const string& hotel_name) const ;
    int bookedRoomsNumber(const string& hotel_name) const ;
    void printDb();
};

void BookingDatabase::addGuest(int64_t time, const string& hotelName, uint32_t guestId, uint16_t roomCount){
    clearOldBookings(time);
    hotel_guests_[hotelName][guestId] += roomCount;
    time_bookings_[time].push_back(tie(guestId, hotelName, roomCount));
    hotel_rooms_[hotelName] += roomCount;
    //printDb();
}

void BookingDatabase::clearOldBookings(int64_t time){
    if (time_bookings_.empty()) return;
    auto it = begin(time_bookings_);
    if (time - prev(end(time_bookings_))->first >= 86400) {
        time_bookings_.clear();
        hotel_guests_.clear();
        hotel_rooms_.clear();
        return;
    }
    while (it != end(time_bookings_) && time - it->first >= 86400){
        for (const auto& tuples: it->second){
            uint32_t clientId  = get<0>(tuples);
            string hotelName   = get<1>(tuples);
            uint16_t roomCount = get<2>(tuples);
            hotel_guests_[hotelName][clientId] -= roomCount;
            hotel_rooms_[hotelName] -= roomCount;
            if (hotel_guests_[hotelName][clientId] == 0){
                hotel_guests_[hotelName].erase(clientId);
            }
        }
        ++it;
    }
    time_bookings_.erase(begin(time_bookings_), it);
}

int BookingDatabase::uniqueClientsNumber(const string& hotel_name) const {
    if (hotel_guests_.count(hotel_name) == 0) {
        return 0;
    }
    return hotel_guests_.at(hotel_name).size();
}

void BookingDatabase::printDb(){
    cout << "--------------------" << endl;
    for(auto h: hotel_guests_){
        for (auto g: h.second){
            cout << h.first << ": " << g.first << " - " << g.second << endl;
        }
    }
    for (auto t: time_bookings_){
        for (auto tup: t.second){
            uint32_t clientId  = get<0>(tup);
            string hotelName   = get<1>(tup);
            uint16_t roomCount = get<2>(tup);
            cout << t.first << ": " << "C_id: " << clientId << ", hotel: " << hotelName << ", roomCount: " << roomCount << endl;
        }
    }
    cout << "--------------------" << endl;
}

int BookingDatabase::bookedRoomsNumber(const string& hotel_name) const {
    if (hotel_rooms_.count(hotel_name) == 0) {
        return 0;
    }
    return hotel_rooms_.at(hotel_name);
}

int main(){
    cin.tie(nullptr);
    ios_base :: sync_with_stdio (false);

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
