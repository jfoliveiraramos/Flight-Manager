/** @file airport.h
 *  @brief Contains the airport class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef AED_FEUP_PROJ_2_22_23_AIRPORT_H
#define AED_FEUP_PROJ_2_22_23_AIRPORT_H

#include <string>
#include <unordered_set>
#include <list>
#include <cmath>
#include "../../../Pointers.h"
#include "../Flight/Flight.h"

using namespace std;

/** @brief airport class to represent an airport.
 *
 */
class Airport {

public:

    //! @brief Holds the airport code.
    string code;

    //! @brief Holds the airport name.
    string name;

    //! @brief Holds the city that the airport belongs to.
    string city;

    //! @brief Holds the country that the airport belongs to.
    string country;

    //! @brief Holds the airport latitude.
    float latitude;

    //! @brief Holds the airport longitude.
    float longitude;

    //! @brief Holds the distance from the source airport.
    int dist;

    //! @brief Holds the flight that depart from the airport.
    list<Flight> flights;

    //! @brief Holds the airport has already visited or not.
    bool visited;

    //! @brief Holds all paths from the airport.
    list<Flight> path;

    //! @brief Holds the num from the airport.
    int num;

    //! @brief Holds the low from the airport.
    int low;

    //! @brief Holds true if airport is in the stack or false if otherwise.
    bool inStack;

    /** Create a new airport with a code, a name, a city, a country, a latitude and a longitude.
     *
     * @param code Of Type string.
     * @param name Of Type string.
     * @param country Of Type string.
     * @param latitude Of Type string.
     * @param longitude Of Type string.
     */
    Airport(string code, string name, string city, string country, float latitude, float longitude);

    /** Create a copy of a airport.
     *
     * @param airport Of Type const airport.
     */
    Airport(const Airport& airport);

    /** Create a new airport.
     *
     * Does nothing.
     */
    Airport();

    /** @brief Hash function declaration.
     *
     */
    struct hashFunction
    {
        size_t operator()(const AirportPTR& airport) const;
    };

    /** @brief Calculate distance between two Airports.
     *
     * Calculate the distance between latitudes and longitudes,
     * convert latitudes to radians and apply the Haversine formula.
     *
     * @param longitude Of float type.
     * @param latitude Of float type.
     * @return double that corresponds to the distance.
     */
    double distanceTo(float longitude, float latitude) const;

    /** @brief Add flights to the list of flights.
     *
     * @param flight of flight type.
     * @return Void.
     */
    void addFlight(Flight flight);

    /** @brief Represents the number of flights.
     *
     * @return The number of flights.
     */
    int getnumFlights();

    /** @brief Represents all the flights.
     *
     * @return A list of flights.
     */
    list<Flight> getFlights();
};

/** @brief Operator overload.
 *
 * Compares if two airports have the same code.
 *
 * @param airport1 Of type const AirportPTR, by reference.
 * @param airport2 Of type const AirportPTR, by reference.
 * @return True if the codes are equals.
 */
bool operator ==(const AirportPTR& airport1, const AirportPTR& airport2);

#endif //AED_FEUP_PROJ_2_22_23_AIRPORT_H
