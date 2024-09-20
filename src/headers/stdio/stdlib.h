#ifndef STDLIB_H
#define STDLIB_H 1
#pragma once

#include <stddef.h>

void	*malloc(size_t);				//< The standard function.
void	*realloc(void *, size_t);		//< The standard function.
void	*calloc(size_t, size_t);		//< The standard function.
void	free(void *);					//< The standard function.

#endif