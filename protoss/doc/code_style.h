// code_style.h
// Hongwei Li (lihw81@gmail.com)
// Created at 2013/06/08
//
// <Description>


#ifndef KW_CODE_H
#define KW_CODE_H


#include <user.h>

#include <core.h>

#include <system.h>


#define ONE_MACRO


enum 
{
    ONE_ENUM, //<!
};


struct AStruct
{
};


class OtherA;
struct OtherB;


class AClass
{
public:
    AClass(int a,
        int b,
        int c, 
        int d);

    // Some comments.
    ~AClass();

    void aMemberFunc();

private:
    static int s_memberVariable; //<!  
    int m_memberVariable; 
    int *m_aPointer;  
    int &m_aReference;
};

int g_globalVariable;

// About function declarations
void aFunc();
void APIENTRY bFunc();
void *cFunc();
void APIENTRY * dFunc();
void eFunc(int a, int b, int c);
void fFunc(int a, ...);
void gFunc(int a,
    int b, 
    int c,
    int d,
    int e);
void (*aFuncPointer)();


#endif // !KW_CODE_H

