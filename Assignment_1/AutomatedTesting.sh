#!/bin/bash

echo "Testing child_processes with 2 processes."
./child_processes 2
echo "Testing child_processes with 4 processes."
./child_processes 4
echo "Testing child_processes with 8 processes."
./child_processes 8

echo "Testing child_processes_chain with 2 processes."
./child_processes_chain 2
echo "Testing child_processes_chain with 4 processes."
./child_processes_chain 4
echo "Testing child_processes_chain with 8 processes."
./child_processes_chain 8
