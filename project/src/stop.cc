/**
 * @file stop.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "src/stop.h"

#include <iostream>
#include <vector>

Stop::Stop(int id, double longitude, double latitude) :
           id_(id), longitude_(longitude), latitude_(latitude) {
  // Defaults to Westbound Coffman Union stop
  // no initialization of list of passengers necessary
}

// add new passenger to the back of the passengers_ list
int Stop::AddPassengers(Passenger * pass) {
  passengers_.push_back(pass);
  return 1;
}

// load passengers on bus until bus is full or no passengers remain
bool Stop::LoadPassengers(Bus * bus) {
    Passenger *pass;
    bool loaded = false;
    // continue loaded while there are still passengers are stop
    while (passengers_.empty() != 1) {
      pass = passengers_.front();
      // bus will return false if passenger can't fit
      if (bus->LoadPassenger(pass)) {
        pass->GetOnBus();
        passengers_.pop_front();
        loaded = true;
      } else {
        // exit loop if bus is full
        break;
      }
    }
    // bool is used in bus Move() to check if loading needs to be done
    return loaded;
}

void Stop::Update() {
  // Update each Passenger waiting at Stop
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    (*it)->Update();
  }
}

// passengers use index to know which stop is their destination.
int Stop::GetId() const {
  return id_;
}

void Stop::Report(std::ostream& os) const {
  os << "ID: " << id_ << std::endl;
  os << "Passengers waiting: " << passengers_.size() << std::endl;
  for (std::list<Passenger *>::const_iterator it = passengers_.begin();
      it != passengers_.end(); it++) {
    (*it)->Report();
  }
}

// return both coordinates at once to avoid two methods
std::tuple<double, double> Stop::GetCoordinates() {
  return std::make_tuple(longitude_, latitude_);
}

// number of passengers currently at stop
int Stop::GetNumPassengers() {
  return passengers_.size();
}
