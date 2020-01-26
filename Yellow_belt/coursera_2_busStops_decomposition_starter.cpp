#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

QueryType getQueryType(const string& str){
    if (str == "NEW_BUS") return QueryType::NewBus;
    else if (str == "BUSES_FOR_STOP") return QueryType::BusesForStop;
    else if (str == "STOPS_FOR_BUS") return QueryType::StopsForBus;
    else return QueryType::AllBuses;
}

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string type;
  is >> type;
  switch (getQueryType(type)){
    case QueryType::NewBus:{
      q.type = QueryType::NewBus;
      string& bus = q.bus;
      cin >> bus;
      int stop_count;
      cin >> stop_count;
      vector<string>& stops = q.stops;
      stops.resize(stop_count);
      for (string& stop : stops) {
        cin >> stop;
      }
      break;
    }
    case QueryType::BusesForStop:{
      q.type = QueryType::BusesForStop;
      string& stop = q.stop;
      is >> stop;
      break;
    }
    case QueryType::StopsForBus:{
      q.type = QueryType::StopsForBus;
      string& bus = q.bus;
      is >> bus;
      break;
    }
    case QueryType::AllBuses:
      q.type = QueryType::AllBuses;
  }

  return is;
}

struct BusesForStopResponse {
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses.empty()) {
    os << "No stop";
  } else {
    for (const string& bus : r.buses) {
      os << bus << " ";
    }
  }
  return os;
}

struct StopsForBusResponse {
    vector<string> stop_order;
    map<string, vector<string>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stop_order.empty()) {
        os << "No bus";
      } else {
        for (const string& stop : r.stop_order) {
          if (stop != *r.stop_order.begin()) os << endl;
          os << "Stop " << stop << ": ";
          if (r.stops.at(stop).empty()) {
            os << "no interchange";
          } else {
            for (const string& other_bus : r.stops.at(stop)) {
              os << other_bus << " ";
            }
          }
        }
      }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses.empty()) {
        os << "No buses";
      } else {
        for (const auto& bus_item : r.buses) {
          if (bus_item != *r.buses.begin()) os << endl;
          os << "Bus " << bus_item.first << ": ";
          for (const string& stop : bus_item.second) {
            os << stop << " ";
          }
        }
      }
  return os;
}

class BusManager {
private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
public:
  void AddBus(const string& bus, const vector<string>& stops) {
      buses_to_stops[bus] = stops;
      for (const string& stop : stops) {
        stops_to_buses[stop].push_back(bus);
      }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse buses_response;
    if (stops_to_buses.count(stop) > 0) {
        for (const string& bus : stops_to_buses.at(stop)) {
          buses_response.buses.push_back(bus);
        }
      }
      return buses_response;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
      StopsForBusResponse stops_response;
      if (buses_to_stops.count(bus) != 0) {
        for (const string& stop : buses_to_stops.at(bus)) {
          stops_response.stops[stop];
          stops_response.stop_order.push_back(stop);
          if (stops_to_buses.at(stop).size() > 1){
            for (const string& other_bus : stops_to_buses.at(stop)) {
              if (bus != other_bus) {
                stops_response.stops[stop].push_back(other_bus);
              }
            }
          }
        }
      }
      return stops_response;
  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse all_buses;
    if (!buses_to_stops.empty()) {
        for (const auto& bus_item : buses_to_stops) {
          all_buses.buses[bus_item.first] = bus_item.second;
        }
      }
    return all_buses;
  }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
/*
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string typeStr;
  is >> typeStr;
  if (typeStr == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count = 0;
    is >> stop_count;
    q.stops.resize(stop_count);
    for (auto& stop : q.stops) {
      is >> stop;
    }
  } else if (typeStr == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (typeStr == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (typeStr == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }

  return is;
}

struct BusesForStopResponse {
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses.empty()) {
    os << "No stop" << endl;
  } else {
    for (const auto& bus : r.buses) {
      os << bus << " ";
    }
    os << endl;
  }
  return os;
}

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops_for_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops_for_buses.empty()) {
    os << "No bus" << endl;
  } else {
    for (const auto& stop_and_buses : r.stops_for_buses) {
      os << "Stop " << stop_and_buses.first << ":";
      if (stop_and_buses.second.size() == 1) {
        os << " no interchange" << endl;
      } else {
        for (const auto& bus : stop_and_buses.second) {
          if (bus != r.bus) {
            os << " " << bus;
          }
        }
        os << endl;
      }
    }
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
    os << "No buses" << endl;
  } else {
    for (const auto& bus_and_stops : r.buses_to_stops) {
      os << "Bus " << bus_and_stops.first << ":";
      for (const auto& stop : bus_and_stops.second) {
        os << " " << stop;
      }
      os << endl;
    }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops.insert(make_pair(bus, stops));
    for (const auto& stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
      return BusesForStopResponse{vector<string>()};
    } else {
      return BusesForStopResponse{stops_to_buses.at(stop)};
    }
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    vector<pair<string, vector<string>>> result;

    if (buses_to_stops.count(bus) > 0) {
      for (const auto& stop : buses_to_stops.at(bus)) {
        result.push_back(make_pair(stop, stops_to_buses.at(stop)));
      }
    }
    return StopsForBusResponse{bus, result};
  }

  AllBusesResponse GetAllBuses() const {
    return AllBusesResponse{buses_to_stops};
  }

private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};
*/
