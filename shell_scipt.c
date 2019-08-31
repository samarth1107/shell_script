//Samarth chauhan
//2018410
//CSB


//all header file which will be required to run the c program
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include "/usr/include/readline/readline.h"


//prototype of functions
void welcome_message();
void ending_message();
int takeInput(char*);
void show_directory();
void Command_handler(char**,int);
int count_word(char*,char**);
void in_echo(char**,int);
void in_pwd(char**,int);
void in_cd(char**,int);
void ext_cat(char**,int);
void ext_date(char**,int);
void ext_ls(char**,int);
void ext_rm(char**,int);
void ext_mkdir(char**,int);
void add_in_history(char*);
void show_history(char**,int);

//welcome message
void welcome_message() 
{ 
	system("clear");
	printf("\n\n\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"); 
	printf("\n---------------------------Welcome to SAM SHELL----------------------"); 
	printf("\n_____________________________________________________________________"); 
	printf("\n\n\nEntering shell as : @%s user", getenv("USER")); 
	printf("\nEnter you command when you see '------->>>'  to exit from shell enter 'exit' ");
	printf("\n "); 
} 

//ending message
void ending_message() 
{ 
	printf("\n\n\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"); 
	printf("\n---------------------Thank you for using SAM Shell-------------------"); 
	printf("\n_____________________________________________________________________\n"); 
	printf("\n"); 
} 

//this function will take input
int takeInput(char* input_str) 
{ 
	char* temp=readline("------->>> ");
	//scanf("\n------->>> %s",temp);
	if (strlen(temp)!=0) 
	{		
		strcpy(input_str,temp); 
		return 0; 
	} 	
	return 1;
} 

// this function will print present working directory 
void show_directory() 
{ 
	char pwd[1024]; 
	printf("\nDirectory is ==> %s\n", getcwd(pwd, sizeof(pwd))); 
}

//this function will call correcsponding function related to commands
void Command_handler(char** user_input,int no_of_words) 
{ 
	int i=0, choice = 0; 
	char* list_of_cmd[10]; 	

	//list of cmd include command take this shell can handle
	list_of_cmd[0] = "exit"; 
	list_of_cmd[1] = "cd"; 
	list_of_cmd[2] = "pwd"; 
	list_of_cmd[3] = "history"; 
	list_of_cmd[4] = "echo";
	list_of_cmd[5] = "cat";
	list_of_cmd[6] = "date";
	list_of_cmd[7] = "ls";
	list_of_cmd[8] = "rm";
	list_of_cmd[9] = "mkdir";

	//comparing processed input string with shell commands
	while (i<10) 
	{ 
		if (strcmp(user_input[0], list_of_cmd[i]) == 0) 
		{ 
			choice = i + 1; 
			break; 
		} 
		i++;
	} 
 
	//now calling function corresponding to their function
	if(choice==1)
	{
		ending_message(); 
		exit(0);
	}
	else if(choice==2)
	{
		in_cd(user_input,no_of_words); 
	}
	else if(choice==3)
	{
		in_pwd(user_input,no_of_words);
	}
	else if(choice==4)
	{
		show_history(user_input,no_of_words);		
	}
	else if(choice==5)
	{
		in_echo(user_input,no_of_words);
	}
	else if(choice==6)
	{
		ext_cat(user_input,no_of_words);
	}
	else if(choice==7)
	{	
		ext_date(user_input,no_of_words);
	}
	else if(choice==8)
	{
		ext_ls(user_input,no_of_words);
	}
	else if(choice==9)
	{
		ext_rm(user_input,no_of_words);
	}
	else if(choice==10)
	{	
		ext_mkdir(user_input,no_of_words);
	}
	else
	{
		printf("\nThis command is out of scope of the shell or maybe an invalid command ");
		printf("\n Don't worry you can try other command\n");
	}
} 

//this will count number of words in string
int count_word(char* str, char** user_input) 
{ 
	int i=0; 
	while(i<100) 
	{ 
		user_input[i] = strsep(&str," "); 

		if (user_input[i] == NULL) 
			break; 
		if (strlen(user_input[i]) == 0) 
			i--; 
		i++;
	} 
	return i;
} 

//this will work for for echo command
void in_echo(char** text,int word_count)
{
	if (word_count>1)
		{
			int option=0;
			for(int i=0;i<word_count;i++)
			{
				if (strcmp(text[i],"-n")==0)
				{
					option=1;
					break;
				}
				else if (strcmp(text[i],"-E")==0)
				{
					option=2;
					break;
				}
			}

			if (option==0)
			{
				for(int i=1;i<word_count;i++)printf("%s ",text[i]);
				printf("\n");
			}
			else if(option==1)for(int i=2;i<word_count;i++)printf("%s ",text[i]);
			else if(option==2)
			{
				for(int i=2;i<word_count;i++)printf("%s ",text[i]);
				printf("\n");
			}
		}

		else printf("\n");
}

