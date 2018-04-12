#include "A4_sort_helpers.h"
#include <stdlib.h>

//260762008 Tianze Lin

int lines = 0;
// Function: read_all() 
// Provided to read an entire file, line by line.
// No need to change this one.
void read_all( char *filename ){
    
    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
	
    while( curr_line < MAX_NUMBER_LINES && 
           fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) )
    {
        curr_line++;
    }
    text_array[curr_line][0] = '\0';
    lines = curr_line;//determine the length of text_array
    fclose(fp);
}

// Function: read_all() 
// Provided to read only the lines of a file staring with first_letter.
// No need to change this one.
void read_by_letter( char *filename, char first_letter ){

    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
    text_array[curr_line][0] = '\0';
	
    while( fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) ){
        if( text_array[curr_line][0] == first_letter ){
            curr_line++;
        }

        if( curr_line == MAX_NUMBER_LINES ){
            sprintf( buf, "ERROR: Attempted to read too many lines from file.\n" );
            write( 1, buf, strlen(buf) );
            break;
        }
    }
    lines = curr_line;//determine the length of text_array
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q1.
void sort_words( ){
    int j;
    char temp[200];
    //insertion sort
    for (int i = 1; i < lines; i++){
        strcpy(temp, text_array[i]);
        j = i;
        while(j>0 && strcmp(temp,text_array[j-1]) < 0)
        {
            strcpy(text_array[j], text_array[j-1]);
            j--;
        }
        strcpy(text_array[j],temp);
    }
}

sem_t* array[27];
// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2.
int initialize( ){
    // Remove the current place-holder code, and write your own.
    char buffer[100];
    for(int i=0; i<27;i++){
        sprintf(buffer, "array%d", i);
        if (i != 1){
            array[i] = (sem_t *) malloc (sizeof(sem_t));
            array[i] = sem_open(buffer, O_CREAT | O_EXCL, 0644, 0);
            sem_unlink (buffer);
        }else{
	    	array[1] = (sem_t *) malloc (sizeof(sem_t));
    		array[1] = sem_open("array1", O_CREAT | O_EXCL, 0644, 1);
    		sem_unlink ("array1");
	}
    }

    return 0;
}

// YOU MUST COMPLETE THIS FUNCTION FOR Q2 and Q3.   
int process_by_letter( char* input_filename, char first_letter ){
    // For Q2, keep the following 2 lines in your solution (maybe not at the start).
    // Add lines above or below to ensure the "This process will sort..." lines
    // are printed in the right order (alphabetical).
    // For Q3, uncomment the following 2 lines and integrate them with your overall solution.
    int i=(first_letter-'a')+1;
    sem_wait(array[i]);
    //sprintf(buf, "This process will sort the letter %c.\n", first_letter);
    //write(1, buf, strlen(buf));
    read_by_letter(input_filename, first_letter);
    sort_words();

    //write on a file
    FILE* fp;
    if(i==1){
	fp = fopen("temp.txt", "w");
    }else{
	fp = fopen("temp.txt", "a");
    }
    
    for(int i=0; i<lines; i++){
	fprintf(fp, "%s", text_array[i]);
    }   
    if(i<26){
        sem_post(array[++i]);
    }else{
        sem_post(array[0]);
    }
    return 0;
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2 and Q3.
int finalize( ){
    // For Q2, keep the following 2 lines in your solution (maybe not at the start).
    // Add lines above or below to ensure the "Sorting complete!" line
    // is printed at the very end, after all letter lines.
    
    sem_wait(array[0]);
    read_all("temp.txt");

    for(int i=0; i<lines; i++){
        printf("%s",text_array[i]);
	fflush(stdout);
    }
    
    sprintf( buf, "Sorting complete!\n" );
    write( 1, buf, strlen(buf) );

    // For Q3, come up with a way to accumulate the sorted results from each
    // letter process and print the overal sorted values to standard out.
    // You are not allowed to read from the input file, or call sort_words
    // directly from this function.

    return 0;
}

