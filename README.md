# Basic Healthcare Management System (C)

A simple console-based healthcare management system written in C. This project demonstrates basic C programming skills and a menu-driven console interface for managing simple records.

## Features
- Menu-driven console interface
- Data input and display
- Simple record file management (persistent storage in local files)
- Written entirely in C
- Designed as a learning exercise for C fundamentals

## Prerequisites
- A C compiler such as `gcc`
- A POSIX-like environment (Linux, macOS, WSL on Windows) or any environment with a working C toolchain

## How to Build and Run (functional, step-by-step)

Follow these exact commands in a terminal. Commands assume a Unix-like shell (Linux, macOS, or WSL on Windows).

1. Clone the repository:
   git clone https://github.com/Shem-apiyo/basic_healthcare_system.git

2. Navigate into the project directory:
   cd basic_healthcare_system

3. Inspect the files (optional but helpful):
   ls -la

4. Create the data directory used by the program (the program expects a writable `data/` directory):
   mkdir -p data

5. Compile the program. If the repository has a single source file named `basic_healthcare_management_system.c`, run:
   gcc -Wall -Wextra -std=c11 basic_healthcare_management_system.c -o management_system

   If there are multiple `.c` files, compile them all together:
   gcc -Wall -Wextra -std=c11 *.c -o management_system

   Notes:
   - `-Wall -Wextra` enables common compiler warnings to help catch issues.
   - `-std=c11` ensures a modern C standard; change if your code targets another standard.

6. Run the program:
   ./management_system

7. Typical runtime steps (within the program):
   - Use the on-screen menu to add records, view records, or delete records.
   - Records are stored in the `data/` directory (for example `data/records.txt`). The exact filename depends on the program; see the source if unsure.

8. If you get a "file not found" error for a data file, create an empty file the program expects (example):
   touch data/records.txt

9. If you prefer using a Makefile, create a simple Makefile with this content and run `make`:
   all:
\tgcc -Wall -Wextra -std=c11 basic_healthcare_management_system.c -o management_system

10. Troubleshooting:
- If compilation fails with "file not found" for the source file, confirm the filename with `ls` and adjust the gcc command accordingly.
- On Windows (without WSL), install MinGW or use an IDE that supports C compilation, or run the build in WSL.

## Project Structure (necessary files)

- `basic_healthcare_management_system.c` — main source code file (required)
- `Makefile` — optional (useful to build the project with `make`)
- `data/` — directory where the program stores persistent records (create with `mkdir -p data` if missing)
- `data/records.txt` or similar — example persistent data file created/used by the program
- `README.md` — this file
- `LICENSE` — MIT license file
- `.gitignore` — optional, recommended to ignore compiled binaries and data files

Note: If any of the above files are missing in the repository, the program can still run if the main source file exists; create `data/` and an empty `data/records.txt` file before running if needed.

## Usage
Run the compiled program and follow the on-screen menu to add, view, or manage records. The program uses simple file-based storage to persist records between runs.

## Purpose
This project is intended as a learning exercise to practice:
- C syntax and control structures
- User input handling
- Console-based application design
- Basic file I/O and record management

## Contributing
Contributions are welcome. If you'd like to improve the program (bug fixes, additional features, better file formats, tests), please open an issue or submit a pull request.

## License
This project is licensed under the MIT License.
