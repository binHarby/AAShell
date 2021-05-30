#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void scanner(char com[], char *para[])
{
  int cnt = 0;
  int  a = 0; 
  int  b = 0;
  char ln[1024];
  char *words[100], *pointerchar;

 //////////////////////////////////////// 
 //get every letter of each line
  while(1){
    int getl = fgetc (stdin);

    ln[cnt++] = (char) getl;
    if ( getl == '\n' ){
          break;
    }
  }
 // if only one letter is entered, return 
  if (cnt == 1){
	return;
  }

  //here, we are splitting the line by '\n' character
  //to ensure line termination 

  pointerchar = strtok (ln," \n" );
////////////////////////////////////////////////////////
  // get each word from the line
  while(pointerchar != NULL) {
    //copy each word to an words
    words[a++] = strdup (pointerchar);
    //continue through the line words
    pointerchar = strtok (NULL," \n");
  }
/////////////////////////////////////////////////////////////
  // get the command
  strcpy ( com, words[0] );
  
  // put the options in order
  for ( int b = 0; b < a; b++ ){
    para[b] = words[b];
  }
  para[a] = NULL;  // NULL-terminate the parameter list
}

void main()
{
  char  comm[65];
  char  *options[35];
  char final_command[100];
  int start_up=1;
  //setting the path for both proceses
  char vim[]="vim";
  char gedit[]="gedit";
  char man[]="man";

  char *envp[] = {(char *)"PATH=/bin", 0 }; //casting string of path as a char array, followed by a terminating char
  while (1) {                 
   if((start_up)||!(strcmp(comm,vim))||!(strcmp(comm,man))){
    //clear the screen
    printf(" \33[1H\33[2J");
    start_up=0;
   }
    printf("🌛🦸🌜:");   // display prompt
    scanner (comm,options); // read input from terminal
    if (fork() != 0){

      wait(NULL);           
    }
    else{
      strcpy(final_command,"/bin/"); //copy the absuolute diractory to final command array
      strcat(final_command,comm); //append the program/command to the path
	//use execve syscall to execute the command
      execve(final_command, options, envp); 
    }
  }
}
