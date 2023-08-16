#pragma once

using namespace std;

struct Header{
    // Blueprint for an image's header. 
    char  idLength;
    char  colorMapType;
    char  dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char  bitsPerPixel;
    char  imageDescriptor;

    Header(
        char  idLength = 0,
        char  colorMapType = 0,
        char  dataTypeCode = 2, // uncompressed true-color image
        short colorMapOrigin = 0,
        short colorMapLength = 0,
        char  colorMapDepth = 0,
        short xOrigin = 0,
        short yOrigin = 0,
        short width = 0,
        short height = 0,
        char  bitsPerPixel = 24,
        char  imageDescriptor = 0
    );

    bool operator==(const Header& rhs) const;
};
