#include "M4F.BTRT.h"
#include "include/M4F.BTRT.h"


using namespace MP4;
BTRT::BTRT()
{
    this->_type.append( "BTRT" );
}

void BTRT::processData(MP4::IBinaryStream * stream, size_t length ) {
    this->_dataLength = length;
    if (length != 8) {
        printf("bad value of bitrate! length %d\n", (int)length);
        exit(1);
    }
    bitrate = MP4::readUnsignedLong(stream);
//    stream->ignore(length);
}

std::string BTRT::description()
{
    std::ostringstream o;
    std::string indent = countIndent();

    o << indent << this->_type << "(DataAtom)" << "[" << _dataLength << "bytes]" << " bitrate: " << bitrate << "\n";

    return o.str();
}

