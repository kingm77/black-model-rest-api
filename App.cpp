#include "App.h"

#include <iostream>

// routes handler
#include "FunctionHandler.h"
#include "RouteHandler.h"

// server
#include "PricingServer.h"

// black-scholes controller
#include "BlackScholesHandler.h"

#include <cpprest/uri.h>

#include "strConstant.h"


std::unique_ptr<PricingServer> g_http;

//////////////////////////////////////////////////
// STart the Server with the Given URL
//
void app::StartServer(const utility::string_t& address)
{
	// Build our listener's URI from the address given
	// We just append VanillaPricer/ to the base URL
	web::uri_builder uri(address);
	uri.append_path(utility::conversions::to_string_t(str::route::BASE_ROUTE));
	ucout << uri.to_uri().to_string() << std::endl;
	auto addr = uri.to_uri().to_string();
	/////////////////////////////////
	// Create an Instance of the Server and Invoke Wait to 
	// start the Server...
	g_http = std::unique_ptr<PricingServer>(new PricingServer(addr, GenerateApiRoutes()));
	g_http->Open().wait();
	//---- Indicate the start and spit URI to the Console
	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;
}

////////////////////////////////////////
// Simply Closes the Connection... Close returns 
// pplx::task<void> ...we need to Call wait to invoke the 
// operation...
void app::ShutDown()
{
	g_http->Close().wait();
	return;
}

Router app::GenerateApiRoutes()
{
	Router mainRouter{};
	Router pricerRouter{};
	Router blackScholesRouter{};

	blackScholesRouter.get(str::route::CALL_ROUTE, std::make_shared<FunctionHandler>(BlackScholesHandler::handlePrincingCall));
	blackScholesRouter.get(str::route::PUT_ROUTE, std::make_shared<FunctionHandler>(BlackScholesHandler::handlePricingPut));

	pricerRouter.use(str::route::BLACK_SCHOLES_ROUTE, std::make_shared<RouterHandler>(blackScholesRouter));

	mainRouter.use(str::route::BASE_ROUTE, std::make_shared<RouterHandler>(pricerRouter));

	return mainRouter;
}
