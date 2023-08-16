#include "Header.h"

Header::Header(
    char  _idLength,
    char  _colorMapType,
    char  _dataTypeCode,
    short _colorMapOrigin,
    short _colorMapLength,
    char  _colorMapDepth,
    short _xOrigin,
    short _yOrigin,
    short _width,
    short _height,
    char  _bitsPerPixel,
    char  _imageDescriptor
) : idLength(_idLength),
    colorMapType(_colorMapType),
    dataTypeCode(_dataTypeCode),
    colorMapOrigin(_colorMapOrigin),
    colorMapLength(_colorMapLength),
    colorMapDepth(_colorMapDepth),
    xOrigin(_xOrigin),
    yOrigin(_yOrigin),
    width(_width),
    height(_height),
    bitsPerPixel(_bitsPerPixel),
    imageDescriptor(_imageDescriptor)
    {}

bool Header::operator==(const Header& rhs) const {
    return (( idLength == rhs.idLength ) 
            && ( colorMapType == rhs.colorMapType ) 
            && ( dataTypeCode == rhs.dataTypeCode )
            && ( colorMapOrigin == rhs.colorMapOrigin )
            && ( colorMapLength == rhs.colorMapLength )
            && ( colorMapDepth == rhs.colorMapDepth )
            && ( xOrigin == rhs.xOrigin )
            && ( yOrigin == rhs.yOrigin )
            && ( width == rhs.width )
            && ( height == rhs.height )
            && ( bitsPerPixel == rhs.bitsPerPixel )
            && ( imageDescriptor == rhs.imageDescriptor ));
}