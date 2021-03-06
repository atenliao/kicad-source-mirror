/*
* This program source code file is part of KiCad, a free EDA CAD application.
*
* Copyright (C) 2020 Mark Roszko <mark.roszko@gmail.com>
* Copyright (C) 2020 KiCad Developers, see AUTHORS.txt for contributors.
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation, either version 3 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KIPLATFORM_APP_H_
#define KIPLATFORM_APP_H_

class wxString;
class wxWindow;

namespace KIPLATFORM
{
    namespace APP
    {
        /**
         * Registers the application for restart with the OS with the given command line string to pass as args
         *
         * @param aCommandLine is string the OS will invoke the application with
         */
        bool RegisterApplicationRestart( const wxString& aCommandLine );

        /**
         * Unregisters the application from automatic restart
         *
         * Depending on OS, this may not be required
         */
        bool UnregisterApplicationRestart();

        /**
         * Whether or not the window supports setting a shutdown block reason
         */
        bool SupportsShutdownBlockReason();

        /**
         * Sets the block reason why the window/application is preventing OS shutdown.
         * This should be set far ahead of any close event.
         *
         * This is mainly intended for Windows platforms where this is a native feature.
         *
         * @param aWindow that will have a shutdown blocker message
         * @param aReason to display why the shutdown block is occuring
         */
        void SetShutdownBlockReason( wxWindow* aWindow, const wxString& aReason );

        /**
         * Removes any shutdown block reason set
         *
         * @param aWindow that has a shutdown block reason set
         */
        void RemoveShutdownBlockReason( wxWindow* aWindow );
    }
}

#endif // KIPLATFORM_UI_H_