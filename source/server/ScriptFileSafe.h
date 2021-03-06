/*
This file is part of "Rigs of Rods Server" (Relay mode)

Copyright 2007   Pierre-Michel Ricordel
Copyright 2014+  Rigs of Rods Community

"Rigs of Rods Server" is free software: you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3
of the License, or (at your option) any later version.

"Rigs of Rods Server" is distributed in the hope that it will
be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar. If not, see <http://www.gnu.org/licenses/>.
*/

// copied from the angelscript library and edited for use in Rigs of Rods Multiplayer Server
// 01 Jan 2012

#pragma once

#ifdef WITH_ANGELSCRIPT
//
// ScriptFileSafe
//
// This class encapsulates a FILE pointer in a reference counted class for
// use within AngelScript.
//

#ifndef SCRIPTFILESAFE_H__
#define SCRIPTFILESAFE_H__

//---------------------------
// Compilation settings
//

// Set this flag to turn on/off write support
//  0 = off
//  1 = on

#ifndef AS_WRITE_OPS
#define AS_WRITE_OPS 1
#endif




//---------------------------
// Declaration
//

#include <angelscript.h>
#include <string>
#include <stdio.h>

BEGIN_AS_NAMESPACE

class ScriptFileSafe
{
public:
    ScriptFileSafe();

    void AddRef() const;
    void Release() const;

    // TODO: Implement the "r+", "w+" and "a+" modes
    // mode = "r" -> open the file for reading
    //        "w" -> open the file for writing (overwrites existing file)
    //        "a" -> open the file for appending
    int  Open(const std::string &filename, const std::string &mode);
    int  Close();
    int  GetSize() const;
    bool IsEOF() const;

    // Reading
    int      ReadString(unsigned int length, std::string &str);
    int      ReadLine(std::string &str);
    asINT64  ReadInt(asUINT bytes);
    asQWORD  ReadUInt(asUINT bytes);
    float    ReadFloat();
    double   ReadDouble();

    // Writing
    int WriteString(const std::string &str);
    int WriteInt(asINT64 v, asUINT bytes);
    int WriteUInt(asQWORD v, asUINT bytes);
    int WriteFloat(float v);
    int WriteDouble(double v);

    // Cursor
    int GetPos() const;
    int SetPos(int pos);
    int MovePos(int delta);

    // Big-endian = most significant byte first
    bool mostSignificantByteFirst;

protected:
    ~ScriptFileSafe();

    mutable int refCount;
    FILE       *file;
};

// This function will determine the configuration of the engine
// and use one of the two functions below to register the file type
void RegisterScriptFile(asIScriptEngine *engine);

// Call this function to register the file type
// using native calling conventions
void RegisterScriptFile_Native(asIScriptEngine *engine);

// Use this one instead if native calling conventions
// are not supported on the target platform
void RegisterScriptFile_Generic(asIScriptEngine *engine);

END_AS_NAMESPACE

#endif // SCRIPTFILESAFE_H__

#endif // WITH_ANGELSCRIPT