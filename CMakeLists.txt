cmake_minimum_required(VERSION 3.9)
project(black)


find_package(cpprestsdk REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_target_properties(cpprestsdk::cpprestsdk_openssl_internal PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "CPPREST_NO_SSL_LEAK_SUPPRESS"
  INTERFACE_LINK_LIBRARIES "OpenSSL::SSL"
)

add_executable(app utils.cpp BlackScholes.cpp BlackScholesHandler.cpp RouteHandler.cpp Router.cpp FunctionHandler.cpp RouterHandler.cpp PricingServer.cpp App.cpp main.cpp)
target_link_libraries(app PRIVATE cpprestsdk::cpprest)