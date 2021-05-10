/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          entity.sp
 *  Description:   Entity related.
 *
 *  Copyright (c) 2021 laper32.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * ============================================================================
 */

#if defined _smlib2_entity_included
    #endinput
#endif

#define _smlib2_entity_included

inline bool EntitySetParent(int parent, int child)
{
    SetVariantString("!activator");
    return AcceptEntityInput(child, "SetParent", parent, child, 0);
}