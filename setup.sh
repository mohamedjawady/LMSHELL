# install build tools for compilation

sudo apt install build-essential -y

# build executable
make

# add lmshell to bin path

sudo cp lmshell /usr/bin/lmshell

# clean generated files
make clean
