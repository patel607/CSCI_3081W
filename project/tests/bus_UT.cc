/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/bus.h"
#include "../src/random_passenger_generator.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class BusTests : public ::testing::Test {
 protected:
  Bus* bus;

  Stop ** out_stops = new Stop *[2];
  Stop ** in_stops = new Stop *[2];
  std::list<Stop *> out_stops_list;
  std::list<Stop *> in_stops_list;

  Stop * stop_out_1 = new Stop(0, 44.972392, -93.243774);
  Stop * stop_out_2 = new Stop(1, 44.973580, -93.235071);
  Stop * stop_in_1 = new Stop(2, 44.972392, -93.243774);
  Stop * stop_in_2 = new Stop(3, 44.972392, -93.243774);

  double * out_distances = new double[1];
  double * in_distances = new double[1];

  std::list<double> out_probs;

  std::list<double> in_probs;

  Route * out;
  Route * in;

  Passenger* kevin;
  Passenger* dan;

  virtual void SetUp() {
    out_stops_list.push_back(stop_out_1);
    out_stops[0] = stop_out_1;
    out_stops_list.push_back(stop_out_2);
    out_stops[1] = stop_out_2;

    in_stops_list.push_back(stop_in_1);
    in_stops[0] = stop_in_1;
    in_stops_list.push_back(stop_in_2);
    in_stops[1] = stop_in_2;

    out_distances[0] = 2;
    in_distances[1] = 2;

    out_probs.push_back(0);
    out_probs.push_back(0);

    in_probs.push_back(0);
    in_probs.push_back(0);

    RandomPassengerGenerator * out_generator
      = new RandomPassengerGenerator(out_probs, out_stops_list);
    RandomPassengerGenerator * in_generator
      = new RandomPassengerGenerator(in_probs, in_stops_list);

    out = new Route("outgoing", out_stops,
                            out_distances, 2, out_generator);
    in = new Route("incoming", in_stops,
                            in_distances, 2, in_generator);

    kevin = new Passenger(1, "Kevin");
    dan = new Passenger(3, "Dan");

    stop_out_1->AddPassengers(kevin);
    stop_in_1->AddPassengers(dan);

    bus = new Bus("bus", out, in, 1, 1);
  }

  virtual void TearDown() {
    delete bus;
  }

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(BusTests, Constructor) {
  // SetUp();
  // getter methods show constructor has been intialized correctly
  EXPECT_FALSE(bus->IsTripComplete());
  EXPECT_EQ(bus->GetName(), "bus");
  EXPECT_EQ(bus->GetCapacity(), 1);
  EXPECT_EQ(bus->GetNumPassengers(), 0);
  EXPECT_EQ(bus->GetNextStop()->GetId(), 0);

	std::string expected_out_1 = "Name: bus\n"
                               "Speed: 1\n"
                               "Distance to next stop: 2\n"
                               "\tPassengers (0): \n";

	testing::internal::CaptureStdout();
	bus->Report(std::cout);
	std::string output1 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, expected_out_1);
}

TEST_F(BusTests, LoadPassenger) {
  // SetUp();
  EXPECT_EQ(bus->GetNumPassengers(), 0);
  // true shows loaded passeneger
  EXPECT_TRUE(bus->LoadPassenger(kevin));
  EXPECT_EQ(bus->GetNumPassengers(), 1);
  // false shows failed to load because at max capacity
  EXPECT_FALSE(bus->LoadPassenger(dan));
  EXPECT_EQ(bus->GetNumPassengers(), 1);
}

TEST_F(BusTests, UnloadPassengers) {
  // SetUp();
  EXPECT_EQ(bus->GetNumPassengers(), 0);
  EXPECT_TRUE(bus->LoadPassenger(kevin));
  EXPECT_EQ(bus->GetNumPassengers(), 1);
  // unloaded kevn at destination stop
  EXPECT_TRUE(bus->UnloadPassengers(stop_out_2));
  EXPECT_EQ(bus->GetNumPassengers(), 0);
  // successful loading
  EXPECT_TRUE(bus->LoadPassenger(dan));
  // failed to unload because no passengers on bus have '3' as destination stop
  EXPECT_FALSE(bus->UnloadPassengers(stop_out_1));
  EXPECT_EQ(bus->GetNumPassengers(), 1);
}

TEST_F(BusTests, NextStop) {
  // SetUp();
  // bus starts on way to first stop
  EXPECT_EQ(bus->GetNextStop(), stop_out_1);
  bus->Move();
  EXPECT_EQ(bus->GetNextStop(), stop_out_1);
  bus->Move();
  EXPECT_EQ(bus->GetNextStop(), stop_out_1);
  bus->Move();
  // bus now on incoming route
  EXPECT_EQ(bus->GetNextStop(), stop_in_1);
  bus->Move();
  EXPECT_EQ(bus->GetNextStop(), stop_in_1);
  bus->Move();
  EXPECT_EQ(bus->GetNextStop(), stop_in_2);
  // bus should not move if at end of trip
  EXPECT_TRUE(bus->IsTripComplete());
  EXPECT_FALSE(bus->Move());
}

TEST_F(BusTests, Update) {
  SetUp();
  EXPECT_EQ(bus->GetNextStop(), stop_out_1);
  bus->Update();
  EXPECT_EQ(bus->GetNumPassengers(), 0);
  bus->Update();
  EXPECT_EQ(bus->GetNumPassengers(), 0);
  bus->Update();
  EXPECT_EQ(bus->GetNumPassengers(), 1);
  bus->Update();
  EXPECT_EQ(dan->GetTotalWait(), 0);
  EXPECT_EQ(bus->GetNumPassengers(), 1);
  bus->Update();
  EXPECT_EQ(bus->GetNumPassengers(), 1);
  bus->Update();
  EXPECT_EQ(bus->GetNumPassengers(), 1);
}

TEST_F(BusTests, BusData) {
  // SetUp();
  bus->UpdateBusData();
  // BusData struct has been intialized properly
  EXPECT_EQ(bus->GetBusData().id, bus->GetName());
  EXPECT_EQ(bus->GetBusData().num_passengers, bus->GetNumPassengers());
  EXPECT_EQ(bus->GetBusData().capacity, bus->GetCapacity());

  double curr_long, curr_lat;
  double prev_long, prev_lat;
  std::tie(prev_long, prev_lat) =
                      out->GetPreviousStop()->GetCoordinates();
  std::tie(curr_long, curr_lat) =
                      out->GetDestinationStop()->GetCoordinates();
  // check if position is near because double rounding
  EXPECT_NEAR(bus->GetBusData().position.x, (prev_long + curr_long)/2.0, 0.0001);
  EXPECT_NEAR(bus->GetBusData().position.y, (prev_lat + curr_lat)/2.0, 0.0001);
}
