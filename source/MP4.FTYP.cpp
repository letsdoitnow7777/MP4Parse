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

#include "MP4.FTYP.h"

using namespace MP4;
          
FTYP::FTYP()
{
    this->_type.append( "FTYP" );
}

FTYP::~FTYP()
{
    std::vector< std::string * >::iterator it;
    
    for( it = _compatibleBrands.begin(); it != _compatibleBrands.end(); ++it )
    {
        delete *( it );
    }
}

std::string FTYP::description()
{
    std::string s;
    std::string * brand;
    std::vector< std::string * >::iterator it;
    std::ostringstream o;
    std::string indent = countIndent();
    
    o << indent << this->_type << "(Atom)" << " Major brand:" << _majorBrand << \
                                            "Minor version:" << _minorVersion << \
                                            " Compatible brands: \n";
    
    s = o.str();
    
    for( it = _compatibleBrands.begin(); it != _compatibleBrands.end(); ++it )
    {
        brand = *( it );
        
        o << "  " << *( brand ) << "\t";
    }
    o << "\n";
    
    return o.str();
}

void FTYP::processData(MP4::IBinaryStream * stream, size_t length )
{
    std::string * s;
    char brand[ 5 ];
    
    memset( brand, 0, 5 );
    stream->read( brand, 4 );
    _majorBrand.append( brand );
    
    _minorVersion = stream->readBigEndianUnsignedInteger();
    
    if( length > 8 )
    {
        length -= 8;
        
        while( length > 0 )
        {
            stream->read( brand, 4 );
            
            length -= 4;
            s       = new std::string( brand );
            
            _compatibleBrands.push_back( s );
        }
    }
}
