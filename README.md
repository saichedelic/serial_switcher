# serial_switcher
Serial Command based remote switching using Arduino w/ master key control

Functions offered based on State of Master Swtich state:

"MON_REQ": Sends a request to get the active state of the switches.
"READ": Reads the last stored value from EEPROM
"SYNC": Syncs the last value stored in EEPROM

For now switching is possible by sending a string of 16 characters based on sequence.
Eg: "0001000011110001"

It can act weird if the sequence contains anything other than 0's or 1's. Will be fixed sooon.

To get it working, set Node ID in the code.
Command sequence is "NODE_ID:command"
Example packet to read and write is as follows,
1:READ
1:0001000011110001

This was sketched with a wireless interface in mind.
I use a generic wireless UART link to communicate with multiple devices over a single serial interface.

NOTE: The master switch is a DPDT toggle. Essentially restarts the arduino whenever the switch is toggled between manual and automatic modes.
