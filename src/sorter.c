#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "tools.h"

#define MAX_INPUT_STRING_SIZE 1000



void free_memory(char** array, int count){
    for (int i = 0; i <= count; i++ ){
        free(array[i]);
    }
    free(array);
}


int main(int argc, char** argv){

    if (argc != 2){
        fprintf(stderr,"PLease correct count of arguments = %d",argc);
        return -1;
    }

    FILE* input_file = fopen(argv[1],"rb");

    if (input_file == NULL){
        fprintf(stderr,"Input file not found (%s)",argv[1]);
        return -1;
    }
    
    
    char** strings = (char**)malloc( sizeof(char*) * 5);
    if(strings == NULL){
        fprintf(stderr,"Failed to allocate memory");
        return -1;
    }
    int count_of_strings = 0;
    while(1 == 1){
        if (count_of_strings != 0){
            strings = (char**)realloc(strings,sizeof(char*) * (count_of_strings + 1));
            if (strings == NULL){
                fclose(input_file);
                free_memory(strings,count_of_strings);
                fprintf(stderr,"Failed to allocate memory");
                return -1;
            }
        }
        
        strings[count_of_strings] = (char*)malloc( sizeof(char) * MAX_INPUT_STRING_SIZE);

        if(strings[count_of_strings] == NULL){
            fclose(input_file);
            free_memory(strings,count_of_strings);
            fprintf(stderr,"Failed to allocate memory");
            return -1;
        }

        if( fgets(strings[count_of_strings], MAX_INPUT_STRING_SIZE, input_file) == NULL){
            break;
        }
        count_of_strings++;
    }
    


    add_new_line_symbol(strings[count_of_strings-1]);

    deleting_symbols(strings,&count_of_strings);

    qsort(strings,count_of_strings * sizeof(char) , sizeof(char*), des_cmp);

    int count_printed_strings = 0;
    while( count_printed_strings < 100 && count_of_strings > count_printed_strings){
        printf("%s",strings[count_printed_strings]);
        count_printed_strings++;
    }

    free_memory(strings,count_of_strings);
    fclose(input_file);
 
}