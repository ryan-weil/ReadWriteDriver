#include "Halo.h"

#define halo3_magic_address 0x1AB9BA8
#define haloreach_magic_address 0x23EC960

typedef struct Map
{
	uintptr_t BattleRifle;
	uintptr_t SniperRifle;
	uintptr_t PlayerInformation;
};

Map halo3maps[24];
Map haloreachmaps[24];

void InitializeHalo3MapValues()
{
	// Assembly
	halo3maps[0].BattleRifle = 0x18CFBAB58;
	halo3maps[0].SniperRifle = 0x18CFBC9F8;
	halo3maps[0].PlayerInformation = 0x18CE5AA14;

	// Avalanche
	halo3maps[1].BattleRifle = 0x18C0E8468;
	halo3maps[1].SniperRifle = 0x18C0FCD78;
	halo3maps[1].PlayerInformation = 0x18BF37F10;

	// Blackout
	halo3maps[2].BattleRifle = 0x18D3E0E88;
	halo3maps[2].SniperRifle = 0x18D3E6B88;
	halo3maps[2].PlayerInformation = 0x18D29400C;

	// Citadel
	halo3maps[3].BattleRifle = 0x18D476908;
	halo3maps[3].SniperRifle = 0x18D472818;
	halo3maps[3].PlayerInformation = 0x18D331288;

	// Cold Storage
	halo3maps[4].BattleRifle = 0x18D1ED5B8;
	halo3maps[4].SniperRifle = 0x18D1F1578;
	halo3maps[4].PlayerInformation = 0x18D099F70;

	// Construct
	halo3maps[5].BattleRifle = 0x18CFCC4B8;
	halo3maps[5].SniperRifle = 0x18CFD0B38;
	halo3maps[5].PlayerInformation = 0x18CF8A81C;

	// Epitaph
	halo3maps[6].BattleRifle = 0x18D416EF8;
	halo3maps[6].SniperRifle = 0x18D41DB28;
	halo3maps[6].PlayerInformation = 0x18D2D316C;

	// Foundry
	halo3maps[7].BattleRifle = 0x18CAA9798;
	halo3maps[7].SniperRifle = 0x18CAADF38;
	halo3maps[7].PlayerInformation = 0x18C925E28;

	// Ghost Town
	halo3maps[8].BattleRifle = 0x18D16E628;
	halo3maps[8].SniperRifle = 0x18D174D98;
	halo3maps[8].PlayerInformation = 0x18D016194;

	// Guardian
	halo3maps[9].BattleRifle = 0x18D194C08;
	halo3maps[9].SniperRifle = 0x18D1A6FE8;
	halo3maps[9].PlayerInformation = 0x18D04DC18;

	// Heretic
	halo3maps[10].BattleRifle = 0x18D315A98;
	halo3maps[10].SniperRifle = 0x18D6D3EF8;
	halo3maps[10].PlayerInformation = 0x18D5916FC;

	// High Ground
	halo3maps[11].BattleRifle = 0x18C961D18;
	halo3maps[11].SniperRifle = 0x18C96CE18;
	halo3maps[11].PlayerInformation = 0x18C7F2860;

	// Isolation
	halo3maps[12].BattleRifle = 0x18CDFAE08;
	halo3maps[12].SniperRifle = 0x18CDFFEF8;
	halo3maps[12].PlayerInformation = 0x18CCABFC4;

	// Last Resort
	halo3maps[13].BattleRifle = 0x18CAFD708;
	halo3maps[13].SniperRifle = 0x18CB0BDB8;
	halo3maps[13].PlayerInformation = 0x18C9772F4;

	// Longshore
	halo3maps[14].BattleRifle = 0x18C866488;
	halo3maps[14].SniperRifle = 0x18C86A3B8;
	halo3maps[14].PlayerInformation = 0x18C6E1C04;

	// Narrows
	halo3maps[15].BattleRifle = 0x18CF726B8;
	halo3maps[15].SniperRifle = 0x18CF7C698;
	halo3maps[15].PlayerInformation = 0x18CE22018;

	// Orbital
	halo3maps[16].BattleRifle = 0x18CF0E328;
	halo3maps[16].SniperRifle = 0x18CF12B58;
	halo3maps[16].PlayerInformation = 0x18CD9E898;

	// Rats Nest
	halo3maps[17].BattleRifle = 0x18CB75B58;
	halo3maps[17].SniperRifle = 0x18CB79A88;
	halo3maps[17].PlayerInformation = 0x18C9C3A9C;

	// Sandbox
	halo3maps[18].BattleRifle = 0x18C7E10A8;
	halo3maps[18].SniperRifle = 0x18C7E4FD8;
	halo3maps[18].PlayerInformation = 0x18C660250;

	// Sandtrap
	halo3maps[19].BattleRifle = 0x18CADECB8;
	halo3maps[19].SniperRifle = 0x18CAE4028;
	halo3maps[19].PlayerInformation = 0x18C944740;

	// Snowbound
	halo3maps[20].BattleRifle = 0x18CC78908;
	halo3maps[20].SniperRifle = 0x18CC85818;
	halo3maps[20].PlayerInformation = 0x18CB11414;

	// Standoff
	halo3maps[21].BattleRifle = 0x18CA4B118;
	halo3maps[21].SniperRifle = 0x18CA4E678;
	halo3maps[21].PlayerInformation = 0x18C8D67F8;

	// The Pit
	halo3maps[22].BattleRifle = 0x18CD76C98;
	halo3maps[22].SniperRifle = 0x18CD7B438;
	halo3maps[22].PlayerInformation = 0x18CBEEA48;

	// Valhalla
	halo3maps[23].BattleRifle = 0x18CBCA8C8;
	halo3maps[23].SniperRifle = 0x18CBD59C8;
	halo3maps[23].PlayerInformation = 0x18CA8D468;
}

