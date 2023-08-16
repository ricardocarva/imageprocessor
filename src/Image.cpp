#include <fstream>
#include <stdexcept>
#include <iostream>

#include "Image.h"

using namespace std;

 /* ~~~~~~~~~~~ Construction / Destruction ~~~~~~~~~~~ */
Image::Image(){ _pxamount = 0; }

Image::Image(const string filename){
    ifstream file(filename, ios_base::binary);

    if (file.is_open()){
        Read(file);
        file.close();
    } else {
        throw runtime_error("Error: Unable to open " + filename);
    }
}

Image::Image(const Image& rhs){ CopyToThis(rhs); }

Image::Image(const Header& header){
     _header = header;
     _pxamount = header.width * header.height;
}

Image::~Image(){}

/* ~~~~~~~~~~~ Operators ~~~~~~~~~~~ */
Image& Image::operator=(const Image& rhs) {
    if (this != &rhs){

        _header = {0,0,2,0,0,0,0,0,0,0,24,0};
        _pixels.clear();
        _pixels.shrink_to_fit(); 
        _pxamount = 0;

        CopyToThis(rhs);
    }

    return *this;
}

bool Image::operator==(const Image& rhs) const {
    if(!(_header == rhs._header)) { return false; }

    for (unsigned int i = 0; i < rhs._pxamount; i++ ){
        if (!(_pixels[i] == rhs._pixels[i])){
            cout << "Goal R: " << (int)_pixels[i]._R << " G: " << (int)_pixels[i]._G << " B: " << (int)_pixels[i]._B << endl;
            cout << "Res R: " << (int)rhs._pixels[i]._R << " G: " << (int)rhs._pixels[i]._G << " B: " << (int)rhs._pixels[i]._B << endl;

            cout << "pos: " << i << endl;
            
            return false;
        } 
    } 

    return true;
}

/* ~~~~~~~~~~~ Accessors / Mutators ~~~~~~~~~~~ */ 
Header Image::GetHeader() const {
    return _header;
}

Pixel Image::GetPx(const int i) const {
    return _pixels[i];
}

int Image::GetPxAmount() const {
    return _pxamount;
}

void Image::AddPx(const Pixel px){ _pixels.push_back(px); }

void Image::AddPx(const int& R, const int& G, const int& B){
    Pixel px((unsigned char)R, (unsigned char)G, (unsigned char)B);
    _pixels.push_back(px);
}

void Image::AddPx(const float& R, const float& G, const float& B){
    Pixel px((unsigned char)R, (unsigned char)G, (unsigned char)B);
    _pixels.push_back(px);
}

void Image::SetDimensions(const short& height, const short& width){
    _header.width = width;
    _header.height = height;
    _pxamount = height * width;
}

/* ~~~~~~~~~~~ IO ~~~~~~~~~~~ */ 
void Image::Read(ifstream& file){
    ReadHeader(file);
    _pxamount = _header.width * _header.height;
    ReadPixels(file);
}

void Image::ReadHeader(ifstream& file){
    file.read(&_header.idLength, sizeof(_header.idLength));
    file.read(&_header.colorMapType, sizeof(_header.colorMapType));
    file.read(&_header.dataTypeCode, sizeof(_header.dataTypeCode));
    file.read((char*)&_header.colorMapOrigin, sizeof(_header.colorMapOrigin));
    file.read((char*)&_header.colorMapLength, sizeof(_header.colorMapLength));
    file.read(&_header.colorMapDepth, sizeof(_header.colorMapDepth));
    file.read((char*)&_header.xOrigin, sizeof(_header.xOrigin));
    file.read((char*)&_header.yOrigin, sizeof(_header.yOrigin));
    file.read((char*)&_header.width, sizeof(_header.width));
    file.read((char*)&_header.height, sizeof(_header.height));
    file.read(&_header.bitsPerPixel, sizeof(_header.bitsPerPixel));
    file.read(&_header.imageDescriptor, sizeof(_header.imageDescriptor));
}

void Image::ReadPixels(ifstream& file){
    // Read file in order B-G-R (TGA structure)
    int i = 0;
    
    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;

    while (i < _pxamount){
        file.read((char*)&blue, sizeof(blue));
        file.read((char*)&green, sizeof(green));
        file.read((char*)&red, sizeof(red));

        Pixel px(red, green, blue);
        _pixels.push_back(px);
        i++;
    }
}

void Image::Write(const string filename){
    ofstream file(filename, ios_base::binary);

    WriteHeader(file);
    WritePixels(file);

    file.close();
}

void Image::WriteHeader(ofstream& file){
    file.write(&_header.idLength, sizeof(_header.idLength));
    file.write(&_header.colorMapType, sizeof(_header.colorMapType));
    file.write(&_header.dataTypeCode, sizeof(_header.dataTypeCode));
    file.write((char*)&_header.colorMapOrigin, sizeof(_header.colorMapOrigin));
    file.write((char*)&_header.colorMapLength, sizeof(_header.colorMapLength));
    file.write(&_header.colorMapDepth, sizeof(_header.colorMapDepth));
    file.write((char*)&_header.xOrigin, sizeof(_header.xOrigin));
    file.write((char*)&_header.yOrigin, sizeof(_header.yOrigin));
    file.write((char*)&_header.width, sizeof(_header.width));
    file.write((char*)&_header.height, sizeof(_header.height));
    file.write(&_header.bitsPerPixel, sizeof(_header.bitsPerPixel));
    file.write(&_header.imageDescriptor, sizeof(_header.imageDescriptor));
}

void Image::WritePixels(ofstream& file){
    // Write file in order B-G-R (TGA structure)
    for (int i = 0; i < _pxamount; i++){
        file.write((char*)&_pixels[i]._B, sizeof(_pixels[i]._B));
        file.write((char*)&_pixels[i]._G, sizeof(_pixels[i]._G));
        file.write((char*)&_pixels[i]._R, sizeof(_pixels[i]._R));
    }
}

/* ~~~~~~~~~~~ Helpers ~~~~~~~~~~~ */ 
void Image::CopyToThis(const Image& rhs){
    _header = rhs._header;
    _pxamount = rhs._pxamount;

    if (rhs._pixels.size() > 0){
        for (int i = 0; i < _pxamount; i++ ){
        _pixels.push_back(rhs._pixels[i]);
    }
    }
}