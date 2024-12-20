#pragma once
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>


class ColorGC {
private:
    uint32_t color; // Internal representation: 0xAARRGGBB

public:
    // Constructors
    ColorGC();
    ColorGC(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    

    ColorGC(uint32_t rgba);

    // Getters for individual components
    uint8_t getRed() ;
    uint8_t getGreen() ;
    uint8_t getBlue() ;
    uint8_t getAlpha() ;

    // Setters for individual components
    void setRed(uint8_t r);
    void setGreen(uint8_t g);
    void setBlue(uint8_t b);
    void setAlpha(uint8_t a);

    // Get the entire RGBA value
    uint32_t getARGB() const;

    // Set the entire RGBA value
    void setARGB(uint32_t rgba);

    // Convert to string in hexadecimal format
    std::string toHex() ;


};
