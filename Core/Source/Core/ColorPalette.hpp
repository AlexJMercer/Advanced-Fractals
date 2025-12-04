#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <random>

namespace Core
{
    struct pixel_t
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };


    class ColorPalette
    {
    public:
        ColorPalette();
        ~ColorPalette() = default;

        pixel_t m_startColor, m_endColor;
        static constexpr size_t PALETTE_SIZE = 256;

        void generateRandom();
        void generateGradient();
        const std::vector<pixel_t>& getColors() const;

    private:
        std::mt19937_64 m_rng;
        std::uniform_int_distribution<int> m_distByte;
        std::uniform_int_distribution<int> m_distDark;
        std::uniform_int_distribution<int> m_distBright;
        
        std::vector<pixel_t> m_colors;

        pixel_t linearInterpolation(const pixel_t& startColor, const pixel_t& endColor, float t);
    };
}