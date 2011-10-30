#include <iostream>
#include <cstdio>
#include <vector>
#include <regex.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <sys/wait.h>
#include <signal.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/stat.h>

#include "argtable2.h"

#define RIGHT 0
#define WRONG 2
#define TIME_EXCEEDED 3
#define COMPILE_ERROR 1
#define ILLEGAL_FILE 4

#define RUN_TIME_ERROR 5
#define PRESENTATION_ERROR 6

using namespace std;
int exit_status,pid;
char comm[100];
#ifdef DEBUG
	string err[]={"right","compile err","wrong","time excd","illegal file"};
#endif

void time_out(int i)
{
	sprintf(comm,"kill -s 9 %d",pid);
	system(comm);
	#ifdef DEBUG
		cerr<<err[TIME_EXCEEDED]<<endl;
	#endif

	exit(TIME_EXCEEDED);
}

string getfile(string s)
{
	unsigned int i = s.find_last_of('/');
	if(i != string::npos)
		return s.substr(0, i);
	return "";
}

string getext(string s)
{
	unsigned int i = s.find_last_of('.');
	if(i != string::npos)
		return s.substr(i+1);
	return "";
}

bool match(const char *pattern, const char *filename);
bool checkForSystemCalls(const char *filename);

string file;
string inFile, outFile;
int timeLimit;
int memoryLimit;
int testCount;
string problemDir;
string problemCode;
string jailDir;

int nonBinary(const char *inString) 
{
	char *str = (char*) inString;
	while( *str != '\0' ) {
		if ( (*str <= 'z' && *str >= 'A') || ( *str >= '0' && *str <= '9') || *str == '/' || *str == '\\' || *str == '_' || *str ==' ' || *str == '.') {
				str++;
		}
		else return 0;
	}
	return 1;
}

int directoryExists(string dir) {
	struct stat st;
	return !stat(dir.c_str(), &st);
}

int printGlossary( void* argtable[], string str) {
	if ( str != "help" ) {
		printf("Missing %s parameter.\n", str.c_str());
	}
	arg_print_syntaxv(stdout, argtable,"\n\n");
	arg_print_glossary(stdout, argtable, "%-25s %s\n");
	exit(1);
}

