#include "BlendMode.h"
#include "Pixel.h"

#include <iostream>

/* ~~~~~~~~~~~ Blending Modes ~~~~~~~~~~~ */
void BlendMode::Multiply(const Image& layerA, const Image& layerB, Image& layerC){
    // Multiplies the standardized (based on the domain 0...1) tonal values of the fore- and background's pixels. 

    for (int i = 0; i < layerC.GetPxAmount(); i++){
        float r = MultiplyCalc(layerA.GetPx(i)._normalR, layerB.GetPx(i)._normalR);
        float g = MultiplyCalc(layerA.GetPx(i)._normalG, layerB.GetPx(i)._normalG);
        float b = MultiplyCalc(layerA.GetPx(i)._normalB, layerB.GetPx(i)._normalB);

        Pixel::FormatFloatRGB(r,g, b);
        layerC.AddPx(r, g, b);
    }
}

void BlendMode::Subtract(const Image& layerA, const Image& layerB, Image& layerC){
    // Common mathematical subtraction. 
    for (int i = 0; i < layerC.GetPxAmount(); i++){
        float r = SubtractCalc(layerA.GetPx(i)._normalR, layerB.GetPx(i)._normalR);
        float g = SubtractCalc(layerA.GetPx(i)._normalG, layerB.GetPx(i)._normalG);
        float b = SubtractCalc(layerA.GetPx(i)._normalB, layerB.GetPx(i)._normalB);

        Pixel::FormatFloatRGB(r,g, b);
        layerC.AddPx(r, g, b);
    }
}

void BlendMode::Screen(const Image& layerA, const Image& layerB, Image& layerC){
    // The opposite of Multiply. Fore- and background are »negatively multiplied«. 
    for (int i = 0; i < layerC.GetPxAmount(); i++){
        float r = 1.0f - (ScreenCalc(layerA.GetPx(i)._normalR, layerB.GetPx(i)._normalR));
        float g = 1.0f - (ScreenCalc(layerA.GetPx(i)._normalG, layerB.GetPx(i)._normalG));
        float b = 1.0f - (ScreenCalc(layerA.GetPx(i)._normalB, layerB.GetPx(i)._normalB));

        Pixel::FormatFloatRGB(r,g, b);
        layerC.AddPx(r, g, b);
    }
} 

void BlendMode::Overlay(const Image& layerA, const Image& layerB, Image& layerC){
    // This mode is a combination of the modes Multiply and Screen, dependent on the background's tonal value. If the background is darker than 50% gray, the tonal values get multiplied, otherwise they get »screened« (and afterwards they are doubled in both cases). 

   for (int i = 0; i < layerC.GetPxAmount(); i++){
        float r = OverlayCalc(layerA.GetPx(i)._normalR, layerB.GetPx(i)._normalR);
        float g = OverlayCalc(layerA.GetPx(i)._normalG, layerB.GetPx(i)._normalG);
        float b = OverlayCalc(layerA.GetPx(i)._normalB, layerB.GetPx(i)._normalB);

        Pixel::FormatFloatRGB(r,g, b);
        layerC.AddPx(r, g, b);
    } 
}

void BlendMode::Greenify(const Image& layerA, Image& layerB){
    // Add 200 to tbe image's green channel.
    for (int i = 0; i < layerB.GetPxAmount(); i++){
        int G = (layerA.GetPx(i)._G) + 200;
        Pixel::Clamp(G);

        layerB.AddPx(layerA.GetPx(i)._R, G, layerA.GetPx(i)._B);
    } 
}

void BlendMode::ScaleRB(const Image& layerA, Image& layerB){
    // Scale the red channel by 4, and the blue channel by 0.
    for (int i = 0; i < layerB.GetPxAmount(); i++){
        float r = (layerA.GetPx(i)._normalR) * 4.0;
        Pixel::FormatFloat(r);

        layerB.AddPx((int)r, (int)layerA.GetPx(i)._G, 0);
    } 
}

void BlendMode::SplitColorChannels(const Image& layerRGB, Image& layerR, Image& layerG, Image& layerB){
    // Splits each color channel From A into different images.
    for (int i = 0; i < layerB.GetPxAmount(); i++){
        int R = (int)layerRGB.GetPx(i)._R;
        int G = (int)layerRGB.GetPx(i)._G;
        int B = (int)layerRGB.GetPx(i)._B;

        layerR.AddPx(R,R,R);
        layerG.AddPx(G,G,G);
        layerB.AddPx(B,B,B);
    } 
}

void BlendMode::CombineColorChannels(const Image& layerR, const Image& layerG, const Image& layerB, Image& layerRGB){
    // Combine RGB color channels from respective R,G,B layers into the RGB layer.
    for (int i = 0; i < layerB.GetPxAmount(); i++){
        int R = (int)layerR.GetPx(i)._R;
        int G = (int)layerG.GetPx(i)._G;
        int B = (int)layerB.GetPx(i)._B;

        layerRGB.AddPx(R,G,B);
    }  
}

void BlendMode::Rotate180(const Image& layerA, Image& layerB){
   for (int i = (layerB.GetPxAmount() - 1); i >= 0; i--){
        Pixel px = layerA.GetPx(i);
        layerB.AddPx(px);
    }   
}

void BlendMode::CombineImages(const Image& layerA, const Image& layerB, const Image& layerC, Image& layerD, Image& layerE){
    // A,B = top and C,D = bottom of image E
    Combine2Images(layerC, layerD, layerE); // draw lowerhalf image
    Combine2Images(layerA, layerB, layerE); // draw upperhalf image
}

/* ~~~~~~~~~~~ Helpers ~~~~~~~~~~~ */
float BlendMode::MultiplyCalc(const float& colorA, const float& colorB) const {
    // C = A * B
    return (colorA * colorB); 
}
float BlendMode::SubtractCalc(const float& colorA, const float& colorB) const {
    // C = B - A
    return (colorB - colorA); 
}

float BlendMode::ScreenCalc(const float& colorA, const float& colorB) const {
    // 1 - C = (1-A) * (1-B)
    return ((1.0f - colorA) * (1.0f - colorB));
}

float BlendMode::OverlayCalc(const float& colorA, const float& colorB) const {
    // B <= 0,5 : C = 2*A*B
    // B > 0,5 : C = 1-2*(1-A)*(1-B)

    if (colorB > 0.5f){ return (1.0f - (2.0f * ScreenCalc(colorA, colorB))); }
    return (MultiplyCalc(colorA, colorB) * 2.0f); 
}

void BlendMode::Combine2Images(const Image& inLayer1, const Image& inLayer2, Image& outLayer){
    int singleImgHeight = inLayer1.GetHeader().height;

    for (int i = 0; i < singleImgHeight; i++){ 
        for (int j = 0; j < outLayer.GetHeader().width; j++){
            if (j < singleImgHeight){ 
                outLayer.AddPx(inLayer1.GetPx(j + (singleImgHeight * i)));
                continue; 
            }
            outLayer.AddPx(inLayer2.GetPx(j + (singleImgHeight * (i-1))));
        }
   }
}