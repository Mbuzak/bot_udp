#!/bin/bash
cmake --build build/
./build/src/client/bot_udp $1 $2 $3 $4 $5
