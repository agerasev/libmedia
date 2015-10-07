#pragma once

#include <cstdio>
#define logMessage(...) do { fprintf(stdout,__VA_ARGS__); fprintf(stdout,"\n"); } while(false)
#define logWarning(...) do { fprintf(stderr,__VA_ARGS__); fprintf(stderr,"\n"); } while(false)
