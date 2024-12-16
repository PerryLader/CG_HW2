#include "ColorGC.h"
#include <algorithm>


ColorGC::ColorGC() : color(0xFF000000) {} // Default: black, fully opaque
ColorGC::ColorGC(uint8_t r, uint8_t g, uint8_t b, uint8_t a )
    : color((a << 24) | (r << 16) | (g << 8) | b) {
}

ColorGC::ColorGC(double r, double g, double b, double a ){
    uint8_t red = static_cast<uint8_t>(r);
    uint8_t green = static_cast<uint8_t>(g);
    uint8_t blue = static_cast<uint8_t>(b);
    uint8_t alpha = static_cast<uint8_t>(a);

    // Pack into 0xAARRGGBB format
    color = (static_cast<uint32_t>(alpha) << 24) |
        (static_cast<uint32_t>(red) << 16) |
        (static_cast<uint32_t>(green) << 8) |
        static_cast<uint32_t>(blue);

}

ColorGC::ColorGC(uint32_t rgba) : color(rgba) {}

// Getters for individual components
uint8_t ColorGC::getRed()  { return (color >> 16) & 0xFF; }
uint8_t ColorGC::getGreen()  { return (color >> 8) & 0xFF; }
uint8_t ColorGC::getBlue()  { return color & 0xFF; }
uint8_t ColorGC::getAlpha()  { return (color >> 24) & 0xFF; }

// Setters for individual components
void ColorGC::setRed(uint8_t r) { color = (color & 0xFF00FFFF) | (r << 16); }
void ColorGC::setGreen(uint8_t g) { color = (color & 0xFFFF00FF) | (g << 8); }
void ColorGC::setBlue(uint8_t b) { color = (color & 0xFFFFFF00) | b; }
void ColorGC::setAlpha(uint8_t a) { color = (color & 0x00FFFFFF) | (a << 24); }

// Get the entire RGBA value
uint32_t ColorGC::getRGBA()  const{ return color; }

// Set the entire RGBA value
void ColorGC::setRGBA(uint32_t rgba) { color = rgba; }

// Convert to string in hexadecimal format
std::string ColorGC::toHex()  {
    std::ostringstream ss;
    ss << "#" << std::hex << std::setfill('0') << std::setw(8) << color;
    return ss.str();
}




