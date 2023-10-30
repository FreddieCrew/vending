#include <a_samp>
#include <Pawn.CMD>
#include <vending>

main() {
  print("Server started");
}

public OnPlayerRequestClass(playerid, classid) {
    SetSpawnInfo(playerid, 0, 0, 1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    return 1;
}

public OnPlayerSpawn(playerid) {
	SetPlayerHealth(playerid, 50.0);
	return 1;
}

CMD:createvending(playerid, params[]) {
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	
 	CreateVendingMachine(X, Y, Z, 0.00000, 0.00000, 198.69562+5, MACHINE_TYPE_SODA);
	return 1;
}
