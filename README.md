# Vending
Simple library for creating server-side vending machines.

## Functions
```c
CreateVendingMachine(Float:X, Float:Y, Float:Z, Float:Rx, Float:Ry = 0.0, Float:Rz = 0.0, type = MACHINE_TYPE_SODA);
GetPlayerNearVendingMachineID(playerid);
GetVendingMachinePos(machineid, &Float:X, &Float:Y, &Float:Z);
GetVendingMachineRotation(machineid, &Float:RX, &Float:RY, &Float:RZ);
bool:IsValidVendingMachine(machineid);
DestroyVendingMachine(machineid);
```
## Callbacks
```c
public OnPlayerUseVendingMachine(playerid, type)
```
