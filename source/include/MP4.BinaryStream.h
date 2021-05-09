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

#ifndef _MP4_BINARY_STREAM_
#pragma once
#define _MP4_BINARY_STREAM_

#include "mp4.h"

namespace MP4
{

    class IBinaryStream {
    public:
        virtual uint16_t readBigEndianUnsignedShort() = 0;
        virtual uint16_t readLittleEndianUnsignedShort() = 0;

        virtual uint32_t readBigEndianUnsignedInteger() = 0;
        virtual uint32_t readLittleEndianUnsignedInteger() = 0;

        virtual uint64_t readBigEndianUnsignedLong() = 0;

        virtual float readBigEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength ) = 0;

        virtual std::string * readBigEndianISO639Code() = 0;

        virtual void readMatrix( matrix * m ) = 0;

        virtual bool eof() const = 0;
        virtual std::istream & get( char * s, std::streamsize n ) = 0;
        virtual std::istream & ignore( std::streamsize n = 1, int delim = EOF ) = 0;
        virtual std::istream & read( char * s, std::streamsize n ) = 0;
    };

    class BinaryStream: public IBinaryStream
    {
    private:

    protected:
        std::ifstream stream;

    public:
        explicit BinaryStream(char * filename );
        virtual ~BinaryStream();

        uint8_t readUnsignedChar();
        int8_t readSignedChar();

        uint16_t readUnsignedShort();
        int16_t readSignedShort();
        uint16_t readBigEndianUnsignedShort() override;
        uint16_t readLittleEndianUnsignedShort() override;

        uint32_t readUnsignedInteger();
        int32_t readSignedInteger();
        uint32_t readBigEndianUnsignedInteger() override;
        uint32_t readLittleEndianUnsignedInteger() override;

        uint64_t readUnsignedLong();
        int64_t readSignedLong();
        uint64_t readBigEndianUnsignedLong() override;
        uint64_t readLittleEndianUnsignedLong();

        float readFloat();
        double readDouble();

        float readBigEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength ) override;
        float readLittleEndianFixedPoint( unsigned int integerLength, unsigned int fractionalLength );

        std::string * readBigEndianISO639Code() override;
        std::string * readNULLTerminatedString();
        std::string * readUTF8String();
        std::string * readLongUTF8String();

        void readMatrix( matrix * m ) override;

        bool good() const;
        bool eof() const override;
        bool fail() const;
        bool bad() const;
        int peek();
        int get();
        int sync();
        std::streampos tellg();
        std::streamsize readsome( char * s, std::streamsize n );
        std::streamsize gcount() const;
        std::istream & get( char & c );
        std::istream & get( char * s, std::streamsize n ) override;
        std::istream & get( char * s, std::streamsize n, char delim );
        std::istream & get( std::streambuf & sb );
        std::istream & get( std::streambuf & sb, char delim );
        std::istream & getline(char * s, std::streamsize n );
        std::istream & getline(char * s, std::streamsize n, char delim );
        std::istream & ignore( std::streamsize n = 1, int delim = EOF ) override;
        std::istream & read( char * s, std::streamsize n ) override;
        std::istream & putback( char c );
        std::istream & unget();
        std::istream & seekg( std::streampos pos );
        std::istream & seekg( std::streamoff off, std::ios_base::seekdir dir );
        void clear();
    };

}

#endif /* MP4_BINARY_STREAM_ */
