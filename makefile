# CFLAGS=-O3 -std=c11 -fPIC -g -fopenmp -Xassembler -mrelax-relocations=no
# CFLAGS=-O3 -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address,undefined -fPIC -g -fopenmp -Xassembler -mrelax-relocations=no
CFLAGS=-O3 -Weverything -Wno-declaration-after-statement -Wno-missing-prototypes -Wno-unsafe-buffer-usage -std=c17 -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address,undefined -fPIC -g -fopenmp -Xassembler -mrelax-relocations=no
# CXXFLAGS=-O3 -std=c++11 -fPIC -g -fopenmp -Xassembler -mrelax-relocations=no
# CXXFLAGS=-O3 -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address,undefined -fPIC -g -fopenmp -Xassembler -mrelax-relocations=no
CXXFLAGS=-O3 -Weverything -Wno-c++98-compat -Wno-missing-prototypes -Wno-unsafe-buffer-usage -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address,undefined -fPIC -g -fopenmp -Xassembler -mrelax-relocations=no
LDFLAGS=-fopenmp
ARCHIVES=libgen.a 
LD=g++
CC=clang
CXX=clang++

all: libgen.a approx

# archives
libgen.a: gen_lib.o
	ar rcs libgen.a gen_lib.o


assignment-openmp-advanced.tgz: makefile approx.cpp \
                            libgen.a \
                            sequential reduce mergesort lcs \
                            params.sh \
                            assignment-openmp-advanced.pdf
	tar zcvf assignment-openmp-advanced.tgz \
                            libgen.a \
                            makefile approx.cpp \
                            sequential reduce mergesort lcs \
                            .gitignore params.sh \
                            assignment-openmp-advanced.pdf
