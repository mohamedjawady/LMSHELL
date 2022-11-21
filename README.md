
# LMSHELL
LMSHELL is a lightweight Linux shell.  
This project is written as a school project and has the sole purpose of testing functionalities of nix operating systems.


## Authors

- [@mohamedjawady](https://www.github.com/mohamedjawady)


## Run Locally

Clone the project

```bash
  git clone https://github.com/mohamedjawady/LMSHELL
```

Go to the project directory

```bash
  cd LMSHELL
```

Install dependencies

```bash
  sudo apt install build-essential
```

Build the project

```bash
  make
```


## Progress  
Every piece of functionality is separately tested in the Sandbox directory. Afterwards, progress is done in the root directory. 
### 1. Experimenting with
- [H,M] C build tools
- [F,E,W] Linux system calls

### 2. Implementation
Functionalities are added in the course of iterations. 
#### 2.1. Iteration 1
- Shell prompt ([curr-dir] % ).
- Separate process for commands, quit to exit.
- 2 execution modes; interactive and bach.
- Commands Parser.  

Modes:  

| Mode             | Usage                                                                |
| ----------------- | ------------------------------------------------------------------ |
| Interactive | {context: lmshell} <path> % [EXPRESSION] |
| Bach | lmshell file.lm |

Expression Forms:

| Expression             | Form                                                                |
| ----------------- | ------------------------------------------------------------------ |
| Simple | `cmd` |
| Multiple | `cmd1; cmd2; ...cmdi` |
| AND | `cmd1 && cmd2 && ...cmdi` |
| OR | `cmd1 \|\| cmd2 \|\| ...cmdi` |


## Notes

- Executable files within the "Sandbox" directory can be compiled seperately using a local compile.sh script
- Not all commands are mapped to executables, some are built-ins, i.e. cd.