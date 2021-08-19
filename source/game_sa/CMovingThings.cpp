#include "StdInc.h"

void CMovingThings::InjectHooks() {
    ReversibleHooks::Install("CMovingThings", "Render", 0x717150, &CMovingThings::Render);
    ReversibleHooks::Install("CMovingThings", "Render_BeforeClouds", 0x7178F0, &CMovingThings::Render_BeforeClouds);
    ReversibleHooks::Install("CMovingThings", "Shutdown", 0x717C20, &CMovingThings::Shutdown);
    ReversibleHooks::Install("CMovingThings", "Init", 0x717D00, &CMovingThings::Init);
    ReversibleHooks::Install("CMovingThings", "Update", 0x7185B0, &CMovingThings::Update);
}

// 0x717150
void CMovingThings::Render() {
    //empty
}

// 0x7178F0
void CMovingThings::Render_BeforeClouds() {
    CPlaneTrails::Render();
}

// 0x717C20
void CMovingThings::Shutdown() {
    CEscalators::Shutdown();
}

// 0x717D00
void CMovingThings::Init() {
    CPlaneTrails::Init();
    CPointLights::Init();
    CEscalators::Init();
}

// 0x7185B0
void CMovingThings::Update() {
    CPlaneTrails::Update();
    CEscalators::Update();
}

