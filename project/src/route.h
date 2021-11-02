/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>
#include <string>

#include "src/passenger_generator.h"
#include "src/stop.h"
#include "src/data_structs.h"

class PassengerGenerator;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the aggregation of Stop objects.
 *
 * Holds information about list of stops to be used by buses. 
 * 
 */
class Route {
 public:
  /**
  * @brief Constructs a route with a name, lists of stops and distances, and a PassengerGenerator.
  *
  *
  * @param[in] string holding a name of a created passenger
  * @param[in] Stop ** holding list of stops in route.
  * @param[in] double * holding list of distances between adjacent stops.
  * @param[in] int holding number of stops in route.
  * @param[in] PassengerGenerator * holding PassengerGenerator object to create passengers in simulator.
  *
  */
  Route(std::string name, Stop ** stops, double * distances, int num_stops,
        PassengerGenerator *);
  /**
  * @brief Creates a clone of the current route.
  * @return Route * with all same attributes of prototype route.
  *
  */
  Route * Clone();
  /**
  * @brief Calls Update() on each stop in the route and generates passengers at stops.
  *
  */
  void Update();
  /**
  * @brief Outputs name_, num_stops_, and calls Report() on each stop in route.
  * @param[in] ostream used to output information.
  *
  */
  void Report(std::ostream&);
  /**
  * @brief Returns true if all stops in route have been visited, false otherwise.
  * @return bool indicating that there are no more stops in route to be visited.
  *
  */
  bool IsAtEnd() const;
  /**
  * @brief Increments destination to the next stop if not at end of route.
  *
  */
  void NextStop();  // Change destination_stop_ to next stop
  /**
  * @brief Returns pointer to next stop in route.
  * @return Stop * of current destination that bus will move towards.
  *
  */
  Stop * GetDestinationStop() const;    // Get pointer to next stop
  /**
  * @brief Returns total distance between first stop and destination stop in route.
  * @return double of distance between beginning of route and current destination.
  *
  */
  double GetTotalRouteDistance() const;
  /**
  * @brief Returns distance to next stop in route.
  * @return double of distance between previous stop and current destination.
  *
  */
  double GetNextStopDistance() const;
  /**
  * @brief Get the previous stop on the current route given destination_stop_index_.
  * @return Stop* of previous stop on route.
  *
  */
  Stop * GetPreviousStop();
  /**
  * @brief Called by the visualizer to get the name of the route.
  * @return string of name of route.
  * 
  */
  std::string GetName();
  /**
  * @brief Called by the visualizer to get the route's list of Stop pointers.
  * @return list<Stop *>> representing list of stops of route.
  * 
  */
  std::list<Stop *> GetStops();
  /**
  * @brief Called by visualizer to instruct route to populate the RouteData struct with latest information.
  * 
  */
  void UpdateRouteData();
  /**
  * @brief Called by the visualizer to obtain the RouteData struct.
  * @return RouteData struct with most recent information of route.
  * 
  */
  RouteData GetRouteData();

 private:
  /**
  * @brief Generates passengers on its route using generator_.
  * @return 1 indicating passenger has been successfully generated.
  *
  */
  int GenerateNewPassengers();       // generates passengers on its route
  PassengerGenerator * generator_;  ///< used to generate passengers at stops
  std::list<Stop *> stops_;  ///< list of stops that comprise route
  std::list<double> distances_between_;  // length = num_stops_ - 1
  std::string name_;  ///< route identification
  int num_stops_;  ///< number of stops route has
  int destination_stop_index_;  // always starts at zero, no init needed
  Stop * destination_stop_;  ///< current destination of bus
  double trip_time_;  // derived data - total distance travelled on route
  RouteData route_data_;  ///< struct used for visualizer
};
#endif  // SRC_ROUTE_H_

