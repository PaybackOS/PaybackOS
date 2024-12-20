---
layout: default
title: Memory Allocation
author: ThatOSDeveloper
---

# {{ page.title }}

Author: {{ page.author }}

## Overview

Memory allocation is a very important part of any OS in general, without it there would be no way to store data in memory, it is a very basic thing that is required for any OS to function.

How we went about developing a memory allocation solution was simple, do what everyone else did, take the Public Domain liballoc and put it in our own kernel then make the hooks it needs to function properly.

## The hooks and what they do

First we have the ```liballoc_lock();``` and ```liballoc_unlock();``` functions which allow us to lock liballoc to stop more than once memory allocation from doing anything at a time (useful on a multithreaded system where multiple apps run at once)

Then we have the 2 main ones which are ```liballoc_alloc();``` and ```liballoc_free();``` These handle allocating memory itself which is the heart of liballoc, liballoc_alloc handles the allocation of it while free handles marking it as free to use for future allocations.

[back](../)