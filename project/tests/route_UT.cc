/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/random_passenger_generator.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class RouteTests : public ::testing::Test {
 protected:
  Route* route;

  Stop ** stops = new Stop *[2];
  std::list<Stop *> stops_list;

  Stop * stop_1 = new Stop(0, 44.972392, -93.243774);
  Stop * stop_2 = new Stop(1, 44.973580, -93.235071);

  double * dist = new double[1];

  std::list<double> probs;

  Passenger* kevin = new Passenger(12, "Kevin");
  Passenger* dan = new Passenger(11, "Dan");

	virtual void SetUp() {
    stop_2->AddPassengers(kevin);

    stops_list.push_back(stop_1);
    stops[0] = stop_1;
    stops_list.push_back(stop_2);
    stops[1] = stop_2;
    dist[0] = 4;
    probs.push_back(0);
    probs.push_back(0);

    RandomPassengerGenerator * gen
      = new RandomPassengerGenerator(probs, stops_list);

    route = new Route("route", stops, dist, 2, gen);
  }

  virtual void TearDown() {
    delete route;
  }

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RouteTests, Constructor) {
  // getter methods show constructor has been intialized correctly
  EXPECT_EQ(route->IsAtEnd(), false);
  EXPECT_EQ(route->GetName(), "route");
  EXPECT_EQ(route->GetDestinationStop(), stops[0]);
  EXPECT_EQ(route->GetNextStopDistance(), dist[0]);

	std::string expected_out_1 = "Name: route\n"
                               "Num stops: 2\n"
                               "ID: 0\n"
                               "Passengers waiting: 0\n"
                               "ID: 1\n"
                               "Passengers waiting: 1\n"
                               "Name: Kevin\n"
                               "Destination: 12\n"
                               "Total Wait: 0\n"
                               "\tWait at Stop: 0\n"
                               "\tTime on bus: 0\n";

	testing::internal::CaptureStdout();
	route->Report(std::cout);
	std::string output1 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, expected_out_1);
}

TEST_F(RouteTests, NextStop) {
  // haven't traveled through entire route yet
  EXPECT_FALSE(route->IsAtEnd());
  // first stop is destination
  EXPECT_EQ(route->GetDestinationStop(), stop_1);
  EXPECT_EQ(route->GetNextStopDistance(), 4);
  route->NextStop();
  // next stop in list is destination
  EXPECT_EQ(route->GetDestinationStop(), stop_2);
  EXPECT_EQ(route->GetPreviousStop(), stop_1);
  // no more stops past this destination stop
  EXPECT_TRUE(route->IsAtEnd());
}

TEST_F(RouteTests, Clone) {
  Route* clone = route->Clone();
  EXPECT_EQ(route->IsAtEnd(), clone->IsAtEnd());
  EXPECT_EQ(route->GetName(), clone->GetName());
  EXPECT_EQ(route->GetDestinationStop(), clone->GetDestinationStop());
  EXPECT_EQ(route->GetNextStopDistance(), clone->GetNextStopDistance());
}

TEST_F(RouteTests, Update) {
  route->Update();
  // update should increase wait time by 1
  EXPECT_EQ(kevin->GetTotalWait(), 1);
  route->Update();
  EXPECT_EQ(kevin->GetTotalWait(), 2);
}

TEST_F(RouteTests, RouteData) {
  SetUp();
  route->UpdateRouteData();
  EXPECT_EQ(route->GetRouteData().id, route->GetName());
  // check if individual stops have correct info
  EXPECT_EQ(route->GetRouteData().stops.at(0).id, std::to_string(stop_1->GetId()));
  EXPECT_EQ(route->GetRouteData().stops.at(0).num_people, stop_1->GetNumPassengers());
  EXPECT_EQ(route->GetRouteData().stops.at(1).id, std::to_string(stop_2->GetId()));
  EXPECT_EQ(route->GetRouteData().stops.at(1).num_people, stop_2->GetNumPassengers());
}
