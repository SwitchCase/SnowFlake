ARGLIB_PATH     = libs/argtable
DATE	  	= $(ARGLIB_PATH)/arg_date.o
DBL  	  	= $(ARGLIB_PATH)/arg_dbl.o
END 	  	= $(ARGLIB_PATH)/arg_end.o
FILE	  	= $(ARGLIB_PATH)/arg_file.o
INT   	  	= $(ARGLIB_PATH)/arg_int.o
LIT  	  	= $(ARGLIB_PATH)/arg_lit.o
REM   	  	= $(ARGLIB_PATH)/arg_rem.o
REX   	  	= $(ARGLIB_PATH)/arg_rex.o
STR   	  	= $(ARGLIB_PATH)/arg_str.o
TABLE 	  	= $(ARGLIB_PATH)/argtable2.o
ARGLIB 	  	= $(DATE) $(DBL) $(END) $(FILE) $(INT) $(LIT) $(REM) $(REX) $(STR) $(TABLE)
SRCPATH   	= src
SRC 	  	= $(SRCPATH)/snowFlake.c
EXECPATH  	= exec
INCLUDE   	= include

all: $(SRC) snowFlake snowFlake-debug

snowFlake: $(EXECPATH)/snowFlake.o $(ARGLIB)
	gcc -o snowFlake $(EXECPATH)/snowFlake.o $(ARGLIB) -lmysqlclient_r

snowFlake-debug: $(EXECPATH)/snowFlake-debug.o $(ARGLIB)
	gcc -o snowFlake-debug -g $(EXECPATH)/snowFlake-debug.o $(ARGLIB) -lmysqlclient_r

$(EXECPATH)/snowFlake.o: $(SRC)
	gcc -o $(EXECPATH)/snowFlake.o -c -I /usr/include/mysql -I $(INCLUDE) $(SRC)

$(EXECPATH)/snowFlake-debug.o: $(SRC)
	gcc -o $(EXECPATH)/snowFlake-debug.o -c -I /usr/include/mysql -I $(INCLUDE) $(SRC) -DDEBUG
clean:
	rm -rf $(EXECPATH)/* snowFlake snowFlake-debug
