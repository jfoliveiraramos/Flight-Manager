/** @file Application.cpp
 *  @brief Contains the Application class implementation.
 *  @author -
 *  @bug No known bugs.
 */

#include "Application.h"
#include <stdexcept>
#include "../Graph/Locals/Coordinates.h"
#include "../Graph/Locals/CityLocal.h"
#include "../Graph/Locals/AirportLocal.h"

Application::Application() {}

void Application::startApplication() {
    database->read();
    startMenu();
}

void Application::startMenu() {
    menu.startMenu();
    menu.breakLine();
    displayMenu();
}

void Application::safeInput(string &option, int &safeOption) {
    try {
        cin >> option;
        safeOption = stoi(option);
    }
    catch (const invalid_argument &ia) {
        menu.breakLine();
        menu.getInvalidMessage();
        menu.breakLine();
        safeOption = 0;
    }
}

void Application::menuSafety(string &option, int &safeOption) {
    while (!safeOption) {
        menu.displayMenu();
        safeInput(option, safeOption);
    }
}

void Application::airportListMenuSafety(string &option, int &safeOption) {
    while (!safeOption) {
        menu.displayListsMenu();
        safeInput(option, safeOption);
    }
}


void Application::airportNumbersSafety(string &option, int &safeOption) {
    while (!safeOption) {
        menu.displayNumbersMenu();
        safeInput(option, safeOption);
    }
}

void Application::localMenuSafety(string &option, int &safeOption, string typeLocal) {
    while (!safeOption) {
        menu.displayLocalMenu(typeLocal);
        safeInput(option, safeOption);
    }
}

void Application::statisticsMenuSafety(std::string &option, int &safeOption) {
    while (!safeOption) {
        menu.displayStatisticsMenu();
        safeInput(option, safeOption);
    }
}

void Application::maxYFlightsMenuSafety(std::string &option, int &safeOption) {
    while (!safeOption) {
        menu.displayMaxYFlightsMenu();
        safeInput(option, safeOption);
    }
}

void Application::filterNetworkTrajectoriesSafety(std::string &option, int &safeOption) {
    while (!safeOption) {
        menu.displayNetworkMenu();
        safeInput(option, safeOption);
    }
}

void Application::airportNumbersMenu(int &oldOption) {
    string option;
    int safeOption = 0;
    airportNumbersSafety(option, safeOption);
    while (safeOption != QUIT) {
        switch (safeOption) {
            case FLIGHTS: {
                string airportCode;
                cout << "Type the airport code to check flights total number:";
                cin >> airportCode;
                cout << numbersApplication.numbersFlights(airportCode) << endl;
                break;
            }
            case DIFFERENT_AIRLINES: {
                string airportCode;
                cout << "Type the airport code to check all airlines operating:";
                cin >> airportCode;
                cout << numbersApplication.numbersAirlines(airportCode) << endl;
                break;
            }
            case CITY: {
                string airportCode;
                cout << "Type the airport code to check all flights cities:";
                cin >> airportCode;
                cout << numbersApplication.numbersCities(airportCode) << endl;
                break;
            }
            case BY_COUNTRIES: {
                string airportCode;
                cout << "Type the airport code to check the number of countries to flight:";
                cin >> airportCode;
                cout << numbersApplication.numbersCountries(airportCode) << endl;
                break;
            }
            default: {
                menu.breakLine();
                menu.getWrongMessage();
                safeOption = 0;
                break;
            }
        }
        menu.breakLine();
        safeOption = 0;
        airportNumbersSafety(option, safeOption);
    }
    safeOption = 0;
}

