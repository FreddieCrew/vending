/* 
MIT License

Copyright (c) 2023 John Michael Reyes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Special thanks:
wuzi(https://github.com/wuzi/vending) and his server-side vending machine library(https://github.com/wuzi/vending).
*/

#if defined _vending_creator_included
	#endinput
#endif
#define _vending_creator_included

#tryinclude <a_samp>

#define MAX_VENDINGS (250)
#define MACHINE_TYPE_SODA (1)
#define MACHINE_TYPE_SNACK (2)
#define MACHINE_RADIUS (0.7)


#if MAX_VENDINGS >= 1000
    #if !defined DISABLE_MACHINE_LIMIT
        #error Using 1000 machines or more is not recommended. To ignore this warning, define #DISABLE_MACHINE_LIMIT.
    #endif
#endif


enum __vending {
    __type,
    __objectid,
    Float: __posX,
    Float: __posY,
    Float: __posZ,
    Float: __posR,
    Float: __posRx,
    Float: __posRy,
    Float: __posRz,
    __id
};
static __vendinginfo[MAX_VENDINGS][__vending];

enum E_VENDING_MACHINE {
	e_Model,
	e_Interior,
	Float: e_PosX,
	Float: e_PosY,
	Float: e_PosZ,
	Float: e_RotX,
	Float: e_RotY,
	Float: e_RotZ,
	Float: e_FrontX,
	Float: e_FrontY,
    	e_Type
}

