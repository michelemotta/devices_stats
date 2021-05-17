# README

The repository is a proof-of-concept of a client-server application. The server is a multi-client implementation without thread creations for new connections. The multi-clients are served using the system call select(...).

## Build and Run

In order to build and run:
```
cmake -S . -B build
cd build
./device_stats
```

At this point, the server is ready to accept requests from clients. There is a simple script in ./test/client.sh, but whatever TCP client can be used.

The server validates and counts only messages that obey the following pattern:
```
device_name:body of the message that is ignored
```

Each time a client sends a request the total amount of messages is printed on stdout.

## Class diagram

[Class Diagram](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/michelemotta/devices_stats/main/class.iuml)

## Sequence diagram

[Sequence diagram](http://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/michelemotta/devices_stats/main/sequence.iuml)