//this function is for present directory 
void in_pwd(char** argruments,int word_count)
{	      
		char pwd[200];

		if (word_count>2)printf("Error: pwd accepts only one argrument");

		else if (word_count>1)
		{
			pid_t process_id = fork();  
  
    		if (process_id == -1) 
			{ 
        		printf("\nError: Some unexpected error occured during execution of the command\n"); 
        		return; 
    		} 

			else if (process_id == 0) 
			{       
				if (strcmp(argruments[1],"-L")==0)printf("\nCurrent working logical directory (with symbolic link) -->>> %s \n",getcwd(pwd, sizeof(pwd)));
				else if (strcmp(argruments[1],"-P")==0)
				{
					if (execvp(argruments[0],argruments)<0)printf("\nError: Some unexpected error occured during execution of the command");

					else printf(" <<<<<<----Current working physical directory (without symbolic link) \n");
				}
				else printf("\nError : incorrect option is enterterd\n");	
				exit(0);
    		} 

			else 
			{ 
        		wait(NULL);  
        		return; 
    		}				
		}

		else if(word_count==1)printf("\nYou are working in the -->>> %s \n",getcwd(pwd, sizeof(pwd)));

		else printf("\nError: pwd accepts only one argrument\n");	
}

//this function is for cd command
void in_cd(char** argruments,int word_count)
{
	if (word_count>2)
	{
		if (strcmp(argruments[1],"-L")==0)
		{
			if(chdir(argruments[2])!=0)
			{
				printf("\nError: %s path or directory doesn't exist\n",argruments[2]);
			}
			else 
			{
				chdir(argruments[1]);
				show_directory();
			}
		}
	
		else if(strcmp(argruments[1],"-P")==0)
		{
			pid_t process_id = fork();  
  
    		if (process_id == -1) 
			{ 
        		printf("\nError: Some unexpected error occured during execution of the command\n"); 
        		return; 
    		} 

			else if (process_id == 0) 
			{       
				if (execvp(argruments[0],argruments)>=0)
				{
					printf(" <<<<<<----Current working physical directory (without symbolic link) \n");
					show_directory();
				}
				else printf("\nError: Some unexpected error occured during execution of the command\n");	
				exit(0);
    		} 

			else 
			{ 
        		wait(NULL);  
        		return; 
    		} 
		}
	
		else printf("\nError: Either option is invalid or not supported by the shell\n");
	}

	else if(word_count>1)
	{
		if(chdir(argruments[1])!=0)printf("\nError: %s path or directory doesn't exist\n",argruments[1]);
		else show_directory();
	}

	else printf("\nError: Enter path or directory\n");	 

}

