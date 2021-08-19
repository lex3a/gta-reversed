#include "StdInc.h"

#include "CTaskSimpleJetPack.h"

void (*(&CCheat::m_aCheatFunctions)[TOTAL_CHEATS])() = *reinterpret_cast<void (*(*)[TOTAL_CHEATS])()>(0x8A5B58);
int (&CCheat::m_aCheatHashKeys)[TOTAL_CHEATS] = *reinterpret_cast<int (*)[TOTAL_CHEATS]>(0x8A5CC8);
char (&CCheat::m_CheatString)[CHEAT_STRING_SIZE] = *reinterpret_cast<char (*)[CHEAT_STRING_SIZE]>(0x969110);
bool (&CCheat::m_aCheatsActive)[TOTAL_CHEATS] = *reinterpret_cast<bool (*)[TOTAL_CHEATS]>(0x969130);
bool& CCheat::m_bHasPlayerCheated = *reinterpret_cast<bool*>(0x96918C);

// NOTSA
std::vector<Cheat> cheats = {
        { 0x4385b0,  CCheat::WeaponCheat1, "WeaponCheat1", 0xde4b237d, CHEAT_WEAPON_SET1 },
        { 0x438890,  CCheat::WeaponCheat2, "WeaponCheat2", 0xb22a28d1, CHEAT_WEAPON_SET2 },
        { 0x438b30,  CCheat::WeaponCheat3, "WeaponCheat3", 0x5a783fae, CHEAT_WEAPON_SET3 },
        { 0x438e40,  CCheat::MoneyArmourHealthCheat, "MoneyArmourHealthCheat", 0xeeccea2b, CHEAT_HEALTH_ARMOR_250K },
        { 0x438e90,  CCheat::WantedLevelUpCheat, "WantedLevelUpCheat", 0x42af1e28, CHEAT_WANTED_LEVEL_2STARS },
        { 0x438f20,  CCheat::WantedLevelDownCheat, "WantedLevelDownCheat", 0x555fc201, CHEAT_CLEAR_WANTED_LEVEL },
        { 0x438f40,  CCheat::SunnyWeatherCheat, "SunnyWeatherCheat", 0x2a845345, CHEAT_SUNNY_WEATHER },
        { 0x438f50,  CCheat::ExtraSunnyWeatherCheat, "ExtraSunnyWeatherCheat", 0xe1ef01ea, CHEAT_VERY_SUNNY_WEATHER },
        { 0x438f60,  CCheat::CloudyWeatherCheat, "CloudyWeatherCheat", 0x771b83fc, CHEAT_OVERCAST_WEATHER },
        { 0x438f70,  CCheat::RainyWeatherCheat, "RainyWeatherCheat", 0x5bf12848, CHEAT_RAINY_WEATHER },
        { 0x438f80,  CCheat::FoggyWeatherCheat, "FoggyWeatherCheat", 0x44453a17, CHEAT_FOGGY_WEATHER },
        { 0x0, nullptr, "", 0xfcff1d08, CHEAT_FASTER_CLOCK },
        { 0x438f90,  CCheat::FastTimeCheat, "FastTimeCheat", 0xb69e8532, CHEAT_FASTER_GAMEPLAY },
        { 0x438fc0,  CCheat::SlowTimeCheat, "SlowTimeCheat", 0x8b828076, CHEAT_SLOWER_GAMEPLAY },
        { 0x439b20,  CCheat::MayhemCheat, "MayhemCheat", 0xdd6ed9e9, CHEAT_PEDS_ATTACK_OTHER_WITH_GOLFCLUB },
        { 0x439c70,  CCheat::EverybodyAttacksPlayerCheat, "EverybodyAttacksPlayerCheat", 0xa290fd8c, CHEAT_HAVE_ABOUNTY_ON_YOUR_HEAD },
        { 0x0, nullptr, "", 0x3484b5a7, CHEAT_EVERYONE_ARMED },
        { 0x43a4a0,  CCheat::TankCheat, "TankCheat", 0x43db914e, CHEAT_SPAWN_RHINO },
        { 0x43a4b0,  CCheat::StockCarCheat, "StockCarCheat", 0xdbc0dd65, CHEAT_SPAWN_BLOODRINGBANGER },
        { 0x43a4c0,  CCheat::StockCar2Cheat, "StockCar2Cheat", 0x00000000, CHEAT_SPAWN_RANCHER },
        { 0x43a4d0,  CCheat::StockCar3Cheat, "StockCar3Cheat", 0xd08a30fe, CHEAT_SPAWN_HOTRINGA },
        { 0x43a4e0,  CCheat::StockCar4Cheat, "StockCar4Cheat", 0x37bf1b4e, CHEAT_SPAWN_HOTRINGB },
        { 0x43a4f0,  CCheat::HearseCheat, "HearseCheat", 0xb5d40866, CHEAT_SPAWN_ROMERO },
        { 0x43a500,  CCheat::LovefistCheat, "LovefistCheat", 0xe63b0d99, CHEAT_SPAWN_STRETCH },
        { 0x43a510,  CCheat::TrashmasterCheat, "TrashmasterCheat", 0x675b8945, CHEAT_SPAWN_TRASHMASTER },
        { 0x43a520,  CCheat::GolfcartCheat, "GolfcartCheat", 0x4987d5ee, CHEAT_SPAWN_CADDY },
        { 0x439d80,  CCheat::BlowUpCarsCheat, "BlowUpCarsCheat", 0x2e8f84e8, CHEAT_BLOW_UP_ALL_CARS },
        { 0x0, nullptr, "", 0x1a9aa3d6, CHEAT_INVISIBLE_CAR },
        { 0x0, nullptr, "", 0xe842f3bc, CHEAT_PERFECT_HANDLING },
        { 0x438ff0,  CCheat::SuicideCheat, "SuicideCheat", 0x0d5c6a4e, CHEAT_SUICIDE },
        { 0x0, nullptr, "", 0x74d4fcb1, CHEAT_BGREEN_LIGHTS_CHEAT },
        { 0x0, nullptr, "", CHEAT_AGGRESSIVE_DRIVERS },
        { 0x4390d0,  CCheat::PinkCarsCheat, "PinkCarsCheat", 0x66516ebc, CHEAT_PINK_TRAFFIC },
        { 0x4390f0,  CCheat::BlackCarsCheat, "BlackCarsCheat", 0x4b137e45, CHEAT_BLACK_TRAFFIC },
        { 0x0, nullptr, "", 0x00000000, CHEAT_CARS_ON_WATER },
        { 0x0, nullptr, "", 0x78520e33, CHEAT_BOATS_FLY },
        { 0x439110,  CCheat::FatCheat, "FatCheat", 0x3a577325, CHEAT_FAT_PLAYER },
        { 0x439150,  CCheat::MuscleCheat, "MuscleCheat", 0xd4966d59, CHEAT_MAX_MUSCLE },
        { 0x439190,  CCheat::SkinnyCheat, "SkinnyCheat", 0x5fd1b49d, CHEAT_SKINNY_PLAYER },
        { 0x4391d0,  CCheat::ElvisLivesCheat, "ElvisLivesCheat", 0xa7613f99, CHEAT_ELVIS_IS_EVERYWHERE },
        { 0x439dd0,  CCheat::VillagePeopleCheat, "VillagePeopleCheat", 0x1792d871, CHEAT_PEDS_ATTACK_YOU_WITH_ROCKETS },
        { 0x439230,  CCheat::BeachPartyCheat, "BeachPartyCheat", 0xcbc579df, CHEAT_BEACH_PARTY },
        { 0x439360,  CCheat::GangsCheat, "GangsCheat", 0x4fedccff, CHEAT_GANGMEMBERS_EVERYWHERE },
        { 0x4393d0,  CCheat::GangLandCheat, "GangLandCheat", CHEAT_GANGS_CONTROLS_THE_STREETS },
        { 0x439e50,  CCheat::NinjaCheat, "NinjaCheat", 0x44b34866, CHEAT_NINJA_THEME },
        { 0x4393f0,  CCheat::LoveConquersAllCheat, "LoveConquersAllCheat", 0x2ef877db, CHEAT_SLUT_MAGNET },
        { 0x4394b0,  CCheat::AllCarsAreShitCheat, "AllCarsAreShitCheat", 0x2781e797, CHEAT_CHEAP_TRAFFIC },
        { 0x4394e0,  CCheat::AllCarsAreGreatCheat, "AllCarsAreGreatCheat", 0x2bc1a045, CHEAT_FAST_TRAFFIC },
        { 0x0, nullptr, "", 0xb2afe368, CHEAT_CARS_FLY },
        { 0x0, nullptr, "", 0xfa8dd45b, CHEAT_HUGE_BUNNY_HOP },
        { 0x43a530,  CCheat::FlyboyCheat, "FlyboyCheat", 0x8ded75bd, CHEAT_SPAWN_HYDRA },
        { 0x43a540,  CCheat::VortexCheat, "VortexCheat", 0x1a5526bc, CHEAT_SPAWN_VORTEX },
        { 0x0, nullptr, "", 0xa48a770b, CHEAT_SMASH_N_BOOM },
        { 0x0, nullptr, "", 0xb07d3b32, CHEAT_ALL_CARS_HAVE_NITRO },
        { 0x0, nullptr, "", 0x80c1e54b, CHEAT_CARS_FLOAT_AWAY_WHEN_HIT },
        { 0x439510,  CCheat::MidnightCheat, "MidnightCheat", CHEAT_ALWAYS_MIDNIGHT },
        { 0x439540,  CCheat::DuskCheat, "DuskCheat", 0x5dad0087, CHEAT_STOP_GAME_CLOCK_ORANGE_SKY },
        { 0x439570,  CCheat::StormCheat, "StormCheat", 0x7f80b950, CHEAT_THUNDER_STORM },
        { 0x439590,  CCheat::SandstormCheat, "SandstormCheat", 0x6c0fa650, CHEAT_SAND_STORM },
        { 0x4395a0,  CCheat::PredatorCheat, "PredatorCheat", 0xf46f2fa4, CHEAT_UNUSED },
        { 0x0, nullptr, "", 0x70164385, CHEAT_MEGAJUMP },
        { 0x0, nullptr, "", 0x00000000, CHEAT_INFINITE_HEALTH },
        { 0x0, nullptr, "", 0x885d0b50, CHEAT_INFINITE_OXYGEN },
        { 0x4395b0,  CCheat::ParachuteCheat, "ParachuteCheat", 0x151bdcb3, CHEAT_GET_PARACHUTE },
        { 0x439600,  CCheat::JetpackCheat, "JetpackCheat", 0xadfa640a, CHEAT_GET_JETPACK },
        { 0x4396c0,  CCheat::NotWantedCheat, "NotWantedCheat", 0xe57f96ce, CHEAT_I_DO_AS_I_PLEASE },
        { 0x4396f0,  CCheat::WantedCheat, "WantedCheat", 0x040cf761, CHEAT_SIX_WANTED_STARS },
        { 0x0, nullptr, "", 0xe1b33eb9, CHEAT_MEGA_PUNCH },
        { 0x0, nullptr, "", 0xfeda77f7, CHEAT_NEVER_GET_HUNGRY },
        { 0x439710,  CCheat::RiotCheat, "RiotCheat", 0x8ca870dd, CHEAT_RIOT_MODE },
        { 0x439720,  CCheat::FunhouseCheat, "FunhouseCheat", 0x9a629401, CHEAT_FUNHOUSE_THEME },
        { 0x439880,  CCheat::AdrenalineCheat, "AdrenalineCheat", 0xf53ef5a5, CHEAT_ADRENALINE_MODE },
        { 0x0, nullptr, "", 0xf2aa0c1d, CHEAT_INFINITE_AMMO },
        { 0x4398d0,  CCheat::DrivebyCheat, "DrivebyCheat", 0xf36345a8, CHEAT_WEAPON_AIMING_WHILE_DRIVING },
        { 0x0, nullptr, "", 0x8990d5e1, CHEAT_REDUCED_TRAFFIC },
        { 0x439f60,  CCheat::CountrysideInvasionCheat, "CountrysideInvasionCheat", 0xb7013b1b, CHEAT_COUNTRY_TRAFFIC },
        { 0x0, nullptr, "", 0xcaec94ee, CHEAT_WANNA_BE_IN_MY_GANG },
        { 0x0, nullptr, "", 0x31f0c3cc, CHEAT_NO_ONE_CAN_STOP_US },
        { 0x0, nullptr, "", 0xb3b3e72a, CHEAT_ROCKET_MAYHEM },
        { 0x0, nullptr, "", 0xc25cdbff, CHEAT_MAX_RESPECT },
        { 0x0, nullptr, "", 0xd5cf4eff, CHEAT_MAX_SEX_APPEAL },
        { 0x439930,  CCheat::StaminaCheat, "StaminaCheat", 0x680416b1, CHEAT_MAX_STAMINA },
        { 0x439940,  CCheat::WeaponSkillsCheat, "WeaponSkillsCheat", 0xcf5fda18, CHEAT_HITMAN_LEVEL_FOR_ALL_WEAPONS },
        { 0x4399d0,  CCheat::VehicleSkillsCheat, "VehicleSkillsCheat", 0xf01286e9, CHEAT_MAX_DRIVING_SKILLS },
        { 0x43a550,  CCheat::ApacheCheat, "ApacheCheat", 0xa841cc0a, CHEAT_SPAWN_HUNTER },
        { 0x43a560,  CCheat::QuadCheat, "QuadCheat", 0x31ea09cf, CHEAT_SPAWN_QUAD },
        //{ 0x43a570,  CCheat::TankerCheat, "TankerCheat", 0xe958788a, CHEAT_SPAWN_TANKER_TRUCK },
        { 0x43a660,  CCheat::DozerCheat, "DozerCheat", 0x02c83a7c, CHEAT_SPAWN_DOZER },
        { 0x43a670,  CCheat::StuntPlaneCheat, "StuntPlaneCheat", 0xe49c3ed4, CHEAT_SPAWN_STUNT_PLANE },
        { 0x43a680,  CCheat::MonsterTruckCheat, "MonsterTruckCheat", 0x171ba8cc, CHEAT_SPAWN_MONSTER },
        { 0x0, nullptr, "", 0x86988dae, CHEAT_PROSTITUTES_PAY_YOU },
        { 0x0, nullptr, "", 0x2bdd2fa1, CHEAT_ALL_TAXIS_NITRO },
};

