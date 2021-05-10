/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          sound.sp
 *  Description:   Sound utilities
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

#if defined _sound_included
    #endinput
#endif

#define _sound_included

inline void EmitSoundEx(
    const int[] clients,                int numClients,                         const char[] sample, 
    int entity = SOUND_FROM_PLAYER,     int channel = SNDCHAN_AUTO,             int level = SNDLEVEL_NORMAL, 
    int flags = SND_NOFLAGS,            float volume = SNDVOL_NORMAL,           int pitch = SNDPITCH_NORMAL, 
    int speakerentity = -1,             const float origin[3] = NULL_VECTOR,    const float dir[3] = NULL_VECTOR, 
    bool updatePos = true,              float soundtime = 0.0)
{
    char sound[256];
    FormatEx(sound, 256, "*%s", sample);

    EmitSound(
        clients, numClients, sound, 
        entity, channel, level, 
        flags, volume, pitch, 
        speakerentity, origin, dir, 
        updatePos, soundtime
        );
}

inline void EmitSoundOne(
    int client,                             const char[] sample,                    int entity = SOUND_FROM_PLAYER, 
    int channel = SNDCHAN_AUTO,             int level = SNDLEVEL_NORMAL,            int flags = SND_NOFLAGS, 
    float volume = SNDVOL_NORMAL,           int pitch = SNDPITCH_NORMAL,            int speakerentity = -1, 
    const float origin[3] = NULL_VECTOR,    const float dir[3] = NULL_VECTOR,       bool updatePos = true, 
    float soundtime = 0.0)
{
    char sound[256];
    FormatEx(sound, 256, "*%s", sample);
    EmitSoundToClient(
        client, sound, entity, 
        channel, level, flags, 
        volume, pitch, speakerentity, 
        origin, dir, updatePos, 
        soundtime
        );
}

inline void EmitSoundAll(
    const char[] sample,                int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, 
    int level = SNDLEVEL_NORMAL,        int flags = SND_NOFLAGS,        float volume = SNDVOL_NORMAL, 
    int pitch = SNDPITCH_NORMAL,        int speakerentity = -1,         const float origin[3] = NULL_VECTOR, 
    const float dir[3] = NULL_VECTOR,   bool updatePos = true,          float soundtime = 0.0)
{
    char sound[256];
    FormatEx(sound, 256, "*%s", sample);
    EmitSoundToAll(
        sound, entity, channel, 
        level, flags, volume, 
        pitch, speakerentity, origin, 
        dir, updatePos, soundtime
        );
}