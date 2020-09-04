#include"query.h"

std::istream& operator >> (std::istream& is, Query& q) {
	std::string str;
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
