/** @file airport.cpp
 *  @brief Contains the airport Class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include <algorithm>
#include "Airport.h"


Airport::Airport(string code, string name, string city, string country, float latitude, float longitude) :
        code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

Airport::Airport(const Airport &airport) {
    this->code = airport.code;
    this->name = airport.name;
    this->city = airport.city;
    this->country = airport.country;
    this->latitude = airport.latitude;
    this->longitude = airport.longitude;
}

Airport::Airport() {}

bool operator==(const AirportPTR &airport1, const AirportPTR &airport2) {
    return airport1->code == airport2->code;
}

size_t Airport::hashFunction::operator()(const AirportPTR &airport) const {

    return hash<string>()(airport->code);
}

double Airport::distanceTo(float latitude, float longitude) const {

    double thisLatitude = this->latitude, thisLongitude = this->longitude;
    double otherLatitude = latitude, otherLongitude = longitude;

    double distanceLat = (thisLatitude - otherLatitude) * M_PI / 180.0;
    double distanceLon = (thisLongitude - otherLongitude) * M_PI / 180.0;

    otherLatitude = (otherLatitude) * M_PI / 180.0;
    thisLatitude = (thisLatitude) * M_PI / 180.0;
    double a = pow(sin(distanceLat / 2), 2) + pow(sin(distanceLon / 2), 2) *
                                              cos(otherLatitude) * cos(thisLatitude);
    double earthRadius = 6371;
    double b = 2 * asin(sqrt(a));
    return earthRadius * b;
}

void Airport::addFlight(Flight flight) {
    flights.push_back(flight);
}

int Airport::getnumFlights() {
    return flights.size();
}

list<Flight> Airport::getFlights() {
    return flights;
}



