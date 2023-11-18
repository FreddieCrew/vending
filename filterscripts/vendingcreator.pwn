#include <a_samp>
#include <Pawn.CMD>
#include <sscanf2>
#include <vending>

#define FILTERSCRIPT

new machineobject[MAX_VENDINGS];


public OnFilterScriptInit() {
	LoadVendingMachines("vending.txt");
	print("Vending Machine creator successfully loaded\n");
	return 1;
}

public OnPlayerUseVendingMachine(playerid, type) {
	new Float: PrevHealth;

    GetPlayerHealth(playerid, PrevHealth);

    if (type == MACHINE_TYPE_SODA && PrevHealth < 100.0) {
        SetPlayerHealth(playerid, PrevHealth + 30);
        if (PrevHealth >= 90.0 && PrevHealth < 100.0) {
            SetPlayerHealth(playerid, PrevHealth + 10);
        }
    } else if (type == MACHINE_TYPE_SNACK && PrevHealth < 100.0) {
        SetPlayerHealth(playerid, PrevHealth + 45);
        if (PrevHealth >= 90.0 && PrevHealth < 100.0) {
            SetPlayerHealth(playerid, PrevHealth + 10);
        }
    }
	return 1;
}

CMD:createvending(playerid, const params[]) {
	new Float: X, Float: Y, Float: Z, Float: mX, Float: mY, Float: mZ, Float: mRx, Float: mRy, Float: mRz, type, machineid, File: machines = fopen("vending.txt", io_append), string[128], object;
	GetPlayerPos(playerid, X, Y, Z);
	if (sscanf(params, "i", type)) return SendClientMessage(playerid, -1, "Syntax: /createvending [type]");

	if (type > 2 || type < 1) return SendClientMessage(playerid, -1, "Invalid vending type");
	
	if (type == 1) {
 		machineid = CreateVendingMachine(X, Y-1.0, Z, 0.00000, 0.00000, 198.69562+5, MACHINE_TYPE_SODA);
 		object = 1;
	} else if (type == 2) {
        machineid = CreateVendingMachine(X, Y-1.0, Z, 0.00000, 0.00000, 198.69562+5, MACHINE_TYPE_SNACK);
		object = 2;
	}
	
	GetVendingMachinePos(machineid, mX, mY, mZ);
	GetVendingMachineRotation(machineid, mRx, mRy, mRz);
	
 	format(string, sizeof(string), "%f, %f, %f, %f, %f, %f, %d ;\r\n", X, Y, Z, mRx, mRy, mRz, object);
	fwrite(machines, string);
	fclose(machines);
	return 1;
}

LoadVendingMachines(const Path[]) {
	static File: File, buffer[256], type, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, count = 0;

	File = fopen(Path, io_read);
	if (!File) return printf("[Error]: The file %s does not exist on scriptfiles.\n", Path);

	while (fread(File, buffer) > 0) {
		if (!sscanf(buffer, "p<,>ffffffi", X, Y, Z, rX, rY, rZ, type)) {
		    count++;
			machineobject[count] = CreateVendingMachine(X, Y, Z, rX, rY, rZ, type);
		}
	}
	fclose(File);
	return 1;
}
