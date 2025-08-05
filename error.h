//
// Created by jewul on 03/08/2025.
//

/******************************************************************************
 * ERRORS
 * Routines to handle translation-time and runtime errors.
 *
 * FILE: error.h
 *
 * MODULE: Error
 ******************************************************************************/

#ifndef ERROR_H
#define ERROR_H

extern int errorCount;

//-------------------------------------------------------------------------
//	Abort codes for fatal translator errors.
//-------------------------------------------------------------------------


enum TAbortCode {
	abortInvalidCommandLineArgs		= -1,
	abortSourceFileOpenFailed       = -2,
	abortIFormFileOpenFailed        = -3,
	abortAssemblyFileOpenFailed     = -4,
	abortTooManySyntaxErrors        = -5,
	abortStackOverflow              = -6,
	abortCodeSegmentOverflow        = -7,
	abortNestingTooDeep             = -8,
	abortRuntimeError               = -9,
	abortUnimplementedFeature       = -10,
};

void AbortTranslation(TAbortCode ac);

#endif //ERROR_H
