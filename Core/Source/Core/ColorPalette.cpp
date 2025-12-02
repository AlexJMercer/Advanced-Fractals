#include "ColorPalette.hpp"



namespace Core
{

    ColorPalette::ColorPalette() :
        m_rng(std::random_device{}()),
        m_distByte(0, 255),
        m_distDark(0, 35),
        m_distBright(100, 255)
    {
        m_colors.resize(PALETTE_SIZE);
        generateGradient();
    }


    const std::vector<pixel_t>& ColorPalette::getColors() const
    {
        return m_colors;
    }


    pixel_t ColorPalette::linearInterpolation(const pixel_t& fromColor, const pixel_t& toColor, float t)
    {
        return {
            (uint8_t)(fromColor.red + (toColor.red) * t),
            (uint8_t)(fromColor.green + (toColor.green) * t),
            (uint8_t)(fromColor.blue + (toColor.blue) * t)
        };
    }


    void ColorPalette::generateRandom()
    {
        for (auto& color : m_colors)
            color = {
                (uint8_t)m_distByte(m_rng),
                (uint8_t)m_distByte(m_rng),
                (uint8_t)m_distByte(m_rng)
            };
    }


    void ColorPalette::generateGradient()
    {
        pixel_t a = { (uint8_t)m_distDark(m_rng), (uint8_t)m_distDark(m_rng), (uint8_t)m_distDark(m_rng) };
        pixel_t b = { (uint8_t)m_distBright(m_rng), (uint8_t)m_distBright(m_rng), (uint8_t)m_distBright(m_rng) };

        for (size_t i = 0; i < PALETTE_SIZE; i++) 
        {
            float t = float(i) / float(PALETTE_SIZE - 1);
            m_colors[i] = linearInterpolation(a, b, t);
        }
    }

}