/**/
/*calling the header files needed for this program*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//for misc symbollic const and types
#include<string.h> //header file to use functions like memcpy

/* The maximum length command is constant and 80*/
#define MAX_LINE 80


//prototyping the required functions
int characterized(char *arrayOfChar);//to read input
void tokenized(char *input, int input_size, char* args[]);//to tokenize the input stream
void showHistory(int counter, char history[][MAX_LINE+1],char pidArray[][10]);//to show the history


int main() {//this is the main function
    char *args[MAX_LINE/2 + 1]; /* an array of character strings */
    int should_run = 1; /* flag to determine when to exit program */
    char input[MAX_LINE + 1];//the input array to take user input characters
    memset(input, 0, sizeof(input));//setting all the index of input array to 0, so that we can fill up all spaces in array
    int input_size;//length of the user input characters    
    char history[10][MAX_LINE + 1];//this is 2-d array to store the past commands with their id and pid
    int counter = 0;//a counter to go through the 10 item in the history array
    char pidArray[10][10]; //this is 2d array to store the pid s from fork call
    char str[10]; //this is a string to store the pid
    int n=0;//another counter for the pidArray
    
    
    while (should_run) { //checking if the flag is still true           
        printf("CSCI3120>");//prompt for the users
        fflush(stdout);//flushing the output stream  
    
        input_size=characterized(input);//reading the input stream and storing the size of the stream     


                if (strcmp(input, "!!") == 0) { //if the user types in !!, we execute the latest command            
                memcpy(input, history[counter % 10], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }

                
                if (strcmp(input, "!1") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }                
                 if (strcmp(input, "!2") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)-1], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }
                 if (strcmp(input, "!3") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)-2], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }
                 if (strcmp(input, "!4") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)-3], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }
                 if (strcmp(input, "5") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)-4], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }
                 if (strcmp(input, "!6") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)-5], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }
                 if (strcmp(input, "!7") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)-6], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }
                 if (strcmp(input, "!8") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)-7], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }
                 if (strcmp(input, "!9") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)-8], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }
                 if (strcmp(input, "!10") == 0) { //if the user types in !N, we execute the latest command            
                memcpy(input, history[(counter%10)-9], MAX_LINE + 1);//copying the command from the history
                input_size = strlen(input); //setting the input_size to the size of the command               
                }
                

                
        tokenized(input, input_size, args);//calling the tokenized function to tokenize the line of characters



        if (strcmp(args[0], "history") == 0) {//if input is history
            showHistory(counter, history, pidArray);//calling the function
            continue;//continue to next steps
        }
        counter ++; //increasing the number of commands in the history for new command
        memcpy(history[counter% 10], input, MAX_LINE + 1);//copying the next command into history



        if (strcmp(args[0], "exit") == 0) {//if input is exit
            should_run = 0; //change the flag should_run
            continue;//to continue to next steps
        }


        
        
        int status;//decalring a randon integer for the wait call
        int exec_status;//decalring int for execvp return
        
        pid_t pid = fork();//fork function call, that returns a pid for the process
        
        if(n<10){//checking the counter
        sprintf(str, "%d", pid);//changing the pid from int to string type
        memcpy(pidArray[n% 10], str, sizeof(str)); //copying str into pidArray     
        n++; //incrementing the counter
        }   
        
        
        if (pid < 0) {//if the fork was not created
            exit(1);//exit with error
        }

         else if (pid == 0) {//if this is the child process
                 
            exec_status = execvp(args[0], args);//calliing execvp
           
            if (exec_status == -1) {//if the execvp returns -1
                printf("Invalid command!\n");
                exit(1);//invoking the exit with error
            }
        }

        else if(pid > 0){//if this is the parent process
                wait(&status);//wait for the child to finish, by &status returning the pid of the child process
            }
    }

    return 0;//return 0 to the main method
}




int characterized(char *arrayOfChar) {//this function reads the input stream character by character
        
    char ch; //defining the variable to hold each char    
    int index  = 0;//defining the array index
    while ((index < MAX_LINE)&&((ch = getchar()) != '\n')) {//reading the input till the length is less than 80 and reach nextLine character
        arrayOfChar[index++] = ch;
    }    
    arrayOfChar[index] = 0;//setting the last index as zero, as we did not include the nextLine character    
    return index;//returning the current index as it is the length of the input stream excluding nextLine char
    
}




void tokenized(char *input, int input_size, char* args[]) { //this function divides the input stream into tokens and store tokens in an array
    
    //some variables for this function
    int num = 0;
    int end = -1;    
    args[0] = NULL;//the first item is set to NULL
    
    
    
    for (int k = 0; k <= input_size; k++) {//we have to go through the user input stream  
    
        
        if (input[k] != ' ' && input[k] != '\r' && input[k] != '\v' && input[k] != '\f' && input[k] != '\t' && input[k]) {//all the delimiters are checked        
            continue;//if none of these delimiters are true, we go back to for loop iteration            
        } 
        
        
        else {
            if (end != k-1) {//check it is not the first element of input                
                args[num] = (char*)malloc(k-end);//allocating memory to copy              
                memcpy(args[num], &input[end+1], k-end-1);//copying everything except the last one               
                args[num][k-end] = 0;//the last item of the array is set to 0
                args[++num] = NULL; //the last pointer is set to NULL
            }
            end = k;//setting the counter to end
        }
        
        }        
        }
    
    
    




void showHistory(int counter, char history[][MAX_LINE+1],char pidArray[][10]) {  //this function shows the history when called


    if(counter>0){//if there is any history in the memory
            printf("ID\tPID\t\tCommands\n");//the headline to print id, pid and commands
        for (int i = counter, j = 1;  i > 0 && j<11 ; i --, j++) {//the for loop to go through the history contents
            printf("%d\t%d\t%s\n", j,pidArray[i%10], history[i%10]);//printing the content
        }
    }
    
    
    else {
        printf("No history found!\n");//if there is no history in the memory
    }
    
}




/*-----------------------thank you-----------------------*/



