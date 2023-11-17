#include <a_samp>
#include <Pawn.CMD>
#include <sscanf2>
#include <vending>

main() {
  print("Server started");
}

public OnPlayerRequestClass(playerid, classid) {
    SetSpawnInfo(playerid, 0, 0, 1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    return 1;
}

public OnPlayerUseVendingMachine(playerid, type) {
	new id = GetPlayerNearVendingMachineID(playerid), string[128];
	if(type == 1) {
	    format(string, sizeof(string), "Machine ID: %d | Enjoy your coke, cheers!", id);
		SendClientMessage(playerid, -1, string);
	}
	else if(type == 2) {
	    format(string, sizeof(string), "Machine ID: %d | Enjoy your snack!", id);
		SendClientMessage(playerid, -1, string);
	}
	return 1;
}

public OnPlayerSpawn(playerid) {
	SetPlayerHealth(playerid, 50.0);
	return 1;
}

CMD:createvending(playerid, params[]) {
	new Float:X, Float:Y, Float:Z, type;
	GetPlayerPos(playerid, X, Y, Z);
	if (sscanf(params, "i", type)) return SendClientMessage(playerid, -1, "Syntax: /createvending [type]");

	if (type > 2 || type < 1) return SendClientMessage(playerid, -1, "Invalid vending type");
	
	if (type == 1) {
 		CreateVendingMachine(X, Y, Z, 0.00000, 0.00000, 198.69562+5, MACHINE_TYPE_SODA);
	}
	else if (type == 2) {
        CreateVendingMachine(X, Y, Z, 0.00000, 0.00000, 198.69562+5, MACHINE_TYPE_SNACK);
	}
	return 1;
}
