#!/bin/bash
ip_addr=(`ifconfig en0 | grep "inet " | awk '{ print $2}'`)
echo $ip_addr