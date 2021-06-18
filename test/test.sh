#!/bin/bash

echo -n "minitalk tester: " > test.log
date "+%Y/%m/%d %H:%M:%S" >> test.log
echo >> test.log

if [ ! -x ../server ]; then
    echo "No server executable found. Compiling..." | tee -a test.log
    make server -C .. 
fi

if [ ! -x ../client ]; then
    echo "No client executable found. Compiling..." | tee -a test.log
    make client -C .. 
fi

echo "Starting server..." | tee -a test.log
(../server > server.log)&
echo "Server started (PID = $!)"

# logfile
sleep 1
echo "[minitalk server] launched on PID = $!" > server_ref.log

../client $! 0123456789 | tee -a test.log
../client $! qwertyuiopasdfghjklzxcvbnm | tee -a test.log

echo "Stoping server..." | tee -a test.log
kill -INT $!
echo "Server stoped" | tee -a test.log

cat output_ref.log >> server_ref.log

echo "checking diff..." | tee -a test.log
diff server.log server_ref.log >> test.log

if [ $? -eq 0 ]; then
    echo "        diff OK:)" | tee -a test.log
    exit 0
else
    echo "        diff KO:)" | tee -a test.log
    exit 1
fi
