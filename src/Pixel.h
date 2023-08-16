#pragma once

struct Pixel{
    // Blueprint for an image's pixel.
    unsigned char _R;
    unsigned char _G;
    unsigned char _B;

    // tone values normalized to range 0-1.
    float _normalR;
    float _normalG;
    float _normalB;

    Pixel(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0);
    bool operator==(const Pixel& rhs) const;

    static void Clamp(float& value);
    static void Clamp(int& value);
    static void NormalToRaw(float& value);
    static void FormatFloat(float& value); 
    static void FormatFloatRGB(float& r, float& g, float& b);
};