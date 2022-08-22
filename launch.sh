#!/bin/bash

# Start the first process
./app 34566 &


  
# Start the second process
exec nginx -g "daemon off;" &

  
# Wait for any process to exit
wait -n
  
# Exit with status of process that exited first
exit $?