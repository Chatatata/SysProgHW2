#!/bin/sh

echo "cleaning build artifacts"
make clean >> /dev/null

echo "running make"
make >> /dev/null

echo "running tests"

sudo ./kill_child_on_exit_unit_tests

if [ $? -ne 0 ]; then
    echo "unit test failed."
    exit 1
fi

./kill_child_on_exit_unit_tests

if [ $? -ne 0 ]; then
    echo "unit test failed."
    exit 1
fi

echo "test suite completed."
