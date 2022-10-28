#include<common.h>
#include<ctype.h>
#include<validations.h>

int validName(char name[]){
    if(name[0]=='\0'){
       return 0;
    } 
    if(isdigit(name[0])){
        return 0;
    }
    for(int i=0;i<strlen(name);i++)
    {
        if(((name[i]>=97)&&(name[i]<=122))||((name[i]<=90)))
        {
           continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int validPhoneno(long int phoneno){
    int count = 0;
    while(phoneno>0){
        phoneno = phoneno/10;
        count++;
    }
    if(count!=10){
        return 0;
    } else {
        return 1;
    }
}

int validPassword(char password[])
{
    int i,number,special,capital,small;
    number=special=capital=small=0;
    for(i=0;password[i]!='\0';i++)
    {
        if(password[i]>='0' && password[i]<='9')
        {
            number=1;
        }
        if(password[i]>='a' && password[i]<='z'){
            small=1;
        }
            
        if(password[i]>='A' && password[i]<='Z')
        {
            capital=1;
        }
        if(password[i]=='!' || password[i]=='@' || password[i]=='#' || password[i]=='$' || password[i]=='%' || password[i]=='*')
        {
            special=1;
        }
    }
    if(number==0 || special==0 || capital==0 || small==0){
        return 0;
    } else {
        return 1;
    }
}
