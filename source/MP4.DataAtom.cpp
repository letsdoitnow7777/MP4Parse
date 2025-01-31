/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
 
/* $Id$ */

#include "MP4.DataAtom.h"
#ifdef __unix__
  #include <algorithm>
  #include <iomanip>
#endif

using namespace MP4;

std::string DataAtom::description()
{
    std::ostringstream o;
    std::string indent = countIndent();

    o << indent << this->_type << "(DataAtom)" << "[" << _size << "bytes]"  << "str: " << _data << "\n";

    return o.str();
}

static std::string ToHex(const char* s, int len, bool upper_case)
{
    std::ostringstream ret;

    for (std::string::size_type i = 0; i < len; ++i)
    {
        int z = s[i]&0xff;
        ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << z;
    }

    return ret.str();
}

void DataAtom::processData(MP4::IBinaryStream *stream, size_t length) {
    const int maxSizeWeWantToStore = 40;
    this->_size = length;
    this->_dataLength = length;
    char* buffer = new char[length];
    stream->read(buffer, length );
    int copyLength = std::min((int)length, maxSizeWeWantToStore);
    std::string hexBuf = ToHex(buffer, copyLength, true);
    printf("type %s process data: %d . data - %s\n", _type.c_str(), (int)length, hexBuf.c_str());

    _data = hexBuf;
    std::string strView;
    for (int i = 0; i < copyLength; i++) {
        uint8_t symbol = buffer[i];
        if (symbol != 0) {
            strView += (char)symbol;
        }
    }
    printf("                     string data - %s\n", strView.c_str());

}
