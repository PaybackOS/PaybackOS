#ifndef STTY_H
#define STTY_H 1
#pragma once

int init_serial();
char read_serial();
void write_serial(char a);
void print_serial(char* data);

#endif