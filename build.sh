LIBS=
LIB_DIR=

INCLUDE_DIRS=

SRC_FILES="../src/socket_linux.cpp ../src/socket_interface.cpp"
MAIN_FILE=../src/main.cpp
EXECUTABLE_NAME=vor_server

CFLAGS="-pedantic -Wall -std=c++11 -o $EXECUTABLE_NAME"

# set -x

pushd .
if [ ! -d "build" ]; then
	mkdir build
fi
cd build

pwd

g++ $CFLAGS $SRC_FILES $MAIN_FILE $INCLUDE_DIRS $LIB_DIR $LIBS

RESULT=$?
if [ $RESULT -eq 0 ]; then
    ./$EXECUTABLE_NAME
fi

popd