static const Float: sc_VendingMachines[][E_VENDING_MACHINE] = {
	{955, 0, -862.82, 1536.60, 21.98, 0.00, 0.00, 180.00, -862.84, 1537.60, 1},
	{956, 0, 2271.72, -76.46, 25.96, 0.00, 0.00, 0.00, 2271.72, -77.46, 2},
	{955, 0, 1277.83, 372.51, 18.95, 0.00, 0.00, 64.00, 1278.73, 372.07, 1},
	{956, 0, 662.42, -552.16, 15.71, 0.00, 0.00, 180.00, 662.41, -551.16, 2},
	{955, 0, 201.01, -107.61, 0.89, 0.00, 0.00, 270.00, 200.01, -107.63, 1},
	{955, 0, -253.74, 2597.95, 62.24, 0.00, 0.00, 90.00, -252.74, 2597.95, 1},
	{956, 0, -253.74, 2599.75, 62.24, 0.00, 0.00, 90.00, -252.74, 2599.75, 2},
	{956, 0, -76.03, 1227.99, 19.12, 0.00, 0.00, 90.00, -75.03, 1227.99, 2},
	{955, 0, -14.70, 1175.35, 18.95, 0.00, 0.00, 180.00, -14.72, 1176.35, 1},
	{1977, 7, 316.87, -140.35, 998.58, 0.00, 0.00, 270.00, 315.87, -140.36, 2},
	{1775, 17, 373.82, -178.14, 1000.73, 0.00, 0.00, 0.00, 373.82, -179.14, 2},
	{1776, 17, 379.03, -178.88, 1000.73, 0.00, 0.00, 270.00, 378.03, -178.90, 2},
	{1775, 17, 495.96, -24.32, 1000.73, 0.00, 0.00, 180.00, 495.95, -23.32, 2},
	{1776, 17, 500.56, -1.36, 1000.73, 0.00, 0.00, 0.00, 500.56, -2.36, 2},
	{1775, 17, 501.82, -1.42, 1000.73, 0.00, 0.00, 0.00, 501.82, -2.42, 2},
	{956, 0, -1455.11, 2591.66, 55.23, 0.00, 0.00, 180.00, -1455.13, 2592.66, 2},
	{955, 0, 2352.17, -1357.15, 23.77, 0.00, 0.00, 90.00, 2353.17, -1357.15, 1},
	{955, 0, 2325.97, -1645.13, 14.21, 0.00, 0.00, 0.00, 2325.97, -1646.13, 1},
	{956, 0, 2139.51, -1161.48, 23.35, 0.00, 0.00, 87.00, 2140.51, -1161.53, 2},
	{956, 0, 2153.23, -1016.14, 62.23, 0.00, 0.00, 127.00, 2154.03, -1015.54, 2},
	{955, 0, 1928.73, -1772.44, 12.94, 0.00, 0.00, 90.00, 1929.73, -1772.44, 1},
	{1776, 1, 2222.36, 1602.64, 1000.06, 0.00, 0.00, 90.00, 2223.36, 1602.64, 2},
	{1775, 1, 2222.20, 1606.77, 1000.05, 0.00, 0.00, 90.00, 2223.20, 1606.77, 2},
	{1775, 1, 2155.90, 1606.77, 1000.05, 0.00, 0.00, 90.00, 2156.90, 1606.77, 2},
	{1775, 1, 2209.90, 1607.19, 1000.05, 0.00, 0.00, 270.00, 2208.90, 1607.17, 2},
	{1776, 1, 2155.84, 1607.87, 1000.06, 0.00, 0.00, 90.00, 2156.84, 1607.87, 2},
	{1776, 1, 2202.45, 1617.00, 1000.06, 0.00, 0.00, 180.00, 2202.43, 1618.00, 2},
	{1776, 1, 2209.24, 1621.21, 1000.06, 0.00, 0.00, 0.00, 2209.24, 1620.21, 2},
	{1776, 3, 330.67, 178.50, 1020.07, 0.00, 0.00, 0.00, 330.67, 177.50, 2},
	{1776, 3, 331.92, 178.50, 1020.07, 0.00, 0.00, 0.00, 331.92, 177.50, 2},
	{1776, 3, 350.90, 206.08, 1008.47, 0.00, 0.00, 90.00, 351.90, 206.08, 2},
	{1776, 3, 361.56, 158.61, 1008.47, 0.00, 0.00, 180.00, 361.54, 159.61, 2},
	{1776, 3, 371.59, 178.45, 1020.07, 0.00, 0.00, 0.00, 371.59, 177.45, 2},
	{1776, 3, 374.89, 188.97, 1008.47, 0.00, 0.00, 0.00, 374.89, 187.97, 2},
	{1775, 2, 2576.70, -1284.43, 1061.09, 0.00, 0.00, 270.00, 2575.70, -1284.44, 1},
	{1775, 15, 2225.20, -1153.42, 1025.90, 0.00, 0.00, 270.00, 2224.20, -1153.43, 1},
	{955, 0, 1154.72, -1460.89, 15.15, 0.00, 0.00, 270.00, 1153.72, -1460.90, 1},
	{956, 0, 2480.85, -1959.27, 12.96, 0.00, 0.00, 180.00, 2480.84, -1958.27, 2},
	{955, 0, 2060.11, -1897.64, 12.92, 0.00, 0.00, 0.00, 2060.11, -1898.64, 1},
	{955, 0, 1729.78, -1943.04, 12.94, 0.00, 0.00, 0.00, 1729.78, -1944.04, 1},
	{956, 0, 1634.10, -2237.53, 12.89, 0.00, 0.00, 0.00, 1634.10, -2238.53, 2},
	{955, 0, 1789.21, -1369.26, 15.16, 0.00, 0.00, 270.00, 1788.21, -1369.28, 1},
	{956, 0, -2229.18, 286.41, 34.70, 0.00, 0.00, 180.00, -2229.20, 287.41, 2},
	{955, 256, -1980.78, 142.66, 27.07, 0.00, 0.00, 270.00, -1981.78, 142.64, 1},
	{955, 256, -2118.96, -423.64, 34.72, 0.00, 0.00, 255.00, -2119.93, -423.40, 1},
	{955, 256, -2118.61, -422.41, 34.72, 0.00, 0.00, 255.00, -2119.58, -422.17, 1},
	{955, 256, -2097.27, -398.33, 34.72, 0.00, 0.00, 180.00, -2097.29, -397.33, 1},
	{955, 256, -2092.08, -490.05, 34.72, 0.00, 0.00, 0.00, -2092.08, -491.05, 1},
	{955, 256, -2063.27, -490.05, 34.72, 0.00, 0.00, 0.00, -2063.27, -491.05, 1},
	{955, 256, -2005.64, -490.05, 34.72, 0.00, 0.00, 0.00, -2005.64, -491.05, 1},
	{955, 256, -2034.46, -490.05, 34.72, 0.00, 0.00, 0.00, -2034.46, -491.05, 1},
	{955, 256, -2068.56, -398.33, 34.72, 0.00, 0.00, 180.00, -2068.58, -397.33, 1},
	{955, 256, -2039.85, -398.33, 34.72, 0.00, 0.00, 180.00, -2039.86, -397.33, 1},
	{955, 256, -2011.14, -398.33, 34.72, 0.00, 0.00, 180.00, -2011.15, -397.33, 1},
	{955, 2048, -1350.11, 492.28, 10.58, 0.00, 0.00, 90.00, -1349.11, 492.28, 1},
	{956, 2048, -1350.11, 493.85, 10.58, 0.00, 0.00, 90.00, -1349.11, 493.85, 2},
	{955, 0, 2319.99, 2532.85, 10.21, 0.00, 0.00, 0.00, 2319.99, 2531.85, 1},
	{956, 0, 2845.72, 1295.04, 10.78, 0.00, 0.00, 0.00, 2845.72, 1294.04, 2},
	{955, 0, 2503.14, 1243.69, 10.21, 0.00, 0.00, 180.00, 2503.12, 1244.69, 1},
	{956, 0, 2647.69, 1129.66, 10.21, 0.00, 0.00, 0.00, 2647.69, 1128.66, 2},
	{1209, 0, -2420.21, 984.57, 44.29, 0.00, 0.00, 90.00, -2419.21, 984.57, 1},
	{1302, 0, -2420.17, 985.94, 44.29, 0.00, 0.00, 90.00, -2419.17, 985.94, 1},
	{955, 0, 2085.77, 2071.35, 10.45, 0.00, 0.00, 90.00, 2086.77, 2071.35, 1},
	{956, 0, 1398.84, 2222.60, 10.42, 0.00, 0.00, 180.00, 1398.82, 2223.60, 2},
	{956, 0, 1659.46, 1722.85, 10.21, 0.00, 0.00, 0.00, 1659.46, 1721.85, 2},
	{955, 0, 1520.14, 1055.26, 10.00, 0.00, 0.00, 270.00, 1519.14, 1055.24, 1},
	{1775, 6, -19.03, -57.83, 1003.63, 0.00, 0.00, 180.00, -19.05, -56.83, 1},
	{1775, 18, -16.11, -91.64, 1003.63, 0.00, 0.00, 180.00, -16.13, -90.64, 1},
	{1775, 16, -15.10, -140.22, 1003.63, 0.00, 0.00, 180.00, -15.11, -139.22, 1},
	{1775, 17, -32.44, -186.69, 1003.63, 0.00, 0.00, 180.00, -32.46, -185.69, 1},
	{1775, 16, -35.72, -140.22, 1003.63, 0.00, 0.00, 180.00, -35.74, -139.22, 1},
	{1776, 6, -36.14, -57.87, 1003.63, 0.00, 0.00, 180.00, -36.16, -56.87, 2},
	{1776, 18, -17.54, -91.71, 1003.63, 0.00, 0.00, 180.00, -17.56, -90.71, 2},
	{1776, 16, -16.53, -140.29, 1003.63, 0.00, 0.00, 180.00, -16.54, -139.29, 2},
	{1776, 17, -33.87, -186.76, 1003.63, 0.00, 0.00, 180.00, -33.89, -185.76, 2},
	{1775, 6, -19.03, -57.83, 1003.63, 0.00, 0.00, 180.00, -19.05, -56.83, 1},
	{1776, 6, -36.14, -57.87, 1003.63, 0.00, 0.00, 180.00, -36.16, -56.87, 2},
	{1775, 18, -16.11, -91.64, 1003.63, 0.00, 0.00, 180.00, -16.13, -90.64, 1},
	{1776, 18, -17.54, -91.71, 1003.63, 0.00, 0.00, 180.00, -17.56, -90.71, 2},
	{1776, 16, -16.53, -140.29, 1003.63, 0.00, 0.00, 180.00, -16.54, -139.29, 2},
	{1775, 16, -15.10, -140.22, 1003.63, 0.00, 0.00, 180.00, -15.11, -139.22, 1},
	{1776, 17, -33.87, -186.76, 1003.63, 0.00, 0.00, 180.00, -33.89, -185.76, 2},
	{1775, 17, -32.44, -186.69, 1003.63, 0.00, 0.00, 180.00, -32.46, -185.69, 1},
	{1775, 16, -35.72, -140.22, 1003.63, 0.00, 0.00, 180.00, -35.74, -139.22, 1}
};




