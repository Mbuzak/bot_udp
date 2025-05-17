# BOT UDP
Digital thermometer UDP

## Requirements
- GCC 13.3 or newer
- CMake 3.28 or newer

## Installation
```
mkdir build && cd build
cmake ..
cmake --build .
```

## Example
`./run.sh 127.0.0.1 5000 2 5 ./log.txt`
`./build/src/server/server`

```
[Info] Id: 1	Time: 0s	Temperature: 59 C	Power supply: Battery 	Checksum: 62
[Info] Send
[Info] Id: 1	Time: 0s	Temperature: 59 C	Power supply: Battery 	Checksum: 62
[Info] Id: 1	Time: 0s	Temperature: 59 C	Power supply: Battery 	Checksum: 62
[Info] Send
[Info] Id: 2	Time: 5s	Temperature: 78 C	Power supply: Ethernet 	Checksum: 86
[Info] Id: 2	Time: 5s	Temperature: 78 C	Power supply: Ethernet 	Checksum: 86
[Info] Send
[Info] Id: 3	Time: 10s	Temperature: 26 C	Power supply: Battery 	Checksum: 41
```
