#include "M4F.SegmentData.h"

using namespace MP4;
SegmentData::SegmentData()
{
    this->_type.append( "SEGM" );
}

void SegmentData::processData(MP4::IBinaryStream * stream, size_t length ) {
    this->_dataLength = length;
    if (length != 24) {
        printf("bad value of SEGM( 3 longs length %d\n", (int)length);
        exit(1);
    }
    segmentData[0] = MP4::readBigEndianUnsignedLong(stream);
    segmentData[1] = MP4::readBigEndianUnsignedLong(stream);
    segmentData[2] = MP4::readBigEndianUnsignedLong(stream);
//    std::cout << "parsing TYPE tag. " << "int1: " << segmentData[0] << "    int2: " << segmentData[1] << " int3: " << segmentData[2] << "\n";
}

std::string SegmentData::description()
{
    std::ostringstream o;
    std::string indent = countIndent();

    o << indent << this->_type << "(DataAtom)" << "[" << _dataLength << "bytes]" << \
     " segmentData0: " << segmentData[0] << "\t" \
     " segmentData1: " << segmentData[1] << "\t" \
     " segmentData2: " << segmentData[2] << "\t" \
     << "\n";

    return o.str();
}

