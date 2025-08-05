//
// Created by jewul on 04/08/2025.
//

/******************************************************************************
 *   ERRORS
 *   Routines to handle translation-time and runtime errors.
 *
 *   FILE: error.cpp
 *
 *   MODULE: Error
 ******************************************************************************/

//------------------------------------------------------------------------------
// Abort Messages:	Keyed to enumeration type TAbortCode
//------------------------------------------------------------------------------

#include <stdlib.h>	// deprecated
#include <cstdlib>
#include <iostream>
#include <cstddef>

#include "error.h"

static const char *abortMsg[] = {
	NULL,
	"Invalid command line arguments",
	"Failed to open source file",
	"Failed to open intermediate form file",
	"Failed to open assembly file",
	"Too many syntax errors",
	"Stack overflow",
	"Code segment overflow",
	"Nesting too deep",
	"Runtime error",
	"Unimplemented feature",
};

//------------------------------------------------------------------------------
// AbortTranslation:	A fatal error occurred during the translation.
//                      Print the abort code to the error file and then exit.
// ac : abort code
//------------------------------------------------------------------------------
void AbortTranslation(TAbortCode ac)
{
	std::cerr << "*** Fatal translator error: " << abortMsg[-ac] << std::endl;	// the negative sign is to correct the TAbortCode enumerations
	exit(ac);
}
