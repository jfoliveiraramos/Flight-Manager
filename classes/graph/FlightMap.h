/** @file FlightMap.h
 *  @brief Contains the FlightMap class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef AED_FEUP_PROJ_2_22_23_FLIGHTMAP_H
#define AED_FEUP_PROJ_2_22_23_FLIGHTMAP_H

#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <stack>
#include "Airport/Airport.h"
#include "Locals/Local.h"
#include "City/City.h"

using namespace std;

//! @brief Redefinition of the name for ease of use.
typedef unordered_map<City,  unordered_set<AirportPTR, Airport::hashFunction>, City::hashFunction> AirportsPerCity_Set;

/** @brief FlightMap class to represent a flight map and all implementations that uses a graph directly.
 *
 */
class FlightMap {

    //! @brief Holds all airports.
    unordered_map<string,  AirportPTR> airports;

    //! @brief Holds the airports per city.
    AirportsPerCity_Set airportsPerCity;

public:

    /** Create a new FlightMap.
     *
     * Does nothing.
     */
    FlightMap();

    /** @brief Sets the airports to the given argument.
     *
     * @param airports of const unordered_map<string,  AirportPTR> type.
     * @return Void.
     */
    void setAirports(const unordered_map<string,  AirportPTR> airports);

    /** @brief Returns the airports.
     *
     * @return unordered_map<string,  AirportPTR> of airports.
     */
    unordered_map<string,  AirportPTR> getAirports();

    /** @brief Returns the airports per city.
     *
     * @return AirportsPerCity_Set of airports.
     */
    AirportsPerCity_Set getAirportsPerCity();

    /** @brief Sets the airportsPerCity to the given argument.
     *
     * @param airportsPerCity of AirportsPerCity_Set type.
     * @return Void.
     */
    void setAirportsPerCity(AirportsPerCity_Set airportsPerCity);

    /** @brief Returns the shortest number of flights from a certain airport to another.
     *
     * It uses BFS algorithm.
     * Temporal Complexity : O(|A| + |F|), A represents the number
     * of airports and F represents the number of flights.
     *
     * @param airportDepart of AirportPTR type.
     * @param airportDestination of AirportPTR type.
     * @param airlines of unordered_set<string> type.
     * @return One or more lists with the minors airport paths.
     */
    int minimumDistance(AirportPTR airportDepart, AirportPTR airportDestination, unordered_set<string> airlines);

    /** @brief Returns list with the shortest trajectories.
     *
     * It uses BFS algorithm.
     * Temporal Complexity : O(|A| + |F|), A represents the number
     * of airports and F represents the number of flights.
     *
     * @param airportDepart of AirportPTR type.
     * @param airportDestination of AirportPTR type.
     * @param airlines of unordered_set<string> type.
     * @param minimumFlights of int type.
     * @return One or more lists with the minors airport paths.
     */
    list<list<Flight>> getTrajectories(AirportPTR airportDepart, AirportPTR airportDestination,
                                       unordered_set<string> airlines, int minimumFlights);

    /** @brief Represents the minor flights using an specific local.
     *
     * The local can be an airport, a city or a pair of coordinates.
     *
     * @param origin of LocalPTR type.
     * @param destination of LocalPTR type.
     * @param airlines of unordered_set<string> type.
     * @return list<list<flight>> of flights.
     */
    list<pair<AirportPTR, list<Flight>>> getFlights(LocalPTR origin, LocalPTR destination,
                                                    unordered_set<string> airlines);

    /** @brief Represents all airports that can be reachable from another specific one.
     *
     * It uses the BFS algorithm.
     * Temporal Complexity : O(|A| + |F|), A represents the number
     * of airports and F represents the number of flights.
     *
     * @param airportPtr of AirportPTR type.
     * @param y of int type.
     * @return unordered_set<AirportPTR> of airports.
     */
    unordered_set<AirportPTR> reachableAirports(AirportPTR airportPtr, int y);

    /** @brief Determines the reachable airports, parting from a given local and using a maximum number of flights.
     *
     * It uses the "reachableAirports" method.
     *
     * @param origin of LocalPTR type.
     * @param y of int type.
     * @return set of reachable airports, of type unordered_set<AirportPTR>
     */
    unordered_set<AirportPTR> airportsWithMaxYFlights(LocalPTR origin, int y);

    /** @brief Determines the reachable cities, parting from a given local and using a maximum number of flights.
     *
     * It uses the "reachableAirports" method.
     *
     * @param origin of LocalPTR type.
     * @param y of int type.
     * @return set of reachable cities, of type unordered_set<city, city::hashFunction>
     */
    unordered_set<City, City::hashFunction> citiesWithMaxYFlights(LocalPTR origin, int y);

    /** @brief Determines the reachable countries, parting from a given local and using a maximum number of flights.
     *
     * It uses the "reachableAirports" method.
     *
     * @param origin of LocalPTR type.
     * @param y of int type.
     * @return set of reachable countries, of type unordered_set<string>
     */
    unordered_set<string> countriesWithMaxYFlights(LocalPTR origin, int y);

    /** @brief Represents the auxiliary code to calculate articulation points.
     *
     * It uses the DFS implementation.
     * Temporal Complexity : O(|A| + |F|), A represents the number
     * of airports and F represents the number of flights.
     *
     * @param airport of AirportPTR type.
     * @param index of int type, by reference.
     * @param stack of stack<AirportPTR> type, by reference.
     * @param answer of list<AirportPTR> type, by reference.
     * @return Void.
     */
    void dfsArticulationPoints(AirportPTR airport, int &index, stack<AirportPTR> &stack, list<AirportPTR> &answer);

    /** @brief Represents the articulation points.
     *
     * It uses the "dfsArticulationPoints" method.
     * Temporal Complexity : O(|A| + |F|), A represents the number
     * of airports and F represents the number of flights.
     *
     * @return List of airports.
     */
    list<AirportPTR> articulationPoints();

    /** @brief Updates the maximum diameter.
     *
     * Temporal Complexity : O(|A| + |F|), A represents the number
     * of airports and F represents the number of flights.
     *
     * @param airportDepart Of AirportPTR type.
     * @param diameter Of int type, by reference.
     * @return Void.
     */
    void diameterBFS(AirportPTR airportDepart, int &diameter);

    /** @brief Represents the diameter of the graph.
     *
     * Temporal Complexity : O(|A|(|A|+|F|)), A represents the number
     * of airports and F represents the number of flights.
     *
     * @return diameter of int type.
     */
    int diameter();

    /** @brief Visits all airports through depth first search(BFS).
     *
     * Temporal Complexity : O(|A| + |F|), A represents the number
     * of airports and F represents the number of flights.
     *
     * @param airport Of AirportPTR type.
     * @return void.
     */
    void dfs(AirportPTR airport);

    /** @brief Represents the number of connected components.
     *
     * It uses the DFS implementation.
     * Temporal Complexity : O(|A| + |F|), A represents the number
     * of airports and F represents the number of flights.
     *
     * @return int number.
     */
    int connectedComponents();
};

#endif
