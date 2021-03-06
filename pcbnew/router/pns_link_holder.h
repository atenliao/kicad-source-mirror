/*
 * KiRouter - a push-and-(sometimes-)shove PCB router
 *
 * Copyright (C) 2019 CERN
 * Author: Seth Hillbrand <hillbrand@ucdavis.edu>
 * Author: Tomasz Wlostowski <tomasz.wlostowski@cern.h>
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

#ifndef PCBNEW_ROUTER_PNS_LINK_HOLDER_H_
#define PCBNEW_ROUTER_PNS_LINK_HOLDER_H_

#include "pns_item.h"
#include "pns_linked_item.h"

namespace PNS
{
class LINK_HOLDER : public ITEM
{
public:
    typedef std::vector<LINKED_ITEM*> LINKS;

    LINK_HOLDER( PnsKind aKind ) : ITEM( aKind )
    {}

    ///> Adds a reference to an item registered in a NODE that is a part of this line.
    void Link( LINKED_ITEM* aLink )
    {
        m_links.push_back( aLink );
    }

    ///> Returns the list of links from the owning node that constitute this
    ///> line (or NULL if the line is not linked)
    LINKS& Links()
    {
        return m_links;
    }

    bool IsLinked() const
    {
        return m_links.size() != 0;
    }

    ///> Checks if the segment aLink is a part of the line.
    bool ContainsLink( const LINKED_ITEM* aItem ) const
    {
        return std::find( m_links.begin(), m_links.end(),
                aItem ) != m_links.end();
    }

    LINKED_ITEM* GetLink( int aIndex ) const
    {
        return m_links[aIndex];
    }

    ///> Erases the linking information. Used to detach the line from the owning node.
    virtual void ClearLinks()
    {
        m_links.clear();
    }

    ///> Returns the number of segments that were assembled together to form this line.
    int LinkCount() const
    {
        return m_links.size();
    }

    void ShowLinks() const
    {
        #if 0 // fixme: move outside header
        if( !IsLinked() )
        {
            wxLogTrace( "PNS", "item %p: no links", this );
            return;
        }

        wxLogTrace( "PNS", "item %p: %d links", this, (int) m_links.size() );

        for( int i = 0; i < (int) m_links.size(); i++ )
            wxLogTrace( "PNS", "item %d: %p\n", i, m_links[i] );
        #endif
    }

protected:
    ///> Copies m_links from the line aParent.
    void copyLinks( const LINK_HOLDER* aParent )
    {
        m_links = aParent->m_links;
    }

    ///> List of segments in the owning NODE (ITEM::m_owner) that constitute this line, or NULL
    ///> if the line is not a part of any node.
    LINKS m_links;
};

} // namespace PNS
#endif /* PCBNEW_ROUTER_PNS_LINK_HOLDER_H_ */
