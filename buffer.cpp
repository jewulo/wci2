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
 *   I/O Buffers
 *
 *   Process the I/O files. Included are member functions to read the
 *   source file and write to the list file.
 *
 *   CLASSES: TTextInBuffer, TSourceBuffer
 *          TTextOutBuffer, TListBuffer
 *
 *   FILE: buffer.cpp
 *
 *   MODULE: Buffer
 *
 * ***************************************************************************/


char eofChar = 0x7F;  // special end-of-file character
int  inputPosition;   // *virtual* position of the current character in the input buffer (with tabs expanded)

int listFlag = True;  // true if list source lines, else false
//----------------------------------------------------------------------------
// Constructor: Construct an input text buffer by opening the input file.
//
// pInputFileName: pointer to the name of the input file
// ac:             abort code to use if open failed.
//----------------------------------------------------------------------------
TTextInBuffer::TTextInBuffer(const char *pInputFilename, TAbortCode ac)
   :  pFileName(new char[strlen(pInputFilename) + 1]),
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

   if      (*pChar == eofChar)   { return  eofChar; } // end of file
   else if (*pChar == '\0')      { ch = GetLine();} // end of line
   else {
      ++pChar;
      ++inputPosition;
      ch = *pChar;
   }

   // -- if tab character, increment inputPosition to the next
   // -- multiple of tabSize.
   if (ch == '\t') { inputPosition += tabSize - inputPosition;}
   return ch;
}

//----------------------------------------------------------------------------
// PutBackChar: Put the current character back into the input buffer so that
//              the next call to GetChar will fetch this character.
//              (Only called to put back a '.')
//
// Return: next previous character.
//----------------------------------------------------------------------------
char TTextInBuffer::PutBackChar(void)
{
   --pChar;
   --inputPosition;

   return *pChar;
}

/******************************************************************************
 * Source Buffer.
 ******************************************************************************/

//----------------------------------------------------------------------------
// Constructor: Construct a source buffer by opening the source file.
//              Initialize the list file, and read the first line from
//              the source file.
//
// pInputFileName: pointer to the name of source file.
//----------------------------------------------------------------------------
TSourceBuffer::TSourceBuffer(const char *pSourceFileName)
   : TTextInBuffer(pSourceFileName, abortSourceFileOpenFailed)
{
   //-- Initialize the list file and read the first source line.
   if (listFlag) list.Initialize(pSourceFileName);
   GetLine();
   // TSourceBuffer::GetLine();  // IDE says that you have to qualify name to explicitly specify the method call.
}

//----------------------------------------------------------------------------
// GetLine: Read the next line from the source file, and print it to the
//          list file preceded by the line number and the current nesting
//          level.
//
// Return: first character of the source line of the end-of-file character
//         if at the end of the file.
//----------------------------------------------------------------------------
char TSourceBuffer::GetLine(void)
{
   extern int lineNumber, currentNestingLevel;

   //-- If at the end of the source file, return the end-of-file char.
   if (file.eof()) pChar = &eofChar;

   //-- Else read the next source line and print it to the list file.
   else {
      file.getline(text, maxInputBufferSize);
      pChar = text;  // point to the first source line char

      if (listFlag)
         list.PutLine(text, ++currentLineNumber, currentNestingLevel);
   }

   inputPosition = 0;
   return *pChar;
}

/******************************************************************************
 * List Buffer.
 ******************************************************************************/
const int maxPrintLineLength  = 80;
const int maxLinesPerPage     = 50;

TListBuffer list;    // the list file buffer

//----------------------------------------------------------------------------
// PrintPageHeader: Start a new page of the list file and print
//                  the page header.
//----------------------------------------------------------------------------
void TListBuffer::PrintPageHeader(void)
{
   const char formFeedChar = '\f';

   std::cout << formFeedChar << "Page " << ++pageNumber
             << "    " << pSourceFileName << "    " << date
             << std::endl << std::endl;

   lineCount = 0;
}

//----------------------------------------------------------------------------
// Initialize:  Initialize the list buffer. Set the date for the page header
//              and print the first header.
//
// pFileName:   pointer to source file name (for the page header).
//----------------------------------------------------------------------------
void TListBuffer::Initialize(const char *pFileName)
{
   text[0] = '\0';
   pageNumber = 0;

   //-- Copy the source file name.
   pSourceFileName = new char[strlen(pFileName) + 1];
   strcpy(pSourceFileName, pFileName);

   //-- Set the date.
   time_t timer;
   time(&timer);
   strcpy(date, asctime(localtime(&timer)));
   date[strlen(date) - 1] = '\0';   // remove '\n' at the end.

   PrintPageHeader();
}

//----------------------------------------------------------------------------
// PutLine: Print a line of text to the list file.
//----------------------------------------------------------------------------
void TListBuffer::PutLine(void)
{
   //--Start a new page if the current one is full.
   if (listFlag && (lineCount == maxLinesPerPage)) {
      PrintPageHeader();
   }

   //--Truncate the line if it's too long.
   text[maxPrintLineLength] = '\0';

   //--Print the text line. and then blank out the text.
   std::cout << text << std::endl;
   text[0] = '\0';

   ++lineCount;
}
