#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    BusManager::buses_to_stops.insert(make_pair(bus, stops));
    for (const auto& stop : stops) {
      BusManager::stops_to_buses[stop].push_back(bus);
    }
  }

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if (BusManager::stops_to_buses.count(stop) == 0) {
      return BusesForStopResponse{vector<string>()};
    } else {
      return BusesForStopResponse{BusManager::stops_to_buses.at(stop)};
    }
  }

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    vector<pair<string, vector<string>>> result;

    if (BusManager::buses_to_stops.count(bus) > 0) {
      for (const auto& stop : BusManager::buses_to_stops.at(bus)) {
        result.push_back(make_pair(stop, BusManager::stops_to_buses.at(stop)));
      }
    }
    return StopsForBusResponse{bus, result};
  }

AllBusesResponse BusManager::GetAllBuses() const {
    return AllBusesResponse{BusManager::buses_to_stops};
  }
