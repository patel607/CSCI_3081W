/**
 * @file bus.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "src/bus.h"

Bus::Bus(std::string name, Route * out, Route * in,
         int capacity, double speed) {
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  distance_remaining_ = out->GetNextStopDistance();
}

// add passenger to list given a new passenger
bool Bus::LoadPassenger(Passenger * new_passenger) {
  // check that there's space on bus
  if (passengers_.size() < (unsigned)passenger_max_capacity_) {
    // add passenger to the back of list and set flag that passenger is on bus
    passengers_.push_back(new_passenger);
    new_passenger->GetOnBus();
    return true;
  }
  return false;
}

// Move returns true if no passengers have been loaded or bus trip is complete
//  bus doesn't move distance when loading/unloading passengers
bool Bus::Move() {
  // don't move if no more stops to visit
  if (IsTripComplete()) {
    return false;
  }
  // if we have reached the next stop
  if (distance_remaining_ <= 0) {
    // if we are currently on the outgoing route
    if (!outgoing_route_->IsAtEnd()) {
      Stop* destination_ = outgoing_route_->GetDestinationStop();
      // if there are no passengers to load or unload at this stop
      outgoing_route_->NextStop();
      if (!(UnloadPassengers(destination_) ||
          destination_->LoadPassengers(this))) {
        // no passengers unloaded/loaded means move past current
        // and we subtract the distance we already travelled past
        distance_remaining_ += outgoing_route_->GetNextStopDistance();
      } else {
        // passengers to unload/load so we stop and set distance to next stop
        distance_remaining_ = outgoing_route_->GetNextStopDistance();
      }
    } else {
      // equivalent responses if we are on the outgoing route
      Stop* destination_ = incoming_route_->GetDestinationStop();
      incoming_route_->NextStop();
      if (!(UnloadPassengers(destination_) ||
           destination_->LoadPassengers(this))) {
        distance_remaining_ += incoming_route_->GetNextStopDistance();
      } else {
        distance_remaining_ = incoming_route_->GetNextStopDistance();
      }
    // set distance_remaining to distance till next stop
    }
    // move towards next stop if we are not at a stop
  } else {
    distance_remaining_ -= speed_;
  }
  return true;
}

// Method to unload passengers if passenger destination ID matches stop ID
bool Bus::UnloadPassengers(Stop * curr_stop) {
  bool unloaded = false;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    // Check if Passenger ID matches current stop ID
    if ((*it)->GetDestination() == curr_stop->GetId()) {
      passengers_.remove(*it);
      --it;
      unloaded = true;
    }
  }
  return unloaded;
}

// bool Refuel() {
//  // This may become more complex in the future
//  fuel_ = max_fuel_;
// }

// update all passengers on bus and then call Move() AFTER
void Bus::Update() {  // using common Update format
for (std::list<Passenger *>::iterator it = passengers_.begin();
        it != passengers_.end(); it++) {
      (*it)->Update();
    }
  Move();
  UpdateBusData();
}


void Bus::Report(std::ostream& os) {
  os << "Name: " << name_ << std::endl;
  os << "Speed: " << speed_ << std::endl;
  os << "Distance to next stop: " << distance_remaining_ << std::endl;
  os << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    (*it)->Report();
  }
}

// checks if both routes have been traversed through completely
bool Bus::IsTripComplete() {
    if (outgoing_route_->IsAtEnd() && incoming_route_->IsAtEnd()) {
      return true;
    }
    return false;
  }

// update bus_data_ struct with most recent information in Update
void Bus::UpdateBusData() {
  // Store a unique identifier for the bus
  bus_data_.id = GetName();
  bus_data_.num_passengers = GetNumPassengers();
  bus_data_.capacity = GetCapacity();

  double curr_long, curr_lat;
  double prev_long, prev_lat;
  // depending on route, store previous stop and current stop coordinates
  if (!outgoing_route_->IsAtEnd()) {
    std::tie(prev_long, prev_lat) =
                      outgoing_route_->GetPreviousStop()->GetCoordinates();
    std::tie(curr_long, curr_lat) =
                      outgoing_route_->GetDestinationStop()->GetCoordinates();
  } else {
    std::tie(prev_long, prev_lat) =
                      incoming_route_->GetPreviousStop()->GetCoordinates();
    std::tie(curr_long, curr_lat) =
                      incoming_route_->GetDestinationStop()->GetCoordinates();
  }
  // compute and store the average of the latitudes and longitudes
  // belonging to the current and previous stops in position
  bus_data_.position.x = (prev_long + curr_long)/2.0;
  bus_data_.position.y = (prev_lat + curr_lat)/2.0;
}

// called by the visualizer to obtain the BusData struct
BusData Bus::GetBusData() {
  return bus_data_;
}

// called by the visualizer to get the name of the bus
std::string Bus::GetName() const {
  return name_;
}

// called by the visualizer to get the pointer to the bus's next stop
Stop * Bus::GetNextStop() {
  if (!outgoing_route_->IsAtEnd()) {
    return outgoing_route_->GetDestinationStop();
  } else {
    return incoming_route_->GetDestinationStop();
  }
}

// called by the visualizer to get the current number of passengers on the bus
size_t Bus::GetNumPassengers() {
  return passengers_.size();
}

// called by the visualizer to get max capacity of bus.
int Bus::GetCapacity() {
  return passenger_max_capacity_;
}
