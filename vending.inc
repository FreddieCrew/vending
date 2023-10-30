#if defined _vending_creator_included
	#endinput
#endif
#define _vending_creator_included

#tryinclude <a_samp>

#define MAX_VENDINGS 100
#define MACHINE_TYPE_SODA 1
#define MACHINE_TYPE_SNACK 2

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




stock CreateVendingMachine(Float:X, Float:Y, Float:Z, Float:Rx, Float:Ry = 0.0, Float:Rz = 0.0, type = MACHINE_TYPE_SODA) {
    static __count;
    __count++;

    if (count == MAX_VENDINGS) {
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

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if (newkeys & KEY_SECONDARY_ATTACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        for (new i = 0; i < MAX_VENDINGS; i++) {
            if (!IsValidObject(__vendinginfo[i][__objectid]) || !IsPlayerInRangeOfPoint(playerid, 1.0, __vendinginfo[i][__posX], __vendinginfo[i][__posY], __vendinginfo[i][__posZ])) continue;

            if (__vendinginfo[i][__type] == MACHINE_TYPE_SODA) {
                ApplyAnimation(playerid, "VENDING", "VEND_USE", 10.0, 0, 0, 0, 0, 0, 1);
                SetTimerEx("__StartUsingEvent", 2500, false, "ii", playerid, 1);
            }
            else if (__vendinginfo[i][__type] == MACHINE_TYPE_SNACK) {
                ApplyAnimation(playerid, "VENDING", "VEND_USE", 10.0, 0, 0, 0, 0, 0, 1);
                SetTimerEx("__StartUsingEvent", 2500, false, "ii", playerid, 2);
            }
        }
    }

    #if defined __vending_OnPlayerKeyStateChang
    __vending_OnPlayerKeyStateChang(playerid, newkeys, oldkeys);
	#endif
    return 1;
}

public OnPlayerConnect(playerid) {
    __PreloadAnimLibs(playerid);

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
    if(type == 1) {
        ApplyAnimation(playerid, "VENDING", "VEND_Drink_P", 3.33, 0, 0, 0, 0, 0, 1);
    }
    else if(type == 2) {
        ApplyAnimation(playerid, "VENDING", "VEND_Eat_P", 1.67, 0, 0, 0, 0, 0, 1);
    }
    SetTimerEx("__EndUsingEvent", 3, false, "ii", playerid, type);

    return 1;
}

forward __EndUsingEvent(playerid, type);
public __EndUsingEvent(playerid, type) {
    static Float:
     PrevHealth;

    GetPlayerHealth(playerid, PrevHealth);

    if (type == MACHINE_TYPE_SODA) {
        SetPlayerHealth(playerid, PrevHealth + 30);
        if (PrevHealth >= 90.0 && PrevHealth < 100.0) {
            SetPlayerHealth(playerid, PrevHealth + 10);
        }
    }
    else if(type == MACHINE_TYPE_SNACK) {
        SetPlayerHealth(playerid, PrevHealth + 45);
        if (PrevHealth >= 90.0 && PrevHealth < 100.0) {
            SetPlayerHealth(playerid, PrevHealth + 10);
        }
    }
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