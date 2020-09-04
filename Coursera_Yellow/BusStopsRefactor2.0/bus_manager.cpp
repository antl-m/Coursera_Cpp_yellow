#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
	buses_to_stops[bus] = stops;
	for (const std::string& stop : buses_to_stops[bus]) {
		stops_to_buses[stop].push_back(bus);
	}
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
	BusesForStopResponse res;
	if (stops_to_buses.count(stop) == 0) {
		res.buses.push_back("No stop");
	}
	else {
		res.buses = stops_to_buses.at(stop);
	}
	return res;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
	StopsForBusResponse res;
	if (buses_to_stops.count(bus) != 0) {
		for (const std::string& stop : buses_to_stops.at(bus)) {
			res.order.push_back(stop);
			if (stops_to_buses.at(stop).size() == 1) {
				res.base[stop].push_back("no interchange");
			}
			else {
				for (const std::string& other_bus : stops_to_buses.at(stop)) {
					if (bus != other_bus) {
						res.base[stop].push_back(other_bus);
					}
				}
			}
		}
	}
	return res;
}

AllBusesResponse BusManager::GetAllBuses() const {
	AllBusesResponse res;
	res.base = buses_to_stops;
	return res;
}
