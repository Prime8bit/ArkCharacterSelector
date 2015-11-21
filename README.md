# ArkCharacterSelector
This is a small application used to allow players of ARK: Survival Evolved to switch between characters in the single player mode.

## Installation
The Visual C++ 2013 Redistributable package must be installed for this application to work. If you do not have it installed then you can find an installer in this project's bin directory named "vcredist_(architecture).exe". You can also install it from Microsoft's [official link](https://www.microsoft.com/en-us/download/details.aspx?id=40784).

Download the zip package for this application from the bin directory of this project. If one does not exist then you must build one from source. See the **Build Instructions** section for details.
Extract all files into the same folder as the ARK Game executable called "ShooterGame.exe". This file is generally located at:

    Windows - C:\Program Files (x86)\Steam\steamapps\common\ARK\ShooterGame\binaries
	Linux - ~/.steam/steam/steamapps/common/ARK/ShooterGame/Binaries/Linux
	Mac - Are macs even capable of playing ARK: Survival Evolved? Also, I don't own a Mac and have no idea of the location. 
	
Windows users will also neet to change the compatibility settings to run as Administrator. The reason for this is that the application can't edit files anywhere in "Program Files (x86)" or "Program files" without admin privileges. It needs this ability to rename your character's files.

You should now be able to use ArkCharacterSelector.exe to choose characters. If the tool does not work as expected then you may be able to see error info logged in the ArkCharacterSelector.log file.

## Usage
Click the "New" button to run ARK: Survival Evolve in "New Character Mode". In this mode, ARK will allow you to create a new character when you start a single player game. Select a character and click the "Play" button to play as that character. Select a Character and hit the "Delete" button to delete that character.

The map will be the same for all characters allowing you to build bases with one character and use those bases with another.

If the tool does not work as expected then you may be able to see errors logged in the ArkCharacterSelector.log file.

**IMPORTANT: When you switch characters, the last character you used will be found lying unconscious in the place where you logged off. That character can be killed in that state (even by your current character if you are so inclined) and normal death penalties apply... including dropping of loot. Ensure that your characters are in a safe location before switching characters so they aren't killed by random dinos.**

**IMPORTANT: If you name characters the same name then you may get unexpected results. This utility is not designed to backup a single character, it is designed to allow you to play multiple charcters.**

**IMPORTANT: You should ensure that ARK: Survival Evolved is not running while using the ARK Character Selector. If you do not then you may get unexpected results.**

**DISCLAIMER: I do not own the rights to the ARK: Survival Evolved name or logo. I am not a member of the ARK: Survival Evolved team. Neither I nor they are responsible for corrupted save data due to the usage of this tool. I do my best to ensure it does not corrupt save data, especially since I use this tool myself, but you use it at your own risk.**

## Build Instructions
This application was developed with cross-platform capability in mind. It was developed using Qt Creator 3.5.1 using Qt 5.5. It is possible that this application will work with other versions of Qt, but I make no guarantees. The root of the repository is the root of the project.

1. Open project.
2. Build project.

There isn't anything complicated about the build procedure. The application assumes that all save files are located in the relative directory "../Saved/SavedArksLocal" and that the location of ShooterGame.exe is in the same directory as the application.

## License
ARK Character Selector uses the MIT license. See LICENSE for details.

This tool was created with Qt which uses the LPGL license. See the files in the Qt_License directory for details.
