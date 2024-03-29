/** @file DataBase.cpp
 *  @brief Contains the DataBase Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include "Database.h"
#include <sstream>
#include <fstream>
#include <unordered_set>

using namespace std;

Database::Database() = default;

void Database::readAirlines() {
    ifstream airlineFile("../resources/airlines.csv");
    string line;

    getline(airlineFile, line);

    string code, name, callSign, country;

    do {
        getline(airlineFile, code, ',');
        if (code == "") break;
        getline(airlineFile, name, ',');
        getline(airlineFile, callSign, ',');
        getline(airlineFile, country);
        airlines.insert(pair<string, Airline>(code, {code, name, callSign, country}));

    } while (true);

}

void Database::readAirports() {
    ifstream airportFile("../resources/airports.csv");
    string line;

    getline(airportFile, line);

    string code, name, cityName, country, latitude, longitude;

    do {
        getline(airportFile, code, ',');
        if (code == "") break;
        getline(airportFile, name, ',');
        getline(airportFile, cityName, ',');
        getline(airportFile, country, ',');
        getline(airportFile, latitude, ',');
        getline(airportFile, longitude);

        AirportPTR airport{new Airport(
                code, name, cityName, country, stof(latitude), stof(longitude))};

        City city{cityName, country};
        if (airportsPerCity.find(city) != airportsPerCity.end())
            airportsPerCity[city].insert(airport);

        else {
            unordered_set<AirportPTR, Airport::hashFunction> airports;
            airports.insert(airport);
            airportsPerCity.insert(pair<City, unordered_set<AirportPTR, Airport::hashFunction>>(city, airports));
        }
        this->airports.insert(pair<string, AirportPTR>(code, airport));

    } while (true);
}

void Database::readFlights() {
    ifstream flightsFile("../resources/flights.csv");
    string line;

    getline(flightsFile, line);

    string originCode, destinationCode, companyCode;

    do {
        getline(flightsFile, originCode, ',');
        if (originCode == "") break;
        getline(flightsFile, destinationCode, ',');
        getline(flightsFile, companyCode);

        airports[originCode]->addFlight({destinationCode, companyCode});

    } while (true);
}

void Database::read() {
    readAirports();
    readAirlines();
    readFlights();

    flightMap->setAirports(airports);
    flightMap->setAirportsPerCity(airportsPerCity);
}

AirportPTR Database::getAirport(string code) {
    return airports[code];
}

Airline Database::getAirline(string code) {
    return airlines[code];
}

AirportsPerCity_Set Database::getAirportsPerCity() {
    return airportsPerCity;
}

unordered_map<string, AirportPTR> Database::getAirports() {
    return airports;
}

unordered_map<string, Airline> Database::getAirlines() {
    return airlines;
}

int Database::diameter() {
    return flightMap->diameter();
}

list<pair<AirportPTR, list<Flight>>> Database::getTrajectories(LocalPTR origin, LocalPTR destination) {

    unordered_set<string> airlinesCodes;

    for (auto airline: airlines) {
        airlinesCodes.insert(airline.first);
    }

    return flightMap->getFlights(origin, destination, airlinesCodes);
}

list<pair<AirportPTR, list<Flight>>>
Database::getTrajectories(LocalPTR origin, LocalPTR destination, unordered_set<string> airlines) {


    return flightMap->getFlights(origin, destination, airlines);
}

FlightMapPtr Database::getFlightMapPtr() {
    return flightMap;
}

unordered_set<AirportPTR> Database::airportsWithMaxYFlights(LocalPTR origin, int y) {
    return flightMap->airportsWithMaxYFlights(origin, y);
}

unordered_set<City, City::hashFunction> Database::citiesWithMaxYFlights(LocalPTR origin, int y) {
    return flightMap->citiesWithMaxYFlights(origin, y);
}

unordered_set<string> Database::countriesWithMaxYFlights(LocalPTR origin, int y) {
    return flightMap->countriesWithMaxYFlights(origin, y);
}

list<AirportPTR> Database::getArticulationPoints() {
    return flightMap->articulationPoints();
}

int Database::getConnectedComponents() {
    return flightMap->connectedComponents();
}