void InitializeHaloReachMapValues()
{
	// Sword Base
	haloreachmaps[0].BattleRifle = 0x1CD72CB20;
	haloreachmaps[0].SniperRifle = 0x1CD243214;
	haloreachmaps[0].PlayerInformation = 0x1CB8FA66C;

	// Power House
	haloreachmaps[1].BattleRifle = 0x1CC788ADC;
	haloreachmaps[1].SniperRifle = 0x1CC98ED60;
	haloreachmaps[1].PlayerInformation = 0x1CA703580;

	// Spire
	haloreachmaps[2].BattleRifle = 0x1CDC53BD8;
	haloreachmaps[2].SniperRifle = 0x1CD8519B0;
	haloreachmaps[2].PlayerInformation = 0x1CAF6A6F8;

	// Zealot
	haloreachmaps[3].BattleRifle = 0x1CD4A0AC4;
	haloreachmaps[3].SniperRifle = 0x1CD812860;
	haloreachmaps[3].PlayerInformation = 0x1CC75AF7C;

	// Countdown
	haloreachmaps[4].BattleRifle = 0x1CCCFD4E0;
	haloreachmaps[4].SniperRifle = 0x1CD6B132C;
	haloreachmaps[4].PlayerInformation = 0x1CB7AB850;

	// Boardwalk
	haloreachmaps[5].BattleRifle = 0x1CC59D730;
	haloreachmaps[5].SniperRifle = 0x1CC2EB9D8;
	haloreachmaps[5].PlayerInformation = 0x1CA1160F4;

	// Reflection
	haloreachmaps[6].BattleRifle = 0x1CC99D81C;
	haloreachmaps[6].SniperRifle = 0x1CCB90DD0;
	haloreachmaps[6].PlayerInformation = 0x1CB49652C;

	// Boneyard
	haloreachmaps[7].BattleRifle = 0x1CDA473F8;
	haloreachmaps[7].SniperRifle = 0x1CD61FFC0;
	haloreachmaps[7].PlayerInformation = 0x1CACFDB14;

	// Forge World
	haloreachmaps[8].BattleRifle = 0x1CC5756D8;
	haloreachmaps[8].SniperRifle = 0x1CC986900;
	haloreachmaps[8].PlayerInformation = 0x1C9A7F7F4;

	// Condemned
	haloreachmaps[9].BattleRifle = 0x1CD385250;
	haloreachmaps[9].SniperRifle = 0x1CD6ECDEC;
	haloreachmaps[9].PlayerInformation = 0x1CBFAAE50;
}

