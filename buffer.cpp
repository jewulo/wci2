//
// Created by jewul on 03/08/2025.
//

/******************************************************************************
 * I/O BUFFERS
 * Process text I/O files. Included are member functions
 * to read the source file and write to the list file.
 *
 * CLASSES: TTextInBuffer, TSourceBuffer, TTextOutBuffer, TListBuffer
 *
 * FILE: buffer.cpp
 *
 * MODULE: Buffer
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <iostream> // iostream.h not found
#include <time.h>

#include "buffer.h"
#include "common.h"

/******************************************************************************
 * Text Input Buffer.
 ******************************************************************************/

char eofChar = 0x7F;  // special end-of-file character
int  inputPosition;   // *virtual* position of the current character in the input buffer (with tabs expanded)

//----------------------------------------------------------------------------
// Constructor: Construct an input text buffer by opening the input file.
//
// pInputFileName: pointer to the name of the input file
// ac:             abort code to use if open failed.
//----------------------------------------------------------------------------
TTextInBuffer::TTextInBuffer(const char *pInputFilename, TAbortCode ac)
 : pFileName(new char[strlen(pInputFilename) + 1]),
   text{},
   pChar(nullptr)
{
 // -- Copy the input file name.
 strcpy(pFileName, pInputFilename);

 // -- Open the input file. Abort if failed.
 // file.open(pFileName, std::ios::in | std::ios::nocreate); // std::ios::nocreate does not exist in the standard
 file.open(pFileName, std::ios::in); // this will achieve the same thing.
 if (!file.good()) AbortTranslation(ac);
}

//----------------------------------------------------------------------------
// GetChar: Fetch and return the next character from the text buffer.
//          If at the end of the buffer, read the next source line.
//          If at the end of the file, return the end-of-file character.
//
// Return: next character from the source file or the end-of-file character.
//----------------------------------------------------------------------------
char TTextInBuffer::GetChar(void)
{
 const int tabSize = 8; // size of tabs
 char ch;               // character return

 if      (*pChar == eofChar) { return  eofChar; } // end of file
 else if (*pChar == '\0') { ch == GetLine();} // end of line
 else {
    ++pChar;
    ++inputPosition;
    ch = *pChar;
 }
 // -- iF tab character, increament inputPosition to the next
 // -- multiple of tabSize.
 if (ch == '\t') { inputPosition += tabSize - inputPosition;}
 return ch;
}