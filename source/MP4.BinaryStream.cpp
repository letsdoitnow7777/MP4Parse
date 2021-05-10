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

#include "MP4.BinaryStream.h"

namespace MP4{
    BinaryStream::BinaryStream(char * filename )
    {
        this->stream.open( filename, std::ios::binary | std::ios::in );

        if( this->stream.is_open() == false || this->stream.good() == false )
        {
            std::cout << "Failed to make binary stream" << std::endl;
        }
    }

    BinaryStream::~BinaryStream(void )
    {
        if( this->stream.is_open() )
        {
            this->stream.close();
        }
    }

    uint8_t readUnsignedChar(IBinaryStream *s)
    {
        uint8_t n;

        s->read( ( char * )&n, 1 );

        return n;
    }


    int8_t readSignedChar(IBinaryStream *s)
    {
        int8_t n;

        s->read( ( char * )&n, 1 );

        return n;
    }


    uint16_t readUnsignedShort(IBinaryStream *s  )
    {
        uint16_t n;

        s->read( ( char * )&n, 2 );

        return n;
    }

    int16_t readSignedShort(IBinaryStream *s  )
    {
        int16_t n;

        s->read( ( char * )&n, 2 );

        return n;
    }

    uint16_t readBigEndianUnsignedShort(IBinaryStream *s)
    {
        uint8_t  c[ 2 ];
        uint16_t n;

        s->read( ( char * )c, 2 );

        n = ( uint16_t )c[ 0 ] << 8
            | ( uint16_t )c[ 1 ];

        return n;
    }

    uint16_t readLittleEndianUnsignedShort(IBinaryStream *s)
    {
        uint8_t  c[ 2 ];
        uint16_t n;

        s->read( ( char * )c, 2 );

        n = ( uint16_t )c[ 1 ] << 8
            | ( uint16_t )c[ 0 ];

        return n;
    }


    uint32_t readUnsignedInteger(IBinaryStream *s  )
    {
        uint32_t n;

        s->read( ( char * )&n, 4 );

        return n;
    }

    int32_t readSignedInteger(IBinaryStream *s)
    {
        int32_t n;

        s->read( ( char * )&n, 4 );

        return n;
    }

    uint32_t readBigEndianUnsignedInteger(IBinaryStream *s)
    {
        uint8_t  c[ 4 ];
        uint32_t n;

        s->read( ( char * )c, 4 );

        n = ( uint32_t )c[ 0 ] << 24
            | ( uint32_t )c[ 1 ] << 16
            | ( uint32_t )c[ 2 ] << 8
            | ( uint32_t )c[ 3 ];

        return n;
    }

    uint32_t readLittleEndianUnsignedInteger(IBinaryStream *s)
    {
        uint8_t  c[ 4 ];
        uint32_t n;

        s->read( ( char * )c, 4 );

        n = ( uint32_t )c[ 3 ] << 24
            | ( uint32_t )c[ 2 ] << 16
            | ( uint32_t )c[ 1 ] << 8
            | ( uint32_t )c[ 0 ];

        return n;
    }


    uint64_t readUnsignedLong(IBinaryStream *s)
    {
        uint64_t n;

        s->read( ( char * )&n, 8 );

        return n;
    }

    int64_t readSignedLong(IBinaryStream *s)
    {
        int64_t n;

        s->read( ( char * )&n, 8 );

        return n;
    }

    uint64_t readBigEndianUnsignedLong(IBinaryStream *s)
    {
        uint8_t  c[ 8 ];
        uint64_t n;

        s->read( ( char * )c, 8 );

        n = ( uint64_t )c[ 0 ] << 56
            | ( uint64_t )c[ 1 ] << 48
            | ( uint64_t )c[ 2 ] << 40
            | ( uint64_t )c[ 3 ] << 32
            | ( uint64_t )c[ 4 ] << 24
            | ( uint64_t )c[ 5 ] << 16
            | ( uint64_t )c[ 6 ] << 8
            | ( uint64_t )c[ 7 ];

        return n;
    }

    uint64_t readLittleEndianUnsignedLong(IBinaryStream *s)
    {
        uint8_t  c[ 8 ];
        uint64_t n;

        s->read( ( char * )c, 8 );

        n = ( uint64_t )c[ 7 ] << 56
            | ( uint64_t )c[ 6 ] << 48
            | ( uint64_t )c[ 5 ] << 40
            | ( uint64_t )c[ 4 ] << 32
            | ( uint64_t )c[ 3 ] << 24
            | ( uint64_t )c[ 2 ] << 16
            | ( uint64_t )c[ 1 ] << 8
            | ( uint64_t )c[ 0 ];

        return n;
    }

