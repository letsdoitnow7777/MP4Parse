
#ifndef _M4F_BTRT_H_
#define _M4F_BTRT_H_
#pragma once

#include "mp4.h"
#include "MP4.DataAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class BTRT : DataAtom
    {
    private:
        uint64_t bitrate;


    protected:


    public:
        BTRT();

        void processData(MP4::IBinaryStream * stream, size_t length ) override;
        std::string description() override;
    };
}

#endif /* _M4F_BTRT_H_ */
