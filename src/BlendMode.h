#pragma once

#include "Image.h"

class BlendMode{
    // Blendmode is a collection of functions to perform image manipulations.
    // Tonal values are normalized to a range (0-1) in calculations.
    // Blending modes involving more than one image assume all have the same dimensions (width x height)
    // Source of standard mode descriptions and formulae: http://www.simplefilter.de/en/basics/mixmods.html

    protected:
        /* ~~~~~~~~~~~ Blending Modes ~~~~~~~~~~~ */
        void Multiply(const Image& layerA, const Image& layerB, Image& layerC);
        void Subtract(const Image& layerA, const Image& layerB, Image& layerC);
        void Screen(const Image& layerA, const Image& layerB, Image& layerC);
        void Overlay(const Image& layerA, const Image& layerB, Image& layerC);
        void Greenify(const Image& layerA, Image& layerB);
        void ScaleRB(const Image& layerA, Image& layerB);
        void SplitColorChannels(const Image& layer, Image& layerR, Image& layerG, Image& layerB);
        void CombineColorChannels(const Image& layerR, const Image& layerG, const Image& layerB, Image& layer);
        void Rotate180(const Image& layerA, Image& layerB);
        void CombineImages(const Image& layerA, const Image& layerB, const Image& layerC, Image& layerD, Image& layerE);

        /* ~~~~~~~~~~~ Helpers ~~~~~~~~~~~ */
        float MultiplyCalc(const float& colorA, const float& colorB) const;
        float SubtractCalc(const float& colorA, const float& colorB) const;
        float ScreenCalc(const float& colorA, const float& colorB) const;
        float OverlayCalc(const float& colorA, const float& colorB) const;
        void Combine2Images(const Image& layerA, const Image& layerB, Image& layerE);
};