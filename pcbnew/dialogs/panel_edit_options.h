/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2010-2014 Jean-Pierre Charras, jean-pierre.charras at wanadoo.fr
 * Copyright (C) 1992-2020 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef __dialog_general_options_h
#define __dialog_general_options_h

#include "panel_edit_options_base.h"

class PAGED_DIALOG;
class PCB_BASE_EDIT_FRAME;


class PANEL_EDIT_OPTIONS : public PANEL_EDIT_OPTIONS_BASE
{
private:
    PCB_BASE_EDIT_FRAME* m_Frame;

public:
    PANEL_EDIT_OPTIONS( PCB_BASE_EDIT_FRAME* aFrame, PAGED_DIALOG* aWindow );

protected:
    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;
};


#endif	// __dialog_general_options_h
