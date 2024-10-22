#!/bin/bash

#
# ********************************************************************************************************************
#  COPYRIGHT
#  ------------------------------------------------------------------------------------------------------------------
#  \verbatim
#  Copyright (c) 2022-2023 by Vector Informatik GmbH. All rights reserved.
#
#  This software is copyright protected and proprietary to Vector Informatik GmbH.
#  Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
#  All other rights remain with Vector Informatik GmbH.
#  \endverbatim
# ********************************************************************************************************************
#

echo "downloading json.hpp from GitHub"

if ! command -v curl &> /dev/null; then
    echo "curl not found"
else
    echo "using curl to download library"
    # -L = follow redirect
    # -f = fail silently on server errors, no output
    curl -L -f https://github.com/nlohmann/json/releases/download/v3.6.1/json.hpp --output json.hpp
    if [ $? -eq 0 ]; then
        exit
    fi
    echo "curl failed to download"
fi


if ! command -v wget &> /dev/null; then
    echo "wget not found"
else
    echo "using wget to download library"
    wget https://github.com/nlohmann/json/releases/download/v3.6.1/json.hpp
    if [ $? -eq 0 ]; then
        exit
    fi
    echo "wget also failed to download"
fi    

echo "Neither wget nor curl could be used to download. Please download the library manually"
exit 1
