/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <iostream>
#include <list>
#include <string>

#include "src/passenger.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/data_structs.h"

class PassengerUnloader;
class PassengerLoader;
class Route;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the representation of buses.
 *
 * Holds information about movement of bus.
 *  Contains a list of passengers waiting to deboard bus.
 * 
 */
class Bus {
 public:
  /**
  * @brief Constructs a bus with a name, two routes, a capacity, and a speed.
  *
  *
  * @param[in] string holding a name of a created bus
  * @param[in] Route * holding list of stops in outgoing route.
  * @param[in] Route * holding list of stops in incoming route.
  * @param[in] int holding maximum capacity of passengers that can be on bus.
  * @param[in] double holding amount of distance bus travels in one time unit.
  *
  */
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                                                 double speed = 1);
  /**
  * @brief Add Passenger to passengers_ list of bus.
  * @param[out] Passenger gets flagged as on bus with GetOnBus().
  *
  */
  bool LoadPassenger(Passenger *);  // returning revenue delta
  /**
  * @brief Move bus towards next stop if not currently at stop.
  *   If stop is reached, passengers are unloaded and then loaded.
  *   Bus moves past stop if no passengers need to be loaded or unloaded.
  * @return bool is unused currently.
  *  
  */
  bool Move();
  /**
  * @brief Unload passengers if ID matches with stop ID.
  * @param[out] Stop holding ID to compare with passengers on bus.
  * @return bool indicating if passengers need to be unloaded at stop.
  *
  */
  bool UnloadPassengers(Stop *);
  /**
  * @brief Calls Update() on each passenger on bus and Move().
  *
  */
  void Update();
  /**
  * @brief Outputs name_, speed_, distance_remaining_, and calls Report() on all passengers in list.
  * @param[in] ostream used to output information.
  * 
  */
  void Report(std::ostream&);
  /**
  * @brief Checks if bus has finished travelling through all stops of both routes.
  * @return bool indicating if both routes have been traversed through completely.
  * 
  */
  bool IsTripComplete();
  /**
  * @brief Called by visualizer to instruct bus to populate the BusData struct with latest information.
  * 
  */
  void UpdateBusData();
  /**
  * @brief Called by the visualizer to obtain the BusData struct.
  * @return BusData struct with most recent information of bus.
  * 
  */
  BusData GetBusData();
  /**
  * @brief Called by the visualizer to get the name of the bus.
  * @return string of name of bus.
  * 
  */
  std::string GetName() const;
  /**
  * @brief Called by the visualizer to get the pointer to the bus's next stop.
  * @return Stop* of the next stop of current route.
  * 
  */
  Stop * GetNextStop();
  /**
  * @brief Called by the visualizer to get the current number of passengers on the bus.
  * @return size_t representing current number of passengers on bus.
  * 
  */
  size_t GetNumPassengers();
  /**
  * @brief called by the visualizer to get the maximum number of passengers that the bus can hold.
  * @return int representing the maximum capacity of the bus.
  * 
  */
  int GetCapacity();

 private:
  std::list<Passenger *> passengers_;  ///< list of passengers held in bus
  int passenger_max_capacity_;  ///< maximum amount of passengers held by bus
  std::string name_;  ///< name of bus
  double speed_;  // could also be called "distance travelled in one time step"
  Route * outgoing_route_;  ///< first route that the bus travels
  Route * incoming_route_;  ///< route traveled on after outgoing route is done
  double distance_remaining_;  // when negative?, unload/load procedure occurs
                              // AND next stop set
  BusData bus_data_;  ///< struct used for visualizer
  // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
};
#endif  // SRC_BUS_H_
