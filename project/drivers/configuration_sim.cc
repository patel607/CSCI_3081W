/**
 * @file configuration_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <sstream>
#include <fstream>

#include "src/config_manager.h"
#include "src/configuration_simulator.h"

int main(int argc, char**argv) {
  // NOTE: this usage will change depending on
  //       how you build your config_sim classes
  //   E.g., how will you handle getting the length of simulation value?
  std::cout << "Usage: ./build/bin/configuration_sim";
  std::cout << std::endl;
  std::cout << "Usage: ./build/bin/configuration_sim <config_filename>";
  std::cout << std::endl;
  std::cout << "Usage: ./build/bin/configuration_sim <config_filename> ";
  std::cout << "<rounds>";
  std::cout << std::endl;
  std::cout << "Usage: ./build/bin/configuration_sim <config_filename> ";
  std::cout << "<rounds> <bus_interval>";
  std::cout << std::endl;

  //   Create ConfigManager
  ConfigManager* cm = new ConfigManager();
  int rounds = 25;
  int interval = 5;
  ConfigurationSimulator* cs;

  // Check command line params for config file name
  // only one arg means no parameters used, use default file
  if (argc == 1) {
    cm->ReadConfig("config.txt");
    std::cout << "Using default config file." << std::endl;

    // limit to 4 parameters
  } else if (argc > 1 && argc < 5) {
    if (argc > 1) {
      // if file doesn't exist, print errors and use default config file
      if (!(std::ifstream("config/" + std::string(argv[1])))) {
        std::cout << "This file is not recognized. ";
        std::cout << "Using default config file instead." << std::endl;
        cm->ReadConfig("config.txt");
      } else {
        cm->ReadConfig(argv[1]);
      }
    }
    // ifs instead of else ifs to continue reading parameters
    if (argc > 2) {
      // third arg read as rounds
      rounds = std::atoi(argv[2]);
    }
    if (argc > 3) {
      // fourth arg read as bus interval
      interval = std::atoi(argv[3]);
    }
    // incorrect number of args will produce incorrect format response
  } else {
    std::cout << "Not the correct format. Refer to correct format usage.";
    std::cout << std::endl;
    return 0;
  }
  // atoi will produce int of zero when non-int value is inputted for arg
  // in this case produce input error message for rounds and/or interval
  if (rounds == 0 || interval == 0) {
    if (rounds == 0) {
      std::cout << "Please input an integer greater than 0 for rounds.";
      std::cout << std::endl;
    }
    if (interval == 0) {
      std::cout << "Please input an integer greater than 0 for bus_intervals.";
      std::cout << std::endl;
    }
    return 0;
  }

  //   Create ConfigurationSimulator
  cs = new ConfigurationSimulator(cm);

  std::cout << "/*************************" << std::endl << std::endl;
  std::cout << "         STARTING" << std::endl;
  std::cout << "        SIMULATION" << std::endl;
  std::cout << "*************************/" << std::endl;

  // configuration_simulator requires vector
  std::vector<int> interval_vec;
  interval_vec.push_back(interval);

  //   Call Start on ConfigurationSimulator
  cs->Start(interval_vec, rounds);

  std::cout << "/*************************" << std::endl << std::endl;
  std::cout << "           BEGIN" << std::endl;
  std::cout << "          UPDATING" << std::endl;
  std::cout << "*************************/" << std::endl;

  // Start for loop, length of simulation (where from?)
  for (int i = 0; i < rounds; i++) {
    // Call Update on ConfigurationSimulator
    cs->Update();
  }

  std::cout << "/*************************" << std::endl << std::endl;
  std::cout << "        SIMULATION" << std::endl;
  std::cout << "         COMPLETE" << std::endl;
  std::cout << "*************************/" << std::endl;

  return 0;
}
