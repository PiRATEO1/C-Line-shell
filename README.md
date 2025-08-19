Cline Shell cline
A lightweight, cross-platform command-line shell built from the ground up in C. Cline serves as a simple yet powerful interface for interacting with the operating system, combining the core principles of classic Unix shells with modern usability features like command history and tab completion.

This project was developed to explore fundamental concepts of systems programming, including process management, memory allocation, and platform-specific API usage for both Windows and Unix-like systems.

✨ Features
Cross-Platform: Works on both Windows (via MinGW) and Unix-like systems (Linux, macOS).

Interactive Prompt: Displays the current working directory to keep you oriented.

Command History: Cycle through previous commands using the Up and Down arrow keys.

Built-in Commands: Includes essential commands like cd, pwd, exit, and clear.

External Command Execution: Can launch any program or command available in the system's PATH.

🚀 Getting Started
Prerequisites
A C compiler (e.g., GCC/MinGW).

The GNU Readline library.

On Windows (MSYS2/MinGW):

pacman -S mingw-w64-x86_64-readline

On Debian/Ubuntu:

sudo apt-get install libreadline-dev

On macOS (Homebrew):

brew install readline

Compilation
To compile the shell, you must link the Readline library using the -lreadline flag.

gcc -std=c99 -Wall cline.c -o cline -lreadline

(On Windows, you may want to name the output cline.exe)

Execution
Run the compiled executable from your terminal:

./cline

🛠️ Built-in Commands
Cline comes with several built-in commands that are handled internally for speed and functionality.

Command

Description

Usage Example

cd [path]

- Changes the current working directory to the specified path.

- cd /var/log

pwd

- Prints the full path of the current working directory.

clear / cls

- Clears the terminal screen. Works with both clear and cls.

start [app]

- (Windows only) Launches an application by name (e.g., notepad, calc).
e.g: start notepad

exit
- Exits the Cline shell and returns to the parent terminal.

exit