void CCheat::InjectHooks() {
    ReversibleHooks::Install("CCheat", "AddToCheatString", 0x438480, &CCheat::AddToCheatString);
    ReversibleHooks::Install("CCheat", "HandleSpecialCheats", 0x439A10, &CCheat::HandleSpecialCheats);
    ReversibleHooks::Install("CCheat", "DoCheats", 0x439AF0, &CCheat::DoCheats);
    ReversibleHooks::Install("CCheat", "ResetCheats", 0x438450, &CCheat::ResetCheats);
    ReversibleHooks::Install("CCheat", "IsZoneStreamingAllowed", 0x407410, &CCheat::IsZoneStreamingAllowed);
    ReversibleHooks::Install("CCheat", "EnableLegimateCheat", 0x438370, &CCheat::EnableLegitimateCheat);

    for (auto& cheat: cheats) {
        if (cheat.installAddress == 0x0) {
            continue;
        }

        ReversibleHooks::Install("CCheat", cheat.methodName, cheat.installAddress, &cheat.method);

        for (auto& cheatFunc: CCheat::m_aCheatFunctions) {
            if (reinterpret_cast<unsigned long>(cheatFunc) == cheat.installAddress) {
                cheatFunc = static_cast<void (*)(void)>(cheat.method);
            }
        }
    }
}

