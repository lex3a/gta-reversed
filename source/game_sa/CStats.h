/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eStats.h"
#include "eStatModAbilities.h"
#include "eStatsReactions.h"

enum eStatUpdateState {
    STAT_UPDATE_DECREASE = 0,
    STAT_UPDATE_INCREASE = 1
};

enum eStatMessageCondition {
    STATMESSAGE_LESSTHAN = 0,
    STATMESSAGE_MORETHAN = 1
};

struct tStatMessage {
    short stat_num; // unique stat id
    bool displayed;
    unsigned char condition; // this can be lessthan/morethan, see eStatMessageCondition
    float value;             // value stat must reach to display message
    char text_id[8];         // text id from american.gxt text file to display
};

VALIDATE_SIZE(tStatMessage, 0x10);

class CVehicle;
class CBike;
class CBmx;

class CStats {
public:
    static constexpr size_t FIRST_INT_STAT = 120;
    static constexpr size_t FIRST_UNUSED_STAT = 82;

    static tStatMessage (&StatMessage)[8];
    static unsigned int& TotalNumStatMessages;
    static char (&LastMissionPassedName)[8];
    static int (&TimesMissionAttempted)[100];
    static int (&FavoriteRadioStationList)[14];
    static int (&PedsKilledOfThisType)[32];
    static float (&StatReactionValue)[59];
    static int (&StatTypesInt)[223];
    static float (&StatTypesFloat)[82];
    static short& m_ThisStatIsABarChart;
    static bool& bStatUpdateMessageDisplayed;
    static unsigned int& m_SprintStaminaCounter;
    static unsigned int& m_CycleStaminaCounter;
    static unsigned int& m_CycleSkillCounter;
    static unsigned int& m_SwimStaminaCounter;
    static unsigned int& m_SwimUnderWaterCounter;
    static unsigned int& m_DrivingCounter;
    static unsigned int& m_FlyingCounter;
    static unsigned int& m_BoatCounter;
    static unsigned int& m_BikeCounter;
    static unsigned int& m_FatCounter;
    static unsigned int& m_RunningCounter;
    static unsigned int& m_WeaponCounter;
    static unsigned int& m_DeathCounter;
    static unsigned int& m_MaxHealthCounter;
    static unsigned int& m_AddToHealthCounter;
    static unsigned int& m_LastWeaponTypeFired;

    static void InjectHooks();

    static char* GetStatID(eStats stat);
    static bool GetStatType(eStats stat);
    static float GetStatValue(eStats stat);
    static char GetTimesMissionAttempted(unsigned char missionId);
    static void RegisterMissionAttempted(unsigned char missionId);
    static void RegisterMissionPassed(unsigned char missionId);
    static bool PopulateFavoriteRadioStationList();
    static int* GetFullFavoriteRadioStationList();
    static int FindMostFavoriteRadioStation();
    static int FindLeastFavoriteRadioStation();
    static int FindCriminalRatingNumber();
    static float GetPercentageProgress();
    static void BuildStatLine(char* line, void* pValue1, int metrics, void* pValue2, int type);
    static int ConvertToMins(int value);
    static int ConvertToSecs(int value);
    static bool SafeToShowThisStat(eStats stat);
    static bool CheckForThreshold(float* pValue, float range);
    static bool IsStatCapped(eStats stat);
    static void ProcessReactionStatsOnDecrement(eStats stat);
    static void CheckForStatsMessage();
    static void LoadStatUpdateConditions();
    static void LoadActionReactionStats();
    static int FindMaxNumberOfGroupMembers();
    static float GetFatAndMuscleModifier(eStatModAbilities statMod);
    static void DecrementStat(eStats stat, float value);
    static void SetStatValue(eStats stat, float value);
    static void RegisterFastestTime(eStats stat, int fastestTime);
    static void RegisterBestPosition(eStats stat, int position);
    static char* FindCriminalRatingString();
    static int ConstructStatLine(int arg0, unsigned char arg1);
    static void ProcessReactionStatsOnIncrement(eStats stat);
    static void DisplayScriptStatUpdateMessage(unsigned char state, eStats stat, float value);
    static void UpdateRespectStat(unsigned char arg0);
    static void UpdateSexAppealStat();
    static void Init();
    static void IncrementStat(eStats stat, float value);
    static void SetNewRecordStat(eStats stat, float value);
    static void UpdateFatAndMuscleStats(unsigned int value);
    static void UpdateStatsWhenSprinting();
    static void UpdateStatsWhenRunning();
    static void UpdateStatsWhenCycling(bool arg0, CBmx* bmx);
    static void UpdateStatsWhenSwimming(bool arg0, bool arg1);
    static void UpdateStatsWhenDriving(CVehicle* vehicle);
    static void UpdateStatsWhenFlying(CVehicle* vehicle);
    static void UpdateStatsWhenOnMotorBike(CBike* bike);
    static void UpdateStatsWhenWeaponHit(eWeaponType weaponType);
    static void UpdateStatsWhenFighting();
    static void UpdateStatsOnRespawn();
    static void UpdateStatsAddToHealth(unsigned int addToHealth);
    static void ModifyStat(eStats stat, float value);
    static bool Save();
    static bool Load();
};
