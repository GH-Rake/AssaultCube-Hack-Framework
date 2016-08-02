# ACHack Framework v0.2

This is a framework I started working on and have stopped development at this time.  Aimbot & ESP are working.

## What does this do?

The idea is all the backend stuff is already written, when you start working on a new game you just make wrappers or derived classes that interface between the new game and the framework.

## Why?

Why a framework?  Make my life easier, put as much of this repetitive stuff on autopilot as possible.

## Usage

Launch Assault Cube.  Compile project.  Inject the DLL.

## TODO

Combine with pattern scan project goodies
Add some polymorphism.
Replace aimbot/esp classes & member functions with namespaces
Get Laid

```
#!c++

#ifdef FW_EXTERNAL
#include "FW\external\patternscan.h"
#else
#include "FW\internal\patternscan.h"
#endif
```

## Development History

My projects are really just one big project that has been evolving for the past 2 years in different forms and this will be my attempt to put all the stuff together into one master framework that I can put in a sack and take with me where ever I go.  Started External Assault Cube aimbot, went internal with it, then ported it to OpenArena, now I've rewritten everything I learned into this framework.  I put this project on pause until I finish the pattern scan project

##Credits

I couldn't have done it all without the help of my friends at http://GuidedHacking.com