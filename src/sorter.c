#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

//-------------------------------Tools------------------------------

#define MAX_INPUT_STRING_SIZE 1000



void free_memory(char** array, int count){
    for (int i = 0; i <= count; i++ ){
        free(array[i]);
    }
    free(array);
}
void add_new_line_symbol(char* string)
{
    int count_of_sybmol = 0;
    while( string[count_of_sybmol] != '\n' && string[count_of_sybmol] != '\0' && count_of_sybmol < MAX_SIZE_OF_LINE){
        count_of_sybmol++;
    }
    string[count_of_sybmol] = '\n';
}

void swap(char **xp, char **yp) 
{ 
    char *temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

int des_cmp(const void *first_string, const void  *second_string)
{
    const char  **temp1 = (const char **)first_string;
    const char  **temp2 = (const char **)second_string;

    return -strcmp(*temp1,*temp2); 
}

int check_punctuation_mark(char symbol)
{
    if( ( symbol == '.' ) || ( symbol == ',' ) || ( symbol == ';' ) || ( symbol == ':' )|| ( symbol == '!' ) || ( symbol == '?' ))
    {
        return 1;
    }
    else
        return 0;
}

void rewrite( char *string , int start )
{
    if( start  > MAX_SIZE_OF_LINE )
        return;
    while( string[start] != '\n' && string[start] != '\0' )
    {
        string[start] = string[start + 1];
        start ++;
    }
    string[start] = '\0';
    string[start + 1] = '\0';

}

void deleting_symbols( char** strings, int* count_of_strings )
{
    for( int i = 0 ; i < *count_of_strings ; i++ )
    {
        int number_of_char = 0;
        while( (strings[i][ number_of_char ] != '\n') && (strings[i][ number_of_char ] != '\0') )
        {
            if( check_punctuation_mark( strings[i][number_of_char] ) )
            {
                rewrite( strings[i] , number_of_char );
            }
            else
            {
                number_of_char++;
            }
        }
    }
}
//-----------------------------------Main--------------------------------------------


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