int readCommandLineArgs(int argc, char* argv[]) 
{
	struct arg_file *source 	= arg_file1(NULL, NULL, "<source code>", "*Source code file");
	struct arg_file *jail   	= arg_file1("j", "jail", "<file>", "*Jail to restrict executable in.");
	struct arg_file *problem    = arg_file0("p", "problem", "<file>", "Problem directory containing all problem set, relative to jail directory. DEFAULT - <jail>/problem");
	struct arg_str *probset  	= arg_str1("s", "problemset", "<Problem Code>", "*Code of problem to test. Must be inside the problem directory");
	struct arg_int *timelimit   = arg_int1("t", "config", "<n>", "*Time limit of problem set");
	struct arg_int *memory      = arg_int0("m", "memory", "<n>", "Memory limits to set in KB");
	struct arg_int *countSet    = arg_int1("c", "countset", "<n>",  "*Total number of problems in test set");
	struct arg_str *inF  		= arg_str0("i", "infile", "<file prefix>", "Prefix used for each of the input files. eg for - in0,in1,in2... prefix is \"in\"");
	struct arg_str *outF	 	= arg_str0("o", "outfile", "<file prefix>", "Prefix used for each of the output files. eg for - out0,out1,out2... prefix is \"out\"");
	struct arg_lit *help 		= arg_lit0("h", "help", "This help menu");
	struct arg_end *end    		= arg_end(10);
	void *argtable[]        	= { source, jail, problem, probset, timelimit, memory, countSet, inF, outF, help, end };

	int nerrors = arg_parse(argc, argv, argtable);
	string tmp;
	if ( !nerrors) {
		if ( help->count) {
			printGlossary(argtable, "help");
		}
		if ( source->count) {
			if ( strlen(source->filename[0]) < 256 && nonBinary(source->filename[0]) ) {
				file = string(source->filename[0]);
			}
			else {
				printf("Sourcefile name larger than 256 characters\n");
				printGlossary(argtable, "source");
			}
		}
		else {
			printGlossary(argtable, "source");
		}

		if ( jail->count ) {
			if ( strlen(jail->filename[0]) < 256 && nonBinary(jail->filename[0])) {
				if ( !directoryExists(jail->filename[0])) {
					cerr<<"Errors encountered when trying to open "<<jail->filename[0]<<". Ensure it exists and has the correct permissions\n";
					exit(1);
				}
				jailDir = string(jail->filename[0]);
			}
		}
		else {
			printGlossary(argtable, "jail");
		}

		if ( problem->count) {
			tmp = jailDir + "/"+ string(problem->filename[0]);
			if ( directoryExists(tmp) && nonBinary(tmp.c_str())) {
				problemDir = tmp;
			}
		}
		else {
			problemDir = jailDir + "/problems";
		}

		if ( probset->count ) {
			tmp = problemDir + "/" + string(probset->sval[0]);
			if ( directoryExists(tmp) && nonBinary(tmp.c_str())) {
				problemCode = string(probset->sval[0]);
			}
		}
		
		if ( timelimit->count) {
			timeLimit = timelimit->ival[0];
		}
		else {
			printGlossary(argtable, "timeLimit");
		}

		if ( memory->count) {
			memoryLimit = memory->ival[0];
		}
		
		if ( countSet->count) {
			testCount = countSet->ival[0];
		}
		else {
			printGlossary(argtable, "CountSet");
		}

		if ( inF->count) {
			tmp = string (inF->sval[0]);
			if ( nonBinary(tmp.c_str()) && tmp.size() < 32 ) {
				inFile = tmp;
			}
			else {
				printf("Invalid inFile parameter given. Ensure it is less than 32 characters wide\n");
				printGlossary(argtable, "inFile");
			}
		}
		
		if ( outF->count ) {
			tmp = string (outF->sval[0]);
			if ( nonBinary(tmp.c_str()) && tmp.size() < 32 ) {
				outFile = tmp;
			}
			else {
				printf("Invalid outFile parameter given. Ensure it is less than 32 characters wide\n");
				printGlossary(argtable, "outFile");
			}
		}

	}
	else {
		arg_print_errors(stdout, end, "judge");
		printGlossary(argtable, "help");
		exit(1);
	}
	    arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));
	return 1;
}