// Forwards
forward OnPlayerUseVendingMachine(playerid, type);
forward bool:IsValidVendingMachine(id);

/* 
* Natives for Pawno

native CreateVendingMachine(Float:X, Float:Y, Float:Z, Float:Rx, Float:Ry = 0.0, Float:Rz = 0.0, type = MACHINE_TYPE_SODA);
native GetPlayerNearVendingMachineID(playerid);
native GetVendingMachinePos(machineid, &Float:X, &Float:Y, &Float:Z);
native GetVendingMachineRotation(machineid, &Float:RX, &Float:RY, &Float:RZ);
native bool:IsValidVendingMachine(machineid);
native DestroyVendingMachine(machineid);
*/


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    static Float:X, Float:Y, Float:A[3], Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

    if ((newkeys & KEY_SECONDARY_ATTACK) && !(oldkeys & KEY_SECONDARY_ATTACK) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && (GetPlayerAnimationIndex(playerid) != 1660) && (GetPlayerAnimationIndex(playerid) != 1657) && (GetPlayerAnimationIndex(playerid) != 1659)) {
        for (new i = 0; i < MAX_VENDINGS; i++) {
            GetXYInFrontOfVending(i, X, Y, 0.5);
            if (!IsValidVendingMachine(__vendinginfo[i][__objectid]) || !IsPlayerInRangeOfPoint(playerid, MACHINE_RADIUS, X-0.7, Y, __vendinginfo[i][__posZ])) continue;

            if (__vendinginfo[i][__type] == MACHINE_TYPE_SODA) {
                GetVendingMachineRotation(i, A[0], A[1], A[2]);
                SetPlayerPos(playerid, pos[0], pos[1]+0.2, pos[2]);
                SetPlayerFacingAngle(playerid, A[2]+0.3);
                ApplyAnimation(playerid, "VENDING", "VEND_USE", 10.0, 0, 0, 0, 0, 0, 1);
                PlayerPlaySound(playerid, 42600, 0.0, 0.0, 0.0);
                SetTimerEx("__StartUsingEvent", 2500, false, "ii", playerid, 1);
            } else if (__vendinginfo[i][__type] == MACHINE_TYPE_SNACK) {
                GetVendingMachineRotation(i, A[0], A[1], A[2]);
                SetPlayerPos(playerid, pos[0], pos[1]+0.2, pos[2]);
                SetPlayerFacingAngle(playerid, A[2]+0.3);
                ApplyAnimation(playerid, "VENDING", "VEND_USE", 10.0, 0, 0, 0, 0, 0, 1);
                PlayerPlaySound(playerid, 42601, 0.0, 0.0, 0.0);
                SetTimerEx("__StartUsingEvent", 2500, false, "ii", playerid, 2);
            }
        }
    }

    #if defined vending_OnPlayerKeyStateChange
        vending_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#endif
    return 1;
}

