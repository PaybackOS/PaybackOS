#ifndef LOG_H
#define LOG_H 1
#pragma once

/*
A simple logging function

Log level 1 is OK or nothing is broken
Log level 2 is WARN or a warning that something may be broken but it is not known
Log level 3 is ERROR or a error that is something is broken and the OS will no longer be able to work
*/
void log(int level, char* effect);

#endif