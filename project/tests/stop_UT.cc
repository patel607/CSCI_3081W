/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/bus.h"
#include "../src/route.h"
#include "../src/random_passenger_generator.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class StopTests : public ::testing::Test {
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

  virtual void SetUp() {
    out_stops_list.push_back(stop_out_1);
    out_stops[0] = stop_out_1;
    out_stops_list.push_back(stop_out_2);
    out_stops[1] = stop_out_2;

    in_stops_list.push_back(stop_in_1);
    in_stops[0] = stop_in_1;
    in_stops_list.push_back(stop_in_2);
    in_stops[1] = stop_in_2;

    out_distances[0] = 4;
    in_distances[1] = 4;

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

    bus = new Bus("bus", out, in, 1, 1);
  }

  virtual void TearDown() {
    delete bus;
    delete out;
    delete in;
  }

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(StopTests, Constructor) {
  SetUp();
  // getter methods show constructor has been intialized correctly
	EXPECT_EQ(stop_out_1->GetId(), 0);
	EXPECT_EQ(stop_out_1->GetNumPassengers(), 0);
  EXPECT_EQ(stop_out_1->GetCoordinates(), std::make_tuple(44.972392, -93.243774));

	std::string expected_out_1 = "ID: 0\n"
                               "Passengers waiting: 0\n";

	testing::internal::CaptureStdout();
	stop_out_1->Report(std::cout);
	std::string output1 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, expected_out_1);
}

TEST_F(StopTests, AddPassengers) {
  SetUp();
  Passenger* kevin = new Passenger(12, "Kevin");
  Passenger* dan = new Passenger(11, "Dan");
  stop_out_2->AddPassengers(kevin);
  // passenger list size increasing accordingly
  EXPECT_EQ(stop_out_2->GetNumPassengers(), 1);
  stop_out_2->AddPassengers(dan);
  EXPECT_EQ(stop_out_2->GetNumPassengers(), 2);
}

TEST_F(StopTests, LoadPassengers) {
  SetUp();
  Passenger* kevin = new Passenger(12, "Kevin");
  Passenger* dan = new Passenger(11, "Dan");
  stop_out_2->AddPassengers(kevin);
  stop_out_2->AddPassengers(dan);
  // successful load since bus has space
  EXPECT_TRUE(stop_out_2->LoadPassengers(bus));
  // kevin no longer at stop
  EXPECT_EQ(stop_out_2->GetNumPassengers(), 1);
  // failure to load since bus at max capacity
  EXPECT_FALSE(stop_out_2->LoadPassengers(bus));
  // dan remains at stop
  EXPECT_EQ(stop_out_2->GetNumPassengers(), 1);
}

TEST_F(StopTests, Update) {
  SetUp();
  Passenger* kevin = new Passenger(12, "Kevin");
  Passenger* dan = new Passenger(11, "Dan");
  stop_in_1->AddPassengers(kevin);
  stop_in_1->Update();
  // update should increase wait time by 1
  EXPECT_EQ(kevin->GetTotalWait(), 1);

  stop_in_1->AddPassengers(dan);
  stop_in_1->Update();
  // check individual passengers times are updated independently
  EXPECT_EQ(dan->GetTotalWait(), 1);
  EXPECT_EQ(kevin->GetTotalWait(), 2);
}
