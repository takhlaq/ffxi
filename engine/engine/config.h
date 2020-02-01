#pragma once
#include <engine/types.h>

namespace lotus
{
    class Config
    {
    public:
        struct Renderer
        {
            uint32_t screen_width = 1600;
            uint32_t screen_height = 900;
            uint32_t borderless = 0;
        } renderer {};
    };
}
