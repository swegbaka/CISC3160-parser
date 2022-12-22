#include <iostream>
#include <stdlib.h>

using namespace std;

struct Expression
{
    int Result;
    char* Error;
    char* Start;       
};

Expression* Number(char*& Stream)
{
    int Result=0;
    bool GotNumber=false;

    char* Read=Stream;

    while(*Read==' ')Read++;
    while(true)
    {
        char c=*Read;
        if('0'<=c && c<='9')
        {
            Result=Result*10+(c-'0');
            GotNumber=true;
            Read++;
        }
        else
        {
            break;
        }    
    }
    if(GotNumber)
    {
        Stream=Read;
        return new Expression(Result);
    }
    else    
    {
        throw Exception(Stream,"Error Here");
    }
}

Expression* GetTerm(char*& Stream); 
Expression* GetFactor(char*& Stream); 
Expression* GetExp(char*& Stream); 


Expression* GetTerm(char*& Stream)
{
    try
    {
        return Number(Stream);
    }    
    catch(Exception& e)
    {
        char* Read=Stream;
        
        if(Is(Read,"("))
        {
           
            Expression* Result=GetExp(Read);
            if(Is(Read,")"))
            {
                
                Stream=Read;
                return Result;
            }
            else
            {
                
                delete Result;
                throw Exception(Stream,"Missing right parentheses"); 
            }        
        }    
        else
        {
            throw e;
        }    
    }    
}    


Expression* GetFactor(char*& Stream)
{
    
    char* Read=Stream;
    Expression* Result=GetTerm(Read);
    while(true)
    {
        
        char Operator=0;
        if(Is(Read,"*"))
            Operator='*';
        else if(Is(Read,"/"))
            Operator='/';
        else
            break;
        if(Operator)
        {
            
            try
            {
                Result=new Expression(Operator,Result,GetTerm(Read));
            }
            catch(Exception& e)
            {
                
                delete Result;
                throw e;
            }        
        }    
    }
    Stream=Read;
    return Result;    
}     


Expression* GetExp(char*& Stream)
{
    
    char* Read=Stream;
    Expression* Result=GetFactor(Read);
    while(true)
    {
        
        char Operator=0;
        if(Is(Read,"+"))
            Operator='+';
        else if(Is(Read,"-"))
            Operator='-';
        else
            break;
        if(Operator)
        {
            
            try
            {
                Result=new Expression(Operator,Result,GetFactor(Read));
            }
            catch(Exception& e)
            {
                
                delete Result;
                throw e;
            }        
        }    
    }
    Stream=Read;
    return Result;    
}     