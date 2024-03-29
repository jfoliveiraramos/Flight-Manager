/** @file DataBase.h
 *  @brief Contains the DataBase class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef AED_FEUP_PROJ_2_22_23_DATABASE_H
#define AED_FEUP_PROJ_2_22_23_DATABASE_H

#include <algorithm>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include "../Graph/FlightMap.h"
#include "../Graph/Airline/Airline.h"

/** @brief database class to read all input files and store all information.
 *
 *  Intended to be instanced once and creates a database
 *  for use within the app.
 *  Holds prototype functions to read the following input files:
 *  "airlines.csv", "airports.csv" and "flights.csv".
 *  Stores their data accordingly.
 */
class Database {

private:

    //! @brief Represents the FlightMapPtr.
    FlightMapPtr flightMap{new FlightMap()};

    //! @brief Holds all airports per city.
    AirportsPerCity_Set airportsPerCity;

    //! @brief Holds all airports..
    unordered_map<string, AirportPTR> airports;

    //! @brief Holds all airlines.
    unordered_map<string, Airline> airlines;

    /** @brief Reads airlines input file and stores them accordingly.
     *
     *  Reads the file "airlines.csv" and for each line
     *  it reads an airline code, name, its call sign and country.
     *
     *  @return Void.
     */
    void readAirlines();

    /** @brief Reads airports input file and stores them accordingly.
     *
     *  Reads the file "airports.csv" and for each line
     *  it reads an airport code and name, a name of the city and country that belongs to
     *  and its latitude and longitude.
     *  If the airport (name of the city, name of the country) corresponds to a new airport,
     *  it creates a new airport object and adds it to the unordered_map of airports.
     *
     *  @return Void.
     */
    void readAirports();

    /** @brief Reads flights input file and stores them accordingly.
     *
     *  Reads the file "flights.csv" and for each line
     *  it reads its source, target and airline.
     *
     *  @return Void.
     */
    void readFlights();

public:

    /** @brief Does nothing.
     *
     */
    Database();

    /** @brief Stores all the information of the database.
     *
     * @return Void.
     */
    void read();

    /** @brief Returns the code of an specific airport.
    *
    * @param code of string type.
    * @return  airport of AirportPTR type.
    */
    AirportPTR getAirport(string code);

    /** @brief Returns the code of an specific airline.
    *
    * @param code of string type.
    * @return  airline of airline type.
    */
    Airline getAirline(string code);

    /** @brief Returns group of airport divided by cities.
    *
    * @return  AirportsPerCity_Set.
    */
    AirportsPerCity_Set getAirportsPerCity();

    /** @brief Returns all airports.
     *
     * @return unordered_map<string, AirportPTR> with airports.
     */
    unordered_map<string, AirportPTR> getAirports();

    /** @brief Returns all airlines.
     *
     * @return unordered_map<string, airline> with airlines.
     */
    unordered_map<string, Airline> getAirlines();

    /** @brief Invoke diameter from FlightMap class.
     *
     * @return int.
     */
    int diameter();

    /** @brief Returns a list of list of flights to showcase possible trajectories
     * by origin and destination, for all airlines.
     *
     * @param origin Of LocalPTR type.
     * @param destination Of LocalPTR type.
     * @return list<list<flight>> with the trajectories by origin and destination.
     */
    list<pair<AirportPTR, list<Flight>>> getTrajectories(LocalPTR origin, LocalPTR destination);

    /** @brief Invokes getTrajectoriesAllAirlines from FlightMap class.
     *
     * @param origin Of LocalPTR type.
     * @param destination Of int type.
     * @return set of reachable airports, of type unordered_set<AirportPTR>.
     */
    unordered_set<AirportPTR> airportsWithMaxYFlights(LocalPTR origin, int y);

    /** @brief Invokes getTrajectoriesAllAirlines from FlightMap class.
     *
     * @param origin Of LocalPTR type.
     * @param destination Of int type.
     * @return set of reachable cities, of type unordered_set<city, city::hashFunction>.
     */
    unordered_set<City, City::hashFunction> citiesWithMaxYFlights(LocalPTR origin, int y);

    /** @brief Invokes getTrajectoriesAllAirlines from FlightMap class.
     *
     * @param origin Of LocalPTR type.
     * @param destination Of int type.
     * @return set of reachable countries, of type unordered_set<string>.
     */
    unordered_set<string> countriesWithMaxYFlights(LocalPTR origin, int y);

    /** @brief Returns the flight map pointer to use outside database class.
     *
     * @return FlightMapPtr.
     */
    FlightMapPtr getFlightMapPtr();

    /** @brief Returns a list of articulation points.
     *
     * @return list<AirportPTR> of airports.
     */
    list<AirportPTR> getArticulationPoints();

    /** @brief Returns the number of connected components.
     *
     * @return int number.
     */
    int getConnectedComponents();

    /** @brief Returns a list of trajectories.
     *
     * @param origin Of LocalPTR type.
     * @param destination Of LocalPTR type.
     * @param airlines Of unordered_set<string> type.
     * @return list<pair<AirportPTR, list<flight>>>.
     */
    list<pair<AirportPTR, list<Flight>>>getTrajectories(LocalPTR origin,
                                                        LocalPTR destination,
                                                        unordered_set<string> airlines);
};

#endif //AED_FEUP_PROJ_22_23_DATABASE_H
