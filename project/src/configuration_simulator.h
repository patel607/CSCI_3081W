/**
 * @file configuration_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_CONFIGURATION_SIMULATOR_H_
#define SRC_CONFIGURATION_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <list>

#include "src/config_manager.h"

class Route;
class Bus;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for configuration simluator;
 *
 * Functions similarly to visual simulator without the web interfacing needed.
 * 
 */
class ConfigurationSimulator {
 public:
  /**
  * @brief Constructs a simulator object based on parameters the user can enter into command line.
  * @param[in] ConfigManager * able to read a config file.
  *
  */
  explicit ConfigurationSimulator(ConfigManager*);
  /**
  * @brief Destructor of simulator object.
  *
  */
  ~ConfigurationSimulator();

  /**
  * @brief Intializes values for busStartTimings_, numTimeSteps_, and stops in routes.
  * @param[in] vector<int> containing busStartTimings_ value
  * @param[in] int containing numTimeSteps_ value
  * 
  */
  void Start(const std::vector<int>&, const int&);
  /**
  * @brief Creates busses for routes and calls Update and Report() on routes and busses.
  *
  */
  void Update();

 private:
  ConfigManager* configManager_;  ///< used to read config file

  std::vector<int> busStartTimings_;  ///< interval between busses created
  std::vector<int> timeSinceLastBus_;  ///< countdown until next bus created
  int numTimeSteps_;  ///< total time steps of simulation
  int simulationTimeElapsed_;  ///< time past so far in simulation

  std::vector<Route *> prototypeRoutes_;  ///< holds routes in config file
  std::vector<Bus *> busses_;  ///< holds busses that hold routes

  int busId = 1000;  ///< starting index of bus
};

#endif  // SRC_CONFIGURATION_SIMULATOR_H_
