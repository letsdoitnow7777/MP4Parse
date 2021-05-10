#include "M4F.FPS.h"

using namespace MP4;
FPS::FPS()
{
    this->_type.append( "FPS" );
}

void FPS::processData(MP4::IBinaryStream * stream, size_t length ) {
    this->_dataLength = length;
    if (length != 8) {
        printf("bad value of fps! length %d\n", (int)length);
        exit(1);
    }
    fps = MP4::readBigEndianUnsignedLong(stream);
}

std::string FPS::description()
{
    std::ostringstream o;
    std::string indent = countIndent();

    o << indent << this->_type << "(DataAtom)" << "[" << _dataLength << "bytes]" << " fps: " << fps << "\n";

    return o.str();
}