// 0x438480
void CCheat::AddToCheatString(char LastPressedKey) {
    if (CCutsceneMgr::ms_running) {
        return;
    }

    for (auto i = CHEAT_STRING_SIZE - 1 - 1; i >= 1; --i) {
        m_CheatString[i] = m_CheatString[i - 1];
    }
    m_CheatString[0] = LastPressedKey;
    m_CheatString[CHEAT_STRING_SIZE - 1] = 0;

    unsigned int strLen = strlen(m_CheatString);
    if (strLen < CHEAT_MIN_HASH_SIZE) {
        return;
    }

    int hashIndex;
    int cheatStringSize = CHEAT_MIN_HASH_SIZE;
    for (auto i = CHEAT_MIN_HASH_SIZE; i < CHEAT_STRING_SIZE; i++) {
        unsigned int hash = CKeyGen::GetKey(m_CheatString, cheatStringSize);
        cheatStringSize++;

        hashIndex = -1;
        for (int j = 0; j < TOTAL_CHEATS; ++j) {
            if (m_aCheatHashKeys[j] != hash) {
                continue;
            }
            hashIndex = j;
        }
        if (hashIndex == -1) {
            continue;
        }

        if (m_aCheatsActive[hashIndex]) {
            // deactivated
            CHud::SetHelpMessage(TheText.Get((char*)"CHEAT8"), true, false, false);
        } else {
            // activated
            CHud::SetHelpMessage(TheText.Get((char*)"CHEAT1"), true, false, false);
        }

        CStats::IncrementStat(STAT_TIMES_CHEATED, 1.0f);

        auto cheatFunc = m_aCheatFunctions[hashIndex];
        m_bHasPlayerCheated = true;
        if (cheatFunc) {
            cheatFunc();
        } else {
            m_aCheatsActive[hashIndex] ^= true;
        }
        m_CheatString[0] = '\0';
        return;
    }
}

// 0x438450
void CCheat::ResetCheats() {
    memset(&m_aCheatsActive, 0, sizeof(m_aCheatsActive));
    CWeather::ReleaseWeather();
    CTimer::ms_fTimeScale = 1.0f;
    m_CheatString[0] = '\0';
    m_bHasPlayerCheated = false;
}

// 0x439AF0
void CCheat::DoCheats() {
    for (short i = 0; i < 256; ++i)
        if (CPad::NewKeyState.standardKeys[i])
            if (!CPad::OldKeyState.standardKeys[i])
                AddToCheatString(i);
}

// 0x439880
void CCheat::AdrenalineCheat() {
    CPlayerPedData* playerData = FindPlayerPed(-1)->m_pPlayerData;

    m_aCheatsActive[CHEAT_ADRENALINE_MODE] ^= true;
    if (m_aCheatsActive[CHEAT_ADRENALINE_MODE]) {
        playerData->m_bAdrenaline = false;
    } else {
        CPickups::GivePlayerGoodiesWithPickUpMI(MODEL_ADRENALINE, 0);
    }
}

// 0x4394e0
void CCheat::AllCarsAreGreatCheat() {
    m_aCheatsActive[CHEAT_FAST_TRAFFIC] ^= true;
    if (m_aCheatsActive[CHEAT_FAST_TRAFFIC]) {
        HandleSpecialCheats(CHEAT_FAST_TRAFFIC);
        CStreaming::ReclassifyLoadedCars();
    }
}