public OnGameModeInit() {
    for (new i = 0; i < sizeof(sc_VendingMachines); i++) {
        if (sc_VendingMachines[i][e_Model] == 1776) {
            CreateVendingMachine(sc_VendingMachines[i][e_PosX], sc_VendingMachines[i][e_PosY], sc_VendingMachines[i][e_PosZ], sc_VendingMachines[i][e_RotX], sc_VendingMachines[i][e_RotY], sc_VendingMachines[i][e_RotZ], sc_VendingMachines[i][e_Type]);
        } else {
            CreateVendingMachine(sc_VendingMachines[i][e_PosX], sc_VendingMachines[i][e_PosY], sc_VendingMachines[i][e_PosZ]+0.7, sc_VendingMachines[i][e_RotX], sc_VendingMachines[i][e_RotY], sc_VendingMachines[i][e_RotZ], sc_VendingMachines[i][e_Type]);
        }
    }

    #if defined vending_OnGameModeInit
        vending_OnGameModeInit();
    #endif
    return 1;
}

public OnGameModeExit() {
    for(new i; i < sizeof(sc_VendingMachines); i++) {
	DestroyVendingMachine(i);
    }

    #if defined vending_OnGameModeExit
        vending_OnGameModeExit();
    #endif
    return 1;
}

public OnPlayerConnect(playerid) {
    __PreloadAnimLibs(playerid);

    for (new i = 0; i < sizeof(sc_VendingMachines); i++) {
		RemoveBuildingForPlayer(playerid, sc_VendingMachines[i][e_Model], sc_VendingMachines[i][e_PosX], sc_VendingMachines[i][e_PosY], sc_VendingMachines[i][e_PosZ], 0.25);
	}

    #if defined __vending_OnPlayerConnect
    	__vending_OnPlayerConnect(playerid);
    #endif
    return 1;
}

stock __PreloadAnimLibs(playerid) {
    ApplyAnimation(playerid, "VENDING", "null", 4.0, 0, 0, 0, 0, 0, 1);
    return 1;
}

forward __StartUsingEvent(playerid, type);
public __StartUsingEvent(playerid, type) {
    if (type == 1) {
        ApplyAnimation(playerid, "VENDING", "VEND_Drink_P", 3.33, 0, 0, 0, 0, 0, 1);
        CallLocalFunction("OnPlayerUseVendingMachine", "ii", playerid, type);
    } else if (type == 2) {
        ApplyAnimation(playerid, "VENDING", "VEND_Eat_P", 1.67, 0, 0, 0, 0, 0, 1);
        CallLocalFunction("OnPlayerUseVendingMachine", "ii", playerid, type);
    }

    return 1;
}


