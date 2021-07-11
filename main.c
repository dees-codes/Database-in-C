/* @author: Deepson Shrestha; 
   CS250;
   Submitted to: Professor Robert Matthews */    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod1.h"

#define MAX_INPUT_LENGTH 73

int main (int argc, char *argv[])
{ 
  // declaration of file pointer 
  FILE *the_file;
  char *input_file = argv[1];
  if ((the_file = fopen (input_file, "r+")) == NULL) {
    /*Opening the file failed. */
    fprintf (stderr, "Opening the file failed.\n");
    exit(-1);
  }
  
  //function for reading text file into array of structures.
  read_text_file(the_file);
  //closing the file after reading
  fclose(the_file);
  //reopening the file for writing and assigning it to same pointer.
  the_file= fopen(input_file,"w");

  char action[MAX_INPUT_LENGTH];
  char buffer[7]; //to hold the word remove

  
  
  /*Ask input from user*/
  printf("\nType:\n");
  printf("*  'list' to print all the snippets,\n");
  printf("*  'add' to add a prompt,\n");
  printf("*  'remove' <string> to remove every snippet from the database");
  printf(" that contains the entered string as a substring,\n");
  printf("*  'exit' to save your progress and exit the program.\n\n");

  //loop to take user input
  while (1){
    if (fgets(action,40,stdin)!=NULL)
      {
	if(strcmp(action,"add\n")==0){
	  add_a_snippet();
	  printf("\nEnter your command:\n");
	} else if(strcmp(action,"list\n")==0){
	  print_all_structs();
	  printf("\nEnter your command:\n");
	} else if(strcmp(action,"exit\n")==0){
	  exit_after_saving(the_file);
	} else {
	  strncpy(buffer, action, 6);
	  if(strcmp(buffer,"remove")==0){
	    remove_all_snippets(action);
	    printf("\nEnter your command:\n");
	  }
	}
      }
  }

  return (0);
}






	
