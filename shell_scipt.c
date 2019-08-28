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

//welcome message
void welcome_message() 
{ 
	system("clear");
	printf("\n\n\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"); 
	printf("\n------------------------------Welcome to Samarth's SHELL-------------"); 
	printf("\n_____________________________________________________________________"); 
	printf("\n\n\nEntering shell as : @%s user", getenv("USER")); 
	printf("\nEnter you command when you see '------->>>'  to exit from shell enter 'exit' ");
	printf("\n"); 
} 

//this function will take input
int takeInput(char* input_str) 
{ 
	char* temp=readline("\n------->>> ");
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
	printf("\nDirectory is ==> %s", getcwd(pwd, sizeof(pwd))); 
}

//this function will call correcsponding function related to commands
void Command_handler(char** parsed,int no_of_words) 
{ 
	int i=0, choice = 0; 
	char* list_of_cmd[10]; 	

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

	while (i<10) 
	{ 
		if (strcmp(parsed[0], list_of_cmd[i]) == 0) 
		{ 
			choice = i + 1; 
			break; 
		} 
		i++;
	} 
 

	if(choice==1)
	{
		printf("\nThank you for using my shell\nSee you again\n"); 
		exit(0);
	}
	else if(choice==2)
	{
		chdir(parsed[1]); 
		show_directory();
	}
	else if(choice==3)
	{
		in_pwd(parsed,no_of_words);
	}
	else if(choice==4)
	{
		show_history();		
	}
	else if(choice==5)
	{
		in_echo(parsed,no_of_words);
	}
	else if(choice==6)
	{
		ext_cat(parsed,no_of_words);
	}
	else if(choice==7)
	{	
		ext_date(parsed,no_of_words);
	}
	else if(choice==8)
	{
		ext_ls(parsed,no_of_words);
	}
	else if(choice==9)
	{
		ext_rm(parsed,no_of_words);
	}
	else if(choice==10)
	{	
		ext_mkdir(parsed,no_of_words);
	}
	else
	{
		printf("\nthis command is out of scope\n");
	}
} 


//this will count number of words in string
int count_word(char* str, char** parsed) 
{ 
	int i=0; 
	while(i<100) 
	{ 
		parsed[i] = strsep(&str," "); 

		if (parsed[i] == NULL) 
			break; 
		if (strlen(parsed[i]) == 0) 
			i--; 
		i++;
	} 
	return i;
} 

//this will work for for echo command
void in_echo(char** text,int word_cound)
{
	pid_t process_id = fork();  
  
    if (process_id == -1) 
	{ 
        printf("\nError occured in forking child"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{   
		if(word_cound>1)for(int i=1;i<word_cound;i++)printf("%s ",text[i]);

		else printf("Error : Enter what to print");

		exit(0);
    } 
	
	else 
	{ 
        wait(NULL);  
        return; 
    }
}

//this function for present directory 
void in_pwd(char** argruments,int word_count)
{
	char pwd[200];

	if (word_count>1)
		{
			if (strcmp(argruments[1],"-L")==0)printf("\nYou are working in the -->>> %s logical directory",getcwd(pwd, sizeof(pwd)));
			else if (strcmp(argruments[1],"-P")==0)printf("\nYou are working in the -->>> %s physical directory",getcwd(pwd, sizeof(pwd)));
			else printf("\nError : incorrect option is enterterd");
		}

	else printf("\nYou are working in the -->>> %s directory",getcwd(pwd, sizeof(pwd)));
}

//this function will work for cat command
void ext_cat(char** address,int word_count) 
{ 
    pid_t process_id = fork();  
  
    if (process_id == -1) 
	{ 
        printf("\nError occured in forking child"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{       
		if (word_count>3)
		{
			printf("cat take atmost 2 argeuments only");
			exit(0);
		}
		else if (word_count>2)
		{
			if (execl("/bin/cat","/bin/cat",address[1],address[2],NULL)<0)printf("\nError : no file or directory exist with %s",address[2]);  
        	exit(0);
		}
		else if (word_count<2)
		{
			printf("Please enter second argeument or file name");
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
        printf("\nError occured in forking child"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{     
		if (word_count>3)  
		{
			printf("Date take atmost 2 argeuments only");
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
        printf("\nError occured in forking child"); 
        return; 
    } 
	
	else if (process_id == 0) 
	{       
		if (word_count>3)
		{
			printf("ls accepts only 2 argeuments");
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
        printf("\nError occured in forking child"); 
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
        printf("\nError occured in forking child"); 
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
			printf("Error : Enter file name or option for mkdir");  
        	exit(0);
		}		
    } 
	
	else 
	{ 
        wait(NULL);  
        return; 
    } 
} 


int last_pointer=0;
char* history[100];
void add_in_history(char * str)
{
	char *temp;
	strcpy(temp,str);
	history[last_pointer]=temp;
	last_pointer+=1;
}


void show_history()
{
	for (int i=0;i<last_pointer;i++)
	{
		printf("%i %s\n",i,history[i]);
	}
}


int main() 
{ 
	char input_string[100],*processed_string[100]; 
	int execFlag = 0; 
	welcome_message(); 
	show_directory();

	while (1) 
	{ 
		if (takeInput(input_string)) 
			continue; 

		add_in_history(input_string);

		Command_handler(processed_string,count_word(input_string, processed_string)); 		

	} 
	return 0; 
} 
