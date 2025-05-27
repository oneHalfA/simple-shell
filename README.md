# 🐚 Simple C Shell

This is a basic shell written in C. It provides a minimal command-line interface that can execute built-in and external commands, mimicking the behavior of traditional UNIX shells.

## Features

- Execute external commands (e.g., `ls`, `pwd`, `gcc`, etc.)
- Built-in commands:
  - `cd` – change directory
  - `exit` – exit the shell
  - `pwd` = print working directory
  - `echo` - prints text to the terminal
  - `type` - tells how a command is interpreted by the shell
- Basic error handling

## Getting Started

### 🔧 Requirements

- A C compiler (e.g., `gcc`, `clang`)

### 🧪 Build and Run

```bash
git clone https://github.com/yourusername/simple-c-shell.git
cd simple-c-shell
make          # or use: gcc -o mysh shell.c
