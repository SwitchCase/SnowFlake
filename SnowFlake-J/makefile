LIBPATH   = libs/argtable
DATE	  = $(LIBPATH)/arg_date.o
DBL  	  = $(LIBPATH)/arg_dbl.o
END 	  = $(LIBPATH)/arg_end.o
FILE	  = $(LIBPATH)/arg_file.o
INT   	  = $(LIBPATH)/arg_int.o
LIT  	  = $(LIBPATH)/arg_lit.o
REM   	  = $(LIBPATH)/arg_rem.o
REX   	  = $(LIBPATH)/arg_rex.o
STR   	  = $(LIBPATH)/arg_str.o
TABLE 	  = $(LIBPATH)/argtable2.o
LIBS 	  = $(DATE) $(DBL) $(END) $(FILE) $(INT) $(LIT) $(REM) $(REX) $(STR) $(TABLE)
SRCPATH   = src
SRC 	  = $(SRCPATH)/snowFlake.c
EXECPATH  = exec
INCLUDE   = include

all: $(SRC) snowFlake snowFlake-debug

snowFlake: $(EXECPATH)/snowFlake.o $(LIBS)
	gcc -o snowFlake $(EXECPATH)/snowFlake.o $(LIBS) -lmysqlclient_r

snowFlake-debug: $(EXECPATH)/snowFlake-debug.o $(LIBS)
	gcc -o snowFlake-debug -g $(EXECPATH)/snowFlake-debug.o $(LIBS) -lmysqlclient_r

$(EXECPATH)/snowFlake.o: $(SRC)
	gcc -o $(EXECPATH)/snowFlake.o -c -I /usr/include/mysql -I $(INCLUDE) $(SRC)

$(EXECPATH)/snowFlake-debug.o: $(SRC)
	gcc -o $(EXECPATH)/snowFlake-debug.o -c -I /usr/include/mysql -I $(INCLUDE) $(SRC) -DDEBUG
clean:
	rm -rf $(EXECPATH)/* snowFlake snowFlake-debug
