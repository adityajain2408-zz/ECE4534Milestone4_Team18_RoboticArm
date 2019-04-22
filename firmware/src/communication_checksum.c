#include "communication_checksum.h"

char *my_itoa(int num, char *str)
{
    if (str == NULL)
    {
        return NULL;
    }
    sprintf(str, "%d", num);
    return str;
}

char * removeString(char * text, int index, int rm_length)
{
    int i;
    for (i = 0; i < index; ++i){
        if (text[i] == '\0')
        {
            return NULL;
        }
    }

    for (; i < index + rm_length; ++i){
        if (text[i] == '\0')
        {
            text[index] = '\0';
            return NULL;
        }
    }
    char str1[300] = {""};
    char str2[300]= {""};
    strncpy(str1, text, index);
    strncpy(str2, &text[i], strlen(text)-i);
    strcat(str1, str2);
    text = str1;
    if(text[strlen(str1) -1] != '}')
    {
        strcat(str1, "}");
    }
    return text;
}

unsigned int getChecksum(char *json_statement)
{
    char *result = strstr(json_statement, "\"checksum\"");

    int check_position = result - json_statement;

    int end_position, j;
    for (j = check_position; j < strlen(json_statement); j++)
    {
        if (json_statement[j] == ',')
        {
            end_position = j;
            break;
        }
        if(json_statement[j] == '}'){
            check_position = check_position - 2;
            end_position = j-1;
            break;
        }
    }

    int sans_length = end_position - check_position + 1;

    char *json_sans_checksum = removeString(json_statement, check_position, sans_length + 1);

    int checksum = computeChecksum(json_sans_checksum);
    return checksum;
}

unsigned int computeChecksum(char * json_string){
    int i;
    int checksum = 0;
    for(i = 0; i < strlen(json_string); i++){
        char c = json_string[i];
        checksum ^= c;
    }
    
    return checksum;
}
