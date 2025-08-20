C-Line Shell

Version 1.0.1

A lightweight, cross-platform command-line shell built from the ground up in C. Cline serves as a simple yet powerful interface for interacting with the operating system, combining the core principles of classic Unix shells with modern usability features like command history and tab completion.

This project was developed to explore fundamental concepts of systems programming, including process management, memory allocation, and platform-specific API usage for both Windows and Unix-like systems.

FEATURES
Cross-Platform: Works on both Windows (via MinGW) and Unix-like systems (Linux, macOS).

Interactive Prompt: Displays the current working directory to keep you oriented.

Command History: Cycle through previous commands using the Up and Down arrow keys.

Tab Completion: Automatically completes file and directory paths when the Tab key is pressed.

Built-in Commands: Includes essential commands for navigation, system control, and application launching.

External Command Execution: Can launch any program or command available in the system's PATH.

GETTING STARTED
--- For Developers (Compiling from Source) ---

Prerequisites:

A C compiler (e.g., GCC/MinGW).

The GNU Readline library.

On Windows (MSYS2/MinGW): pacman -S mingw-w64-x86_64-readline

On Debian/Ubuntu: sudo apt-get install libreadline-dev

On macOS (Homebrew): brew install readline

Compilation:
To compile the shell, you must link the Readline library using the -lreadline flag.
gcc -std=c99 -Wall cline.c -o cline -lreadline
(On Windows, you may want to name the output cline.exe)

--- For Users (Running Without Compiling - Windows) ---

You can run Cline on any Windows machine without needing to install a compiler by packaging the executable with its required library files.

Find the Executable: Locate your compiled cline.exe file.

Find the Dependencies: Go to your MSYS2 installation folder (usually C:\msys64\ucrt64\bin) and find the following files:

libreadline8.dll

libncursesw6.dll

Create a Package:

Create a new folder (e.g., Cline Shell).

Copy cline.exe into this new folder.

Copy the two .dll files into the same folder.

Run: You can now zip this folder and share it. Users can run cline.exe directly from this folder.

BUILT-IN COMMANDS
Cline comes with several built-in commands that are handled internally for speed and functionality.

cd [path]

Description: Changes the current working directory to the specified path.

Usage Example: cd C:\Users

pwd

Description: Prints the full path of the current working directory.

Usage Example: pwd

clear / cls

Description: Clears the terminal screen. Works with both clear and cls.

Usage Example: clear

camera

Description: (Windows only) Launches the default Windows Camera application.

Usage Example: camera

start [app]

Description: (Windows only) Launches an application by name.

Usage Example: start notepad

shutdown

Description: Shuts down the computer immediately.

Usage Example: shutdown

restart

Description: Restarts the computer immediately.

Usage Example: restart

sleep

Description: Puts the computer into sleep/suspend mode.

Usage Example: sleep

lock

Description: (Windows only) Locks the computer workstation.

Usage Example: lock

help

Description: Displays a list of all available built-in commands.

Usage Example: help

exit

Description: Exits the Cline shell and returns to the parent terminal.

Usage Example: exit