// Functions
stock CreateVendingMachine(Float:X, Float:Y, Float:Z, Float:Rx, Float:Ry = 0.0, Float:Rz = 0.0, type = MACHINE_TYPE_SODA) {
    static __count;
    __count++;

    if (__count == MAX_VENDINGS) {
        print("The vending limit has been exceeded.");
    }

    switch (type) {
        case MACHINE_TYPE_SODA: {
            #if defined Streamer_IncludeFileVersion
            	__vendinginfo[__count][__objectid] = CreateDynamicObject(1775, X, Y, Z, Rx, Ry, Rz);
            #else
           	 __vendinginfo[__count][__objectid] = CreateObject(1775, X, Y, Z, Rx, Ry, Rz);
            #endif
            __vendinginfo[__count][__type] = 1;
        }
        case MACHINE_TYPE_SNACK: {
            #if defined Streamer_IncludeFileVersion
                __vendinginfo[__count][__objectid] = CreateDynamicObject(1776, X, Y, Z, Rx, Ry, Rz);
            #else
                __vendinginfo[__count][__objectid] = CreateObject(1776, X, Y, Z, Rx, Ry, Rz);
            #endif
            __vendinginfo[__count][__type] = 2;
        }
        default: {
            print("[vending.inc] Warning: Invalid vending machine type");
        }
    }

    __vendinginfo[__count][__id] = __count + 1;
    __vendinginfo[__count][__posX] = X;
    __vendinginfo[__count][__posY] = Y;
    __vendinginfo[__count][__posZ] = Z;
    __vendinginfo[__count][__posRx] = Rx;
    __vendinginfo[__count][__posRy] = Ry;
    __vendinginfo[__count][__posRz] = Rz;
    return 1;
}


stock GetPlayerNearVendingMachineID(playerid) {
    static vendingid, Float:X, Float:Y;
    for (new i = 0; i < MAX_VENDINGS; i++) {
        GetXYInFrontOfVending(i, X, Y, 0.5);

        if (!IsValidVendingMachine(i) || !IsPlayerInRangeOfPoint(playerid, MACHINE_RADIUS, X, Y, __vendinginfo[i][__posZ])) continue;
    
        vendingid = i;
    }
    return vendingid;
}

stock GetVendingMachinePos(id, &Float:X, &Float:Y, &Float:Z) {
    X = __vendinginfo[id][__posX];
    Y = __vendinginfo[id][__posY];
    Z = __vendinginfo[id][__posZ];
    return 1;
}

stock GetVendingMachineRotation(id, &Float:RX, &Float:RY, &Float:RZ) {
    RX = __vendinginfo[id][__posRx];
    RY = __vendinginfo[id][__posRy];
    RZ = __vendinginfo[id][__posRz];
    return 1;
}
stock GetXYInFrontOfVending(id, &Float:x, &Float:y, Float:distance) {
    // Function taken from https://github.com/wuzi/vending (Thanks to wuzi for inspiring me to create this system)!
    static Float:a, Float:z;
	GetVendingMachineRotation(id, x, y, a);
	GetVendingMachinePos(id, x, y, z);

	a += 180.0;
	if(a > 359.0) a -= 359.0;

	x += (distance * floatsin(-a, degrees));
	y += (distance * floatcos(-a, degrees));
    return 1;
}

stock bool:IsValidVendingMachine(id) {
    if(__vendinginfo[id][__posX] == 0.0 && __vendinginfo[id][__posY] == 0.0) return false;
    return true;
}

stock DestroyVendingMachine(id) {
    if(!IsValidVendingMachine(id)) return 1;

    __vendinginfo[id][__posX] = 0.0;
    __vendinginfo[id][__posY] = 0.0;
    __vendinginfo[id][__posZ] = 0.0;
    __vendinginfo[id][__posRx] = 0.0;
    __vendinginfo[id][__posRy] = 0.0;
    __vendinginfo[id][__posRz] = 0.0;
    __vendinginfo[id][__id] = -1;

    #if defined Streamer_IncludeFileVersion
        DestroyDynamicObject(__vendinginfo[id][__objectid]);
    #else
        DestroyObject(__vendinginfo[id][__objectid]);
    #endif
    return 1;
}

// ALS Hooks Meta
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect vending_OnPlayerConnect
#if defined vending_OnPlayerConnect
	forward vending_OnPlayerConnect(playerid);
#endif

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange vending_OnPlayerKeyStateChange
#if defined vending_OnPlayerKeyStateChange
forward vending_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit vending_OnGameModeInit
#if defined vending_OnGameModeInit
	forward vending_OnGameModeInit();
#endif
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit vending_OnGameModeExit
#if defined vending_OnGameModeExit
	forward vending_OnGameModeExit();
#endif
