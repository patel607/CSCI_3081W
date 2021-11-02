Refactoring 1 is located on branch refactor/iter2

Refactoring 2 is located on branch refactor/iter3

User Guide and Developer Guide are both located on mainpage.h

Regression test was done using recommendation 1 from Lab 15 with alternative 2 from the iteration 3 writeup.
Created deterministic_passenger_factory.cc and deterministic_passenger_factory.h to use specifically for regression testing.
r_local_simulator.cc was modified from the lab to only include 5 stops on each of the outgoing and incoming routees.

Proceed to the project/src directory and type the following commands in the terminal.

    $ make simple_regression_test
    $ cd ../build/bin/
    $ ./simple_regression_test > rtout1
    $ ./simple_regression_test > rtout2
    $ diff rtout1 rtout2

You should see that there is no difference between the the rtout1 and rtout2 files.