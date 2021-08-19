#include "StdInc.h"

void CTaskSimpleJump::InjectHooks()
{
    ReversibleHooks::Install("CTaskSimpleJump", "Constructor", 0x679AA0, &CTaskSimpleJump::Constructor);
    ReversibleHooks::Install("CTaskSimpleJump", "CheckIfJumpBlocked", 0x67D590, &CTaskSimpleJump::CheckIfJumpBlocked);
    ReversibleHooks::Install("CTaskSimpleJump", "Launch", 0x679B80, &CTaskSimpleJump::Launch);
    ReversibleHooks::Install("CTaskSimpleJump", "StartLaunchAnim", 0x67D7A0, &CTaskSimpleJump::StartLaunchAnim);
    ReversibleHooks::Install("CTaskSimpleJump", "JumpAnimFinishCB", 0x67A020, &CTaskSimpleJump::JumpAnimFinishCB);
    //VTABLE
    ReversibleHooks::Install("CTaskSimpleJump", "Clone", 0x67C510, &CTaskSimpleJump::Clone_Reversed);
    ReversibleHooks::Install("CTaskSimpleJump", "MakeAbortable", 0x679B60, &CTaskSimpleJump::MakeAbortable_Reversed);
    ReversibleHooks::Install("CTaskSimpleJump", "ProcessPed", 0x680C60, &CTaskSimpleJump::ProcessPed_Reversed);
}

CTaskSimpleJump* CTaskSimpleJump::Constructor(bool bCanClimb)
{
    this->CTaskSimpleJump::CTaskSimpleJump(bCanClimb);
    return this;
}

// 0x679AA0
CTaskSimpleJump::CTaskSimpleJump(bool bCanClimb)
{
    m_bCanClimb = bCanClimb;
    m_pClimbEntity = nullptr;
    m_bIsFinished = false;
    m_bIsJumpBlocked = false;
    m_bClimbJump = false;
    m_bLaunchAnimStarted = false;
    m_bHighJump = false;
    m_pAnim = nullptr;
}

// 0x679AF0
CTaskSimpleJump::~CTaskSimpleJump()
{
    if (m_pAnim)
        m_pAnim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);

    if (m_pClimbEntity)
        m_pClimbEntity->CleanUpOldReference(&m_pClimbEntity);
}

// 0x67C510
CTask* CTaskSimpleJump::Clone()
{
    return Clone_Reversed();
}

// 0x679B60
bool CTaskSimpleJump::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return MakeAbortable_Reversed(ped, priority, _event);
}

// 0x680C60;
bool CTaskSimpleJump::ProcessPed(CPed* ped)
{
    return ProcessPed_Reversed(ped);
}

CTask* CTaskSimpleJump::Clone_Reversed()
{
    auto newTask = new CTaskSimpleJump(m_bCanClimb);
    newTask->m_bHighJump = this->m_bHighJump;
    return newTask;
}

bool CTaskSimpleJump::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    if (m_pAnim)
    {
        m_pAnim->m_nFlags |= ANIM_FLAG_FREEZE_LAST_FRAME;
        m_pAnim->m_fBlendDelta = -4.0F;
    }

    return priority == ABORT_PRIORITY_IMMEDIATE;
}

bool CTaskSimpleJump::ProcessPed_Reversed(CPed* ped)
{
    if (!m_bIsFinished)
    {
        if (!m_pAnim)
        {
            if (!StartLaunchAnim(ped))
            {
                m_bLaunchAnimStarted = false;
                return true;
            }
            m_bLaunchAnimStarted = true;
        }
        return this->m_bIsFinished;
    }

    if ((ped->IsPlayer() || m_bCanClimb) && CGame::currArea == AREA_CODE_NORMAL_WORLD)
        m_pClimbEntity = CTaskSimpleClimb::TestForClimb(ped, m_vecClimbPos, m_fClimbAngle, m_nClimbSurfaceType, true);

    if (!m_pClimbEntity)
        CheckIfJumpBlocked(ped);

    if (!m_bIsJumpBlocked)
    {
        Launch(ped);
    }
    else if (ped->IsPlayer())
    {
        CVector empty{};
        CEventSoundQuiet _event(ped, 45.0F, -1, empty);
        GetEventGlobalGroup()->Add(&_event, false);
    }

    return true;
}

