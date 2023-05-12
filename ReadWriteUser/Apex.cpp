#include "Apex.h"

struct GlowMode
{
    int8_t GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};

void EnableGlow(uintptr_t pid, uint64_t Entity, float R, float G, float B)
{
    int a = 1;
    int b = 2;
    GlowMode c = { 101, 101, 46, 90 };

    KeWriteVirtualMemory(pid, (unsigned char*)&a, Entity + 0x3C8, sizeof(int));
    KeWriteVirtualMemory(pid, (unsigned char*)&b, Entity + 0x3D0, sizeof(int));
    KeWriteVirtualMemory(pid, (unsigned char*)&c, Entity + 0x2C4, sizeof(GlowMode));

    KeWriteVirtualMemory(pid, (unsigned char*)&R, Entity + 0x1D0, sizeof(float));
    KeWriteVirtualMemory(pid, (unsigned char*)&G, Entity + 0x1D4, sizeof(float));
    KeWriteVirtualMemory(pid, (unsigned char*)&B, Entity + 0x1D8, sizeof(float));
}

uintptr_t GetEntityById(uintptr_t pid, int Ent, uintptr_t Base)
{
    uintptr_t EntityList = Base + 0x19126a8; // Obtaining EntityList pointer
    uintptr_t BaseEntity = 0;
    KeReadVirtualMemory(pid, (unsigned char*)EntityList, (uintptr_t)&BaseEntity, sizeof(uintptr_t)); // Getting the BaseEntity
    if (!BaseEntity) // Checking if there even is a BaseEntity if not than it makes no sense to try and read the Entitylist anyways
        return NULL;

    uintptr_t Entity;
    KeReadVirtualMemory(pid, (unsigned char*)(EntityList + ((uint64_t)Ent << 5)), (uintptr_t)&Entity, sizeof(uintptr_t));
    return Entity; // Getting the Entity at the Given ID
}

int Apex()
{
    uintptr_t pid = GetPIDByName(L"r5apex.exe");
    uintptr_t apex_base = GetModuleBase(pid, KeGetProcessPEB(pid), L"r5apex.exe");

    while (true)
    {
        for (int i = 0; i < 100; i++) { // Enumerating through the first 100 Entities in the List because thats where all players are stored
            uintptr_t Entity = GetEntityById(pid, i, apex_base); // Getting the Entity

            if (Entity == 0) // Checking if its valid
                continue;

            char playa[7] = { };
            KeReadVirtualMemory(pid, (unsigned char*)(Entity + 0x589), (uintptr_t)&playa, 7);

            if (!strcmp(playa, "player")) //Comparing if the Identifier states that the Entity is indeed a Player
                EnableGlow(pid, Entity, 120, 0, 255);	// Enabling the Glow for that Entity since it is a Player
        }
    }
    return 0;
}