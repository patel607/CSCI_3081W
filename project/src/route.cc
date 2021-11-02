/**
 * @file route.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

/*******************************************************************************
* Includes
******************************************************************************/
#include "src/route.h"

#include <algorithm>
#include <vector>

Route::Route(std::string name, Stop ** stops, double * distances, int num_stops,
             PassengerGenerator * pass_gen) {
  for (int i = 0; i < num_stops; i++) {
    stops_.push_back(stops[i]);
  }
  for (int i = 0; i < num_stops - 1; i++) {
    distances_between_.push_back(distances[i]);
  }

  name_ = name;
  num_stops_ = num_stops;
  generator_ = pass_gen;
  // initialize destination for when bus calls Move()
  destination_stop_ = stops[0];
  destination_stop_index_ = 0;
}

void Route::Update() {
  // Geenerate passengers and update each Stop in the Route
  generator_->GeneratePassengers();
  for (std::list<Stop *>::iterator it = stops_.begin();
       it != stops_.end(); it++) {
    (*it)->Update();
  }
  UpdateRouteData();
}

void Route::Report(std::ostream& os) {
  os << "Name: " << name_ << std::endl;
  os << "Num stops: " << num_stops_ << std::endl;
  int stop_counter = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
      it != stops_.end(); it++) {
    (*it)->Report(os);
    stop_counter++;
  }
}

// return clone to be used with prototype routes
Route * Route::Clone() {
  return new Route(*this);
}

// end of route signifed by reaching the last stop in list
bool Route::IsAtEnd() const {
  if (destination_stop_index_ < num_stops_ - 1) {
    return false;
  }
  return true;
}

// iterates through stops_ with current destination stop to find next stop
void Route::NextStop() {
  if (!IsAtEnd()) {
    // increment destination to we look for next stop in list
    ++destination_stop_index_;
    std::list<Stop*>::const_iterator current_stop_ = stops_.begin();
    for (int i = 0; i < destination_stop_index_; ++i) {
      ++current_stop_;
    }
    destination_stop_ = *current_stop_;
  }
}

// returns current destination stop needed for bus
Stop * Route::GetDestinationStop() const {
  return destination_stop_;
}

// previous stop used to create BusData struct
Stop * Route::GetPreviousStop() {
std::list<Stop*>::const_iterator current_stop_ = stops_.begin();
  for (int i = 0; i < destination_stop_index_-1; ++i) {
    ++current_stop_;
  }
  return *current_stop_;
}

// iterate through distances to find distance for next stop
// to be used after NextStop()
double Route::GetNextStopDistance() const {
  std::list<double>::const_iterator
                  current_distance_ = distances_between_.begin();
  for (int i = 0; i < destination_stop_index_; ++i) {
    ++current_distance_;
  }
  return *current_distance_;
}

// called by the visualizer to get the name of the route
std::string Route::GetName() {
  return name_;
}

// called by the visualizer to get the route's list of Stop pointers
std::list<Stop *> Route::GetStops() {
  return stops_;
}

// update route_data_ struct with most recent information in Update
void Route::UpdateRouteData() {
  // store a unique identifier for the route
  route_data_.id = GetName();
  // create a vector that holds StopData structs.
  std::vector<StopData> temp_stops;
  double lon, lat;

  // loop through the Route's stops
  for (std::list<Stop *>::const_iterator it = stops_.begin();
      it != stops_.end(); it++) {
    // temmpory stop struct to be stored in vector
    StopData temp;
    temp.id = std::to_string((*it)->GetId());
    temp.num_people = (*it)->GetNumPassengers();

    std::tie(lon, lat) = (*it)->GetCoordinates();
    temp.position.x = lon;
    temp.position.y = lat;

    temp_stops.push_back(temp);
  }
  // store the vector of StopData structs
  route_data_.stops = temp_stops;
}

// called by the visualizer to obtain the RouteData struct
RouteData Route::GetRouteData() {
  return route_data_;
}
