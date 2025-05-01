#!/bin/bash
cmake --build build/
./build/src/bot_udp $1 $2 $3 $4 $5