    float readFloat(IBinaryStream *s  )
    {
        uint8_t  exp;
        uint32_t mantissa;
        uint32_t binary;
        float    flt;
        bool     sign;
        int      i;

        binary   = MP4::readBigEndianUnsignedInteger(s);
        sign     = binary >> 31;
        exp      = ( ( binary >> 23 ) & 0xFF );
        mantissa = ( binary & 0x7FFFFF );

        if( exp == 0 && mantissa == 0 )
        {
            return 0;
        }
        else if( exp == 255 && mantissa == 0 )
        {
            return ( sign == 0 ) ? INFINITY : -INFINITY;
        }
        else if( exp == 255 && mantissa != 0 )
        {
            return NAN;
        }
        else if( exp == 0 && mantissa != 0 )
        {
            exp = -126;
        }
        else
        {
            exp      = exp - 127;
            mantissa = mantissa | 0x800000;
        }

        flt = 0;

        for( i = 0; i > -24; i-- )
        {
            if( mantissa & ( 1 << ( i + 23 ) ) )
            {
                flt += pow( 2, i + exp );
            }
        }

        return ( sign == 0 ) ? flt : -flt;
    }

    double readDouble(IBinaryStream *s )
    {
        uint16_t  exp;
        uint64_t mantissa;
        uint64_t binary;
        float    flt;
        bool     sign;
        int      i;

        binary   = MP4::readBigEndianUnsignedLong(s);
        sign     = binary >> 63;
        exp      = ( ( binary >> 52 ) & 0x7FF );
        mantissa = ( binary & 0xFFFFFFFFFFFFF );

        if( exp == 0 && mantissa == 0 )
        {
            return 0;
        }
        else if( exp == 0x7FF && mantissa == 0 )
        {
            return ( sign == 0 ) ? INFINITY : -INFINITY;
        }
        else if( exp == 0x7FF && mantissa != 0 )
        {
            return NAN;
        }
        else
        {
            exp = exp - 1023;
        }

        flt = 0;

        for( i = 0; i > -24; i-- )
        {
            if( mantissa & ( 1 << ( i + 23 ) ) )
            {
                flt += pow( 2, i + exp );
            }
        }

        return ( sign == 0 ) ? flt : -flt;
    }


    float readBigEndianFixedPoint(IBinaryStream *s, unsigned int integerLength, unsigned int fractionalLength)
    {
        uint32_t n;
        unsigned int integer;
        unsigned int fractionalMask;
        unsigned int fractional;

        if( integerLength + fractionalLength == 16 )
        {
            n = readBigEndianUnsignedShort(s);
        }
        else
        {
            n = MP4::readBigEndianUnsignedInteger(s);
        }

        integer        = n >> fractionalLength;
        fractionalMask = pow( 2, fractionalLength ) - 1;
        fractional     = ( n & fractionalMask ) / ( 1 << fractionalLength );

        return integer + fractional;
    }

    float readLittleEndianFixedPoint(IBinaryStream *s, unsigned int integerLength, unsigned int fractionalLength)
    {
        uint32_t n;
        unsigned int integer;
        unsigned int fractionalMask;
        unsigned int fractional;

        if( integerLength + fractionalLength == 16 )
        {
            n = MP4::readLittleEndianUnsignedShort(s);
        }
        else
        {
            n = MP4::readLittleEndianUnsignedInteger(s);
        }

        integer        = n >> fractionalLength;
        fractionalMask = pow( 2, fractionalLength ) - 1;
        fractional     = ( n & fractionalMask ) / ( 1 << fractionalLength );

        return integer + fractional;
    }

    std::string *readBigEndianISO639Code(IBinaryStream *s)
    {
        unsigned char c1;
        unsigned char c2;
        unsigned char c3;
        uint16_t      n;
        std::string * str;

        str = new std::string();
        n = readBigEndianUnsignedShort(s);

        c1 = ( n & 0x7C00 ) >> 10;  // Mask is 0111 1100 0000 0000
        c2 = ( n & 0x03E0 ) >> 5;   // Mask is 0000 0011 1110 0000
        c3 = ( n & 0x001F );        // Mask is 0000 0000 0001 1111

        c1 += 0x60;
        c2 += 0x60;
        c3 += 0x60;

        str->append(( char * )&c1, 1 );
        str->append(( char * )&c2, 1 );
        str->append(( char * )&c3, 1 );

        return str;
    }

    std::string * readNULLTerminatedString(IBinaryStream *s)
    {
        unsigned char c;
        std::string * str;

        s->get( ( char * )&c, 1 );

        str = new std::string;

        while( c != 0 )
        {
            str->append(1, c );

            s->get( ( char * )&c, 1 );
        }

        return str;
    }

    std::string *readUTF8String(IBinaryStream *st)
    {
        unsigned char c;
        uint16_t      length;
        uint16_t      i;
        std::string * s;

        length = readBigEndianUnsignedShort(st);
        s      = new std::string;

        for( i = 0; i < length; i++ )
        {
            st->get( ( char * )&c, 1 );
            s->append( 1, c );
        }

        return nullptr;
    }

