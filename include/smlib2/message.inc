/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          text.sp
 *  Description:   Text chat related.
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

#if defined _smlib2_message_included
#endinput
#endif
#define _smlib2_message_included

#define MAXSPACELENGTH 1024
static char g_PlaceHolder[MAXSPACELENGTH+1];

// Sets default output prefix.
static char ChatPrefix[64] = "[{green}SM{default}]";
static char ChatSpaces[32] = "   ";
static bool ChatConSnd     = true;
static bool SkipNextChatCS = false;
static bool SkipNextPrefix = false;
static bool ReplaceColorEx = false;
static UserMessageType UMType = UM_Protobuf;
static EngineVersion GameEngine = Engine_CSGO;

methodmap Message {
    public static void Init() {
        UMType = GetUserMessageType();
        GameEngine = GetEngineVersion();

        switch (GameEngine) {
            case Engine_Insurgency, Engine_Left4Dead2: {
                ReplaceColorEx = true;
            }
            case Engine_CSGO: {
                ReplaceColorEx = false;
            }
            default: {
                SetFailState("Message.InitUserMessage: CSGO, Insurgency, L4D2 only.");
            }
        }

        for (int i = 0; i < MAXSPACELENGTH; i++) {
            g_PlaceHolder[i] = ' ';
        }
        g_PlaceHolder[MAXSPACELENGTH] = '\0';
    }
}

