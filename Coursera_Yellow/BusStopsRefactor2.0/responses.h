#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

struct BusesForStopResponse {
	std::vector<std::string> buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
	std::vector<std::string> order;
	std::map<std::string, std::vector<std::string>> base;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
	std::map<std::string, std::vector<std::string>> base;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);