//this function will work for cat command
void ext_cat(char** address,int word_count) 
{ 
    pid_t process_id = fork();  
  
    if (process_id == -1) 
	{ 
        printf("\nError: Some unexpected error occured during execution of the command\n"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{       
		if (word_count>3)
		{
			printf("\ncat command take atmost 2 argeuments only");
			exit(0);
		}
		else if (word_count>2)
		{
			if (execl("/bin/cat","/bin/cat",address[1],address[2],NULL)<0)printf("\nError : no file or directory exist with %s",address[2]);  
        	exit(0);
		}
		else if (word_count<2)
		{
			printf("\nPlease enter second argeument or file name");
			exit(0);
		}
		else
		{
			if (execl("/bin/cat","/bin/cat",address[1],NULL)<0)printf("\nError : no file or directory exist with %s",address[1]);  
        	exit(0);
		}		
    } 
	
	else 
	{ 
        wait(NULL);  
        return; 
    } 
} 

//this function will work for date command
void ext_date(char** argruments,int word_count) 
{ 
    pid_t process_id = fork();  
  
    if (process_id == -1) 
	{ 
        printf("\nError: Some unexpected error occured during execution of the command\n"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{     
		if (word_count>3)  
		{
			printf("\nDate take atmost 2 argeuments only");
			exit(0);
		}
		else if (word_count>2)
		{
			if (execl("/bin/date","/bin/date",argruments[1],argruments[2],NULL)<0)printf("\nError : options entered are incorrect");  
        	exit(0);
		}

		else if (word_count>1)
		{
			if (execl("/bin/date","/bin/date",argruments[1],NULL)<0)printf("\nError : option entered is incorrect");  
        	exit(0);
		}
		else
		{
			if (execl("/bin/date","/bin/date",NULL)<0)printf("\nError:");  
        	exit(0);
		}		
    } 
	
	else 
	{ 
        wait(NULL);  
        return; 
    } 
} 

//this function will work for ls command
void ext_ls(char** argruments,int word_count) 
{ 
    pid_t process_id = fork();  
  
    if (process_id == -1) 
	{ 
        printf("\nError: Some unexpected error occured during execution of the command\n"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{       
		if (word_count>3)
		{
			printf("\nls accepts only 2 argeuments");
			exit(0);
		}
		else if (word_count>2)
		{
			if (execl("/bin/ls","/bin/ls",argruments[1],argruments[2],NULL)<0)printf("\nError : option entered is incorrect or directory not exist");  
        	exit(0);
		}
		else if (word_count>1)
		{
			if (execl("/bin/ls","/bin/ls",argruments[1],NULL)<0)printf("\nError : option entered is incorrect");  
        	exit(0);
		}
		else
		{
			if (execl("/bin/ls","/bin/ls",NULL)<0)printf("\nError:");  
        	exit(0);
		}		
    } 
	
	else 
	{ 
        wait(NULL);  
        return; 
    } 
} 

//this function will work for rm command
void ext_rm(char** argruments,int word_count) 
{ 
    pid_t process_id = fork();  
  
    if (process_id == -1) 
	{ 
        printf("\nError: Some unexpected error occured during execution of the command\n"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{       
		if (word_count>3)
		{
			printf("\nrm accepts atmost only 2 argeuments");
			exit(0);
		}
		else if (word_count>2)
		{
			if (execl("/bin/rm","/bin/rm",argruments[1],argruments[2],NULL)<0)printf("\nError : option entered is incorrect or directory not exist");  
        	exit(0);
		}
		else if (word_count>1)
		{
			if (execl("/bin/rm","/bin/rm",argruments[1],NULL)<0)printf("\nError : option entered is incorrect or directory not exist");  
        	exit(0);
		}
		else
		{
			if ("Error : enter file name or options for remove (rm)");  
        	exit(0);
		}		
    } 
	
	else 
	{ 
        wait(NULL);  
        return; 
    } 
} 

//this function will work for mkdir command
void ext_mkdir(char** argruments,int word_count) 
{ 
    pid_t process_id = fork();  
  
    if (process_id == -1) 
	{ 
        printf("\nError: Some unexpected error occured during execution of the command\n"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{       
		if (word_count>3)
		{
			printf("\nmkdir only accepts 2 argrument");
			exit(0);
		}
		else if (word_count>2)
		{
			if (execl("/bin/mkdir","/bin/mkdir",argruments[1],argruments[2],NULL)<0)printf("\nError : option entered is incorrect or directory not exist");  
        	exit(0);
		}
		else if (word_count>1)
		{
			if (execl("/bin/mkdir","/bin/mkdir",argruments[1],NULL)<0)printf("\nError : option entered is incorrect");  
        	exit(0);
		}
		else
		{
			printf("\nError : Enter file name or option for mkdir");  
        	exit(0);
		}		
    } 
	
	else 
	{ 
        wait(NULL);  
        return; 
    } 
} 




//add_in_history & show_history helps in history function
//these 2 parameter are for history stroage
int last_pointer=0;
char* history[100];
void add_in_history(char* str)
{
	char *temp;
	strcpy(temp,str);
	history[last_pointer]=temp;
	last_pointer+=1;
}


void show_history(char** argruments,int word_count)
{
	pid_t process_id = fork();  
  
    if (process_id == -1) 
	{ 
        printf("\nError: Some unexpected error occured during execution of the command\n"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{       
		//for printing 
		if (word_count==1)
		{
			for (int i=0;i<last_pointer;i++)
			{
				printf("\n%i %s",i+1,history[i]);
			}
			printf("\n");
			exit(0);
		}

		// if -c option is present in the command
		else if (word_count==2)
		{
			if (strcmp(argruments[1],"-c")==0)
			{
				last_pointer=0;
				printf("\nHistory cleared\n");
			}
			else printf("\nError: Enter a valid option for history\n");
			exit(0);
		}

		//if -d option is given
		else if(word_count==3)
		{
			if(strcmp(argruments[1],"-d")==0)
			{
				if (atoi(argruments[2])<=last_pointer+1 && atoi(argruments[2])>=1)
				{
					printf("\nHistory at %s delected\n",argruments[2]);			

					if ((atoi(argruments[2])-1)==last_pointer)
					{
						last_pointer-=1;
					}

					else 
					{
						for(int i=atoi(argruments[2])-1;i<=last_pointer-1;i++)
						{
							printf("\n hi again\n");
							history[i]=history[i+1];
						}
					}

				}
				else printf("\nError: Enter valid number\n");
			}
			else printf("\nError: Enter a valid options for history\n");

			exit(0);
		}

		//error handling
		else 
		{
			printf("\nError: History only accepts one argrument or option\n");	
			exit(0);
		}
    } 
	
	else 
	{ 
        wait(NULL);  
        return; 
    } 
}

//main function which will run until user command to exit
int main() 
{ 
	char input_string[100],*processed_string[100]; 
	int execFlag = 0; 
	welcome_message(); 
	show_directory();

	while (1) 
	{ 
		if (takeInput(input_string)==1)continue; 

		add_in_history(input_string);

		Command_handler(processed_string,count_word(input_string, processed_string)); 

	} 
	return 0; 
} 
