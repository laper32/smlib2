/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          server.sp
 *  Description:   Server.
 *
 *  Copyright (c) 2022 laper32.
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

#if defined _smlib2_server_included
    #endinput
#endif

#define _smlib2_server_included

methodmap Server {
    public static void GetIPAddress(char[] ip, int maxlen, int port) {
        int _ip = FindConVar("hostip").IntValue;
        Format(ip, maxlen, "%d.%d.%d.%d", 
        (_ip >> 24) & 0x000000FF, (_ip >> 16) & 0x000000FF, (_ip >> 8) & 0x000000FF, _ip & 0x000000FF);
        port = FindConVar("hostport").IntValue;
    }
}