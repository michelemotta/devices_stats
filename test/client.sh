#!/bin/bash

for i in {1..10}
do
   echo "DEV1:qwerty" | nc localhost 1234 -w 1
   echo "DEV3:qwerty" | nc localhost 1234 -w 1
   echo "DEV89:qwerty" | nc localhost 1234 -w 1
done
