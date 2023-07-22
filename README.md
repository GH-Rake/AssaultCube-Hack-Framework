# Assault Cube Hack Framework - Aimbot & ESP

This repository contains the source code for an Assault Cube Hack Framework, which includes features such as an Aimbot and ESP (Extra Sensory Perception). The framework is designed to provide a set of tools and functionalities that can be used to modify the game Assault Cube.

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

Features
--------

The framework includes the following features:

1.  Aimbot: This feature automatically aligns the player's aim to the target. It is implemented in the `AC_Hack.cpp` file, where the `GetTarget` function is used to lock onto a target if the right mouse button is pressed and the Aimbot is active.

2.  ESP (Extra Sensory Perception): This feature provides the player with additional information about other players, such as their location, health, and other attributes. The implementation can be found in the `AC_Hack.cpp` file, where the `FW::ESP::ESP` function is used to set up the ESP if it is active.

3.  No Recoil: This feature eliminates the recoil effect when shooting. It can be toggled on and off with the F3 key.

4.  Fly Hack: This feature allows the player to fly in the game. It can be toggled on and off with the F4 key.

5.  No Scope: This feature removes the need for a scope when shooting. It can be toggled on and off with the F5 key.

6.  Menu: A menu is provided for the player to interact with the hack features. The menu is built using the `Menu_t` class and can be toggled on and off with the Insert key.

Experience Level
----------------

The source code in this repository is quite advanced and requires a good understanding of C++ and game hacking concepts. Familiarity with the OpenGL library and Windows API is also beneficial.

End Goal
--------

The end goal of this source code is to provide a framework for creating game hacks for Assault Cube. The framework provides a set of tools and functionalities that can be used to modify the game, such as an Aimbot, ESP, and other features. The source code can be used as a starting point for creating your own game hacks.

Code Highlights
---------------

The main loop of the hack is implemented in the `AC_t::HackLoop` function in the `AC_Hack.cpp` file. This function is responsible for reading the game data, player data, and hotkeys, and for drawing the menu and enabling the ESP and Aimbot features if they are active.

The `AC_t::ReadPlayerData` function reads the data of all players in the game and stores it in the `players` vector. Each player is represented by an instance of the `AC_Player_t` class, which contains information such as the player's team, position, and health.

The `AC_t::ReadHotKeys` function reads the state of the hotkeys and toggles the corresponding hack features on and off. For example, if the F1 key is pressed, the Aimbot feature is toggled on or off.

The `AC_t::Load` function initializes the hack features and hooks the `wglSwapBuffers` function to the `hwglSwapBuffers` function, which calls the `AC_t::HackLoop` function every time the game screen is updated.

## Development History

My projects are really just one big project that has been evolving for the past 2 years in different forms and this will be my attempt to put all the stuff together into one master framework that I can put in a sack and take with me where ever I go.  Started External Assault Cube aimbot, went internal with it, then ported it to OpenArena, now I've rewritten everything I learned into this framework.  I put this project on pause until I finish the pattern scan project

FAQ
----

Q: What is an Aimbot? A: An Aimbot is a feature in game hacks that automatically aligns the player's aim to the target.

Q: What is ESP? A: ESP stands for Extra Sensory Perception. It is a feature in game hacks that provides the player with additional information about other players, such as their location, health, and other attributes.

Q: What is the purpose of the `wglSwapBuffers` hook? A: The `wglSwapBuffers` function is a part of the OpenGL library and is responsible for swapping the front and back buffers of the current drawing surface. By hooking this function, the hack can execute its own code every time the game screen is updated.

Q: What is the `AC_Player_t` class? A: The `AC_Player_t` class represents a player in the game. It contains information such as the player's team, position, and health.

The end goal of this source code is to provide a framework for creating game hacks for Assault Cube. The framework provides a set of tools and functionalities that can be used to modify the game, such as an Aimbot, ESP, and other features. The source code can be used as a starting point for creating your own game hacks.

### Official GH Tools

-   [GH Undetected Cheat Engine](https://guidedhacking.com/resources/gh-undetected-cheat-engine-download-udce-driver.14/) - bypasses EAC and Battleye as of release in 2022
-   [GH Unreal Engine Dumper](https://guidedhacking.com/resources/gh-unreal-engine-dumper-ue4-cheat-engine-plugin.763/) - Dumps offsets and much more for all UE4 games
-   [GH Cheat Engine SigMaker Plugin](https://guidedhacking.com/resources/guided-hacking-x64-cheat-engine-sigmaker-plugin-ce-7-2.319/) - Generate code signatures with 2 clicks
-   [GH Entity List Finder](https://guidedhacking.com/resources/gh-entity-list-finder.36/) - Dump the address of the entity list in 5 minutes
-   [GH VMProtect3 Import Fixer](https://guidedhacking.com/resources/gh-vmprotect-3-import-fixer.25/) - Rebuild the import table on the latest VMProtect
-   [GH Offset Dumper](https://guidedhacking.com/resources/guided-hacking-offset-dumper-gh-offset-dumper.51/) - C++ dumper and CSGO netvar manager
-   [GH DLL Injector](https://guidedhacking.com/resources/guided-hacking-dll-injector.4/) - The Best Injector Ever Made
