# Arduino FreeRTOS Examples

Multiple 'bare metal' AVR FreeRTOS examples.

## Install.

    git clone --recurse-submodules --jobs 8 https://github.com/jed-frey/FreeRTOS_AVR_Examples.git

    cd FreeRTOS_AVR_Examples

## Setup environment.

Needs done once per machine/host.

    sudo make env.host # From regular user.
    make env.host # As root

## Build examples.

   make examples
