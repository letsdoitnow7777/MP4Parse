
#ifndef _M4F_SegmentData_H_
#define _M4F_SegmentData_H_
#pragma once

#include "mp4.h"
#include "MP4.DataAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class SegmentData : DataAtom
    {
    private:
        u_int64_t segmentData[3];

    protected:


    public:
        SegmentData();

        void processData(MP4::IBinaryStream * stream, size_t length ) override;
        std::string description() override;
    };
}

#endif /* _M4F_SegmentData_H_ */
