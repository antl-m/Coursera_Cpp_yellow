#include "responses.h"

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
	for (const auto& bus : r.buses) {
		os << bus << " ";
	}
	return os;
}

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
	if (r.order.empty())
		return os << "No bus";

	bool first = true;
	for (const auto& stop : r.order) {
		if (first)
			first = false;
		else
			os << std::endl;

		os << "Stop " << stop << ": ";
		for (const auto& bus : r.base.at(stop)) {
			os << bus << " ";
		}
	}
	return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
	if (r.base.empty())
		return os << "No buses";

	bool first = true;
	for (const auto& [bus, stops] : r.base) {
		if (first)
			first = false;
		else
			os << std::endl;

		os << "Bus " << bus << ": ";
		for (const auto& stop : stops) {
			os << stop << " ";
		}
	}
	return os;
}