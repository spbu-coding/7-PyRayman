#include <string.h> 
#include <stdlib.h>

#define MAX_SIZE_OF_LINE 1000

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
