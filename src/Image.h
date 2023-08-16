#pragma once
#include <vector>

#include "Header.h"
#include "Pixel.h"
#include <string>
class Image {
    // Blueprint of a .TGA Image and its functionality.
    private:
        Header _header;
        vector<Pixel> _pixels;
        int _pxamount;

    public:
        /* ~~~~~~~~~~~ Construction / Destruction~~~~~~~~~~~ */
        Image();
        Image(const string filename); 
        Image(const Image& img);
        Image(const Header& header);
        ~Image();

        /* ~~~~~~~~~~~ Operators ~~~~~~~~~~~ */
        bool operator==(const Image& rhs) const;
        Image& operator=(const Image& rhs);

        /* ~~~~~~~~~~~ Accessors / Mutators ~~~~~~~~~~~ */  
        Header GetHeader() const;
        Pixel GetPx(const int i) const;
        int GetPxAmount() const;

        void AddPx(const Pixel px);
        void AddPx(const int& R, const int& G, const int& B);
        void AddPx(const float& R, const float& G, const float& B);
        void SetDimensions(const short& height, const short& width); 

        /* ~~~~~~~~~~~ IO ~~~~~~~~~~~ */  
        void Read(ifstream& file);
        void ReadHeader(ifstream& file);
        void ReadPixels(ifstream& file);

        void Write(const string filename);
        void WriteHeader(ofstream& file);
        void WritePixels(ofstream& file);

        /* ~~~~~~~~~~~ Helpers ~~~~~~~~~~~ */  
        void CopyToThis(const Image& rhs);
};
