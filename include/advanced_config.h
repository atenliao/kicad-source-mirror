/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2019 KiCad Developers, see AUTHORS.txt for contributors.
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

#ifndef ADVANCED_CFG__H
#define ADVANCED_CFG__H

class wxConfigBase;

/**
 * Class containing "advanced" configuration options.
 *
 * Options set here are for developer or advanced users only. If a general user
 * needs to set one of these for normal KiCad use, either:
 * * They are working around some bug that should be fixed, or
 * * The parameter they are setting is of general interest and should be in the
 *   main application config, with UI provided.
 *
 * Options in this class are, in general, preferable to #defines, as they
 * allow more flexible configuration by developers, and don't hide code from
 * the compiler on other configurations, which can result in broken builds.
 *
 * Never use advanced configs in an untestable way. If a function depends on
 * advanced config such that you cannot test it without changing the config,
 * "lift" the config to a higher level and make pass it as parameter of the code
 * under test. The tests can pass their own values as needed.
 *
 * This also applies to code that does not depend on "common" - it cannot
 * use this class, so you must pass configuration in as proper parameters.
 *
 * Sometimes you can just use values directly, and sometimes helper functions
 * might be provided to allow extra logic (for example when a advanced config
 * applies only on certain platforms).
 *
 * For more information on what config keys set these parameters in the
 * config files, and why you might want to set them, see #AC_KEYS
 *
 */
class ADVANCED_CFG
{
public:
    /**
     * Get the singleton instance's config, which is shared by all
     * consumers of advanced config.
     *
     * This configuration is read-only - to set options, users should
     * add the parameters to their config files at ~/.config/kicad/advanced, or the
     * platform equivalent.
     */
    static const ADVANCED_CFG& GetCfg();

    /**
     * For drawsegments - arcs.
     * Distance from an arc end point and the estimated end point,
     * when rotating from the start point to the end point.
     */
    double m_drawArcAccuracy;

    /**
     * For drawsegments - arcs.
     * When drawing an arc, the angle ( center - start ) - ( start - end )
     * can be limited to avoid extremely high radii.
     */
    double m_drawArcCenterMaxAngle;

    /**
     * Extra fill clearance for zone fills.  Note that for zone tests this is essentially
     * additive with m_DRCEpsilon.  Units are mm.
     */
    double m_ExtraClearance;

    /**
     * Epsilon for DRC tests.  Note that for zone tests this is essentially additive with
     * m_extraClearance.  Units are mm.
     */
    double m_DRCEpsilon;

    /**
     * Hole wall plating thickness.  Used to determine actual hole size from finish hole size.
     * Units are mm.
     */
    double m_HoleWallThickness;

    /**
     * Do real-time connectivity
     */
    bool m_realTimeConnectivity;

    /**
     * Set the stack size for coroutines
     */
    int m_coroutineStackSize;

    /**
     * Show PNS router debug graphics
     */
    bool m_ShowRouterDebugGraphics;

    /**
     * Save files in compact display mode
     * When is is not specified, points are written one per line
     */
    bool m_CompactSave;

    /**
     * When true, strokes the triangulations with visible color
     */
    bool m_DrawTriangulationOutlines;

    /**
     * When true, enable Altium Schematic import (*.SchDoc)
     * the current implementation is highly incomplete
     */
    bool m_PluginAltiumSch;

    /**
     * Sets an absolute minimum pen width for plotting.  Some formats (PDF, for example) don't
     * like ultra-thin lines.  Units are mm.
     */
    double m_MinPlotPenWidth;

private:
    ADVANCED_CFG();

    /**
     * Load the config from the normal config file
     */
    void loadFromConfigFile();

    /*
     * Load config from the given config base
     */
    void loadSettings( wxConfigBase& aCfg );
};

#endif // ADVANCED_CFG__H