// 0x4394b0
void CCheat::AllCarsAreShitCheat() {
    m_aCheatsActive[CHEAT_CHEAP_TRAFFIC] ^= true;
    if (m_aCheatsActive[CHEAT_CHEAP_TRAFFIC]) {
        HandleSpecialCheats(CHEAT_CHEAP_TRAFFIC);
        CStreaming::ReclassifyLoadedCars();
    }
}

// 0x43a550
void CCheat::ApacheCheat() {
    VehicleCheat(MODEL_HUNTER);
}

// 0x439230
void CCheat::BeachPartyCheat() {
    m_aCheatsActive[CHEAT_BEACH_PARTY] ^= true;
    if (m_aCheatsActive[CHEAT_BEACH_PARTY]) {
        int peds[8] = {
            MODEL_BMYBE,
            MODEL_HMYBE,
            MODEL_WFYBE,
            MODEL_BFYBE,
            MODEL_HFYBE,
            -2,
            -2,
            -2,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);

        CPlayerPed* player = FindPlayerPed(-1);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("torso", nullptr, CLOTHES_TEXTURE_TORSO);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("shortskhaki", "shorts", CLOTHES_TEXTURE_LEGS);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("flipflop", "flipflop", CLOTHES_TEXTURE_SHOES);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("glasses04dark", "glasses04", CLOTHES_TEXTURE_GLASSES);

        if (player->m_nPedState != PEDSTATE_DRIVING) {
            CClothes::RebuildPlayer(player, false);
        }

        CWeather::ForceWeatherNow(WEATHER_EXTRASUNNY_LA);

        HandleSpecialCheats(CHEAT_BEACH_PARTY);

        CStreaming::ReclassifyLoadedCars();
    }
}

// 0x4390f0
void CCheat::BlackCarsCheat() {
    m_aCheatsActive[CHEAT_BLACK_TRAFFIC] ^= true;
    if (m_aCheatsActive[CHEAT_BLACK_TRAFFIC]) {
        m_aCheatsActive[CHEAT_PINK_TRAFFIC] = false;
    }
}

// 0x439d80
void CCheat::BlowUpCarsCheat() {
    for (int index = 0; index < CPools::ms_pVehiclePool->m_nSize; index++) {
        CVehicle* vehicle = CPools::ms_pVehiclePool->GetAt(index);
        if (vehicle) {
            vehicle->BlowUpCar(nullptr, false);
        }
    }
}

// 0x438f60
void CCheat::CloudyWeatherCheat() {
    CWeather::ForceWeatherNow(WEATHER_CLOUDY_LA);
}

// 0x439f60
void CCheat::CountrysideInvasionCheat() {
    m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC] ^= true;
    if (m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC]) {
        int peds[8] = {
            MODEL_CWFOFR,
            MODEL_CWFOHB,
            MODEL_CWFYFR1,
            MODEL_CWFYHB,
            MODEL_CWMOFR,
            MODEL_CWMOHB1,
            MODEL_CWMOHB2,
            MODEL_CWMYFR,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);

        CPlayerPed *player = FindPlayerPed(-1);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("timberfawn", "bask1", CLOTHES_TEXTURE_SHOES);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("captruck", "captruck", CLOTHES_TEXTURE_HATS);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("countrytr", "countrytr", CLOTHES_TEXTURE_SPECIAL);

        if (player->m_nPedState != PEDSTATE_DRIVING) {
            CClothes::RebuildPlayer(player, false);
        }
        if (m_aCheatsActive[CHEAT_BEACH_PARTY]) {
            BeachPartyCheat();
        }
        if (m_aCheatsActive[CHEAT_CHEAP_TRAFFIC]) {
            m_aCheatsActive[CHEAT_CHEAP_TRAFFIC] = false;
        }
        if (m_aCheatsActive[CHEAT_FAST_TRAFFIC]) {
            m_aCheatsActive[CHEAT_FAST_TRAFFIC] = false;
        }
        if (m_aCheatsActive[CHEAT_FUNHOUSE_THEME]) {
            FunhouseCheat();
        }

        CStreaming::ReclassifyLoadedCars();
    }
}

// 0x43a660
void CCheat::DozerCheat() {
    VehicleCheat(MODEL_DOZER);
}

// 0x4398d0
void CCheat::DrivebyCheat() {
    m_aCheatsActive[CHEAT_WEAPON_AIMING_WHILE_DRIVING] ^= true;

    CPlayerPed *player = FindPlayerPed(-1);
    if (m_aCheatsActive[CHEAT_WEAPON_AIMING_WHILE_DRIVING] && player->m_aWeapons[WEAPON_KNIFE].m_nType == WEAPON_UNARMED) {
        player->GiveDelayedWeapon(WEAPON_MICRO_UZI, 150);
        player->SetCurrentWeapon(WEAPON_MICRO_UZI);
    }
}

// 0x439540
void CCheat::DuskCheat() {
    m_aCheatsActive[CHEAT_STOP_GAME_CLOCK_ORANGE_SKY] ^= true;
    if (!m_aCheatsActive[CHEAT_STOP_GAME_CLOCK_ORANGE_SKY]) {
        CClock::ms_nGameClockHours = 21;
        CClock::ms_nGameClockMinutes = 0;
        CClock::ms_nGameClockSeconds = 0;
    }
}

// 0x4391d0
void CCheat::ElvisLivesCheat() {
    m_aCheatsActive[CHEAT_ELVIS_IS_EVERYWHERE] ^= true;
    if (m_aCheatsActive[CHEAT_ELVIS_IS_EVERYWHERE]) {
        int peds[8] = {
            MODEL_VHMYELV,
            MODEL_VBMYELV,
            MODEL_VIMYELV,
            -2,
            -2,
            -2,
            -2,
            -2,
        };

        CStreaming::StreamPedsIntoRandomSlots(peds);
    }
}

// 0x439c70
void CCheat::EverybodyAttacksPlayerCheat() {
    m_aCheatsActive[CHEAT_HAVE_ABOUNTY_ON_YOUR_HEAD] ^= true;
    if (m_aCheatsActive[CHEAT_HAVE_ABOUNTY_ON_YOUR_HEAD]) {
        auto player = FindPlayerPed(-1);
        for (auto i = 0; i < CPools::ms_pPedPool->m_nSize; i++) {
            auto ped = CPools::ms_pPedPool->GetAt(i);
            if (!ped || ped->IsPlayer())
                continue;

            ped->m_acquaintance.SetAsAcquaintance(4, CPedType::GetPedFlag(PED_TYPE_PLAYER1));

            CEventAcquaintancePedHate event(player);
            event.m_taskId = TASK_COMPLEX_KILL_PED_ON_FOOT;
            ped->m_pIntelligence->m_eventGroup.Add(&event, false);
        }
    }
}