void Application::displayMaxYFlightsMenu(int &oldOption) {
    string option;
    int safeOption = 0;
    bool fail = 0;
    maxYFlightsMenuSafety(option, safeOption);
    while (safeOption != QUIT) {
        int y;
        cout << "Type the desired maximum number of flights:";
        cin >> y;
        LocalPTR local;
        int trueOption = safeOption;
        safeOption = 0;
        localMenuSafety(option, safeOption, "Target");
        getLocal(safeOption, fail, local, "Target");
        if (!fail) {
            switch (trueOption) {
                case MAX_AIRPORTS: {
                    listingApplication.showReachableAirports(local, y);
                    numbersApplication.numberReachableAirports(local, y);
                    break;
                }
                case MAX_CITIES: {
                    listingApplication.showReachableCities(local, y);
                    numbersApplication.numberReachableCities(local, y);
                    break;
                }
                case MAX_COUNTRIES: {
                    listingApplication.showReachableCountries(local, y);
                    numbersApplication.numberReachableCountries(local, y);
                    break;
                }
                default: {
                    menu.breakLine();
                    menu.getWrongMessage();
                    safeOption = 0;
                    break;
                }
            }
        }
        menu.breakLine();
        safeOption = 0;
        maxYFlightsMenuSafety(option, safeOption);
    }
    oldOption = 0;
}

void Application::filterNetworkTrajectories(int &oldOption) {
    string option;
    int safeOption = 0;
    bool fail = 0;
    filterNetworkTrajectoriesSafety(option, safeOption);
    while (safeOption != QUIT) {
        switch (safeOption) {
            case ALL_AIRLINES: {
                displayTrajectoriesMenu(oldOption);
                break;
            }
            case FILTER_AIRLINES: {
                string tempOption;
                unordered_set<string> airlines;
                while (tempOption != "Q" && tempOption != "q") {
                    menu.breakLine();
                    if (!airlines.empty()) {
                        cout << "Filter contains " << airlines.size() << " airlines..." << endl;
                        for (auto a: airlines)
                            cout << a << endl;
                        menu.breakLine();
                    }
                    cout << "Enter an airline code to add to the filter or Q to exit: ";
                    cin >> tempOption;
                    if (tempOption != "Q" && tempOption != "q")
                        airlines.insert(tempOption);
                }
                LocalPTR origin, destination;
                safeOption = 0;
                localMenuSafety(option, safeOption, "Origin");
                getLocal(safeOption, fail, origin, "Origin");
                safeOption = 0;
                localMenuSafety(option, safeOption, "Destination");
                getLocal(safeOption, fail, destination, "Destination");
                listingApplication.showTrajectories(origin, destination, true, airlines);
                menu.breakLine();
                break;
            }
            default: {
                menu.breakLine();
                menu.getWrongMessage();
                safeOption = 0;
                break;
            }
        }
        menu.breakLine();
        safeOption = 0;
        filterNetworkTrajectoriesSafety(option, safeOption);
    }
    oldOption = 0;
}


void Application::airportListMenu(int &oldOption) {
    string option;
    int safeOption = 0;
    airportListMenuSafety(option, safeOption);
    while (safeOption != QUIT) {
        switch (safeOption) {
            case FLIGHTS: {
                string airportCode;
                cout << "Type the airport code to check all flights:";
                cin >> airportCode;
                listingApplication.listFlights(airportCode);
                break;
            }
            case DIFFERENT_AIRLINES: {
                string airportCode;
                cout << "Type the airport code to check all flights:";
                cin >> airportCode;
                listingApplication.listAirlines(airportCode);
                break;
            }
            case CITY: {
                string airportCode;
                cout << "Type the airport code to check all flights:";
                cin >> airportCode;
                listingApplication.listCities(airportCode);
                break;
            }

            case BY_COUNTRIES: {
                string airportCode;
                cout << "Type the airport code to check all flights:";
                cin >> airportCode;
                listingApplication.listCountries(airportCode);
                break;
            }
            default: {
                menu.breakLine();
                menu.getWrongMessage();
                safeOption = 0;
                break;
            }
        }
        menu.breakLine();
        safeOption = 0;
        airportListMenuSafety(option, safeOption);
    }
    oldOption = 0;
}

void Application::optionFilter(int &option) {
    while (option != QUIT) {
        switch (option) {
            case AIRPORT_LISTS: {
                airportListMenu(option);
                break;
            }
            case AIRPORT_NUMBERS: {
                airportNumbersMenu(option);
                break;
            }
            case AIRPORT_BY_CITY: {
                string city, country;
                cout << "Type the name of city to check airports:";
                cin.ignore();
                getline(cin, city);
                cout << "Type the name of its country:";
                getline(cin, country);
                listingApplication.listAirportsByCity({city, country});
                break;
            }
            default: {
                menu.breakLine();
                menu.getWrongMessage();
                break;
            }
        }
        menu.breakLine();
        menu.displaySearchInfoMenu();
        cin >> option;
    }
    option = 0;
}