methodmap SayText2 < Message {
    public static void Build(int client, const char[] msg)
    {
        if(UMType == UM_Protobuf)
        {
            Protobuf SayText2 = view_as<Protobuf>(StartMessageOne("SayText2", client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            SayText2.SetInt("ent_idx", 0);
            SayText2.SetBool("chat", SkipNextChatCS ? false : ChatConSnd);
            SayText2.SetString("msg_name", msg);
            SayText2.AddString("params", "");
            SayText2.AddString("params", "");
            SayText2.AddString("params", "");
            SayText2.AddString("params", "");
            EndMessage();
        }
        else
        {
            BfWrite SayText = view_as<BfWrite>(StartMessageOne("SayText", client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            SayText.WriteByte(0);
            SayText.WriteByte(true);
            SayText.WriteString(msg);
            EndMessage();
        }
    }
}

methodmap Chat < SayText2 {
    public static int SetPrefix(const char[] prefix) {
        return strcopy(ChatPrefix, 64, prefix);
    }

    public static int SetSpace(const char[] space) {
        return strcopy(ChatSpaces, 32, space);
    }

    // Aiming to set Chat string log in console and chat with sound
    public static void SetChatConSnd(bool consnd) {
        ChatConSnd = consnd;
    }

    // set next chat stop sound and log
    public static void SkipNextChatCS() {
        SkipNextChatCS = true;
    }

    // set next chat ignore prefix
    public static void SkipNextPrefix() {
        SkipNextPrefix = true;
    }

    public static void ProcessColorString(char[] message, int maxLen) {
        if(ReplaceColorEx) {
            ReplaceString(message, maxLen, "{normal}",      "\x07FFFFFF", false);
            ReplaceString(message, maxLen, "{default}",     "\x07FFFFFF", false);
            ReplaceString(message, maxLen, "{white}",       "\x07FFFFFF", false);
            ReplaceString(message, maxLen, "{darkred}",     "\x07FF0000", false);
            ReplaceString(message, maxLen, "{pink}",        "\x07D32CE6", false);
            ReplaceString(message, maxLen, "{green}",       "\x077FFF00", false);
            ReplaceString(message, maxLen, "{lime}",        "\x07BFFF00", false);
            ReplaceString(message, maxLen, "{yellow}",      "\x07FFD700", false);
            ReplaceString(message, maxLen, "{lightgreen}",  "\x0798FB98", false);
            ReplaceString(message, maxLen, "{lightred}",    "\x07EB4B4B", false);
            ReplaceString(message, maxLen, "{red}",         "\x07DC143C", false);
            ReplaceString(message, maxLen, "{gray}",        "\x07DCDCDC", false);
            ReplaceString(message, maxLen, "{grey}",        "\x07DCDCDC", false);
            ReplaceString(message, maxLen, "{olive}",       "\x07808000", false);
            ReplaceString(message, maxLen, "{orange}",      "\x07E4AE39", false);
            ReplaceString(message, maxLen, "{silver}",      "\x07B0C3D9", false);
            ReplaceString(message, maxLen, "{lightblue}",   "\x075E98D9", false);
            ReplaceString(message, maxLen, "{blue}",        "\x074B69FF", false);
            ReplaceString(message, maxLen, "{purple}",      "\x078847FF", false);
            ReplaceString(message, maxLen, "{darkorange}",  "\x07CF6A32", false);
        } else {
            ReplaceString(message, maxLen, "{normal}",      "\x01", false);
            ReplaceString(message, maxLen, "{default}",     "\x01", false);
            ReplaceString(message, maxLen, "{white}",       "\x01", false);
            ReplaceString(message, maxLen, "{darkred}",     "\x02", false);
            ReplaceString(message, maxLen, "{pink}",        "\x03", false);
            ReplaceString(message, maxLen, "{green}",       "\x04", false);
            ReplaceString(message, maxLen, "{lime}",        "\x05", false);
            ReplaceString(message, maxLen, "{yellow}",      "\x05", false);
            ReplaceString(message, maxLen, "{lightgreen}",  "\x06", false);
            ReplaceString(message, maxLen, "{lightred}",    "\x07", false);
            ReplaceString(message, maxLen, "{red}",         "\x07", false);
            ReplaceString(message, maxLen, "{gray}",        "\x08", false);
            ReplaceString(message, maxLen, "{grey}",        "\x08", false);
            ReplaceString(message, maxLen, "{olive}",       "\x09", false);
            ReplaceString(message, maxLen, "{orange}",      "\x10", false);
            ReplaceString(message, maxLen, "{silver}",      "\x0A", false);
            ReplaceString(message, maxLen, "{lightblue}",   "\x0B", false);
            ReplaceString(message, maxLen, "{blue}",        "\x0C", false);
            ReplaceString(message, maxLen, "{purple}",      "\x0E", false);
            ReplaceString(message, maxLen, "{darkorange}",  "\x0F", false);
        }
    }

    public static void RemoveAllColors(char[] message, int maxLen) {
        ReplaceString(message, maxLen, "{normal}",      "", false);
        ReplaceString(message, maxLen, "{default}",     "", false);
        ReplaceString(message, maxLen, "{teamcolor}",   "", false);
        ReplaceString(message, maxLen, "{white}",       "", false);
        ReplaceString(message, maxLen, "{darkred}",     "", false);
        ReplaceString(message, maxLen, "{pink}",        "", false);
        ReplaceString(message, maxLen, "{green}",       "", false);
        ReplaceString(message, maxLen, "{lime}",        "", false);
        ReplaceString(message, maxLen, "{yellow}",      "", false);
        ReplaceString(message, maxLen, "{lightgreen}",  "", false);
        ReplaceString(message, maxLen, "{lightred}",    "", false);
        ReplaceString(message, maxLen, "{red}",         "", false);
        ReplaceString(message, maxLen, "{gray}",        "", false);
        ReplaceString(message, maxLen, "{grey}",        "", false);
        ReplaceString(message, maxLen, "{olive}",       "", false);
        ReplaceString(message, maxLen, "{orange}",      "", false);
        ReplaceString(message, maxLen, "{silver}",      "", false);
        ReplaceString(message, maxLen, "{lightblue}",   "", false);
        ReplaceString(message, maxLen, "{blue}",        "", false);
        ReplaceString(message, maxLen, "{purple}",      "", false);
        ReplaceString(message, maxLen, "{darkorange}",  "", false);
        ReplaceString(message, maxLen, "\x01",          "", false);
        ReplaceString(message, maxLen, "\x02",          "", false);
        ReplaceString(message, maxLen, "\x03",          "", false);
        ReplaceString(message, maxLen, "\x04",          "", false);
        ReplaceString(message, maxLen, "\x05",          "", false);
        ReplaceString(message, maxLen, "\x06",          "", false);
        ReplaceString(message, maxLen, "\x07",          "", false);
        ReplaceString(message, maxLen, "\x08",          "", false);
        ReplaceString(message, maxLen, "\x09",          "", false);
        ReplaceString(message, maxLen, "\x10",          "", false);
        ReplaceString(message, maxLen, "\x0A",          "", false);
        ReplaceString(message, maxLen, "\x0B",          "", false);
        ReplaceString(message, maxLen, "\x0C",          "", false);
        ReplaceString(message, maxLen, "\x0D",          "", false);
        ReplaceString(message, maxLen, "\x0E",          "", false);
        ReplaceString(message, maxLen, "\x0F",          "", false);
    }

    public static void ToSingle(int client, const char[] buffer, any ...) {
        char msg[256];
        VFormat(msg, 256, buffer, 3);
        Format(msg, 256, "%s%s%s", !SkipNextPrefix ? ChatPrefix : "", ChatSpaces, msg);
        ProcessColorString(msg, 256);
        SayText2.Build(client, msg);
        SkipNextChatCS = false;
        SkipNextPrefix = false;
    }

    public static void ToMultiple(int[] clients, int numClients, const char[] buffer, any ...) {
        char msg[256];
        VFormat(msg, 256, buffer, 4);
        Format(msg, 256, "%s%s%s", !SkipNextPrefix ? ChatPrefix : "", ChatSpaces, msg);
        ProcessColorString(msg, 256);
        
        if(UMType == UM_Protobuf)
        {
            Protobuf SayText2 = view_as<Protobuf>(StartMessage("SayText2", clients, numClients, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            SayText2.SetInt("ent_idx", 0);
            SayText2.SetBool("chat", SkipNextChatCS ? false : ChatConSnd);
            SayText2.SetString("msg_name", msg);
            SayText2.AddString("params", "");
            SayText2.AddString("params", "");
            SayText2.AddString("params", "");
            SayText2.AddString("params", "");
            EndMessage();
        }
        else
        {
            BfWrite SayText = view_as<BfWrite>(StartMessage("SayText", clients, numClients, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            SayText.WriteByte(0);
            SayText.WriteByte(true);
            SayText.WriteString(msg);
            EndMessage();
        }

        SkipNextChatCS = false;
        SkipNextPrefix = false;
    }

    public static void ToTeam(int team, bool spec = true, const char[] buffer, any ...) {
        int[] clients = new int[MAXPLAYERS+1];
        int total = 0;
        int iTeam = 0;
        
        for(int client = 1; client <= MaxClients; client++) {
            if (PlayerEx.Exist(client, false)) {
                iTeam = ToolsGetTeam(client); // modify it later

                if (iTeam == team || (spec && iTeam == 1)) {
                    clients[total++] = client;
                }
            }
        }
        char message[256];
        VFormat(message, 256, buffer, 4);
        Chat.ToMultiple(clients, total, message);
    }

    public static void ToAlives(const char[] buffer, any ...) {
        int[] clients = new int [MAXPLAYERS+1];
        int total = 0;

        for (int client = 1; client <= MaxClients; client++) {
            if (PlayerEx.Exist(client, true)) {
                clients[total++]=client;
            }
        }
        
        char message[256];
        VFormat(message, 256, buffer, 4);
        Chat.ToMultiple(clients, total, message);
    }

    public static void ToDeaths(const char[] buffer, any ...) {
        int[] clients = new int[MAXPLAYERS+1];
        int total = 0;

        for (int client = 1; client <= MaxClients; client++) {
            if(PlayerEx.Exist(client, false)) {
                if (!IsPlayerAlive(client)) {
                    clients[total++] = client;
                }
            }
        }
        char message[256];
        VFormat(message, 256, buffer, 4);
        Chat.ToMultiple(clients, total, message);
    }

    public static void ToSpectators(const char[] buffer, any ...) {
        int[] clients = new int[MAXPLAYERS+1];
        int total = 0;

        for (int client = 1; client <= MaxClients; client++) {
            if(PlayerEx.Exist(client, false)) {
                if (GetClientTeam(client) == TEAM_SPECTATOR) {
                    clients[total++] = client;
                }
            }
        }
        char message[256];
        VFormat(message, 256, buffer, 4);
        Chat.ToMultiple(clients, total, message);
    }

    public static void ToAll(const char[] buffer, any ...) {
        char msg[256];
        VFormat(msg, 256, buffer, 2);
        Format(msg, 256, "%s%s%s", !SkipNextPrefix ? ChatPrefix : "", ChatSpaces, msg);
        Chat.ProcessColorString(msg, 256);

        if(UMType == UM_Protobuf)
        {
            Protobuf SayText2 = view_as<Protobuf>(StartMessageAll("SayText2", USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            SayText2.SetInt("ent_idx", 0);
            SayText2.SetBool("chat", SkipNextChatCS ? false : ChatConSnd);
            SayText2.SetString("msg_name", msg);
            SayText2.AddString("params", "");
            SayText2.AddString("params", "");
            SayText2.AddString("params", "");
            SayText2.AddString("params", "");
            EndMessage();
        }
        else
        {
            BfWrite SayText = view_as<BfWrite>(StartMessageAll("SayText", USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            SayText.WriteByte(0);
            SayText.WriteByte(true);
            SayText.WriteString(msg);
            EndMessage();
        }

        SkipNextChatCS = false;
        SkipNextPrefix = false;
    }

}

// ============================================
// HintText
// ============================================

methodmap HintText < Message {
    public static void Write(Protobuf msg, bool color, const char[] message) {
        if (color) {
            char text[2048];
            msg.SetInt("msg_dst", 4);
            msg.AddString("params", "#SFUI_ContractKillStart");
            Format(text, 2048, "</font>%s%s", message, g_PlaceHolder);
            msg.AddString("params", text);
            msg.AddString("params", "");
            msg.AddString("params", "");
            msg.AddString("params", "");
            msg.AddString("params", "");
        } else {
            msg.SetString("text", message);
        }
    }

    public static void Identify(const char[] message, bool &color, char[] adapter, int maxlen) {
        if (StrContains(message, "<font") != -1 || StrContains(message, "<span") != -1) {
            color = true;
            strcopy(adapter, 16, "TextMsg");
        }
        else
        {
            strcopy(adapter, 16, "HintText");
        }
    }

    public static void Build(int client, const char[] msg) {
        if (UMType == UM_Protobuf) {
            char adapter[16];
            bool color = false;
            HintText.Identify(msg, color, string(adapter));
            Protobuf text = view_as<Protobuf>(StartMessageOne(adapter, client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            HintText.Write(text, color, msg);
            EndMessage();
        } else {
            BfWrite text = view_as<BfWrite>(StartMessageOne("HintText", client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            text.WriteString(msg);
            EndMessage();
        }
    }

    public static void ToSingle(int client, const char[] buffer, any ...) {
        char msg[1024];
        SetGlobalTransTarget(client);
        VFormat(msg, 1024, buffer, 3);
        HintText.Build(client, msg);
        SetGlobalTransTarget(LANG_SERVER);
    }

    public static void ToMultiple(int[] clients, int numClients, const char[] buffer, any ...) {
        char msg[1024];
        VFormat(msg, 1024, buffer, 3);

        if(UMType == UM_Protobuf)
        {
            char adapter[16];
            bool color = false;
            HintText.Identify(msg, color, string(adapter));
            Protobuf text = view_as<Protobuf>(StartMessage(adapter, clients, numClients, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            HintText.Write(text, color, msg);
            EndMessage();
        }
        else
        {
            BfWrite text = view_as<BfWrite>(StartMessage("HintText", clients, numClients, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            text.WriteString(msg);
            EndMessage();
        }
    }

    public static void ToAll(const char[] buffer, any ...) {
        char msg[1024];
        VFormat(msg, 1024, buffer, 2);

        if(UMType == UM_Protobuf)
        {
            char adapter[16];
            bool color = false;
            HintText.Identify(msg, color, string(adapter));
            Protobuf text = view_as<Protobuf>(StartMessageAll(adapter, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            HintText.Write(text, color, msg);
            EndMessage();
        }
        else
        {
            BfWrite text = view_as<BfWrite>(StartMessageAll("HintText", USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            text.WriteString(msg);
            EndMessage();
        }
    }
}


// =============================================
// TextMsg
// =============================================

#define HUD_PRINTNOTIFY   1
#define HUD_PRINTCONSOLE  2
#define HUD_PRINTTALK     3
#define HUD_PRINTCENTER   4
static int TextMsgDest = HUD_PRINTCENTER;

methodmap TextMsg < Message {
    public static void SetDest(int val) {
        TextMsgDest = val;
    }
    
    public static void Color(Protobuf msg, const char[] message) {
        if (StrContains(message, "<font") != -1 || StrContains(message, "<span") != -1) {
            char text[2048];
            msg.SetInt("msg_dst", 4);
            msg.AddString("params", "#SFUI_ContractKillStart");
            Format(text, 2048, "</font>%s%s", message, g_PlaceHolder);
            msg.AddString("params", text);
        } else {
            msg.SetInt("msg_dst", TextMsgDest); 
            msg.AddString("params", message);
        }
        msg.AddString("params", "");
        msg.AddString("params", "");
        msg.AddString("params", "");
        msg.AddString("params", "");
    }

    public static void Type(int client, const char[] message) {
        if(UMType == UM_Protobuf) {
            Protobuf msg = view_as<Protobuf>(StartMessageOne("TextMsg", client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            TextMsg.Color(msg, message);
            EndMessage();
        }
        else
        {
            BfWrite msg = view_as<BfWrite>(StartMessageOne("TextMsg", client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            msg.WriteByte(TextMsgDest); 
            msg.WriteString(message);
            msg.WriteString("");
            msg.WriteString("");
            msg.WriteString("");
            msg.WriteString("");
            EndMessage();
        }
    }
    

    public static void ToSingle(int client, const char[] buffer, any ...) {
        char msg[2048];
        SetGlobalTransTarget(client);
        VFormat(msg, 2048, buffer, 3);
        TextMsg.Type(client, msg);
        SetGlobalTransTarget(LANG_SERVER);
    }
    
    public static void ToMultiple(int[] clients, int numClients, const char[] buffer, any ...) {
        char msg[2048];
        VFormat(string(msg), buffer, 3);

        if (UMType == UM_Protobuf) {
            Protobuf text = view_as<Protobuf>(StartMessage("TextMsg", clients, numClients, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            TextMsg.Color(text, msg);
            EndMessage();
        } else {
            BfWrite text = view_as<BfWrite>(StartMessage("TextMsg", clients, numClients, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            text.WriteByte(TextMsgDest); 
            text.WriteString(msg);
            text.WriteString("");
            text.WriteString("");
            text.WriteString("");
            TextMsg.WriteString("");
            EndMessage();
        }
    }

    public static void ToAll(const char[] buffer, any ...) {
        char msg[2048];
        VFormat(string(msg), buffer, 2);

        if (UMType == UM_Protobuf) {
            Protobuf text = view_as<Protobuf>(StartMessageAll("TextMsg", USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
            TextMsg.Color(text, msg);
            EndMessage();
        } else {
        BfWrite text = view_as<BfWrite>(StartMessageAll("TextMsg", USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
        text.WriteByte(TextMsgDest); 
        text.WriteString(msg);
        text.WriteString("");
        text.WriteString("");
        text.WriteString("");
        text.WriteString("");
        EndMessage();
        }
    }
}

// =============================================
// HudMsg
// =============================================

static int hudMsg_clr1[4] = {255, 255, 255, 255};
static int hudMsg_clr2[4] = {255, 255, 255, 255};
static float hudMsg_pos[2] = {-1.0, -1.0}; // at center
static float hudMsg_hold = 1.0;
static int hudMsg_effect = 0;
static float hudMsg_fxTime = 0.0;
static float hudMsg_fadeIn = 0.0;
static float hudMsg_fadeOut = 0.0;

methodmap HudMsg < Message {
    // Vector2D pos
    // float holdtime
    // Color color
    // int effect
    // float fxTime
    // float fadeIn
    // float fadeOut
    public static void SetUMParams(float pos[2], float holdtime, int color[4], int effect, float fxTime, float fadeIn, float fadeOut) {
        hudMsg_pos[0]      = pos[0];
        hudMsg_pos[1]      = pos[1];

        hudMsg_hold        = holdtime;

        hudMsg_clr1[0]     = color[0];
        hudMsg_clr1[1]     = color[1];
        hudMsg_clr1[2]     = color[2];
        hudMsg_clr1[3]     = color[3];

        hudMsg_effect      = effect;
        hudMsg_fxTime      = fxTime;
        hudMsg_fadeIn      = fadeIn;
        hudMsg_fadeOut     = fadeOut;
    }

    public static void ToSingle(int client, int channel, const char[] buffer, any ...) {
        char message[512];
        VFormat(string(message), buffer, 4);

        Protobuf HudMsg = view_as<Protobuf>(StartMessageOne("HudMsg", client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
        HudMsg.SetInt("channel", channel);
        HudMsg.SetVector2D("pos", hudMsg_pos);
        HudMsg.SetColor("clr1", hudMsg_clr1);
        HudMsg.SetColor("clr2", hudMsg_clr2);
        HudMsg.SetInt("effect", hudMsg_effect);
        HudMsg.SetFloat("fade_in_time", hudMsg_fadeIn);
        HudMsg.SetFloat("fade_out_time", hudMsg_fadeOut);
        HudMsg.SetFloat("fx_time", hudMsg_fxTime);
        HudMsg.SetFloat("hold_time", hudMsg_hold);
        HudMsg.SetString("text", message);
        EndMessage();
    }

    public static void ToSingleEx(int client, int channel, const float hold, 
                                const float pos[2], const int color[4], int effect, 
                                float fxTime, float fadeIn, float fadeOut, 
                                const char[] buffer, any ...) {
        char message[512];
        VFormat(string(message), buffer, 11);

        Protobuf HudMsg = view_as<Protobuf>(StartMessageOne("HudMsg", client, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
        HudMsg.SetInt("channel", channel);
        HudMsg.SetFloat("hold_time", hold);
        HudMsg.SetVector2D("pos", pos);
        HudMsg.SetColor("clr1", color);
        HudMsg.SetColor("clr2", hudMsg_clr2);
        HudMsg.SetInt("effect", effect);
        HudMsg.SetFloat("fx_time", fxTime);
        HudMsg.SetFloat("fade_in_time", fadeIn);
        HudMsg.SetFloat("fade_out_time", fadeOut);
        HudMsg.SetString("text", message);
        EndMessage();
    }

    public static void ToMultiple(int[] clients, int numClients, int channel, const char[] buffer, any ...) {
        char message[512];
        VFormat(string(message), buffer, 5);

        Protobuf HudMsg = view_as<Protobuf>(StartMessage("HudMsg", clients, numClients, USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
        HudMsg.SetInt("channel", channel);
        HudMsg.SetVector2D("pos", hudMsg_pos);
        HudMsg.SetColor("clr1", hudMsg_clr1);
        HudMsg.SetColor("clr2", hudMsg_clr2);
        HudMsg.SetInt("effect", hudMsg_effect);
        HudMsg.SetFloat("fade_in_time", hudMsg_fadeIn);
        HudMsg.SetFloat("fade_out_time", hudMsg_fadeOut);
        HudMsg.SetFloat("fx_time", hudMsg_fxTime);
        HudMsg.SetFloat("hold_time", hudMsg_hold);
        HudMsg.SetString("text", message);
        EndMessage();
    }

    public static void ToAll(int channel, const char[] buffer, any ...) {
        char message[512];
        VFormat(string(message), buffer, 3);

        Protobuf HudMsg = view_as<Protobuf>(StartMessageAll("HudMsg", USERMSG_RELIABLE|USERMSG_BLOCKHOOKS));
        HudMsg.SetInt("channel", channel);
        HudMsg.SetVector2D("pos", hudMsg_pos);
        HudMsg.SetColor("clr1", hudMsg_clr1);
        HudMsg.SetColor("clr2", hudMsg_clr2);
        HudMsg.SetInt("effect", hudMsg_effect);
        HudMsg.SetFloat("fade_in_time", hudMsg_fadeIn);
        HudMsg.SetFloat("fade_out_time", hudMsg_fadeOut);
        HudMsg.SetFloat("fx_time", hudMsg_fxTime);
        HudMsg.SetFloat("hold_time", hudMsg_hold);
        HudMsg.SetString("text", message);
        EndMessage();
    }

    public static void ToTeam(int team, int channel, const char[] buffer, any ...) {
        char message[512];
        VFormat(string(message), buffer, 4);

        int[] clients = new int[MAXPLAYERS + 1];
        int total = 0;
        int iTeam = TEAM_NONE;

        // Optimization is needed.
        for (int client = 1; client <= MaxClients; client++) {
            if (IsPlayerExist(client, false) && !IsFakeClient(client)) {
                iTeam = GetClientTeam(client);
                if (iTeam == team) {
                    clients[total++] = client;
                }
            }
        }

        // ToMultiple(int[] clients, int numClients, int channel, const char[] buffer, any ...)
        HudMsg.ToMultiple(clients, total, channel, message);
    }
}