    std::string *readLongUTF8String(IBinaryStream *st)
    {
        unsigned char c;
        uint32_t      length;
        uint32_t      i;
        std::string * s;

        length = MP4::readBigEndianUnsignedInteger(st);
        s      = new std::string;

        for( i = 0; i < length; i++ )
        {
            st->get( ( char * )&c, 1 );
            s->append( 1, c );
        }

        return nullptr;
    }

    void readMatrix(IBinaryStream *s, matrix *m)
    {
        m->a = MP4::readBigEndianFixedPoint(s,  16, 16 );
        m->b = MP4::readBigEndianFixedPoint(s,  16, 16 );
        m->u = MP4::readBigEndianFixedPoint(s,   2, 30 );
        m->c = MP4::readBigEndianFixedPoint(s,  16, 16 );
        m->d = MP4::readBigEndianFixedPoint(s,  16, 16 );
        m->v = MP4::readBigEndianFixedPoint(s,   2, 30 );
        m->x = MP4::readBigEndianFixedPoint(s,  16, 16 );
        m->y = MP4::readBigEndianFixedPoint(s,  16, 16 );
        m->w = MP4::readBigEndianFixedPoint(s,   2, 30 );
    }

    bool BinaryStream::good() const
    {
        return stream.good();
    }

    bool BinaryStream::eof() const
    {
        return stream.eof();
    }

    bool BinaryStream::fail() const
    {
        return stream.fail();
    }

    bool BinaryStream::bad() const
    {
        return stream.bad();
    }

    int BinaryStream::peek()
    {
        return stream.peek();
    }

    int BinaryStream::get()
    {
        return stream.get();
    }

    int BinaryStream::sync()
    {
        return stream.sync();
    }

    std::streampos BinaryStream::tellg()
    {
        return stream.tellg();
    }

    std::streamsize BinaryStream::readsome(char * s, std::streamsize n )
    {
        return stream.readsome( s, n );
    }

    std::streamsize BinaryStream::gcount() const
    {
        return stream.gcount();
    }

    std::istream & BinaryStream::get(char & c )
    {
        return stream.get( c );
    }

    std::istream & BinaryStream::get(char * s, std::streamsize n )
    {
        return stream.get( s, n );
    }

    std::istream & BinaryStream::get(char * s, std::streamsize n, char delim )
    {
        return stream.get( s, n, delim );
    }

    std::istream & BinaryStream::get(std::streambuf & sb )
    {
        return stream.get( sb );
    }

    std::istream & BinaryStream::get(std::streambuf & sb, char delim )
    {
        return stream.get( sb, delim );
    }

    std::istream & BinaryStream::getline(char * s, std::streamsize n )
    {
        return stream.getline( s, n );
    }

    std::istream & BinaryStream::getline(char * s, std::streamsize n, char delim )
    {
        return stream.getline( s, n, delim );
    }

    std::istream & BinaryStream::ignore(std::streamsize n, int delim )
    {
        return stream.ignore( n, delim );
    }

    std::istream & BinaryStream::read(char * s, std::streamsize n )
    {
        return stream.read( s, n );
    }

    std::istream & BinaryStream::putback(char c )
    {
        return stream.putback( c );
    }

    std::istream & BinaryStream::unget()
    {
        return stream.unget();
    }

    std::istream & BinaryStream::seekg(std::streampos pos )
    {
        return stream.seekg( pos );
    }

    std::istream & BinaryStream::seekg(std::streamoff off, std::ios_base::seekdir dir )
    {
        return stream.seekg( off, dir );
    }

    void BinaryStream::clear()
    {
        return stream.clear();
    }


    BinaryStreamBounded::BinaryStreamBounded(IBinaryStream *binaryStream, int len)
            : underlyingStream(binaryStream)
            , length(len)
            , availableBytes(len)
    {

    }

    bool BinaryStreamBounded::eof() const
    {
//        printf("available %d\n", availableBytes);
        return availableBytes == 0 || underlyingStream->eof();
    }

    std::istream & BinaryStreamBounded::get(char * s, std::streamsize n )
    {
        int bytesToReturn = std::min(n, long(availableBytes));
//        printf("get %10d, available %10d, returned %10d\n", (int)n, availableBytes, bytesToReturn);
        availableBytes -= bytesToReturn;

        return underlyingStream->get(s, bytesToReturn);
    }

    std::istream & BinaryStreamBounded::ignore(std::streamsize n, int delim )
    {
        int bytesToReturn = std::min(n, long(availableBytes));
//        printf("ignored %10d, available %10d, returned %10d\n", (int)n, availableBytes, bytesToReturn);
        availableBytes -= bytesToReturn;

        return underlyingStream->ignore( bytesToReturn, delim );
    }

    std::istream & BinaryStreamBounded::read(char * s, std::streamsize n )
    {
        int bytesToReturn = std::min(n, long(availableBytes));
//        printf("read %10d, available %10d, returned %10d\n", (int)n, availableBytes, bytesToReturn);
        availableBytes -= bytesToReturn;

        return underlyingStream->read( s, bytesToReturn );
    }
}
