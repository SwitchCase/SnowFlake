ARGTABLE     = libs/argtable
#DATE	  	= $(ARGLIB_PATH)/arg_date.o
#DBL  	  	= $(ARGLIB_PATH)/arg_dbl.o
#END 	  	= $(ARGLIB_PATH)/arg_end.o
#FILE	  	= $(ARGLIB_PATH)/arg_file.o
#INT   	  	= $(ARGLIB_PATH)/arg_int.o
#LIT  	  	= $(ARGLIB_PATH)/arg_lit.o
#REM   	  	= $(ARGLIB_PATH)/arg_rem.o
#REX   	  	= $(ARGLIB_PATH)/arg_rex.o
#STR   	  	= $(ARGLIB_PATH)/arg_str.o
#TABLE 	  	= $(ARGLIB_PATH)/argtable2.o
#ARGLIB 	  	= $(DATE) $(DBL) $(END) $(FILE) $(INT) $(LIT) $(REM) $(REX) $(STR) $(TABLE)
SRCPATH   	= src
SRC 	  	= $(SRCPATH)/snowFlake.c
EXECPATH  	= exec
INCLUDE   	= include
CONFIG   	= libs/libconfig
LIBRARY 	= -lmysqlclient  -static libs/libconfig/libconfig.a -static libs/argtable/libargtable2.a
LDFLAGS 	= -lz -lpthread -lm -static -static-libgcc -Wall -mglibc
LDPATH  	= -Llibs/argtable -Llibs/libconfig

all: $(SRC) snowFlake snowFlake-debug judge
snowFlake: $(EXECPATH)/snowFlake.o $(ARGLIB)
	gcc -o snowFlake $(EXECPATH)/snowFlake.o $(LIBRARY) $(LDFLAGS)  $(LDPATH)

snowFlake-debug: $(EXECPATH)/snowFlake-debug.o $(ARGLIB)
	gcc -o snowFlake-debug -g $(EXECPATH)/snowFlake-debug.o  $(LIBRARY) $(LDFLAGS) $(LDPATH -DDEBUG)

$(EXECPATH)/snowFlake.o: $(SRC)
	gcc -o $(EXECPATH)/snowFlake.o -c -I /usr/include/mysql -I $(INCLUDE) $(SRC) $(LDFLAGS)

$(EXECPATH)/snowFlake-debug.o: $(SRC)
	gcc -o $(EXECPATH)/snowFlake-debug.o -c -I /usr/include/mysql -I $(INCLUDE) $(SRC) -DDEBUG $(LDFLAGS)
clean:
	rm -rf $(EXECPATH)/* snowFlake snowFlake-debug
smaller: $(SRCPATH)/smaller.c
	gcc -o smaller -L libs/libconfig -lconfig -I $(INCLUDE) $(SRCPATH)/smaller.c -g
libargtable: $(ARGTABLE)/libargtable2.a
	echo "Changing directory to $(ARGTABLE)"
	cd $(ARGTABLE)
	ar -x $(ARGTABLE)/libargtable2.a
	cd ../..
	echo "Comng back"
libconfig: $(CONFIG)/libconfig.a
	echo "Changing directory to $(CONFIG)"
	cd $(CONFIG)
	ar -x $(CONFIG)/libconfig.a
	cd ../..
	echo "Coming back"

judge: $(SRCPATH)/judge.cpp
	g++  $(SRCPATH)/judge.cpp -o $(EXECPATH)/judge $(LIBRARY) $(LDFLAGS) $(LDPATH) -I $(INCLUDE)
judge-debug: $(SRCPATH)/judge.cpp
	g++  $(SRCPATH)/judge.cpp -o $(EXECPATH)/judge-debug $(LIBRARY) $(LDFLAGS) $(LDPATH) -I $(INCLUDE) -DDEBUG
