///////////////////////////////////////////////////////////////////////////////
// @brief File contains logic to create 1 parent and 2 child process. The 
//        child one will sort the command line data and 2nd child process will
//        find median of values.
//
///////////////////////////////////////////////////////////////////////////////
//Includes
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//namespace std
using namespace std;

//Usage
int usage(char* progname)
{
	cout<<"Usage: "<<progname<<"arg1 arg2 arg3 arg4 arg5"<<endl;
	exit(EXIT_FAILURE);
}

//Main Function
int main(int argc,char* argv[])
{
	//place holder for 4 pipes
	int pipe1[2];
	int pipe2[2];
	int pipe3[2];
	int pipe4[2];
	//hold array of numbers
	int numarray[5];
	//child1 pid
	pid_t child1;
	//child2 pid
	pid_t child2;
	//holds counter details
	int cnt=0;
	//holds temp number
	int tempnum=0;
	//used to convert command line parameter to number
	char *end;	
	//holds status information
	int status;
	//holds median value
	float median;

	//check if required command line parameters are entered
	if(argc < 6) {
		usage(argv[0]);
	}

	//convert arguments to number and store in numarray
	for(cnt=0;cnt<5;cnt++) {
		tempnum = strtol(argv[1+cnt], &end, 10);				
		if(tempnum == 0 && (errno != 0 || end == argv[1+cnt])){
			cout<<"Invalid argument"<<endl;
			usage(argv[0]);
		}
		numarray[cnt]=tempnum;
	}

	//open pipes
	status = pipe(pipe1);

	if(status < 0) {
		perror("Pipe1 Failed:");
		exit(EXIT_FAILURE);
	}

        status = pipe(pipe2);

        if(status < 0) {
                perror("Pipe2 Failed:");
                exit(EXIT_FAILURE);
        }

        status = pipe(pipe3);

        if(status < 0) {
                perror("Pipe3 Failed:");
                exit(EXIT_FAILURE);
        }

        status = pipe(pipe4);

        if(status < 0) {
                perror("Pipe4 Failed:");
                exit(EXIT_FAILURE);
        }

	//create child1 process
	child1=fork();

	if(child1<0) {
		perror("Child1 Failed:");
		exit(EXIT_FAILURE);
	} else if(child1 == 0){
		//close pipe1 write end
		close(pipe1[1]);

		//read data from pipe
		read(pipe1[0],numarray,sizeof(numarray));

		//close read pipe
		close(pipe1[0]);

		//close read pipe
		close(pipe2[0]);

		//sort data
		int i,j;
   		for(i=0;i<5;i++){
     			for(j=i+1;j<5;j++){
        			if(numarray[i]>numarray[j]){
            				tempnum=numarray[i];
            				numarray[i]=numarray[j];
            				numarray[j]=tempnum;
         			}
      			}
   		}		

		write(pipe2[1],numarray,sizeof(numarray));

		//close write pipe
		close(pipe1[1]);

		//close read pipe
		close(pipe3[0]);

		write(pipe3[1],numarray,sizeof(numarray));

		//close write pipe
		close(pipe3[1]);

		return EXIT_SUCCESS;
	}

	//create child2 process
        child2=fork();

        if(child2<0) {
                perror("Child2 Failed:");
                exit(EXIT_FAILURE);
        } else if(child2 == 0){
		//close write pipe
		close(pipe3[1]);

		read(pipe3[0],numarray,sizeof(numarray));

		//close read pipe
		close(pipe3[0]);

		//calculate median
		median = numarray[2];

		//close read pipe
		close(pipe4[0]);

		write(pipe4[1],&median,sizeof(median));

		//close write pipe
		close(pipe4[1]);

                return EXIT_SUCCESS;
        }

	//close pipe1 read end
	close(pipe1[0]);

	//send data to child1 via pipe1
	write(pipe1[1],numarray,sizeof(numarray));

	//close pipe1 write end
	close(pipe1[1]);

	//close pipe2 write end
	close(pipe2[1]);

	//read sorted data from child 1
	read(pipe2[0],numarray,sizeof(numarray));

	cout<<"Sorted Data"<<endl;
        for(cnt=0;cnt<5;cnt++){
		cout<<numarray[cnt]<<endl;
        }
	
	//close pipe2 read end
	close(pipe2[0]);

	//close write pipe
	close(pipe4[1]);

	read(pipe4[0],&median,sizeof(median));

	//close read pipe
	close(pipe4[0]);

	cout<<"Median= "<<median<<endl;

	//wait for all child process to exit
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);

	return EXIT_SUCCESS;
}
