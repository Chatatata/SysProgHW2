#!/bin/sh

printf  "\033[1;33mcleaning build artifacts\033[0m\n"
make clean >> /dev/null

printf "\033[1;33mrunning make\033[0m\n"
make >> /dev/null

printf "\033[1;33mrunning tests\033[0m (may ask for password)\n"

sudo ./kill_child_on_exit_unit_tests

if [ $? -ne 0 ]; then
    printf "\033[1;31munit test failed.\033[0m\n"
    exit 1
fi

./kill_child_on_exit_unit_tests

if [ $? -ne 0 ]; then
    printf "\033[1;31munit test failed.\033[0m\n"
    exit 1
fi

printf "\033[1;32mtest suite completed.\033[0m\n"
