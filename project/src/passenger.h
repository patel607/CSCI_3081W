/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the representation of passengers.
 *
 * Holds information about name of passenger and what stop they are trying to end at.
 *  Also holds methods to find if they are on stop or bus and how long they've been waiting at each.
 */
class Passenger {  // : public Reporter {
 public:
  /**
  * @brief Constructs a passenger with a standard name and id.
  *
  *
  * @param[in] int holding an id number
  * @param[in] string holding a name of a created passenger
  *
  */
  explicit Passenger(int = -1, std::string = "Nobody");
  /**
  * @brief Updates wait_at_stop_ or time_on_bus_ depending if passenger is on stop or bus.
  *
  */
  void Update();
  /**
  * @brief Updates wait_at_stop_ to flag that passenger is now on bus and not at stop.
  *
  */
  void GetOnBus();
  /**
  * @brief Returns total amount of time waited from stop and bus.
  * @return int sum of wait_at_stop_ and time_on_bus_.
  *
  */
  int GetTotalWait() const;
  /**
  * @brief Returns true if time_on_bus is greater than 0, false otherwise.
  * @return bool indicating if passenger is on bus.
  * 
  */
  bool IsOnBus() const;
  /**
  * @brief Return destination_stop_id_ of passenger.
  * @return ID of stop where passenger will deboard bus.
  * 
  */
  int GetDestination() const;
  /**
  * @brief Outputs name_, destination_stop_id_, GetTotalWait(), wait_at_stop_, and time_on_bus_.
  *
  */
  void Report() const;

 private:
  std::string name_;  ///< Name of passenger.
  int destination_stop_id_;  ///< ID of stop passenger will exit bus at.
  int wait_at_stop_;  ///< Total time units passenger has been at stop.
  int time_on_bus_;  ///< Total time units passenger has been on the bus.
  int id_;
  static int count_;   // global count, used to set ID for new instances
};
#endif  // SRC_PASSENGER_H_