void Application::displayTrajectoriesMenu(int &oldOption) {
    string option;
    int safeOption = 0;
    localMenuSafety(option, safeOption, "Origin");
    bool fail = 0;
    while (safeOption != QUIT) {
        LocalPTR origin, destination;
        getLocal(safeOption, fail, origin, "Origin");
        safeOption = 0;
        localMenuSafety(option, safeOption, "Destination");
        getLocal(safeOption, fail, destination, "Destination");
        if (!fail)
            listingApplication.showTrajectories(origin, destination, false, {});
        menu.breakLine();
        safeOption = 0;
        localMenuSafety(option, safeOption, "Origin");
    }
    oldOption = 0;
}

void Application::getLocal(int safeOption, bool &fail, LocalPTR &local, string typeLocal) {
    switch (safeOption) {
        case Application::BY_AIRPORT_CODE: {
            string airportCode;
            cout << typeLocal << " airport Code: ";
            cin >> airportCode;
            local = LocalPTR(new AirportLocal(airportCode));
            break;
        }
        case Application::BY_CITY_COUNTRY: {
            string city, country;
            cout << typeLocal << " city Name: ";
            cin.ignore();
            getline(cin, city);
            cout << typeLocal << " Country Name: ";
            getline(cin, country);
            local = LocalPTR(new CityLocal({city, country}));
            break;
        }
        case Application::BY_COORDINATES: {
            float latitude, longitude, radius;
            cout << typeLocal << " Latitude: ";
            cin >> latitude;
            cout << typeLocal << " Longitude: ";
            cin >> longitude;
            cout << typeLocal << " Radius: ";
            cin >> radius;
            local = LocalPTR(new Coordinates(latitude, longitude, radius));
            break;
        }
        default:
            fail = 1;
            this->menu.breakLine();
            this->menu.getWrongMessage();
            break;
    }
}

void Application::displayStatisticsMenu(int &oldOption) {
    string option;
    int safeOption = 0;
    statisticsMenuSafety(option, safeOption);
    while (safeOption != QUIT) {
        switch (safeOption) {
            case GLOBAL_STATISTICS: {
                int k;
                cout << "Type the number for the top airports with most flights: ";
                cin >> k;
                listingApplication.globalStatistic(k);
                break;
            }
            case STATISTICS_BY_COUNTRY: {
                string country;
                int k;
                cout << "Type a country name to check its air transport statistics:";
                cin.ignore();
                getline(cin, country);
                cout << "Type the number for the top airports with most flights: ";
                cin >> k;
                listingApplication.statisticPerCountry(country, k);
                break;
            }
            case ARTICULATION_POINTS: {
                listingApplication.listArticulationPoints();
                break;
            }
            case CONNECTED_COMPONENTS: {
                numbersApplication.showNumberOfComponents();
                break;
            }
            default: {
                menu.breakLine();
                menu.getWrongMessage();
                safeOption = 0;
                break;
            }
        }
        menu.breakLine();
        safeOption = 0;
        statisticsMenuSafety(option, safeOption);
    }
    oldOption = 0;
}

void Application::displayMenu() {
    string option;
    int safeOption = 0;
    menuSafety(option, safeOption);
    while (safeOption != QUIT) {
        switch (safeOption) {
            case AIRPORT_LISTS: {
                string option;
                menu.displaySearchInfoMenu();
                safeInput(option, safeOption);
                optionFilter(safeOption);
                break;
            }
            case MAX_FLIGHT_LISTS: {
                string option;
                displayMaxYFlightsMenu(safeOption);
                break;
            }
            case GENERATE_TRAJECTORIES: {
                string option;
                filterNetworkTrajectories(safeOption);
                break;
            }
            case STATISTICS: {
                string option;
                displayStatisticsMenu(safeOption);
                break;
            }
            default:
                menu.breakLine();
                menu.getWrongMessage();
                safeOption = 0;
                break;
        }
        menu.breakLine();
        menuSafety(option, safeOption);
    }
    cout << menu.QUIT_MESSAGE << endl;
}