// 0x438f50
void CCheat::ExtraSunnyWeatherCheat() {
    CWeather::ForceWeatherNow(WEATHER_EXTRASUNNY_LA);
}

// 0x438f90
void CCheat::FastTimeCheat() {
    if (CTimer::ms_fTimeScale < 4.0f) {
        CTimer::ms_fTimeScale += CTimer::ms_fTimeScale;
    }
}

// 0x439110
void CCheat::FatCheat() {
    CStats::SetStatValue(STAT_FAT, 1000.0f);

    CPlayerPed *player = FindPlayerPed(-1);
    if (player->m_nPedState != PEDSTATE_DRIVING) {
        CClothes::RebuildPlayer(player, false);
    }
}

// 0x43a530
void CCheat::FlyboyCheat() {
    VehicleCheat(MODEL_HYDRA);
}

// 0x438f80
void CCheat::FoggyWeatherCheat() {
    CWeather::ForceWeatherNow(WEATHER_FOGGY_SF);
}

// 0x439720
void CCheat::FunhouseCheat() {
    m_aCheatsActive[CHEAT_FUNHOUSE_THEME] ^= true;
    if (m_aCheatsActive[CHEAT_FUNHOUSE_THEME]) {
        CPostEffects::m_bHeatHazeFX = false;
    } else {
        int peds[8] = {
            MODEL_WMYBELL,
            MODEL_WFYBURG,
            MODEL_WMOICE,
            -2,
            -2,
            -2,
            -2,
            -2,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);

        CPlayerPed *player = FindPlayerPed(-1);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("torso", "torso", CLOTHES_TEXTURE_TORSO);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("legsheart", "legs", CLOTHES_TEXTURE_LEGS);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("timberhike", "bask1", CLOTHES_TEXTURE_SHOES);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("groucho", "grouchos", CLOTHES_TEXTURE_GLASSES);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("hairpink", "head", CLOTHES_TEXTURE_HEAD);

        if (player->m_nPedState != PEDSTATE_DRIVING) {
            CClothes::RebuildPlayer(player, false);
        }

        HandleSpecialCheats(CHEAT_FUNHOUSE_THEME);

        CStreaming::ReclassifyLoadedCars();

        CWeather::ForceWeatherNow(WEATHER_EXTRASUNNY_LA);

        CPostEffects::m_bHeatHazeFX = true;
    }
}

// 0x4393d0
void CCheat::GangLandCheat() {
    m_aCheatsActive[CHEAT_GANGS_CONTROLS_THE_STREETS] ^= true;
    CPopulation::m_bOnlyCreateRandomGangMembers = m_aCheatsActive[CHEAT_GANGS_CONTROLS_THE_STREETS];
}

// 0x439360
void CCheat::GangsCheat() {
    m_aCheatsActive[CHEAT_GANGMEMBERS_EVERYWHERE] ^= true;
    if (m_aCheatsActive[CHEAT_GANGMEMBERS_EVERYWHERE]) {
        int peds[8] = {
            MODEL_BALLAS1,
            MODEL_BALLAS2,
            MODEL_BALLAS3,
            MODEL_FAM1,
            MODEL_FAM2,
            MODEL_LSV1,
            MODEL_LSV2,
            MODEL_LSV3,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
    }
}

// 0x43a520
void CCheat::GolfcartCheat() {
    VehicleCheat(MODEL_CADDY);
}

// Handles BeachParty, Funhouse, AllCarsAreGreat, AllCarsAreCheap cheats toggling
// 0x439A10
void CCheat::HandleSpecialCheats(eCheats cheatID) {
    if (m_aCheatsActive[CHEAT_BEACH_PARTY] && cheatID != CHEAT_BEACH_PARTY) {
        BeachPartyCheat();
    }
    if (m_aCheatsActive[CHEAT_CHEAP_TRAFFIC] && cheatID != CHEAT_CHEAP_TRAFFIC) {
        m_aCheatsActive[CHEAT_CHEAP_TRAFFIC] = false;
    }
    if (m_aCheatsActive[CHEAT_FAST_TRAFFIC] && cheatID != CHEAT_FAST_TRAFFIC) {
        m_aCheatsActive[CHEAT_FAST_TRAFFIC] = false;
    }
    if (m_aCheatsActive[CHEAT_FUNHOUSE_THEME] && cheatID != CHEAT_FUNHOUSE_THEME) {
        FunhouseCheat();
    }
    if (m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC]) {
        if (cheatID != CHEAT_COUNTRY_TRAFFIC) {
            CountrysideInvasionCheat();
        }
    }
}

// 0x438D60
void CCheat::HealthCheat() {
    CPlayerPed* player = FindPlayerPed(-1);
    CPlayerInfo* playerInfo = player->GetPlayerInfoForThisPlayerPed();
    player->m_fHealth = playerInfo->m_nMaxHealth;

    CVehicle *vehicle = FindPlayerVehicle(-1, false);
    if (!vehicle) {
        return;
    }

    vehicle->m_fHealth = 1000.0f;
    if (vehicle->m_vehicleType == VEHICLE_BIKE) {
        auto* bike = static_cast<CBike*>(vehicle);
        bike->field_7BC = 0;
        bike->Fix();
        bike->m_apCollidedEntities[5] = nullptr;
    } else {
        vehicle->Fix();
    }
}

// 0x43a4f0
void CCheat::HearseCheat() {
    VehicleCheat(MODEL_ROMERO);
}

// 0x439600
void CCheat::JetpackCheat() {
    auto player = FindPlayerPed();
    CTaskSimpleJetPack* task = player->m_pIntelligence->GetTaskJetPack();
    if (!task) {
        auto jetpackTask = new CTaskSimpleJetPack(nullptr, 10, 0, nullptr);
        CEventScriptCommand event(3, jetpackTask, false);
        player->m_pIntelligence->m_eventGroup.Add(&event, false);
    }
}

