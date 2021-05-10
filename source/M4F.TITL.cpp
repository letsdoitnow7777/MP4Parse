#include "M4F.TITL.h"

using namespace MP4;
TITL::TITL()
{
    this->_type.append( "TITL" );
}

void TITL::processData(MP4::IBinaryStream * stream, size_t length ) {
//    DataAtom::processData(stream, length);
    for (int i = 0; i < length; i++) {
        uint8_t symbol = MP4::readUnsignedChar(stream);
        if (symbol != 0) {
            titl += (char)symbol;
        }
    }
}

std::string TITL::description()
{
    std::ostringstream o;
    std::string indent = countIndent();

    o << indent << this->_type << "(DataAtom)" << "[" << _dataLength << "bytes]" << " titl: " << titl << "\n";

    return o.str();
}