int Halo()
{
	InitializeHalo3MapValues();
	InitializeHaloReachMapValues();

	uintptr_t pid = GetPIDByName(L"MCC-Win64-Shipping.exe");
	uintptr_t halo3_base = GetModuleBase(pid, KeGetProcessPEB(pid), L"halo3.dll");
	uintptr_t haloreach_base = GetModuleBase(pid, KeGetProcessPEB(pid), L"haloreach.dll");
	int currentMap = 0;
	uintptr_t magicaddress;
	uintptr_t dllbase;
	Map* maps = 0;

	printf("Halo MCC PID: %d\n", pid);
	if (halo3_base != 0)
	{
		dllbase = halo3_base;
		magicaddress = halo3_magic_address;
		maps = halo3maps;
		printf("Halo 3 DLL: 0x%p\n", halo3_base);

		printf("Please input the current map number:\n");
		printf("0) Assembly\n");
		printf("1) Avalanche\n");
		printf("2) Blackout\n");
		printf("3) Citdael\n");
		printf("4) Cold Storage\n");
		printf("5) Construct\n");
		printf("6) Epitaph\n");
		printf("7) Foundry\n");
		printf("8) Ghost Town\n");
		printf("9) Guardian\n");
		printf("10) Heretic\n");
		printf("11) High Ground\n");
		printf("12) Isolation\n");
		printf("13) Last Resort\n");
		printf("14) Longshore\n");
		printf("15) Narrows\n");
		printf("16) Orbital\n");
		printf("17) Rat's Nest\n");
		printf("18) Sandbox\n");
		printf("19) Sandtrap\n");
		printf("20) Snowbound\n");
		printf("21) Standoff\n");
		printf("22) The Pit\n");
		printf("23) Valhalla\n");

		scanf("%d", &currentMap);
	}
	else if (haloreach_base != 0)
	{
		dllbase = haloreach_base;
		magicaddress = haloreach_magic_address;
		maps = haloreachmaps;
		printf("Halo Reach DLL: 0x%p\n", haloreach_base);

		printf("Please input the current map number:\n");
		printf("0) Sword Base\n");
		printf("1) Power House\n");
		printf("2) Spire\n");
		printf("3) Zealot\n");
		printf("4) Countdown\n");
		printf("5) Boardwalk\n");
		printf("6) Reflection\n");
		printf("7) Boneyard\n");
		printf("8) Forge World\n");
		printf("9) Condemned\n");

		scanf("%d", &currentMap);
	}
	
	uintptr_t curr_map = 0;
	KeReadVirtualMemory(pid, (unsigned char*)(dllbase + magicaddress), (uintptr_t)&curr_map, sizeof(uintptr_t));
	
	if (haloreach_base)
	{
		KeReadVirtualMemory(pid, (unsigned char*)(curr_map + 0x0000a000 + 0x000000a0), (uintptr_t)&curr_map, sizeof(uintptr_t));
		KeReadVirtualMemory(pid, (unsigned char*)(curr_map), (uintptr_t)&curr_map, sizeof(uintptr_t));
	}

	uintptr_t pWeapon = curr_map + maps[currentMap].BattleRifle;

	for (int i = 0; i < 2; i++)
	{
		uintptr_t pAutoAimAngle;
		uintptr_t pAutoAimRange;
		uintptr_t pAutoAimFalloffRange;
		uintptr_t pDeviationAngle;

		if (halo3_base)
		{
			pAutoAimAngle = pWeapon + 0x348;
			pAutoAimRange = pWeapon + 0x34C;
			pAutoAimFalloffRange = pWeapon + 0x350;
			pDeviationAngle = pWeapon + 0x360;
		}
		else if (haloreach_base)
		{
			pAutoAimAngle = pWeapon + 0x308;
			pAutoAimRange = pWeapon + 0x30C;
			pAutoAimFalloffRange = pWeapon + 0x310;
			pDeviationAngle = pWeapon + 0x328;
		}
		

		float angle = 1.553;
		float range = 120;

		KeWriteVirtualMemory(pid, (unsigned char*)&angle, pAutoAimAngle, sizeof(float));
		KeWriteVirtualMemory(pid, (unsigned char*)&range, pAutoAimRange, sizeof(float));
		KeWriteVirtualMemory(pid, (unsigned char*)&range, pAutoAimFalloffRange, sizeof(float));
		KeWriteVirtualMemory(pid, (unsigned char*)&angle, pDeviationAngle, sizeof(float));

		pWeapon = curr_map + maps[currentMap].SniperRifle;
	}

	float RunForward = 4.5;
	float RunBackward = 4.0;
	float RunSideways = 4.0;
	float RunAcceleration = 100.0;
	uintptr_t pPlayerInformation = curr_map + maps[currentMap].PlayerInformation;
	uintptr_t pRunForward =  pPlayerInformation + 0x4;
	uintptr_t pRunBackward = pPlayerInformation + 0x8;
	uintptr_t pRunSideways = pPlayerInformation + 0xC;
	uintptr_t pForwardAcceleration = pPlayerInformation + 0x10;
	KeWriteVirtualMemory(pid, (unsigned char*)&RunForward, pRunForward, sizeof(float));
	KeWriteVirtualMemory(pid, (unsigned char*)&RunBackward, pRunBackward, sizeof(float));
	KeWriteVirtualMemory(pid, (unsigned char*)&RunSideways, pRunSideways, sizeof(float));
	KeWriteVirtualMemory(pid, (unsigned char*)&RunAcceleration, pForwardAcceleration, sizeof(float));

	return 0;
}