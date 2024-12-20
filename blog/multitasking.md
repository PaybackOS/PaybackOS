---
layout: default
title: Implementing Multitasking
author: ThatOSDeveloper
---

# {{ page.title }}

Author: {{ page.author }}

Now that the implementation of multitasking is complete, the PaybackOS team would like to share an overview of how a simple multitasking system works and how it can be implemented.

## Overview of Multitasking Types

There are several types of multitasking, each varying in complexity, with some featuring subtypes. Here, we will cover the most common and essential multitasking models.

### Cooperative Multitasking

Cooperative multitasking is a basic form of multitasking where the operating system relies on running applications to yield control voluntarily. In this model, each function or application is added to a list of running tasks, and tasks switch based on when they yield control of the CPU. However, this simplicity comes with several limitations.

#### Drawbacks:
- Applications may fail to yield control voluntarily, leading to system freezes or crashes.
- If one application crashes, it can affect the entire system, as the crashing app controls the sole thread.

#### Key Benefits:
- More simple to build and develop for.

This approach was used in early systems such as Windows 3.x, pre-macOS X versions of macOS, and numerous hobby operating systems.

### Preemptive Multitasking

In a preemptive multitasking system, task switching occurs automatically, without requiring the currently running task to give up control. The operating system dictates these transitions based on various factors, ensuring enhanced stability and responsiveness. Preemptive multitasking is the standard model used by modern operating systems like Linux, *BSD, post-Windows 3.x versions of Windows, and macOS.

#### Key Benefits:
- Tasks are assigned a time slice to run before the operating system forces a switch to another task.
- Tasks run independently, without relying on the cooperation of other tasks, leading to better system stability (this is why it was used in pretty much every major OS).

#### Drawbacks:
- Far more complex to implement.

### Multithreading

Multithreading is a subset of multitasking that can be used with either of the aforementioned approaches. It allows applications to run in parallel by utilizing different threads or cores of the CPU. This approach enables true concurrent execution without one task hindering the progress of another.

#### Key Feature:
- Each task can run on a separate thread, allowing for parallel execution on multi-core processors.
- Multithreading is critical for modern systems to fully utilize hardware capabilities and achieve efficient execution.

[back](../)