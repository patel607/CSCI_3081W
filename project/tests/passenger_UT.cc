/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/passenger.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {

	protected:
  	
  	Passenger* passenger;
  	
	virtual void SetUp() {
    	passenger = new Passenger();
  	}

  	virtual void TearDown() {
    	delete passenger;
  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests, Constructor) {
  	EXPECT_EQ(passenger->IsOnBus(), false);
  	passenger->GetOnBus();
  	EXPECT_EQ(passenger->IsOnBus(), true);
  	EXPECT_EQ(passenger->GetTotalWait(), 1);

  	EXPECT_EQ(passenger->GetDestination(), -1);

	std::string expected_out_1 = "Name: Nobody\n"
  								 "Destination: -1\n"
  								 "Total Wait: 1\n"
  								 "\tWait at Stop: 0\n"
								 "\tTime on bus: 1\n";

	testing::internal::CaptureStdout();
	passenger->Report();
	std::string output1 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, expected_out_1);
}

TEST_F(PassengerTests, Update) {
	passenger->Update();
	EXPECT_EQ(passenger->GetTotalWait(), 1);
	passenger->Update();
	EXPECT_EQ(passenger->GetTotalWait(), 2);
	passenger->GetOnBus();
  	EXPECT_EQ(passenger->IsOnBus(), true);
	EXPECT_EQ(passenger->GetTotalWait(), 3);
	passenger->Update();
  	EXPECT_EQ(passenger->GetTotalWait(), 4);
	passenger->Update();
  	EXPECT_EQ(passenger->GetTotalWait(), 5);

	std::string expected_out_1 = "Name: Nobody\n"
  								 "Destination: -1\n"
  								 "Total Wait: 5\n"
  								 "\tWait at Stop: 2\n"
								 "\tTime on bus: 3\n";

	testing::internal::CaptureStdout();
	passenger->Report();
	std::string output1 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, expected_out_1);
}

TEST_F(PassengerTests, Report) {
	Passenger* adam = new Passenger(12, "Adam");
	Passenger* bob = new Passenger(9, "Bob");
	Passenger* chris = new Passenger(1, "Chris");

	bob->Update();

	chris->Update();
	chris->GetOnBus();
	chris->Update();

	std::string expected_out_1 = "Name: Adam\n"
  								 "Destination: 12\n"
  								 "Total Wait: 0\n"
  								 "\tWait at Stop: 0\n"
								 "\tTime on bus: 0\n";
	std::string expected_out_2 = "Name: Bob\n"
  								 "Destination: 9\n"
  								 "Total Wait: 1\n"
  								 "\tWait at Stop: 1\n"
								 "\tTime on bus: 0\n";
	std::string expected_out_3 = "Name: Chris\n"
  								 "Destination: 1\n"
  								 "Total Wait: 3\n"
  								 "\tWait at Stop: 1\n"
								 "\tTime on bus: 2\n";

	testing::internal::CaptureStdout();
	adam->Report();
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	bob->Report();
	std::string output2 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	chris->Report();
	std::string output3 = testing::internal::GetCapturedStdout();


	EXPECT_EQ(output1, expected_out_1);
	EXPECT_EQ(output2, expected_out_2);
  	EXPECT_EQ(output3, expected_out_3);
}