// 0x67D590
bool CTaskSimpleJump::CheckIfJumpBlocked(CPed* ped)
{
    if (ped->m_bIsStuck || ped->GetEventHandler().GetCurrentEventType() == EVENT_STUCK_IN_AIR)
        return false;

    auto pedColData = CModelInfo::GetModelInfo(ped->m_nModelIndex)->m_pColModel->m_pColData;

    CVector posn = ped->GetPosition() + ped->GetForward() * 0.25F + CVector(0.0F, 0.0F, pedColData->m_pSpheres[2].m_vecCenter.z + 0.25F);

    m_bClimbJump = CWorld::TestSphereAgainstWorld(posn, 0.25F, 0, true, true, false, true, false, false) != 0;

    CVector savedPedPosition = ped->GetPosition();
    ped->SetPosn((*ped->m_matrix) * CVector(0.0F, 0.0F, 0.75F));

    for (unsigned int i = 0; i < pedColData->m_nNumSpheres; i++)
        pedColData->m_pSpheres[i].m_fRadius = 0.3F;

    if (ped->TestCollision(false))
        m_bIsJumpBlocked = true;

    ped->SetPosn(savedPedPosition);

    for (unsigned int i = 0; i < pedColData->m_nNumSpheres; i++)
        pedColData->m_pSpheres[i].m_fRadius = 0.35F;

    return m_bIsJumpBlocked;
}

// 0x679B80
void CTaskSimpleJump::Launch(CPed* ped)
{
    float fHorizontalJumpSpeed = 0.1F;

    auto pSprintAnim = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SPRINT);
    if (pSprintAnim)
        fHorizontalJumpSpeed = lerp(0.17F, 0.22F, pSprintAnim->m_fBlendAmount);
    else
    {
        auto pRunAnim = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_RUN);
        if (pRunAnim)
            fHorizontalJumpSpeed = lerp(0.1F, 0.17F, pRunAnim->m_fBlendAmount);
    }

    float fJumpForce = (ped->IsPlayer() || m_bHighJump) ? 8.5F : 4.5F;

    if (ped->m_pPlayerData)
    {
        float modifier = CStats::GetFatAndMuscleModifier(STAT_MOD_2);
        fHorizontalJumpSpeed *= modifier;
        fJumpForce *= modifier;
    }

    if (ped->IsPlayer() && CCheat::m_aCheatsActive[CHEAT_MEGAJUMP])
        fJumpForce *= 10.0F;

    ped->ApplyMoveForce(0.0F, 0.0F, fJumpForce);

    if (m_bClimbJump)
    {
        ped->m_vecMoveSpeed.x = 0.0F;
        ped->m_vecMoveSpeed.y = 0.0F;
    }
    else if (!m_pClimbEntity && (ped->m_standingOnEntity || ped->m_vecMoveSpeed.SquaredMagnitude2D() < fHorizontalJumpSpeed))
    {
        ped->m_vecMoveSpeed.x = -fHorizontalJumpSpeed * sin(ped->m_fCurrentRotation);
        ped->m_vecMoveSpeed.y = fHorizontalJumpSpeed * cos(ped->m_fCurrentRotation);

        if (ped->m_standingOnEntity)
        {
            ped->m_vecMoveSpeed.x += ped->m_standingOnEntity->AsPhysical()->m_vecMoveSpeed.x;
            ped->m_vecMoveSpeed.y += ped->m_standingOnEntity->AsPhysical()->m_vecMoveSpeed.y;
        }
    }

    ped->bIsStanding = false;
    ped->bIsInTheAir = true;

    if (!m_pClimbEntity)
    {
        if (m_bClimbJump)
        {
            auto pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CLIMB_JUMP, 8.0F);
            pAnim->m_nFlags |= ANIM_FLAG_UNLOCK_LAST_FRAME;
        }
        else
            CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_JUMP_GLIDE, 8.0F);
    }

    if (ped->bDoBloodyFootprints && CLocalisation::Blood())
    {
        auto pHier = GetAnimHierarchyFromSkinClump(ped->m_pRwClump);
        CVector v;
        RwV3dTransformPoints(&v, &v, 1, &RpHAnimHierarchyGetMatrixArray(pHier)[RpHAnimIDGetIndex(pHier, ped->m_apBones[PED_NODE_LEFT_FOOT]->m_nNodeId)]);

        CVector v1 = ped->GetForward() * 0.2F;
        v += v1 + CVector(0.0F, 0.0F, -0.1F);
        CShadows::AddPermanentShadow(SHADOW_DEFAULT, gpBloodPoolTex, &v, v1.x * 0.26F, v1.y * 0.26F, ped->GetForward().x * 0.14F, ped->GetForward().y * 0.14F, 255, 255, 0, 0, 4.0F, 3000, 1.0F);

        v.Set(0.0F, 0.0F, 0.0F);
        RwV3dTransformPoints(&v, &v, 1, &RpHAnimHierarchyGetMatrixArray(pHier)[RpHAnimIDGetIndex(pHier, ped->m_apBones[PED_NODE_RIGHT_FOOT]->m_nNodeId)]);
        v += v1 + CVector(0.0F, 0.0F, -0.1F);
        CShadows::AddPermanentShadow(SHADOW_DEFAULT, gpBloodPoolTex, &v, v1.x * 0.26F, v1.y * 0.26F, ped->GetForward().x * 0.14F, ped->GetForward().y * 0.14F, 255, 255, 0, 0, 4.0F, 3000, 1.0F);

        if (ped->m_nDeathTime <= 40)
        {
            ped->m_nDeathTime = 0;
            ped->bDoBloodyFootprints = false;
        }
        else
            ped->m_nDeathTime -= 40;
    }
}