// 0x4393f0
void CCheat::LoveConquersAllCheat() {
    m_aCheatsActive[CHEAT_SLUT_MAGNET] ^= true;
    if (m_aCheatsActive[CHEAT_SLUT_MAGNET]) {
        int peds[8] = {
            MODEL_BMYPIMP,
            MODEL_BFYPRO,
            MODEL_HFYPRO,
            MODEL_SWFOPRO,
            MODEL_SBFYPRO,
            MODEL_VWFYPRO,
            MODEL_VHFYPRO,
            -2,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);

        CPlayerPed *player = FindPlayerPed(-1);
        player->m_pPlayerData->m_pPedClothesDesc->SetTextureAndModel("gimpleg", "gimpleg", CLOTHES_TEXTURE_SPECIAL);
        if (player->m_nPedState != PEDSTATE_DRIVING) {
            CClothes::RebuildPlayer(player, false);
        }
    }
}

// 0x43a500
void CCheat::LovefistCheat() {
    VehicleCheat(MODEL_STRETCH);
}

// 0x439B20
void CCheat::MayhemCheat() {
    m_aCheatsActive[CHEAT_PEDS_ATTACK_OTHER_WITH_GOLFCLUB] ^= true;
    if (m_aCheatsActive[CHEAT_PEDS_ATTACK_OTHER_WITH_GOLFCLUB]) {
        for (unsigned int pedType = PED_TYPE_CIVMALE; pedType <= PED_TYPE_PROSTITUTE; pedType++) {
            CPedType::SetPedTypeAsAcquaintance(4, static_cast<ePedType>(pedType), 0xFFFFF);
        }

        auto pedPool = CPools::ms_pPedPool;
        if (!pedPool->m_nSize) {
            return;
        }

        for (int pedIndex = 0; pedIndex < pedPool->m_nSize; pedIndex++) {
            CPed* ped = pedPool->GetAt(pedIndex);
            if (!ped || ped->IsPlayer())
                continue;

            for (unsigned int pedType_1 = PED_TYPE_CIVMALE; pedType_1 <= PED_TYPE_PROSTITUTE; ++pedType_1) {
                ped->m_acquaintance.SetAsAcquaintance(4, CPedType::GetPedFlag(static_cast<ePedType>(pedType_1)));
            }
            CPed* closestPed = static_cast<CPed*>(ped->m_pIntelligence->m_entityScanner.GetClosestPedInRange());
            if (closestPed) {
                CEventAcquaintancePedHate event(closestPed);
                event.m_taskId = TASK_COMPLEX_KILL_PED_ON_FOOT;
                ped->m_pIntelligence->m_eventGroup.Add(&event, false);
            }
        }
    } else {
        return;
        // Proper deactivation
        // https://youtu.be/L97xXbFnFWM?t=90
    }
}

// 0x439510
void CCheat::MidnightCheat() {
    m_aCheatsActive[CHEAT_ALWAYS_MIDNIGHT] ^= true;
    if (m_aCheatsActive[CHEAT_ALWAYS_MIDNIGHT]) {
        CClock::ms_nGameClockHours = 0;
        CClock::ms_nGameClockMinutes = 0;
        CClock::ms_nGameClockSeconds = 0;
    }
}

// 0x438e40
void CCheat::MoneyArmourHealthCheat() {
    CPlayerPed* player = FindPlayerPed(-1);
    CPlayerInfo* playerInfo = player->GetPlayerInfoForThisPlayerPed();

    playerInfo->m_nMoney += 250000;
    player->m_fArmour = playerInfo->m_nMaxArmour;
    HealthCheat();
}

// 0x43a680
void CCheat::MonsterTruckCheat() {
    VehicleCheat(MODEL_MONSTERA);
}

// 0x439150
void CCheat::MuscleCheat() {
    CPlayerPed* player = FindPlayerPed(-1);

    CStats::SetStatValue(STAT_MUSCLE, 1000.0f);
    if (player->m_nPedState != PEDSTATE_DRIVING) {
        CClothes::RebuildPlayer(player, false);
    }
}

// 0x439e50
void CCheat::NinjaCheat() {
    m_aCheatsActive[CHEAT_NINJA_THEME] ^= true;
    if (m_aCheatsActive[CHEAT_NINJA_THEME]) {
        if (m_aCheatsActive[CHEAT_BLACK_TRAFFIC]) {
            m_aCheatsActive[CHEAT_BLACK_TRAFFIC] = false;
        }
    } else {
        int peds[8] = {
            MODEL_TRIADA,
            MODEL_TRIADB,
            MODEL_TRIBOSS,
            -2,
            -2,
            -2,
            -2,
            -2,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);

        if (m_aCheatsActive[CHEAT_BEACH_PARTY]) {
            BeachPartyCheat();
        }
        if (m_aCheatsActive[CHEAT_CHEAP_TRAFFIC]) {
            m_aCheatsActive[CHEAT_CHEAP_TRAFFIC] = false;
        }
        if (m_aCheatsActive[CHEAT_FAST_TRAFFIC]) {
            m_aCheatsActive[CHEAT_FAST_TRAFFIC] = false;
        }
        if (m_aCheatsActive[CHEAT_FUNHOUSE_THEME]) {
            FunhouseCheat();
        }
        if (m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC]) {
            CountrysideInvasionCheat();
        }
        CStreaming::ReclassifyLoadedCars();
        if (!m_aCheatsActive[CHEAT_BLACK_TRAFFIC]) {
            m_aCheatsActive[CHEAT_BLACK_TRAFFIC] = true;
            m_aCheatsActive[CHEAT_PINK_TRAFFIC] = false;
        }

        CStreaming::RequestModel(MODEL_KATANA, STREAMING_GAME_REQUIRED);
        CStreaming::LoadAllRequestedModels(false);

        CPlayerPed* player = FindPlayerPed(-1);
        player->GiveWeapon(WEAPON_KATANA, 0, true);
        player->SetCurrentWeapon(WEAPON_KATANA);
    }
}

// 0x4396c0
void CCheat::NotWantedCheat() {
    CPlayerPed* player = FindPlayerPed(-1);
    player->CheatWantedLevel(0);
    player->bWantedByPolice = false;
    m_aCheatsActive[CHEAT_I_DO_AS_I_PLEASE] ^= true;
}

