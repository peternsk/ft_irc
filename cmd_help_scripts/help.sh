#!/bin/bash

if [ $0 == "JOIN" ]; then
    echo -e "JOIN \n\
    Syntax: \n\
    \n\
    JOIN <channels> [<keys>] \n\
    \n\
    Makes the client join the channels in the comma-separated list <channels>,\n\
    specifying the passwords, if needed, in the comma-separated list <keys>.\n\
    [11] If the channel(s) do not exist then they will be created. Defined in RFC 1459.

    "
fi
