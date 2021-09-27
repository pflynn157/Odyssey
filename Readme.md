## Odyssey

Odyssey is a file explorer written in C++ using the Qt framework. It has many of the features you would expect in a file explorer. Currently, all features only work on Linux. It does build and run on Windows, but several features do not work. The build system is CMake. Just run CMake and run make.

### Features

Here is what is currently supported:

1. Tabs (If you are a Linux or Mac user, you will know how great these are)
2. Theme icon support (pulls from the current theme)
3. Icon by mimetype (pulls from theme)
4. Button and text address bars
5. History support (used with the back button)
6. Full cut/copy/paste support, across tabs and with multiple files
7. Trash support (move to trash and restore from trash)
8. Application chooser for files (based on mimetype)
9. Keyboard shortcuts
10. Places sidebar
11. Drive list (harddrive, usb drive, cd, etc)
12. Background refresh   

### Name

If you're curious about the name, there's two reasons. The first is simply because I think its a good name for a file explorer (an odyssey through your file system...). The second is because I named my first significant desktop application- which was also a file explorer- Odyssey, and I have good memories of the time when I worked on it.

### Terminal

Odyssey now has it's own terminal! I wanted to find a way to use the system terminal, but I haven't been successful, and on second thought I'd kind of like to have my own just so it stays portable across systems.

I thought about writing my own (and that's certainly a possibility for down the line), but for now I'm using an unmodified fork of ST, the terminal from Suckless Software. Regardless of what you think of them, their software is good and easy to maintain and work with, and their liberal licensing is nice. The only thing I really did was connect it to the rest of the CMake build system (which will probably give them a heart attack if they ever see it...).

The binary is built as "odyt", and is installed with the rest of the system binaries.


