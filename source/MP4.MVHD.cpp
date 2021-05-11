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

#include "MP4.MVHD.h"

using namespace MP4;
          
MVHD::MVHD()
{
    this->_type.append( "MVHD" );
}

void MVHD::processData(MP4::IBinaryStream * stream, size_t length )
{
    FullBox::processData( stream, length );
    
    if( this->_version == 1 )
    {
        this->_creationTime     = MP4::readBigEndianUnsignedLong(stream);
        this->_modificationTime = MP4::readBigEndianUnsignedLong(stream);
        this->_timeScale        = MP4::readBigEndianUnsignedInteger(stream);
        this->_duration         = MP4::readBigEndianUnsignedLong(stream);
        this->_rate             = MP4::readBigEndianFixedPoint(stream, 16, 16 );
        this->_volume           = MP4::readBigEndianFixedPoint(stream, 8, 8 );
        
        stream->ignore( 10 );
        MP4::readMatrix(stream, &( this->_matrix ) );
        stream->ignore( 24 );
        
        this->_nextTrackId = MP4::readBigEndianUnsignedInteger(stream);
    }
    else
    {
        this->_creationTime     = MP4::readBigEndianUnsignedInteger(stream);
        this->_modificationTime = MP4::readBigEndianUnsignedInteger(stream);
        this->_timeScale        = MP4::readBigEndianUnsignedInteger(stream);
        this->_duration         = MP4::readBigEndianUnsignedInteger(stream);
        this->_rate             = MP4::readBigEndianFixedPoint(stream, 16, 16 );
        this->_volume           = MP4::readBigEndianFixedPoint(stream, 8, 8 );
        
        stream->ignore( 10 );
        MP4::readMatrix(stream, &( this->_matrix ) );
        stream->ignore( 24 );
        
        this->_nextTrackId = MP4::readBigEndianUnsignedInteger(stream);
    }
}

std::string MVHD::description() {
    std::stringstream ss;
    ss << "_creationTime    : " << this->_creationTime     << "\t";
    ss << "_modificationTime: " << this->_modificationTime << "\t";
    ss << "_timeScale       : " << this->_timeScale        << "\t";
    ss << "_duration        : " << this->_duration         << "\t";
    ss << "_rate            : " << this->_rate             << "\t";
    ss << "_volume          : " << this->_volume           << "\n";
    return DataAtom::description();
}