// 0x4395b0
void CCheat::ParachuteCheat() {
    CStreaming::RequestModel(MODEL_GUN_PARA, STREAMING_GAME_REQUIRED);
    CStreaming::LoadAllRequestedModels(false);
    CPlayerPed* player = FindPlayerPed(-1);
    player->GiveWeapon(WEAPON_PARACHUTE, 0, true);
    player->SetCurrentWeapon(WEAPON_PARACHUTE);
}

// 0x4390d0
void CCheat::PinkCarsCheat() {
    m_aCheatsActive[CHEAT_PINK_TRAFFIC] ^= true;
    if (m_aCheatsActive[CHEAT_PINK_TRAFFIC]) {
        m_aCheatsActive[CHEAT_BLACK_TRAFFIC] = false;
    }
}

// unused
// 0x4395a0
void CCheat::PredatorCheat() {
    VehicleCheat(MODEL_PREDATOR);
}

// 0x43a560
void CCheat::QuadCheat() {
    VehicleCheat(MODEL_QUAD);
}

void CCheat::RainyWeatherCheat() {
    CWeather::ForceWeatherNow(WEATHER_RAINY_COUNTRYSIDE);
}

// 0x439710
void CCheat::RiotCheat() {
    m_aCheatsActive[CHEAT_RIOT_MODE] ^= true;
}

// 0x439590
void CCheat::SandstormCheat() {
    CWeather::ForceWeatherNow(WEATHER_SANDSTORM_DESERT);
}

// 0x439190
void CCheat::SkinnyCheat() {
    CStats::SetStatValue(STAT_FAT, 0.0f);
    CStats::SetStatValue(STAT_MUSCLE, 0.0f);

    CPlayerPed* player = FindPlayerPed(-1);
    if (player->m_nPedState != PEDSTATE_DRIVING) {
        CClothes::RebuildPlayer(player, false);
    }
}

// 0x438fc0
void CCheat::SlowTimeCheat() {
    if (CTimer::ms_fTimeScale > 0.25f) {
        CTimer::ms_fTimeScale *= 0.5f;
    }
}

// 0x439930
void CCheat::StaminaCheat() {
    CStats::SetStatValue(STAT_STAMINA, 1000.0f);
}

// 0x43a4b0
void CCheat::StockCarCheat() {
    VehicleCheat(MODEL_BLOODRA);
}

// 0x43a4c0
void CCheat::StockCar2Cheat() {
    VehicleCheat(MODEL_RNCHLURE);
}

// 0x43a4d0
void CCheat::StockCar3Cheat() {
    VehicleCheat(MODEL_HOTRINA);
}

// 0x43a4e0
void CCheat::StockCar4Cheat() {
    VehicleCheat(MODEL_HOTRINB);
}

// 0x439570
void CCheat::StormCheat() {
    CWeather::ForceWeatherNow(WEATHER_RAINY_COUNTRYSIDE);
    CWeather::Rain = 1.0f;
    CWeather::Wind = 1.0f;
}

// 0x43a670
void CCheat::StuntPlaneCheat() {
    VehicleCheat(MODEL_STUNT);
}

// 0x438f40
void CCheat::SunnyWeatherCheat() {
    CWeather::ForceWeatherNow(WEATHER_SUNNY_LA);
}

// 0x43a4a0
void CCheat::TankCheat() {
    VehicleCheat(MODEL_RHINO);
}

// 0x43a570
void CCheat::TankerCheat() {
    return plugin::Call<0x43A570>();

    // incomplete
    CVehicle* vehicle = VehicleCheat(MODEL_PETRO);
    if (!vehicle)
        return;

    CStreaming::RequestModel(MODEL_PETROTR, 0);
    CStreaming::LoadAllRequestedModels(false);

    if (CStreaming::ms_aInfoForModel[MODEL_PETROTR].m_nLoadState != LOADSTATE_LOADED)
        return;

    CTrailer* trailer = new CTrailer(MODEL_PETROTR, 1);
    CVector posn = vehicle->GetPosition();
    trailer->SetPosn(posn);
    trailer->SetOrientation(0.0f, 0.0f, 3.4906585f); // DegreesToRadians() ?
    trailer->m_nStatus = STATUS_TRAIN_MOVING;
    trailer->SetTowLink(vehicle, true);
    CWorld::Add(trailer);
}

// 0x43a510
void CCheat::TrashmasterCheat() {
    VehicleCheat(MODEL_TRASH);
}

// 0x43A0B0
CVehicle* CCheat::VehicleCheat(eModelID vehicleModelId) {
    return plugin::CallAndReturn<CVehicle*, 0x43A0B0, eModelID>(vehicleModelId); // CAutomobile::PlaceOnRoadProperly Places skimmer incorrectly, it's placed at millions units underground
}

// 0x4399d0
void CCheat::VehicleSkillsCheat() {
    CStats::SetStatValue(STAT_DRIVING_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_FLYING_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_BIKE_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_CYCLING_SKILL, 1000.0f);
}

// 0x439c70
void CCheat::VillagePeopleCheat() {

    m_aCheatsActive[CHEAT_PEDS_ATTACK_YOU_WITH_ROCKETS] ^= true;
    if (m_aCheatsActive[CHEAT_PEDS_ATTACK_YOU_WITH_ROCKETS]) {
        m_aCheatsActive[CHEAT_EVERYONE_ARMED] = false;
        EverybodyAttacksPlayerCheat();
    } else {
        int peds[8] = {
            MODEL_WMYCON,
            MODEL_CWMYFR,
            MODEL_ARMY,
            MODEL_LAPDM1,
            MODEL_BIKERB,
            -2,
            -2,
            -2,
        };
        CStreaming::StreamPedsIntoRandomSlots(peds);
        EverybodyAttacksPlayerCheat();
        m_aCheatsActive[CHEAT_EVERYONE_ARMED] = true;
    }
}

// 0x43a540
void CCheat::VortexCheat() {
    VehicleCheat(MODEL_VORTEX);
}

// 0x4396f0
void CCheat::WantedCheat() {
    CPlayerPed* player = FindPlayerPed(-1);
    player->CheatWantedLevel(6);
}

// 0x438f20
void CCheat::WantedLevelDownCheat() {
    CPlayerPed* player = FindPlayerPed(-1);
    player->CheatWantedLevel(0);
}

// 0x438e90
void CCheat::WantedLevelUpCheat() {
    CPlayerPed* player = FindPlayerPed();

    if (!player)
        return;

    uint8_t level = player->GetWantedLevel();
    player->CheatWantedLevel(std::min(level + 2, 6));
}

