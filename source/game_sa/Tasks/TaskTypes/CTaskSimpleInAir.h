/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CTaskTimer.h"
#include "CVector.h"
#include "CAnimBlendAssociation.h"
#include "CEntity.h"

class  CTaskSimpleInAir : public CTaskSimple {
public:
    CVector m_vecPosn;
    float m_fAngle;
    unsigned char m_nSurfaceType;
    char _pad[3];
    CAnimBlendAssociation* m_pAnim;
    float m_fMinZSpeed;
    union {
        unsigned char m_nFlags;
        struct
        {
            unsigned char bUsingJumpGlide : 1;
            unsigned char bUsingFallGlide : 1;
            unsigned char bUsingClimbJump : 1;
        };
    };
    char _pad2[3];
    uint32_t m_nProcessCounter;
    CTaskTimer m_timer;
    CEntity* m_pClimbEntity;
private:
    CTaskSimpleInAir* Constructor(bool bUsingJumpGlide, bool bUsingFallGlide, bool bUsingClimbJump);
public:
    CTaskSimpleInAir(bool bUsingJumpGlide, bool bUsingFallGlide, bool bUsingClimbJump);
    ~CTaskSimpleInAir() override;

    static void InjectHooks();

    CTask* Clone() override { return new CTaskSimpleInAir(bUsingJumpGlide, bUsingFallGlide, bUsingClimbJump); }
    eTaskType GetId() override { return TASK_SIMPLE_IN_AIR; }
    bool ProcessPed(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;

    bool ProcessPed_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);

    static void DeleteAnimCB(CAnimBlendAssociation* pAnim, void* data);

    static float ms_fSlowFallThreshold; // 0x8D2EFC
    static unsigned int ms_nMaxSlowFallFrames; // 0x8D2EF8
};

VALIDATE_SIZE(CTaskSimpleInAir, 0x3C);
