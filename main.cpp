// SimpleServer.cpp : Defines the entry point for the console application.
//


#include "App.h"

#include <iostream>

#include "strConstant.h"

int main()
{
	auto port = utility::conversions::to_string_t(str::app::PORT);

	//--- Create the Server URI base address
	auto address = utility::conversions::to_string_t(str::app::BASE_URL);

	address.append(port);
	
	app::StartServer(address);
	std::cout << "Press ENTER to exit." << std::endl;

	//--- Wait Indefenintely, Untill some one has 
	// pressed a key....and Shut the Server down
	std::string line;
	std::getline(std::cin, line);
	app::ShutDown();
}