// 0x4385b0
void CCheat::WeaponCheat1() {
    CStreaming::RequestModel(MODEL_BRASSKNUCKLE, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_BAT, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_MOLOTOV, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_COLT45, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_CHROMEGUN, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_MICRO_UZI, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_AK47, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_CUNTGUN, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_ROCKETLA, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_SPRAYCAN, STREAMING_GAME_REQUIRED);

    CStreaming::LoadAllRequestedModels(false);

    CPlayerPed* player = FindPlayerPed(-1);
    player->GiveWeaponSet1();

    CPlayerPed* player1 = FindPlayerPed(1);
    if (player1) {
        player->GiveWeaponSet1();
    }

    CStreaming::SetModelIsDeletable(MODEL_BRASSKNUCKLE);
    CStreaming::SetModelIsDeletable(MODEL_MICRO_UZI);
    CStreaming::SetModelIsDeletable(MODEL_BAT);
    CStreaming::SetModelIsDeletable(MODEL_MOLOTOV);
    CStreaming::SetModelIsDeletable(MODEL_COLT45);
    CStreaming::SetModelIsDeletable(MODEL_CHROMEGUN);
    CStreaming::SetModelIsDeletable(MODEL_AK47);
    CStreaming::SetModelIsDeletable(MODEL_CUNTGUN);
    CStreaming::SetModelIsDeletable(MODEL_ROCKETLA);
    CStreaming::SetModelIsDeletable(MODEL_SPRAYCAN);
}

// 0x438890
void CCheat::WeaponCheat2() {
    CStreaming::RequestModel(MODEL_KNIFECUR, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_GRENADE, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_DESERT_EAGLE, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_SAWNOFF, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_TEC9, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_M4, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_SNIPER, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_FLAME, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_FIRE_EX, STREAMING_GAME_REQUIRED);

    CStreaming::LoadAllRequestedModels(false);

    CPlayerPed* player = FindPlayerPed(-1);
    player->GiveWeaponSet2();

    CPlayerPed* player1 = FindPlayerPed(1);
    if (player1) {
        player1->GiveWeaponSet2();
    }

    CStreaming::SetModelIsDeletable(MODEL_KNIFECUR);
    CStreaming::SetModelIsDeletable(MODEL_GRENADE);
    CStreaming::SetModelIsDeletable(MODEL_DESERT_EAGLE);
    CStreaming::SetModelIsDeletable(MODEL_SAWNOFF);
    CStreaming::SetModelIsDeletable(MODEL_TEC9);
    CStreaming::SetModelIsDeletable(MODEL_M4);
    CStreaming::SetModelIsDeletable(MODEL_SNIPER);
    CStreaming::SetModelIsDeletable(MODEL_FLAME);
    CStreaming::SetModelIsDeletable(MODEL_FIRE_EX);
}

// 0x438b30
void CCheat::WeaponCheat3() {
    CStreaming::RequestModel(MODEL_CHNSAW, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_SILENCED, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_SHOTGSPA, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_MP5LNG, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_M4, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_HEATSEEK, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_SATCHEL, STREAMING_GAME_REQUIRED);
    CStreaming::RequestModel(MODEL_BOMB, STREAMING_GAME_REQUIRED);

    CStreaming::LoadAllRequestedModels(false);

    CPlayerPed* player = FindPlayerPed(-1);
    player->GiveWeaponSet3();

    CPlayerPed* player1 = FindPlayerPed(1);
    if (player1) {
        player1->GiveWeaponSet3();
    }

    CStreaming::SetModelIsDeletable(MODEL_CHNSAW);
    CStreaming::SetModelIsDeletable(MODEL_SILENCED);
    CStreaming::SetModelIsDeletable(MODEL_SHOTGSPA);
    CStreaming::SetModelIsDeletable(MODEL_MP5LNG);
    CStreaming::SetModelIsDeletable(MODEL_M4);
    CStreaming::SetModelIsDeletable(MODEL_HEATSEEK);
    CStreaming::SetModelIsDeletable(MODEL_SATCHEL);
    CStreaming::SetModelIsDeletable(MODEL_BOMB);
}

// 0x439940
void CCheat::WeaponSkillsCheat() {
    CStats::SetStatValue(STAT_PISTOL_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_SILENCED_PISTOL_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_DESERT_EAGLE_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_SHOTGUN_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_SAWN_OFF_SHOTGUN_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_COMBAT_SHOTGUN_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_MACHINE_PISTOL_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_SMG_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_AK_47_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_M4_SKILL, 1000.0f);
    CStats::SetStatValue(STAT_RIFLE_SKILL, 1000.0f);
}

// 0x438ff0
void CCheat::SuicideCheat() {
    CPedDamageResponseCalculator damageCalculator(nullptr, 1000.0f, WEAPON_UNARMED, PED_PIECE_TORSO, false);
    CEventDamage damageEvent(nullptr, CTimer::m_snTimeInMilliseconds, WEAPON_UNARMED, PED_PIECE_TORSO, 0, false, false);
    CPlayerPed* pPlayer = FindPlayerPed(-1);
    if (damageEvent.AffectsPed(pPlayer))
        damageCalculator.ComputeDamageResponse(pPlayer, &damageEvent.m_damageResponse, true);
    else
        damageEvent.m_damageResponse.m_bDamageCalculated = true;
    pPlayer->GetEventGroup().Add(&damageEvent, false);
}

// 0x407410
bool CCheat::IsZoneStreamingAllowed() {
    return m_aCheatsActive[CHEAT_ELVIS_IS_EVERYWHERE]
        || m_aCheatsActive[CHEAT_PEDS_ATTACK_YOU_WITH_ROCKETS]
        || m_aCheatsActive[CHEAT_BEACH_PARTY]
        || m_aCheatsActive[CHEAT_GANGMEMBERS_EVERYWHERE]
        || m_aCheatsActive[CHEAT_NINJA_THEME]
        || m_aCheatsActive[CHEAT_SLUT_MAGNET]
        || m_aCheatsActive[CHEAT_FUNHOUSE_THEME]
        || m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC];
}

// Activates the cheat without changing statistics
// unknown name
// 0x438370
void CCheat::EnableLegitimateCheat(eCheats cheat)
{
    void (*pFunction)();

    pFunction = m_aCheatFunctions[cheat];
    if (pFunction)
        return pFunction();

    m_aCheatsActive[CHEAT_WEAPON_SET1 + cheat] ^= true;
}