// 0x67D7A0
bool CTaskSimpleJump::StartLaunchAnim(CPed* ped)
{
    m_pAnim = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_JUMP_LAUNCH);
    if (!m_pAnim)
        m_pAnim = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_JUMP_LAUNCH_R);
    if (m_pAnim)
        return false;

    if (g_surfaceInfos->IsSteepSlope(ped->m_nContactSurface) && DotProduct(ped->GetForward(), ped->field_578) < 0.0F
        || ped->IsPlayer() && !CGameLogic::IsPlayerAllowedToGoInThisDirection(ped, ped->GetForward().x, ped->GetForward().y, ped->GetForward().z, 5.0F))
    {
        ped->m_pedIK.bSlopePitch = true;
        return false;
    }

    auto pMoveAnim = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SPRINT);
    if (!pMoveAnim || pMoveAnim->m_fBlendAmount < 0.3F)
        pMoveAnim = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_RUN);
    if (!pMoveAnim || pMoveAnim->m_fBlendAmount < 0.3F)
        pMoveAnim = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_WALK);

    float fMoveAnimBlendAmount = 0.0F;
    if (pMoveAnim && pMoveAnim->m_fBlendAmount > 0.3F)
    {
        fMoveAnimBlendAmount = pMoveAnim->m_fCurrentTime / pMoveAnim->m_pHierarchy->m_fTotalTime + 0.367F;
        if (fMoveAnimBlendAmount > 1.0F)
            fMoveAnimBlendAmount -= 1.0F;
    }

    m_pAnim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, fMoveAnimBlendAmount >= 0.5F ? ANIM_ID_JUMP_LAUNCH_R : ANIM_ID_JUMP_LAUNCH, 8.0F);

    if (ped->m_pPlayerData)
        m_pAnim->m_fSpeed = CStats::GetFatAndMuscleModifier(STAT_MOD_2);
    m_pAnim->SetFinishCallback(JumpAnimFinishCB, this);
    ped->m_fAimingRotation = ped->m_fCurrentRotation;

    return true;
}

// 0x67A020
void CTaskSimpleJump::JumpAnimFinishCB(CAnimBlendAssociation* pAnim, void* data)
{
    auto pTask = reinterpret_cast<CTaskSimpleJump*>(data);
    pTask->m_bIsFinished = true;
    pTask->m_pAnim = nullptr;
}