int main(int argc,char *argv[])
{
	readCommandLineArgs(argc, argv);

	string ext = getext(file.c_str());

	if ( ext == "" || file == "" || (ext != "cpp" && ext != "c" && ext != "CPP" && ext != "C"))
	{
		#ifdef DEBUG
			cerr<<err[ILLEGAL_FILE]<<endl;
		#endif

		return ILLEGAL_FILE;
	}

	if(checkForSystemCalls(argv[1]))
		return COMPILE_ERROR;

	string flag=" ";
	if(ext.size() == 1)
		flag = " -xc ";

	string cmd = "g++ -lm "+ flag + file +" -o" +  + "/a.out 2>"+ file + "/opc";
	//string sed="sed -i 's#"+ "code" + "##g' " + file+"/opc";
	//system(sed.c_str());	
	#ifdef DEBUG
		cerr<<cmd<<" "<<file<<" "<<ext<<endl;
	#endif

	int i = system(cmd.c_str());
	if(i)
	{
		#ifdef DEBUG
			cerr<<err[COMPILE_ERROR]<<endl;
		#endif
		return COMPILE_ERROR;
	}

	pid=fork();
	if(pid)
	{       
		int status;
		
		signal(SIGALRM,time_out);
		alarm(timeLimit);
		waitpid(pid,&status,0);
		alarm(0);
		
		if(WIFSIGNALED(status))
			return RUN_TIME_ERROR;
			
		string file1 = file + "/op";
		string file2 = "./problems/"+string(argv[2])+"/out"; //change this output file name and the actual file for security issues
		/*ifstream f1(file.c_str());
		
		file = "./problems/"+string(argv[2])+"/out";
		ifstream f2(file.c_str());

		string s="",b1,b2;
		while(1)
		{
			f1>>s;
			if(!s[0])
				break;
			b1 = b1+" "+s;
			s[0]=0;
		}
		s="";
		while(1)
		{
			f2>>s;
			if(!s[0])
				break;
			b2 = b2+" "+s;
			s[0]=0;
		}
*/

		string diff="diff " + file1 + " " + file2;
		int FLAG=system(diff.c_str());
		if(WEXITSTATUS(FLAG)==0)
			exit_status=RIGHT;
		else
			{
			 string diff1="diff -bBiw " + file1 + " " + file2;
			 int FLAG2=system(diff1.c_str());
			 if(WEXITSTATUS(FLAG2)==0)
			 	exit_status=PRESENTATION_ERROR;
			 else
			  	exit_status=WRONG;
			}
	}
	
	else
	{
		int inp = dup(0);
		int op = dup(1);


		string file;
		file = file+"/op";
		int ofid = open(file.c_str(),O_RDWR|O_CREAT|O_TRUNC,0666);
		dup2(ofid,1);
		

		file = "FIX ME";    //change this input file name and the actual file for security issues
		int ifid = open(file.c_str(), O_RDONLY,0);
		dup2(ifid, 0);
		
		file = file + "/a.out";
		execv(file.c_str(), NULL);

		dup2(inp, 0);
		dup2(op, 1);
		return 0;
	}

	#ifdef DEBUG
		cerr<<err[exit_status]<<endl;
	#endif
	return exit_status;	
}

bool checkForSystemCalls(const char *filename)
{
	vector<string> functions, keywords;

	//Read the banned functions from the file
	ifstream func("banned_functions");
	while(true)
	{
		string s;
		func>>s;
		if(func.eof()) break;
		
		functions.push_back(s);
	}
	func.close();

	//Read the banned keywords from the file
	ifstream key("banned_keywords");
	while(true)
	{
		string s;
		key>>s;
		if(key.eof()) break;
		
		keywords.push_back(s);
	}
	key.close();

	//Build regex pattern
	string pattern = "([^a-zA-Z0-9_\\.>]+(";
	for(unsigned int i=0 ; i<keywords.size() ; i++)
	{
		if(i>0) pattern += "|";
		pattern += keywords[i];
	}
	pattern += ")[^a-zA-Z0-9_\\.]+)";

	pattern += "|";
	
	pattern += "([^a-zA-Z0-9_\\.>]+(";
	for(unsigned int i=0 ; i<functions.size() ; i++)
	{
		if(i>0) pattern += "|";
		pattern += functions[i];
	}
	pattern += ")[ \t\n\r]*\\()";

	//cout<<pattern<<endl;
	return match(pattern.c_str(), filename);	
}

bool match(const char *pattern, const char *filename)
{
	//This does not behave exactly like grep
	//The whole file is treated as a single line,
	//so ^ and $ will not work in the regular expression
	
	regex_t reg;
	regcomp(&reg, pattern, REG_EXTENDED|REG_NOTBOL|REG_NOTEOL);

	regmatch_t matches[1];

	ifstream in(filename);
	if(!in) return false;

	in.seekg(0, ios::end);
	int length = in.tellg();
	in.seekg(0, ios::beg);

	char *buffer = new char[length+1];
	in.read(buffer, length);
	buffer[length] = '\0';

	if(regexec(&reg, buffer, 1, matches, 0) == 0)
		return true;

	in.close();

	return false;
}
