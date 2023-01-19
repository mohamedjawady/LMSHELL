
# LMSHELL
LMSHELL is a lightweight Linux shell.  
This project is written as a school project and has the sole purpose of testing functionalities of nix operating systems.


## Authors

- [@mohamedjawady](https://www.github.com/mohamedjawady)
- [@islem77](https://www.github.com/islem77)


## Run Locally

Clone the project

```bash
  git clone https://github.com/mohamedjawady/LMSHELL
```

Go to the project directory

```bash
  cd LMSHELL
```

Install Project

```bash
  bash setup.sh
```



## Progress  
Every piece of functionality is separately tested in the Sandbox directory. Afterwards, progress is done in the root directory. 
### 1. Experimenting with
- [Headers,Make] C build tools
- [Fork,Exec,Wait,Pipe,Dup,Open,Close,Write] Linux system calls

### 2. Implementation
Functionalities are added in the course of iterations. 
#### 2.1. Iteration 1
- Shell prompt ([curr-dir] % ).
- Separate process for commands, quit to exit.
- 2 execution modes; interactive and bach.
- Commands Parser.  
#### 2.1. Iteration 2
- Support for batch mode.
- Support for complex commands.
- Support for the rest of builtins.

Modes:  

| Mode             | Usage                                                                |
| ----------------- | ------------------------------------------------------------------ |
| Interactive | {context: lmshell} <path> % [EXPRESSION] |
| Batch | lmshell file.lm or ./file.lm |

Expression Forms:

| Expression             | Form                                                                |
| ----------------- | ------------------------------------------------------------------ |
| Simple | `cmd` |
| Multiple | `cmd1; cmd2` |
| AND | `cmd1 && cmd2` |
| OR | `cmd1 \|\| cmd2` |
| REDIRECT | `cmd1 > file` |
| PIPE | `cmd1 \| cmd2` |
| COMMENT | `#comment here` |


## Notes

- Executable files within the "Sandbox" directory can be compiled seperately using a local compile.sh script
- Not all commands are mapped to executables, some are built-ins, i.e. cd.