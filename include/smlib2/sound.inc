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