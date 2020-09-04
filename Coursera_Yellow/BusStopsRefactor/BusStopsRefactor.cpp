#include <string>
#include <iostream>
#include <vector>
#include <map>
/*
10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES
*/
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
	string str;
	is >> str;
	if (str == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> q.bus;
		int count;
		is >> count;
		q.stops.resize(count);
		for (int i = 0; i < count; ++i) {
			is >> q.stops[i];
		}
	}
	else if (str == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (str == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (str == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse {
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	for (const auto& bus : r.buses) {
		os << bus << " ";
	}
	return os;
}

struct StopsForBusResponse {
	vector<string> order;
	map<string, vector<string>> base;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.order.empty())
		return os << "No bus";

	bool first = true;
	for (const auto& stop : r.order) {
		if (first)
			first = false;
		else
			os << endl;

		os << "Stop " << stop << ": ";
		for (const auto& bus : r.base.at(stop)) {
			os << bus << " ";
		}
	}
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> base;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.base.empty())
		return os << "No buses";

	bool first = true;
	for (const auto& [bus, stops] : r.base) {
		if (first)
			first = false;
		else
			os << endl;

		os << "Bus " << bus << ": ";
		for (const auto& stop : stops) {
			os << stop << " ";
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		buses_to_stops[bus] = stops;
		for (const string& stop : buses_to_stops[bus]) {
			stops_to_buses[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		BusesForStopResponse res;
		if (stops_to_buses.count(stop) == 0) {
			res.buses.push_back("No stop");
		}
		else {
			res.buses = stops_to_buses.at(stop);
		}
		return res;
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse res;
		if (buses_to_stops.count(bus) != 0) {
			for (const string& stop : buses_to_stops.at(bus)) {
				res.order.push_back(stop);
				if (stops_to_buses.at(stop).size() == 1) {
					res.base[stop].push_back("no interchange");
				}
				else {
					for (const string& other_bus : stops_to_buses.at(stop)) {
						if (bus != other_bus) {
							res.base[stop].push_back(other_bus);
						}
					}
				}
			}
		}
		return res;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse res;
		res.base = buses_to_stops;
		return res;
	}

private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
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