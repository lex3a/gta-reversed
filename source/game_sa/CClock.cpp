#include "StdInc.h"

uint8_t CClock::daysInMonth[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 0x8CCF24

bool& CClock::bClockHasBeenStored = *reinterpret_cast<bool*>(0xB70144);
uint16_t& CClock::ms_Stored_nGameClockSeconds = *reinterpret_cast<uint16_t*>(0xB70148);
uint8_t& CClock::ms_Stored_nGameClockMinutes = *reinterpret_cast<uint8_t*>(0xB7014A);
uint8_t& CClock::ms_Stored_nGameClockHours = *reinterpret_cast<uint8_t*>(0xB7014B);
uint8_t& CClock::ms_Stored_nGameClockDays = *reinterpret_cast<uint8_t*>(0xB7014C);
uint8_t& CClock::ms_Stored_nGameClockMonths = *reinterpret_cast<uint8_t*>(0xB7014D);

uint8_t& CClock::CurrentDay = *reinterpret_cast<uint8_t*>(0xB7014E);
uint16_t& CClock::ms_nGameClockSeconds = *reinterpret_cast<uint16_t*>(0xB70150);
uint8_t& CClock::ms_nGameClockMinutes = *reinterpret_cast<uint8_t*>(0xB70152);
uint8_t& CClock::ms_nGameClockHours = *reinterpret_cast<uint8_t*>(0xB70153);
uint8_t& CClock::ms_nGameClockDays = *reinterpret_cast<uint8_t*>(0xB70154);
uint8_t& CClock::ms_nGameClockMonth = *reinterpret_cast<uint8_t*>(0xB70155);

uint32_t& CClock::ms_nLastClockTick = *reinterpret_cast<uint32_t*>(0xB70158);
uint32_t& CClock::ms_nMillisecondsPerGameMinute = *reinterpret_cast<uint32_t*>(0xB7015C);

void CClock::InjectHooks() {
    ReversibleHooks::Install("CClock", "Initialise", 0x52CD90, &CClock::Initialise);
    ReversibleHooks::Install("CClock", "Update", 0x52CF10, &CClock::Update);
    ReversibleHooks::Install("CClock", "GetGameClockMinutesUntil", 0x52CEB0, &CClock::GetGameClockMinutesUntil);
    ReversibleHooks::Install("CClock", "GetIsTimeInRange", 0x52CEE0, &CClock::GetIsTimeInRange);
    ReversibleHooks::Install("CClock", "NormaliseGameClock", 0x52CDE0, &CClock::NormaliseGameClock);
    ReversibleHooks::Install("CClock", "OffsetClockByADay", 0x52D0B0, &CClock::OffsetClockByADay);
    ReversibleHooks::Install("CClock", "SetGameClock", 0x52D150, &CClock::SetGameClock);
    ReversibleHooks::Install("CClock", "StoreClock", 0x52D020, &CClock::StoreClock);
    ReversibleHooks::Install("CClock", "RestoreClock", 0x52D070, &CClock::RestoreClock);
}

/// @brief Initializes the clock. (0x52CD90)
/// @param millisecondsPerGameMinute Number of milliseconds per one game minute.
void CClock::Initialise(uint32_t millisecondsPerGameMinute) {
    ms_nMillisecondsPerGameMinute = millisecondsPerGameMinute;
    ms_nGameClockMonth = 1;
    ms_nGameClockDays = 1;
    ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
    ms_nGameClockHours = 12;
    ms_nGameClockMinutes = 0;
    ms_nGameClockSeconds = 0;
    bClockHasBeenStored = false;
    CurrentDay = 4;
}

/// @brief Updates the game clock. (0x52CF10)
void CClock::Update() {
    if (ms_nMillisecondsPerGameMinute < (CTimer::m_snTimeInMilliseconds - ms_nLastClockTick) || CCheat::m_aCheatsActive[CHEAT_FASTER_CLOCK]) {
        if (!CCheat::m_aCheatsActive[CHEAT_ALWAYS_MIDNIGHT] && !CCheat::m_aCheatsActive[CHEAT_STOP_GAME_CLOCK_ORANGE_SKY]) {
            // next minute
            ms_nGameClockMinutes++;
            ms_nLastClockTick += ms_nMillisecondsPerGameMinute;

            if (CCheat::m_aCheatsActive[CHEAT_FASTER_CLOCK])
                ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;

            // next hour
            if (ms_nGameClockMinutes >= 60) {
                ms_nGameClockMinutes = 0;
                ms_nGameClockHours++;

                // next day
                if (ms_nGameClockHours >= 24) {
                    ms_nGameClockHours = 0;
                    ms_nGameClockDays++;

                    if (CurrentDay == 7)
                        CurrentDay = 1;
                    else
                        CurrentDay++;

                    CStats::IncrementStat(STAT_DAYS_PASSED_IN_GAME, 1.0f);

                    // next month
                    if (ms_nGameClockDays >= daysInMonth[ms_nGameClockMonth]) {
                        ms_nGameClockDays = 1;
                        if (++ms_nGameClockMonth > 12u)
                                ms_nGameClockMonth = 1;
                    }
                }
            }
        }
    }
    ms_nGameClockSeconds = (CTimer::m_snTimeInMilliseconds - ms_nLastClockTick) * 60 / ms_nMillisecondsPerGameMinute;
}

/// @brief Number of minutes remaining to specific time. (0x52CEB0)
/// @param hours Hour
/// @param minutes Minute
/// @returns Minutes remaining to Hour:Minute
uint16_t CClock::GetGameClockMinutesUntil(uint8_t hours, uint8_t minutes) {
    auto now = ms_nGameClockHours * 60 + ms_nGameClockMinutes;
    auto then = hours * 60 + minutes;

    if (then < now)
        then += 24 * 60; // Add one day

    return then - now;
}

/// @brief Checks if the current hour is greater than or equal to from and less than *to*. (0x52CEE0)
/// @param from Hour for *from*
/// @param to Hour for *to*
/// @returns True if the parameters ensure the check, false otherwise.
bool CClock::GetIsTimeInRange(uint8_t from, uint8_t to) {
    if (from > to)
        return ms_nGameClockHours >= from || ms_nGameClockHours < to;
    else
        return ms_nGameClockHours >= from && ms_nGameClockHours < to;
}

/// @brief Normalizes the game clock. For example hour of 24 means new day and hour 1. (0x52CDE0)
void CClock::NormaliseGameClock() {
    if (ms_nGameClockSeconds >= 60) {
        auto leftMins = ms_nGameClockSeconds / 60;

        // add leftover mins from second counter
        ms_nGameClockMinutes += leftMins;

        // normalize second counter
        ms_nGameClockSeconds %= 60;
    }

    if (ms_nGameClockMinutes >= 60) {
        auto leftHours = ms_nGameClockMinutes / 60;

        // add leftover mins from minute counter
        ms_nGameClockHours += leftHours;

        // normalize minute counter
        ms_nGameClockMinutes %= 60;
    }

    if (ms_nGameClockHours >= 24) {
        auto leftDays = ms_nGameClockHours / 24;

        // add leftover days from hour counter
        ms_nGameClockDays += leftDays;

        // normalize hour counter
        ms_nGameClockHours %= 24;
    }

    if (ms_nGameClockDays > 31) {
        // new month
        ms_nGameClockDays = 1;

        ms_nGameClockMonth++;
    }

    if (ms_nGameClockMonth > 12)
        ms_nGameClockMonth = 1;
}

/// @brief Sets new day. (0x52D0B0)
/// @param timeDirection 0 for previous day, non-zero value for next day.
void CClock::OffsetClockByADay(uint32_t timeDirection) {
    if (timeDirection == 0) {
        ms_nGameClockDays--;

        if (ms_nGameClockDays == 0) {
            ms_nGameClockMonth--;

            if (ms_nGameClockMonth == 0)
                ms_nGameClockMonth = 12;

            ms_nGameClockDays = daysInMonth[ms_nGameClockMonth];
        }
        CurrentDay--;

        if (CurrentDay == 0)
            CurrentDay = 7;
    } else {
        ms_nGameClockDays++;

        if (daysInMonth[ms_nGameClockMonth] < ms_nGameClockDays) {
            ms_nGameClockMonth++;
            ms_nGameClockDays = 1;

            if (ms_nGameClockMonth > 12)
                ms_nGameClockMonth = 1;
        }

        CurrentDay++;

        if (CurrentDay > 7) {
            CurrentDay = 1;
            return;
        }
    }
}

/// @brief Sets the game clock. (0x52D150)
/// @param hours Hour to be set.
/// @param minutes Minute to be set.
/// @param days Day to be set.
void CClock::SetGameClock(uint8_t hours, uint8_t minutes, uint8_t day) {
    ms_nLastClockTick = CTimer::m_snTimeInMilliseconds;
    ms_nGameClockHours = hours;
    ms_nGameClockMinutes = minutes;

    if (day) {
        CurrentDay = day;
        ++ms_nGameClockDays;
    }

    ms_nGameClockSeconds = 0;
    NormaliseGameClock();
}

/// @brief Stores the clock state for loading afterwards. (0x52D020)
void CClock::StoreClock() {
    ms_Stored_nGameClockMonths = ms_nGameClockMonth;
    ms_Stored_nGameClockDays = ms_nGameClockDays;
    ms_Stored_nGameClockHours = ms_nGameClockHours;
    ms_Stored_nGameClockMinutes = ms_nGameClockMinutes;
    ms_Stored_nGameClockSeconds = ms_nGameClockSeconds;
    bClockHasBeenStored = true;
}

/// @brief Loads the last saved clock state. (0x52D070)
void CClock::RestoreClock() {
    ms_nGameClockMonth = ms_Stored_nGameClockMonths;
    ms_nGameClockDays = ms_Stored_nGameClockDays;
    ms_nGameClockHours = ms_Stored_nGameClockHours;
    ms_nGameClockMinutes = ms_Stored_nGameClockMinutes;
    ms_nGameClockSeconds = ms_Stored_nGameClockSeconds;
}
