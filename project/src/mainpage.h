/*! \mainpage Home
 *
 * \section intro Introduction
 * 
 * This project will allow you to simulate a bus route given information on its routes and stops. Currently you are able to visualize a simulation of set routes on the University of Minnesota (VisualSimulator). 
 * You are also able to use a configuration file to give a custom route to the simulator (ConfigurationSimulator), visualization has yet to be implemented for this aspect. 
 * The Devloper Guide describes the necessary objects and the thought process behind the simulation. The User Guide explains how users can access and utilize the different simulators available.
 *
 * \subsection dev_guide Developer Guide
 * 
 * The goal of this simulator is to simulate scenarios involving campus transit via Bus here at the University of Minnesota.
 * The simulation is done in our various Simulators, which contains all the necessary objects of bus transit. The current simulators are listed below in the User Guide.
 * 
 * The necessary objects are as follows:
 * 
 * - Passenger: The smallest unit representing a person which carries an ID of the Stop that is their destination. They also track how long they have been waiting for at a Stop or on a Bus.
 * 
 * - Stop: Contains a list of Passenger objects waiting to get on a Bus and holds an ID for each Passenger to check. Are associated with a probability of a Passenger showing up at that Stop.
 * 
 * - Route: An aggregation of Stop objects. Can access all information on any Stop it contains, including the distance between certain Stop objects. Passenger objects are generated (randomly) at a Stop through the Route, using a PassengerGenerator.
 * 
 * - Bus: Contains a list of Passenger objects waiting to get to their destination Stop. Buses use the Route to move from Stop to Stop, picking up and dropping off Passengers when necessary. Has a capacity and a speed.
 * 
 * Every simulator begins by generating Passengers at the Stops using the Update() method in the Route for 10 time units before Buses are generated.
 * For every time unit, the Passengers add to their wait time, depending on whether they're at the Stop or at the Bus. Also, for every time unit, the Bus moves towards the next Stop on its Route.
 * Buses actually contain two Routes, one incoming and one outgoing. The Bus will start on its outgoing Route first and then will start on its incoming. Once a Bus has finished both Routes, it will exit the simulation.
 * A Bus moves towards the next Stop, and if a Stop is reached during that move, the Bus will only stop if certain conditions are met:
 * The Bus will stop at that Stop if either a Passenger needs to get off at that Stop or if a Passenger is waiting at that Stop. The second condition is automatically failed if the Bus is already at its maximum capacity.
 * If both of the conditions fail, then the Bus will drive past the Stop and travel its full speed in that time unit. If the Bus did stop, then it is possible that the Bus did not travel its full possible distance.
 * In the case where the bus did stop at the Stop, the Bus and Stop will attempt to unload and then load passengers.
 * The Stop handles the loading of Passengers onto the Bus by continuously removing Passengers from the Stop and adding them to the Bus as long as the Stop has Passengers and the Bus isn't full.
 * The Bus handles unloading by checking if any Passengers on the Bus have destination IDs that match the current Stop ID, and those Passengers are removed from the Bus.
 * After the Bus has completed unloading and loading, it will prepare to head towards the next Stop in its Route.
 * The simulator continues generated Passengers and Buses until the end time has been reached.
 *
 * All code in written in C++ and makes use of a Makefile in order to compile all necessary files. Here is the directory structure:
 *
 * - <b>src</b>: contains all main objects needed to run simulations and Makefile.
 * 
 * - <b>drivers</b>: contains driver objects necessary to run manual tests.
 * 
 * - <b>tests</b>: contains Google tests for automated testing.
 * 
 * - <b>build</b>: contains execulables after compiling with Makefile.
 * 
 * - <b>docs</b<: contains documentation on project.
 * 
 * It is recommended to create further simulator variants in order to allow for simulation of more unique scenarios. One such simple variant would be to create a new version of LocalSimulator for a different set of routes. 
 * In order to accomplish this I would recommend using the current local_simulator.cc file as a template, because much of it can remain the same. Follow these steps to make your new simulator:
 * 
 * -# Replaces lines 74 - 108 with the adding of your new Stops to the appropriate Stop list.
 * 
 * -# Replace lines 110 - 127 with two arrays that contain the distances between your new Stops.
 * 
 * -# Replaces lines 130 - 152 by creating two new lists for each Route and add the probabilities of passengers showing up to each Stop in that Route.
 * 
 * -# Change '10' on line 189 and 230 if you want a different time interval between the generation of Bus objects.
 * 
 * -# Change '60' on line 228 if you want a different maximum capacity for each Bus object.
 * 
 * After following these steps you should be able to run your new custom simulator by following the directions to run TransitSimulator below. 
 * 
 * \subsection user_guide User Guide
 * 
 * To begin, open up the terminal and head to the directory where you want the program to be installed. Type the following into your terminal to install the Simulators:
 * 
 *     $ git clone https://github.umn.edu/umn-csci-3081-f19/repo-patel607
 * 
 * Now head to the correct directory within the the new repo:
 * 
 *     $ cd repo-patel607/project
 * 
 * From the project directory you will be able to run all the simulators. Now we need to compile all files necessary for our simulators.
 * 
 *     $ make
 * 
 * From here on out, the different types of simulators that are able to be run are explained.
 * 
 * \subsubsection transit_sim Transit Simulator
 * 
 * TransitSimulator makes use of LocalSimulator which has two preset routes that the busses will travel on. It features 8 stops on the outgoing route, and 9 on the incoming.
 * Buses are created every 10 time steps and begin on the first stop of the outgoing route. The simulation will run for 50 time steps in total.
 * 
 * You can run and see the results of the simulation in the project directory with:
 * 
 *     $ ./build/bin/transit_sim
 * 
 * \subsubsection capture_transit_sim Capture Transit Simulator
 * 
 * CaptureTransitSimulator functions exactly the same as TransitSimulator, but requires a single parameter in order to save the output of the simulation.
 * The simulator can be run in the project directory with:
 * 
 *     $ ./build/bin/capture_transit_sim <filename>
 * 
 * where the output of the simulation is captured in <filename> and saved in the project directory.
 * 
 * \subsubsection vis_sim Visual Simulator
 * 
 * VisualSimulator functions similarly to TransitSimulator, but allows for the visualizing of the simulator to a web interface. Run the VisualSimulator while in the project directory with 
 * 
 *     $ ./build/bin/vis_sim <port_number>
 * 
 * <port_number> can be anything. Try and pick numbers above 8000 and not multiples of 10. Access the visualization on a web browser at the url:
 * 
 *     http://127.0.0.1:<port_number>/web_graphics/project.html
 * 
 * With the VisualSimulator open, you are able to change how long the simulation will run, and how long the simulation should wait before generating a bus (once per route). 
 * When these are deciding click the “Run” button. If you want to run a new Visual Simulation, you need to repeat this entire process.
 * 
 * \subsubsection config_sim Configuration Simulator
 * 
 * ConfigurationSimulator functions similarly to TransitSimulator, but allows for the user to input various parameters to modify the simulation. 
 * Leaving any parameters empty will set them to a default value. The parameters are:
 * 
 * - <b><config_filename></b>: any file that contains the information on the routes, including stops and there positions. File must be in project/config directory. Defaults to "config.txt"
 * 
 * - <b><rounds></b>: any integer above 0 that represents the number of time steps to run. Defaults to 25.
 * 
 * - <b><bus_interval></b>: any integer above 0 that represents the time steps between busses for route 0. Defaults to 5.
 * 
 * You can run the ConfigurationSimulator with any of the following (while in project directory):
 * 
 *     $ ./build/bin/configuration_sim
 * 
 *     $ ./build/bin/configuration_sim <config_filename>
 * 
 *     $ ./build/bin/configuration_sim <config_filename> <rounds>
 * 
 *     $ ./build/bin/configuration_sim <config_filename> <rounds> <bus_interval>
 * 
 * Any configuration file you write for this simulator must follow this format:
 * 
 *     ROUTE_GENERAL, <bus_name>
 * 
 *     Stop Name, Long, Lat, Pass Gen Prob
 * 
 *     ROUTE, <outgoing_route>
 * 
 *     STOP, <stop_name>, <longitude>, <latitude>, <probability>
 *     STOP, <stop_name>, <longitude>, <latitude>, <probability>
 *     .
 *     .
 *     .
 * 
 *     ROUTE, <incoming_route>
 * 
 *     STOP, <stop_name>, <longitude>, <latitude>, <probability>
 *     STOP, <stop_name>, <longitude>, <latitude>, <probability>
 *     .
 *     .
 *     .
 * 
 * - <b><bus_name></b>: string that contains name of bus.
 * 
 * - <b><outgoing_route></b>: string that contains name of outgoing, or first, route.
 * 
 * - <b><incoming_route></b>: string that contains name of incoming, or second, route.
 * 
 * - <b><stop_name></b>: string that contains name of stop.
 * 
 * - <b><longitude></b>: float that contains real world x-coordinate of the stop.
 * 
 * - <b><latitude></b>: float that contains real world y-coordinate of the stop.
 * 
 * - <b><probability></b>: float that contains probability that a passenger is generated in a single time step.
 * 
 * STOPs following a ROUTE are all within that route, and ROUTE’s can contain as many STOPs as you want. 
 * Do not change anything in the file not specified by angle brackets <>. Make sure to save the file in the project/config directory as a text file.
 * 
 * 
 * \copyright 2019 3081 Staff, All rights reserved.
 *
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

#endif  // SRC_MAINPAGE_H_
