## Overview
Simulates one STM32 device with firmware from [smart-heating repository](https://github.com/Akirathan/STM32-smart-heating).

Purpose of this program is to simulate network communication between STM32 device and
web server (in this [repository](https://github.com/Akirathan/STM_comm_web_server)).

The term simulator is misleading because only small part of device functionality is simulated.

## CLI
### Options
- `devsim <dev_id>`
    - Starts the program and creates a device with device id

### Standard input
- `create <dev_id>`
    - Creates device with device ID
