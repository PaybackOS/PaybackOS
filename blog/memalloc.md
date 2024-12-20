---
layout: default
title: Memory Allocation
author: ThatOSDeveloper
---

# {{ page.title }}

Author: {{ page.author }}

Memory allocation is a very important part of any OS in general, without it there would be no way to store data in memory, it is a very basic thing that is required for any OS to function.

How we went about developing a memory allocation solution was simple, do what everyone else did, take the Public Domain liballoc and put it in our own kernel then make the hooks it needs to function properly.

[back](../)