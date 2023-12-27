#pragma once

// Errors of function that solves task
typedef enum Error
{
    ok,
    fileDidNotOpen,
    incorrectInputFile
} Error;

// Function that solving task
Error solveFileTask(const char* const arrayFileName, const char* const numberFileName, const char* const outputFileName);