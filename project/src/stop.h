/**
 * @file stop.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_STOP_H_
#define SRC_STOP_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>
#include <tuple>

#include "src/bus.h"
#include "src/passenger.h"

class Bus;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the representation of stops.
 *
 * Holds information about location of stop.
 *  Contains a list of passengers waiting to board bus.
 * 
 */
class Stop {
 public:
  /**
  * @brief Constructs a passenger with a standard name and id.
  *
  *
  * @param[in] int holding an id number
  * @param[in] double holding longitude coordinate
  * @param[in] double holding latitude coordinate
  *
  */
  explicit Stop(int, double = 44.973723, double = -93.235365);
  // Adding passengers to the stop (from the generator)
  /**
  * @brief Return identity/index of stop. Passengers use index to know which stop is their destination.
  * @return int ID of stop.
  * 
  */
  int GetId() const;
  /**
  * @brief Add passenger to list of passengers.
  * @param[out] Passenger which will be added to list of stop.
  * @return 1 marking successful method call.
  * 
  */
  int AddPassengers(Passenger *);
  /**
  * @brief Remove passengers from stop and add to bus as long as bus has room.
  * @param[out] Bus where passengers will be loaded.
  * @return bool indicating whether passengers were able to be loaded to bus.
  * 
  */
  bool LoadPassengers(Bus *);
  /**
  * @brief Calls Update() on each passenger waiting at stop.
  * 
  */
  void Update();
  /**
  * @brief Outputs id_, number of passengers waiting, and calls Report() on all passengers in list.
  * @param[in] ostream used to output information.
  * 
  */
  void Report(std::ostream&) const;
  /**
  * @brief Returns longitude and latitude as a tuple to be used in structs.
  * @return tuple<double, double> of longitude and latitude.
  * 
  */
  std::tuple<double, double> GetCoordinates();
  /**
  * @brief Returns number of passengers currently waiting at stop.
  * @return int representing number of passengers at stop.
  * 
  */
  int GetNumPassengers();

 private:
  int id_;  ///< index of stop
  std::list<Passenger *> passengers_;  // considered array, vector, queue, list
  double longitude_;  ///< x coordinate of stop
  double latitude_;  ///< y coordinate of stop
  int passengers_present_;  ///< unused variable due to passengers_.size()
};
#endif  // SRC_STOP_H_
