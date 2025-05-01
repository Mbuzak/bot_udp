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
`./run.sh 127.0.0.1 5000 5 2 ./log.txt`

```
[Info] Id: 1	Time: 0s	Temperature: 50 C	Power supply: Ethernet 	Checksum: 52
[Info] Id: 2	Time: 2s	Temperature: 20 C	Power supply: Battery 	Checksum: 26
[Info] Id: 3	Time: 4s	Temperature: 75 C	Power supply: Ethernet 	Checksum: 83
[Info] Id: 4	Time: 6s	Temperature: 103 C	Power supply: Ethernet 	Checksum: 114
```
