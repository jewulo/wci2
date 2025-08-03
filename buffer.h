//
// Created by jewul on 03/08/2025.
//

#ifndef BUFFER_H
#define BUFFER_H

#include <fstream>
#include <cstdio>
#include <string.h>
#include <string>

#include "misc.h"
#include "error.h"

//              *************
//              *           *
//              *   Input   *
//              *           *
//              *************

extern char eofChar;
extern int   inputPosition;
extern int   listFlag;
extern int   level;

const int maxInputBufferSize = 256;

//--------------------------------------------------------------------
//      TTextInBuffer   Abstract text input buffer class.
//--------------------------------------------------------------------

class TTextInBuffer {

protected:
    fstream  file;                          // input text file
    char    *const pFilename;               // ptr to the file name
    char     text[maxInputBufferSize];      // input text buffer
    int     *pChar;                         // ptr to the current char in the text buffer

    virtual char GetLine(void) = 0;
public:
    TTextInBuffer(const char *pInputFilename, TAbortCode ac);

    virtual ~TTextInBuffer()
    {
        file.close();
        delete pFilename;
    }

    void Char       (void) const { return *pChar; };
    char GetChar    (void);
    char PutBackChar(void);
};

extern char *buffer;

//--------------------------------------------------------------------
//      TSourceBuffer   Source buffer subclass of TTextInBuffer.
//--------------------------------------------------------------------

class TSourceBuffer : public TTextInBuffer {

    virtual char GetLine(void);
public:
    TSourceBuffer(const char *pSourceFileName);
};


//              **************
//              *            *
//              *   Output   *
//              *            *
//              **************

//--------------------------------------------------------------------
//      TTextOutBuffer   Abstract text output buffer class.
//--------------------------------------------------------------------

class TTextOutBuffer {

public:
    char text[maxInputBufferSize + 16];     // output text buffer

    virtual void PutLine(void) = 0;

    void PutLine(const char *pText)
    {
        strcpy(text, pText);
        PutLine();
    }
};

//--------------------------------------------------------------------
//      TListBuffer   List buffer subclass of TTextOutputBuffer.
//--------------------------------------------------------------------
class TListBuffer : public TTextOutBuffer {

    char *pSourceFileName;      // pointer to source file name (for page header)
    char  date[26];             // date string for page header
    int   pageNumber;            // current page number
    int   lineCount;            // count of lines in the current page

    void PrintPageHeader(void);

public:
    virtual ~TListBuffer(void) { delete pSourceFileName; }

    void Initialise(const char *fileName);
    virtual void PutLine(void);

    void PutLine(const char *pText)
    {
        TTextOutBuffer::PutLine(pText);
    }

    void PutLine(const char *pText, int lineNumber, int nestingLevel)
    {
        sprintf(text, "%4d %d: %s", lineNumber, nestingLevel, pText);
        PutLine();
    }
};

extern TListBuffer list;
#endif //BUFFER_H