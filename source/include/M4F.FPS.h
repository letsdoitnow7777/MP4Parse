
#ifndef _M4F_FPS_H_
#define _M4F_FPS_H_
#pragma once

#include "mp4.h"
#include "MP4.DataAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class FPS : DataAtom
    {
    private:
        int64_t fps; // fps in kb/s

    protected:


    public:
        FPS();

        void processData(MP4::IBinaryStream * stream, size_t length ) override;
        std::string description() override;
    };
}

#endif /* _M4F_FPS_H_ */
