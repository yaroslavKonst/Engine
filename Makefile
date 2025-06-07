export BUILD_DIR != echo `pwd`/build

export CXX = g++
export CXX_OPTS = -Wall -g -O3
export CXX_OBJ = -c
export AR = ar rcs

.PHONY: all clean

all:
	cd src ; $(MAKE)

clean:
	rm -rf $(BUILD_DIR)
