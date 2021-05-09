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

#ifndef _MP4_UNKNOWN_ATOM_
#pragma once
#define _MP4_UNKNOWN_ATOM_

#include "mp4.h"
#include "MP4.DataAtom.h"

namespace MP4
{
    class UnknownAtomException : public std::exception
    {
        private:
            
            
            
        protected:
            
            unsigned int code;
            
        public:
            
            enum
            {
                NoAtomType = 0x00
            };
            
            UnknownAtomException( void );
            UnknownAtomException( unsigned int c );
            virtual const char * what( void ) const throw();
    };
    
    class UnknownAtom : public DataAtom
    {
        private:
            
            
            
        protected:
            
            
            
        public:
            
            UnknownAtom( void ) = delete;
            explicit UnknownAtom( char * t );
            
            std::string description( void );
            void processData(MP4::BinaryStream * stream, size_t length );
    };
}

#endif /* _MP4_UNKNOWN_ATOM_ */
