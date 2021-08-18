#pragma once

class CMovingThings {
public:
    static void InjectHooks();

    static void Render();
    static void Render_BeforeClouds();
    static void Shutdown();
    static void Init();
    static void Update();
};
