
#ifndef _M4F_TITL_H_
#define _M4F_TITL_H_
#pragma once

#include "mp4.h"
#include "MP4.DataAtom.h"
#include "MP4.BinaryStream.h"

namespace MP4
{
    class Title : DataAtom
    {
    private:
        std::string titl;

    protected:


    public:
        Title();

        void processData(MP4::IBinaryStream * stream, size_t length ) override;
        std::string description() override;
    };
}

#endif /* _M4F_TITL_H_ */
