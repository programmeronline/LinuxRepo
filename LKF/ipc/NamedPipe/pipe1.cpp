///////////////////////////////////////////////////////////////////////////////
// @brief File contains logic read part1.o data present in named pipe
//
///////////////////////////////////////////////////////////////////////////////
//Includes
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

//namespace std
using namespace std;

//Defines
#define NAMED_PIPE_PATH "/tmp/pipe2"

int main()
{
	//holds named pipe file descriptor
	int pipefd=-1;
	//holds stream pointer
	FILE* pipestream=NULL;
        //holds line string
        char linestr[2048];
        //counts number of lines
        int linecnt=0;
        //holds failed position count
        int failedcnt=-1;

	//open named pipe
	pipefd=open(NAMED_PIPE_PATH,O_RDWR);

	//check if named pipe open was successfull
	if(pipefd<0){
		perror("Pipe open failed:");
	}

	//convert to file stream
	pipestream=fdopen(pipefd,"r");

        //loop and read each line with End of file
        while (fgets(linestr, sizeof(linestr),pipestream) != NULL){
                //check if \n is present at end
                if(linestr[strlen(linestr)-1] == '\n'){
                        linestr[strlen(linestr)-1]='\0';
                }
                linecnt++;
                if(NULL != strstr(linestr,"failed")){
                        failedcnt=linecnt;
			break;
                }
        }
        if(-1 != failedcnt){
                cout<<"Program failed on operation "<<failedcnt<<endl;
        }

	//close opened named pipe
	close(pipefd);

	return 0;
}
