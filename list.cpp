//
// Created by jewul on 05/08/2025.
//

/******************************************************************
 * Source File Lister
 *
 * Print the contents of the source file in a formate that includes
 * page headings, line numbers, and nesting levels.
 *
 * FILE: list.cpp
 *
 * USAGE: list <source file>
 *		  <source file> name of the source file to list.
 * ****************************************************************/

#include <iostream>
#include "buffer.h"
#include "error.h"

//---------------------------------------------------------------
// main
//---------------------------------------------------------------
int main(int argc, char *argv[])
{
	char ch;

	//-- Check the command line arguments.
	if (argc != 2) {
		std::cerr << "Usage: list <source file name>" << std::endl;
		AbortTranslation(abortInvalidCommandLineArgs);
	}

	//-- Create source file buffer.
	TSourceBuffer source(argv[1]);

	//-- Loop to fetch each character of the source
	do {
		ch = source.GetChar();
	} while (ch != eofChar);

	return 0;
}