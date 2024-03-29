/**
 * ============================================================================
 *
 *  SourceMod Library 2
 *
 *  File:          fileparser.sp
 *  Description:   Parse the specific resource file.
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

#if defined _smlib2_fileparser_included
    #endinput
#endif

#define _smlib2_fileparser_included

/**
 * File parser for precaching files and relevant resources.
 *
 * Note: You just need to consider following functions what have been listed below:
 *  - FileParser.PrecacheModel()
 *  - FileParser.PrecacheWeapon()
 *  - FileParser.PrecacheTexture()
 *  - FileParser.PrecacheSound()
 *  - FileParser.PrecacheParticle()
 *
 * The params what required to input, which has been shown at the declaration of the function name.
 */
methodmap FileParser {
    /**
     * @brief Reads the current material and precache its textures.
     *
     * @param sFileName            The model name.
     * @param sPath             The texture path.
     * @param bDecal            (Optional) If true, the texture will be precached like a decal.
     * @return                  True if was precached, false otherwise.
     */
    public static bool PrecacheTexture(char[] sFileName, char[] sPath) {
        // Finds the first occurrence of a character in a string
        int iSlash = max(FindCharInString(sFileName, '/', true), FindCharInString(sFileName, '\\', true));
        if (iSlash == -1) iSlash = 0; else iSlash++; /// For the root directory to get correct name
        
        // Dublicate value string
        char sTexture[PLATFORM_LINE_LENGTH];
        strcopy(sTexture, sizeof(sTexture), sPath);

        // If doesn't exist stop
        if (!FileExists(sTexture)) {
            // Try to find file in .vpk
            if (FileExists(sTexture, true)) {
                // Return on success
                return true;
            }

            // Return error
            LogError("FileParser.PrecacheTexture: Invalid material path. File not found: \"%s\" in \"%s\"", sTexture, sFileName[iSlash]);
            return false;
        }

        // Add file to download table
        AddFileToDownloadsTable(sTexture);
        
        // Initialize variables
        char sTypes[4][SMALL_LINE_LENGTH] = { "$baseTexture", "$bumpmap", "$lightwarptexture", "$REFRACTTINTtexture" };
        bool bFound[sizeof(sTypes)];
        int iShift;
        
        // Opens the file
        File hFile = OpenFile(sTexture, "rt");
        
        // If doesn't exist stop
        if (hFile == null) {
            SetFailState("FileParser.PrecacheTexture: Error opening file: \"%s\"", sTexture);
            return false;
        }
        
        // Read lines in the file
        while (hFile.ReadLine(sTexture, sizeof(sTexture))) {
            // Cut out comments at the end of a line
            SplitString(sTexture, "//", sTexture, sizeof(sTexture));

            // i = texture type
            int iSize = sizeof(sTypes);
            for (int x = 0; x < iSize; x++) {
                // Avoid the reoccurrence 
                if (bFound[x]) {
                    continue;
                }
                
                // Validate type
                if ((iShift = StrContains(sTexture, sTypes[x], false)) != -1) {
                    // Shift the type away
                    iShift += strlen(sTypes[x]) + 1;

                    // Checks if string has incorrect quotes
                    int iQuotes = StringEx.CountOccurence(sTexture[iShift], '"');

                    if (iQuotes != 2) {
                        LogError("FileParser.PrecacheTexture: Error with parsing \"%s\" in file: \"%s\"", sTypes[x], sPath);
                    } else {
                        // Sets on success
                        bFound[x] = true;

                        // Copy value string
                        strcopy(sTexture, sizeof(sTexture), sTexture[iShift]);
                        
                        // Trim string
                        TrimString(sTexture);
                        
                        // Strips a quote pair off a string 
                        StripQuotes(sTexture);

                        // Validate size
                        if (!hasLength(sTexture)) {
                            continue;
                        }
                        
                        // Format full path to file
                        Format(sTexture, sizeof(sTexture), "materials\\%s.vtf", sTexture);

                        // Validate material
                        if (FileExists(sTexture)) {
                            // Add file to download table
                            AddFileToDownloadsTable(sTexture);
                        } else {
                            // Validate non default textures
                            if (!FileExists(sTexture, true)) {
                                LogError("FileParser.PrecacheTexture: Invalid texture path. File not found: \"%s\" in \"%s\"", sTexture, sFileName[iSlash]);
                            }
                        }
                    }
                }
            }
        }

        // Close file
        delete hFile; 
        return true;
    }

    /**
     * @brief Reads the current model and precache its materials.
     *
     * @param sFileName             The model path.
     * @return                      True if was precached, false otherwise.
     */
    public static bool PrecacheMaterial(char[] sFileName) {
        // Finds the first occurrence of a character in a string
        int iFormat = FindCharInString(sFileName, '.', true);
        
        // If model path is don't have format, then log, and stop
        if (iFormat == -1) {
            SetFailState("FileParser.PrecacheMaterial: Missing file format: %s", sFileName);
            return false;
        }
        
        // Extract value string
        char sPath[PLATFORM_LINE_LENGTH];
        StrExtract(sPath, sFileName, 0, iFormat);

        // Concatenates one string onto another
        StrCat(sPath, sizeof(sPath), "_materials.txt");

        // Validate if a file exists
        bool bExists = FileExists(sPath);
        
        // Opens/Create the file
        File hBase = OpenFile(sPath, "at+");

        // If file doesn't exist, then write it
        if (!bExists) {
            // Opens the file
            File hFile = OpenFile(sFileName, "rb");

            // If doesn't exist stop
            if (hFile == null) {
                DeleteFile(sPath);
                SetFailState("FileParser.PrecacheMaterial: Error opening file: \"%s\"", sFileName);
                return false;
            }
            
            // Initialize variables
            char sMaterial[PLATFORM_LINE_LENGTH]; int iNumMat; int iChar;

            // Find the total materials amount
            hFile.Seek(204, SEEK_SET);
            hFile.ReadInt32(iNumMat);
            hFile.Seek(0, SEEK_END);
            
            do /// Reads a single binary char
            {
                hFile.Seek(-2, SEEK_CUR);
                hFile.ReadInt8(iChar);
            } 
            while (iChar == 0);

            // Shift the cursor a bit
            hFile.Seek(-1, SEEK_CUR);

            do /// Reads a single binary char
            {
                hFile.Seek(-2, SEEK_CUR);
                hFile.ReadInt8(iChar);
            } 
            while (iChar);

            // Reads a UTF8 or ANSI string from a file
            int iPosIndex = hFile.Position;
            hFile.ReadString(sMaterial, sizeof(sMaterial));
            hFile.Seek(iPosIndex, SEEK_SET);
            hFile.Seek(-1, SEEK_CUR);
            
            // Initialize a material list array
            ArrayList hList = new ArrayList(SMALL_LINE_LENGTH);

            // Reverse loop throught the binary
            while (hFile.Position > 1 && hList.Length < iNumMat)
            {
                do /// Reads a single binary char
                {
                    hFile.Seek(-2, SEEK_CUR);
                    hFile.ReadInt8(iChar);
                } 
                while (iChar);

                // Reads a UTF8 or ANSI string from a file
                iPosIndex = hFile.Position;
                hFile.ReadString(sPath, sizeof(sPath));
                hFile.Seek(iPosIndex, SEEK_SET);
                hFile.Seek(-1, SEEK_CUR);

                // Validate size
                if (!hasLength(sPath))
                {
                    continue;
                }

                // Finds the first occurrence of a character in a string
                iFormat = FindCharInString(sPath, '\\', true);

                // Validate no format
                if (iFormat != -1)
                {
                    // Format full path to directory
                    Format(sPath, sizeof(sPath), "materials\\%s", sPath);
            
                    // Opens the directory
                    DirectoryListing hDirectory = OpenDirectory(sPath);
                    
                    // If doesn't exist stop
                    if (hDirectory == null) {
                        LogError("FileParser.PrecacheMaterial Error opening folder: \"%s\"", sPath);
                        continue;
                    }

                    // Initialize variables
                    char sFile[PLATFORM_LINE_LENGTH]; FileType hType;
                    
                    // Search files in the directory
                    while (hDirectory.GetNext(sFile, sizeof(sFile), hType)) {
                        // Validate file type
                        if (hType == FileType_File) {
                            // Finds the first occurrence of a character in a string
                            iFormat = FindCharInString(sFile, '.', true);
                    
                            // Validate format
                            if (iFormat != -1) {
                                // Validate material format
                                if (!strcmp(sFile[iFormat], ".vmt", false)) {
                                    // Validate unique material
                                    if (hList.FindString(sFile) == -1) {
                                        // Push data into array
                                        hList.PushString(sFile);
                                    }
                                    
                                    // Format full path to file
                                    Format(sFile, sizeof(sFile), "%s%s", sPath, sFile);
                                    
                                    // Store into the base
                                    hBase.WriteLine(sFile);

                                    // Precache model textures
                                    FileParser.PrecacheTexture(sFileName, sFile);
                                }
                            }
                        }
                    }

                    // Close directory
                    delete hDirectory;
                } else {
                    // Concatenates one string onto another
                    StrCat(sPath, sizeof(sPath), ".vmt");
            
                    // Validate unique key
                    if (hList.FindString(sPath) == -1) {
                        // Push data into array
                        hList.PushString(sPath);
                    }
                    
                    // Format full path to file
                    Format(sPath, sizeof(sPath), "materials\\%s%s", sMaterial, sPath);
                    
                    // Store into the base
                    hBase.WriteLine(sPath);
                    
                    // Precache model textures
                    FileParser.PrecacheTexture(sFileName, sPath);
                }
            }

            // Close file
            delete hFile;
            delete hList;
            ///return true;
        } else {
            // Read lines in the file
            while (hBase.ReadLine(sPath, sizeof(sPath))) {
                // Cut out comments at the end of a line
                SplitString(sPath, "//", sPath, sizeof(sPath));
                
                // Trim off whitespace
                TrimString(sPath);

                // If line is empty, then stop
                if (!hasLength(sPath)) {
                    continue;
                }
                
                // Precache model textures
                FileParser.PrecacheTexture(sFileName, sPath);
            }
        }
        
        // Close file
        delete hBase;
        return true;
    }

    /**
     * @brief Reads the current model and precache its resources.
     *
     * @param sFileName            The model path.
     */
    public static void PrecacheResource(char[] sFileName) {
        // Add file to download table
        AddFileToDownloadsTable(sFileName);

        // Initialize variables
        char sResource[PLATFORM_LINE_LENGTH];
        char sTypes[3][SMALL_LINE_LENGTH] = { ".dx90.vtx", ".phy", ".vvd" };

        // Finds the first occurrence of a character in a string
        int iFormat = FindCharInString(sFileName, '.', true);
        
        // i = resource type
        int iSize = sizeof(sTypes);
        for (int i = 0; i < iSize; i++) {
            // Extract value string
            StrExtract(sResource, sFileName, 0, iFormat);
            
            // Concatenates one string onto another
            StrCat(sResource, sizeof(sResource), sTypes[i]);
            
            // Validate resource
            if (FileExists(sResource)) {
                // Add file to download table
                AddFileToDownloadsTable(sResource);
            }
        }
    }

    /**
     * @brief Precache the sound in the sounds table.
     *
     * @param sPath             The sound path.
     * @return                  True if was precached, false otherwise.
     */
    public static bool PrecacheSound(char[] sPath) {
        // If sound didn't exist, then
        if (!FileExists(sPath)) {
            // Try to find file in .vpk
            if (FileExists(sPath, true)) {
                // Return on success
                PrecacheSound(sPath, true);
                return true;
            }

            // Return error
            LogError("FileParser.PrecacheSound: Invalid sound path. File not found: \"%s\"", sPath);
            return false;
        }
        
        // Dublicate value string
        char sSound[PLATFORM_LINE_LENGTH];
        strcopy(sSound, sizeof(sSound), sPath);

        /// @link https://wiki.alliedmods.net/Csgo_quirks#Fake_precaching_and_EmitSound
        if (ReplaceStringEx(sSound, sizeof(sSound), "sound", "*", 5, 1, true) != -1) {
            // Initialize the table index
            static int table = INVALID_STRING_TABLE;

            // Validate table
            if (table == INVALID_STRING_TABLE) {
                // Searches for a string table
                table = FindStringTable("soundprecache");
            }

            // If sound doesn't precache yet, then continue
            if (FindStringIndex(table, sSound) == INVALID_STRING_INDEX) {
                // Add file to download table
                AddFileToDownloadsTable(sPath);

                // Precache sound
                ///bool bSave = LockStringTables(false);
                AddToStringTable(table, sSound);
                ///LockStringTables(bSave);
            }
        } else {
            LogError("FileParser.PrecacheSound: Invalid sound path. File not found: \"%s\"", sPath);
            return false;
        }
        
        // Return on success
        return true;
    }

    /**
     * @brief Reads the current model and precache its sounds.
     *
     * @param sFileName             The model path.
     * @return                      True if was precached, false otherwise.
     */
    public static bool PrecacheModelSound(char[] sFileName) {
        // Finds the first occurrence of a character in a string
        int iFormat = FindCharInString(sFileName, '.', true);
        
        // If model path is don't have format, then log, and stop
        if (iFormat == -1) {
            SetFailState("FileParser.PrecacheModelSound: Missing file format: \"%s\"", sFileName);
            return false;
        }
        
        // Extract value string
        char sPath[PLATFORM_LINE_LENGTH];
        StrExtract(sPath, sFileName, 0, iFormat);

        // Concatenates one string onto another
        StrCat(sPath, sizeof(sPath), "_sounds.txt");
        
        // Validate if a file exists
        bool bExists = FileExists(sPath);
        
        // Opens/Create the file
        File hBase = OpenFile(sPath, "at+");

        // If file doesn't exist, then write it
        if (!bExists) {
            // Opens the file
            File hFile = OpenFile(sFileName, "rb");

            // If doesn't exist stop
            if (hFile == null) {
                DeleteFile(sPath);
                SetFailState("FileParser.PrecacheModelSound: Error opening file: \"%s\"", sFileName);
                return false;
            }
            
            // Initialize variables
            int iChar; ///int iNumSeq;

            // Find the total sequence amount
            /*
                hFile.Seek(180, SEEK_SET);
                hFile.ReadInt32(iNumSeq);
            */
            
            do { /// Reads a single binary char
                hFile.Seek(2, SEEK_CUR);
                hFile.ReadInt8(iChar);
            } while (iChar == 0);

            // Shift the cursor a bit
            hFile.Seek(1, SEEK_CUR);

            do { /// Reads a single binary char
                hFile.Seek(2, SEEK_CUR);
                hFile.ReadInt8(iChar);
            } while (iChar);

            // Loop throught the binary
            while (!hFile.EndOfFile()) {
                // Reads a UTF8 or ANSI string from a file
                hFile.ReadString(sPath, sizeof(sPath));
                
                // Finds the first occurrence of a character in a string
                iFormat = FindCharInString(sPath, '.', true);

                // Validate format
                if (iFormat != -1) {
                    // Validate sound format
                    if (!strcmp(sPath[iFormat], ".mp3", false) || !strcmp(sPath[iFormat], ".wav", false)) {
                        // Format full path to file
                        Format(sPath, sizeof(sPath), "sound/%s", sPath);
                        
                        // Store into the base
                        hBase.WriteLine(sPath);
                        
                        // Add file to download table
                        FileParser.PrecacheSound(sPath);
                    }
                }
            }

            // Close file
            delete hFile; 
            ///return true;
        } else {
            // Read lines in the file
            while (hBase.ReadLine(sPath, sizeof(sPath))) {
                // Cut out comments at the end of a line
                SplitString(sPath, "//", sPath, sizeof(sPath));
                
                // Trim off whitespace
                TrimString(sPath);

                // If line is empty, then stop
                if (!hasLength(sPath)) {
                    continue;
                }
                
                // Add file to download table
                FileParser.PrecacheSound(sPath);
            }
        }
        
        // Close file
        delete hBase;
        return true;
    }

    /**
     * @brief Reads the current model and precache its effects.
     *
     * @param sFileName            The model path.
     * @return                  True if was precached, false otherwise.
     **/
    public static bool PrecacheEffect(char[] sFileName) {
        // Finds the first occurrence of a character in a string
        int iFormat = FindCharInString(sFileName, '.', true);
        
        // If model path is don't have format, then log, and stop
        if (iFormat == -1) {
            SetFailState("FileParser.PrecacheEffect: Missing file format: %s", sFileName);
            return false;
        }

        /// @link https://github.com/VSES/SourceEngine2007/blob/master/src_main/movieobjects/dmeparticlesystemdefinition.cpp
        /*static char sParticleFuncTypes[48][SMALL_LINE_LENGTH] =
        {
            "DmeParticleSystemDefinition", "DmElement", "DmeParticleChild", "DmeParticleOperator", "particleSystemDefinitions",
            "preventNameBasedLookup", "particleSystemDefinitionDict", "snapshot", "untitled", "child", "drag", "delay", "name",
            "renderers", "operators", "initializers", "emitters", "children", "force", "constraints", "body", "duration", "DEBRIES",
            "color", "render", "radius", "lifetime", "type", "emit", "distance", "rotation", "speed", "fadeout", "DEBRIS", "size",
            "material", "function", "tint", "max", "min", "gravity", "scale", "rate", "time", "fade", "length", "definition", "thickness"
        };*/
        
        // Add file to download table
        AddFileToDownloadsTable(sFileName);

        // Extract value string
        char sPath[PLATFORM_LINE_LENGTH];
        StrExtract(sPath, sFileName, 0, iFormat);

        // Concatenates one string onto another
        StrCat(sPath, sizeof(sPath), "_particles.txt");
        
        // Validate if a file exists
        bool bExists = FileExists(sPath);
        
        // Opens/Create the file
        File hBase = OpenFile(sPath, "at+");

        // If file doesn't exist, then write it
        if (!bExists) {
            // Opens the file
            File hFile = OpenFile(sFileName, "rb");

            // If doesn't exist stop
            if (hFile == null) {
                DeleteFile(sPath);
                SetFailState("FileParser.PrecacheEffect: Error opening file: \"%s\"", sFileName);
                return false;
            }

            // Initialize variables
            int iChar; ///int iNumMat;

            do { /// Reads a single binary char
                hFile.Seek(2, SEEK_CUR);
                hFile.ReadInt8(iChar);
            } while (iChar == 0);

            // Shift the cursor a bit
            hFile.Seek(1, SEEK_CUR);

            do { /// Reads a single binary char
                hFile.Seek(2, SEEK_CUR);
                hFile.ReadInt8(iChar);
            } while (iChar);

            // Loop throught the binary
            while (!hFile.EndOfFile()) {
                // Reads a UTF8 or ANSI string from a file
                hFile.ReadString(sPath, sizeof(sPath));

                // Finds the first occurrence of a character in a string
                iFormat = FindCharInString(sPath, '.', true);

                // Validate format
                if (iFormat != -1) {
                    // Validate material format
                    if (!strcmp(sPath[iFormat], ".vmt", false)) {
                        // Format full path to file
                        Format(sPath, sizeof(sPath), "materials\\%s", sPath);
                        
                        // Store into the base
                        hBase.WriteLine(sPath);
                        
                        // Precache model textures
                        FileParser.PrecacheTexture(sFileName, sPath);
                    }
                }
            }

            // Close file
            delete hFile;
            ///return true;
        } else {
            // Read lines in the file
            while (hBase.ReadLine(sPath, sizeof(sPath))) {
                // Cut out comments at the end of a line
                SplitString(sPath, "//", sPath, sizeof(sPath));
            
                // Trim off whitespace
                TrimString(sPath);

                // If line is empty, then stop
                if (!hasLength(sPath)) {
                    continue;
                }

                // Precache model textures
                FileParser.PrecacheTexture(sFileName, sPath);
            }
        }
        
        // Close file
        delete hBase;
        return true;
    }

    /**
     * @brief Precache models and return model index.
     *
     * @note Precache with engine 'hide' models included.
     *
     * @param sModel            The model path.
     * @return                  The model index if was precached, 0 otherwise.
     */
    public static int PrecacheModel(char[] sModel) {
        // If model path is empty, then stop
        if (!hasLength(sModel)) {
            return 0;
        }
        
        // If model didn't exist, then
        if (!FileExists(sModel)) {
            // Try to find file in .vpk
            if (FileExists(sModel, true)) {
                // Return on success
                return PrecacheModel(sModel, true);
            }
            
            // Return error
            SetFailState("FileParser.PrecacheModel: Invalid model path. File not found: \"%s\"", sModel);
            return 0;
        }
        
        // If model doesn't precache yet, then continue
        if (!IsModelPrecached(sModel)) {
            // Precache model materials
            FileParser.PrecacheMaterial(sModel);

            // Precache model resources
            FileParser.PrecacheResource(sModel);
        }
        
        // Return the model index
        return PrecacheModel(sModel, true);
    }

    /**
     * @brief Precache weapon models and return model index.
     *
     * @param sModel            The model path. 
     * @return                  The model index if was precached, 0 otherwise.
     */
    public static int PrecacheWeapon(char[] sModel) {
        // If model path is empty, then stop
        if (!hasLength(sModel)) {
            return 0;
        }
        
        // If model didn't exist, then
        if (!FileExists(sModel)) {
            // Try to find file in .vpk
            if (FileExists(sModel, true)) {
                // Return on success
                return PrecacheModel(sModel, true);
            }

            // Return error
            SetFailState("FileParser.PrecacheWeapon: Invalid model path. File not found: \"%s\"", sModel);
            return 0;
        }

        // If model doesn't precache yet, then continue
        if (!IsModelPrecached(sModel)) {
            // Precache model sounds
            FileParser.PrecacheModelSound(sModel);
            
            // Precache model materials
            FileParser.PrecacheMaterial(sModel);
            
            // Precache model resources
            FileParser.PrecacheResource(sModel);
        }
        
        // Return the model index
        return PrecacheModel(sModel, true);
    }

    /**
     * @brief Precache particle models and return model index.
     *
     * @param sFileName             The model path. 
     * @return                      The model index if was precached, 0 otherwise.
     */
    public static int PrecacheParticle(char[] sFileName) {
        // If model path is empty, then stop
        if (!hasLength(sFileName)) {
            return 0;
        }
        
        // If model didn't exist, then
        if (!FileExists(sFileName)) {
            // Try to find file in .vpk
            if (FileExists(sFileName, true)) {
                // Return on success
                return PrecacheGeneric(sFileName, true);
            }

            // Return error
            SetFailState("FileParser.PrecacheParticle: Invalid model path. File not found: \"%s\"", sFileName);
            return 0;
        }

        // If model doesn't precache yet, then continue
        /**if (!IsGenericPrecached(sFileName))**/
        // Thanks Valve!
        
        // Precache model effects
        FileParser.PrecacheEffect(sFileName);
        
        // Return the model index
        return PrecacheGeneric(sFileName, true);
    }
}

