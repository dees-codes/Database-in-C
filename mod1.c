#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mod1.h"

#define MAX_NAME_LENGTH 32
#define MAX_ADDRESS_LENGTH 64
#define MAX_CITY_LENGTH 16
#define STATE_LENGTH 3
#define ONE_LINE_LENGTH 117

/* What one entry looks like. */
struct snippet {
  char name [MAX_NAME_LENGTH];
  char addr [MAX_ADDRESS_LENGTH];
  char city [MAX_CITY_LENGTH];
  char state [STATE_LENGTH];
  unsigned int zip;
};

char line[ONE_LINE_LENGTH];

//declaring array of pointers to structures
static struct snippet *entry_list[100];

//to count the number of entries in the file/array
int n_entry=100;

//function to read from file into structures
void read_text_file(FILE *the_file)
{
  int entry_line=0;

  //to scan the first word i.e the number of snippets
  fscanf(the_file, "%d", &n_entry);

  //temporary array
  char temp[ONE_LINE_LENGTH];
   
  // reads the first line into buffer which is not used
  fgets (temp, ONE_LINE_LENGTH, the_file);
	
  while(entry_line < n_entry){
    //reads the second line into "line" which is used 
    fgets(line, ONE_LINE_LENGTH, the_file);

    //dynamic allocation of memory for structure
    entry_list[entry_line]= (struct snippet *) malloc (sizeof (struct snippet));
    //copying tokens into elements of structure 
    strcpy(entry_list[entry_line]->name, strtok(line, ":\n"));
    strcpy(entry_list[entry_line]->addr, strtok(NULL, ":\n"));
    strcpy(entry_list[entry_line]->city, strtok(NULL, ":\n"));
    strcpy(entry_list[entry_line]->state, strtok(NULL, ":\n"));
    entry_list[entry_line]->zip = atoi(strtok(NULL, ":\n"));

    //move to next line of entry of struct
    entry_line++;
  }
}


/*function to print contents of structures*/
void print_all_structs()
{
  printf("\n");
  int k;   //counter variable
  //looping through each element of each struct
  for (k=0; k<n_entry; k++) {
    printf("%s\n%s\n%s, %s %d\n\n", entry_list[k]->name, entry_list[k]->addr,
	   entry_list[k]->city, entry_list[k]->state, entry_list[k]->zip);
  }
  
}


/*function to add to snippets*/
void add_a_snippet()
{
  printf("\n");
  //assigning pointer of dynamilcally created memory for struct to new_snippet
  struct snippet *new_snippet;
  new_snippet= (struct snippet *) malloc (sizeof (struct snippet));
  entry_list[n_entry]= new_snippet;

  //Prompting user for input and storing them in structures pointed by array elements
  
  printf("Enter the name:\n");
  fgets(line, MAX_NAME_LENGTH, stdin);
  printf("\n");
  line[strlen(line)-1]='\0';
  strcpy(entry_list[n_entry]->name,line);

  printf("Enter the address:\n");
  fgets(line, MAX_ADDRESS_LENGTH, stdin);
  printf("\n");
  line[strlen(line)-1]='\0';
  strcpy(entry_list[n_entry]->addr,line);

  printf("Enter the city name:\n");
  fgets(line, MAX_CITY_LENGTH, stdin);
  printf("\n");
  line[strlen(line)-1]='\0';
  strcpy(entry_list[n_entry]->city,line);
  
  printf("Enter the state code (not name):\n");
  fgets(line, STATE_LENGTH, stdin);
  printf("\n");
  line[strlen(line)]='\0';
  strcpy(entry_list[n_entry]->state,line);

  printf("Enter the zip code:\n");
  scanf("%u",&(entry_list[n_entry]->zip));
  printf("\n");
  
  n_entry++;
  printf("Information was added.\n");
}


//function to remove snippets
void remove_all_snippets (char string[])
{
  //to hold the argument following the word 'remove'
  char substring[ONE_LINE_LENGTH];
  strtok(string, " \n");

  //copying second token (argument) into substring
  strcpy(substring, strtok(NULL, " \n"));

  //counter variables
  int y;
  int z;
  int initial_entry= n_entry;
  
  for(y=0; y<n_entry; y++){

    //array to hold zip code converted to number.
    char number[15];
    //conversion of unsigned int zip element to string
    sprintf(number,"%u",(entry_list[y]->zip));

    //loop executed when the argument is substring of value of any elements of
    //referred to by the array elements
    if((strstr(entry_list[y]->name, substring)!=NULL) ||
       (strstr(entry_list[y]->addr, substring)!=NULL) ||
       (strstr(entry_list[y]->city, substring)!=NULL) ||
       (strstr(entry_list[y]->state,substring)!=NULL) ||
       (strstr(number,substring)!=NULL)) {
      for(z=y; z<n_entry; z++){
	  entry_list[z] = entry_list[z+1];
      }
      free(entry_list[y]); //freeing up the space occupied by deleted snippet
      n_entry--;
      if (y > 0){
	y--;
      }
    }
  }
  printf("%u snippets were removed.\n",(initial_entry-n_entry));
}
	
	
//this function rewrites the file and exits from the program
void exit_after_saving(FILE *the_file)
{
  //setting pointer to the beginning of the file
  fseek(the_file, 0, SEEK_SET);
  fprintf(the_file,"%d\n",n_entry);

  printf("... writing information to file\n");
  int i;
  for (i=0; i<n_entry; i++){
    fprintf(the_file,"%s:%s:%s:%s:%u\n",entry_list[i]->name, entry_list[i]->addr, entry_list[i]->city, entry_list[i]->state, entry_list[i]->zip);
  }

  printf("Exiting the program\n");
  fclose(the_file);
  exit(0);
}


	     
      





