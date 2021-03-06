# © Jeroen - 31-10-2018
# This file handles: scanning for ports connected,
# check existing connections and removing old ports from a dictionary

from serial.tools import list_ports

# Returns a list with ports that are currently attached


def get_new_ports(existing_ports):
    new_ports = find_available_ports()

    for port in existing_ports:
        if port in new_ports:
            new_ports.remove(port)

    return new_ports

# Handles module searching


def find_available_ports():
    # Get all comports connected
    ports = list_ports.comports()  # list of all ports connected
    result = []  # list to store comports

    for port in ports:
        port_found = port[0]  # port that has been found
        result.append(port_found)  # add port to the list

    return result

# Check if port is still connected


def check_connection(comport):
    # Get all connected com ports
    all_ports = find_available_ports()

    if comport in all_ports:
        return True
    else:
        return False
