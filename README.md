# Simple Shell Project

## Description
This project is a simple implementation of a UNIX command line interpreter. The shell is designed to mimic the functionality of the original UNIX shell, with a focus on learning and understanding the fundamental concepts of operating systems, C programming, and process management.

## Tasks

### 0. Betty would be proud
- **Mandatory**
- Write a beautiful code that passes the Betty checks.

**Repository:**  
GitHub repository: `simple_shell`

### 1. Simple Shell 0.1
- **Mandatory**
- Write a UNIX command line interpreter.

**Usage:**  
`simple_shell`

**Features:**
- Display a prompt and wait for the user to type a command.
- A command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, with no semicolons, pipes, redirections, or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- Handle the “end of file” condition (Ctrl+D).

**Exclusions:**
- No use of the `PATH`.
- No built-ins.
- No handling of special characters like `", ', \, *, &, #`.
- No ability to move the cursor.
- No handling of commands with arguments.

**Core Function:**  
`execve` will be the core part of your Shell; don’t forget to pass the `environ` to it.

**Repository:**  
GitHub repository: `simple_shell`

### 2. Simple Shell 0.2
- **Mandatory**
- Simple Shell 0.1 with additional functionality to handle command lines with arguments.

**Repository:**  
GitHub repository: `simple_shell`

### 3. Simple Shell 0.3
- **Mandatory**
- Simple Shell 0.2 with added functionality to handle the `PATH`.
- `fork` must not be called if the command doesn’t exist.

**Repository:**  
GitHub repository: `simple_shell`

### 4. Simple Shell 0.4
- **Mandatory**
- Simple Shell 0.3 with the implementation of the `exit` built-in, which exits the shell.

**Usage:**  
`exit`

**Repository:**  
GitHub repository: `simple_shell`

### 5. Simple Shell 1.0
- **Mandatory**
- Simple Shell 0.4 with the implementation of the `env` built-in, which prints the current environment.

**Repository:**  
GitHub repository: `simple_shell`

