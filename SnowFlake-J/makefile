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
SRC 	  = snowFlake.c

all: $(SRC) snowFlake snowFlake-debug

snowFlake: snowFlake.o $(LIBS)
	gcc -o snowFlake snowFlake.o $(LIBS) -lmysqlclient_r

snowFlake-debug: snowFlake-debug.o $(LIBS)
	gcc -o snowFlake-debug -g snowFlake-debug.o $(LIBS) -lmysqlclient_r

snowFlake.o: $(SRC)
	gcc -o snowFlake.o -c -I /usr/include/mysql $(SRC)

snowFlake-debug.o: $(SRC)
	gcc -o snowFlake-debug.o -c -I /usr/include/mysql $(SRC) -DDEBUG
