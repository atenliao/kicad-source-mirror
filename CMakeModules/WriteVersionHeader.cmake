#
#  This program source code file is part of KICAD, a free EDA CAD application.
#
#  Copyright (C) 2015 Wayne Stambaugh <stambaughw@gmail.com>
#  Copyright (C) 2015-2020 KiCad Developers, see AUTHORS.txt for contributors.
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, you may find one here:
#  http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
#  or you may search the http://www.gnu.org website for the version 2 license,
#  or you may write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
#

# Create the KiCad version strings
include( ${CMAKE_MODULE_PATH}/KiCadVersion.cmake )
include( ${CMAKE_MODULE_PATH}/KiCadFullVersion.cmake )

# Extract the major and minor build version as a string
string( REGEX MATCH
        "([0-9]+\\.[0-9]+)\\..*"
        KICAD_MAJOR_MINOR_VERSION
        "${KICAD_SEMANTIC_VERSION}"
    )

if( CMAKE_MATCH_COUNT EQUAL 1 )
    # Match slot 0 is the full string, so we want slot 1
    set( KICAD_MAJOR_MINOR_VERSION "${CMAKE_MATCH_1}" )
else()
    message( FATAL_ERROR "Unable to extract major and minor version string" )
endif()


set( _wvh_new_version_text
"/* Do not modify this file, it was automatically generated by CMake. */

/*
 * Define the KiCad build version strings.
 */
#ifndef __KICAD_VERSION_H__
#define __KICAD_VERSION_H__

#define KICAD_VERSION_FULL        \"${KICAD_VERSION_FULL}\"
#define KICAD_SEMANTIC_VERSION    \"${KICAD_SEMANTIC_VERSION}\"
#define KICAD_MAJOR_MINOR_VERSION \"${KICAD_MAJOR_MINOR_VERSION}\"

#endif  /* __KICAD_VERSION_H__ */
" )

set( _wvh_write_version_file ON )

# Only write the header if it has changed, to avoid rebuilds
if( EXISTS ${OUTPUT_FILE} )
    file( READ ${OUTPUT_FILE} _wvh_old_version_text )
    if( _wvh_old_version_text STREQUAL _wvh_new_version_text )
        message( STATUS "Not updating ${OUTPUT_FILE}" )
        set( _wvh_write_version_file OFF )
    endif()
endif()

if( _wvh_write_version_file )
    message( STATUS "Writing ${OUTPUT_FILE} file with version: ${KICAD_VERSION_FULL}" )

    file( WRITE ${OUTPUT_FILE} ${_wvh_new_version_text} )

    # Write a simple document with only the full version
    file( WRITE ${TEXT_OUTPUT_FILE} "${KICAD_VERSION_FULL}" )
endif()

# There should always be a valid version.h file.  Otherwise, the build will fail.
if( NOT EXISTS ${OUTPUT_FILE} )
    message( FATAL_ERROR "Configuration failed to write file ${OUTPUT_FILE}." )
endif()
