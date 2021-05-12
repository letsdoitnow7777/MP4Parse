#include "M4F.FpsRational.h"

using namespace MP4;
FpsRational::FpsRational()
{
    this->_type.append( "FPSR" );
}

void FpsRational::processData(MP4::IBinaryStream * stream, size_t length ) {
    this->_dataLength = length;
    if (length != 8) {
        printf("bad value of fps(rational! length %d\n", (int)length);
        exit(1);
    }
    int fpsRationalUpper = MP4::readBigEndianUnsignedInteger(stream);  // 32 bit, 4 bytes
    int fpsRationalDowner = MP4::readBigEndianUnsignedInteger(stream); // 32 bit, 4 bytes
    fpsRational = fpsRationalUpper/fpsRationalDowner;
}

std::string FpsRational::description()
{
    std::ostringstream o;
    std::string indent = countIndent();

    o << indent << this->_type << "(DataAtom)" << "[" << _dataLength << "bytes]" << " fpsRational: " << fpsRational << "\n";

    return o.str();
}

