# Arduino FreeRTOS Examples

Multiple 'bare metal' AVR FreeRTOS examples.

## Install.

    git clone --recurse-submodules --jobs 8 https://github.com/dapperfu/arduino_FreeRTOS.git

    cd arduino_FreeRTOS

## Setup environment.

Needs done once per machine/host.

    sudo make env.host # From regular user.
    make env.host # As root
    
Setup 
- Arduino
- Arduino Make
- Python

    make env
    

## Build examples.

   make examples
