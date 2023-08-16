#include "Pixel.h"

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue)
: _R(red), _G(green), _B(blue), _normalR((int)red/255.0f), _normalG((int)green/255.0f), _normalB((int)blue/255.0f) 
{}

bool Pixel::operator==(const Pixel& rhs) const {
    return (_R == rhs._R) && (_G == rhs._G) && (_B == rhs._B);
}

void Pixel::Clamp(float& value){
    // Ensures tone value is within range 0-1.
    if (value > 1.0f){ value = 1.0f; }
    if (value < 0.0f){ value = 0.0f; }
}

void Pixel::Clamp(int& value){
    // Ensures tone value is within range 0-255.
    if (value > 255){ value = 255; }
    if (value < 0){ value = 0; }
}

void Pixel::NormalToRaw(float& value){
    // Converts normalized value to range 0-255.
    // Add 0.5f to account for float-point precision issues with truncating when typecasting.
    value = (value * 255.0f) + 0.5f;
}

void Pixel::FormatFloat(float& value){
    // Converts normal referenced tone back to 0-255 range.
    Clamp(value);
    NormalToRaw(value);
}

void Pixel::FormatFloatRGB(float& r, float& g, float& b){
    // Converts normalized rgb referenced tones back to 0-255 range.
    Clamp(r);
    NormalToRaw(r);

    Clamp(g);
    NormalToRaw(g);

    Clamp(b);
    NormalToRaw(b);
}
