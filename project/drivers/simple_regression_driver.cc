/**
 * @file simple_regression_driver.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
/*******************************************************************************
* Includes
******************************************************************************/
#include <ctime>
#include <iostream>
#include <fstream>
#include <random>
#include <string>

#include "src/r_local_simulator.h"

int main() {
  int rounds = 50;  // Number of rounds of generation to simulate in test

  srand((long)1);  // Seed the RNG with same seed every time


  rLocalSimulator my_sim;

  std::cout << "/*************************" << std::endl << std::endl;
  std::cout << "         STARTING" << std::endl;
  std::cout << "        SIMULATION" << std::endl;
  std::cout << "*************************/" << std::endl;

  my_sim.Start();

  std::cout << "/*************************" << std::endl << std::endl;
  std::cout << "           BEGIN" << std::endl;
  std::cout << "          UPDATING" << std::endl;
  std::cout << "*************************/" << std::endl;

  for (int i = 0; i < rounds; i++) {
    my_sim.Update();
  }

  std::cout << "/*************************" << std::endl << std::endl;
  std::cout << "        SIMULATION" << std::endl;
  std::cout << "         COMPLETE" << std::endl;
  std::cout << "*************************/" << std::endl;

  return 0;
}