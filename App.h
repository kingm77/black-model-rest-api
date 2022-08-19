#pragma once
#include <cpprest/json.h>
#include "Router.h"

namespace app {
	void StartServer(const utility::string_t& address);
	Router GenerateApiRoutes();
	void ShutDown();
}
