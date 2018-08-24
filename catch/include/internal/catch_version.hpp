/*
 *  Created by Phil on 14/11/2012.
 *  Copyright 2012 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_VERSION_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_VERSION_HPP_INCLUDED

#include "catch_version.h"

namespace Catch {

    Version::Version
        (   unsigned int _majorVersion,
            unsigned int _minorVersion,
            unsigned int _patchNumber,
            std::string const& _branchName,
            unsigned int _buildNumber )
    :   majorVersion( _majorVersion ),
        minorVersion( _minorVersion ),
        patchNumber( _patchNumber ),
        branchName( _branchName ),
        buildNumber( _buildNumber )
    {}

    std::ostream& operator << ( std::ostream& os, Version const& version ) {
        os  << version.majorVersion << '.'
            << version.minorVersion << '.'
            << version.patchNumber;

        if( !version.branchName.empty() ) {
            os  << '-' << version.branchName
                << '.' << version.buildNumber;
        }
        return os;
    }

    Version libraryVersion( 1, 7, 2, "", 0 );

}

#endif // TWOBLUECUBES_CATCH_VERSION_HPP_INCLUDED
