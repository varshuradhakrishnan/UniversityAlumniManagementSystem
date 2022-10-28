#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************ALUMNI LOGIN & SIGNUP STRUCTURE*******************************************/
typedef struct signUp{
	long int phno;
	int uni_id, experience, yop;
    	char company[60];
	char name[50];
	char addr[50];
}SIGNUP;

typedef struct login{
	int uni_id;
	char uName[20];
	char uPasswd[20];
}LOGIN;

/*********************************STUDENT LOGIN & SIGNUP STRUCTURE*******************************************/
typedef struct studSignUp{
	char name[30],dept[30],addre[50];
    	int regno;
    	long int phono;
}STUDS;

typedef struct StudLogin{
	int regno;
	char sName[20];
	char sPasswd[20];
}STUDL;

/*************************************JOB PROFILE STRUCTURE************************************************/
typedef struct jobProfile{
	int  exp;
	char job_dop[30];
	char jobRole[30];
	char jobSkills[30];
	char companyName[30];
	char contactInfo[80];
}JOB;

/**************************************ALUMNI FUNCTION DECLARATIOS*****************************************/
int signUp(int);
int login();

int signUpWrite(SIGNUP *, int);
int signUpRecs();

int loginWrite(LOGIN *, int);
int loginRead(LOGIN *, int *);

void viewProfile(int);
void editInfo(int);

int getSignupInfo(SIGNUP *, int);
int getLoginInfo(LOGIN *, int);

/*************************************JOB PROFILE FUNCTION DECLARATIOS**************************************/
int postJob();
void viewJobProfile();
int jobPostWrite(JOB *);

/**************************************ADMIN FUNCTION DECLARATIOS******************************************/
void editAlumniInfo();
int deleteAlumniInfo();

/**************************************STUDENT FUNCTION DECLARATIOS****************************************/
int studSignUp(int);
int studLogin();

int studSignUpWrite(STUDS *, int);
int studSignUpRecs();

int studLoginWrite(STUDL *, int);
int studLoginRead(STUDL *, int *);

void viewStudProfile(int);
void studEditInfo(int);
int viewAlumniDetails();

int getSsignupInfo(STUDS *, int);
int getSloginInfo(STUDL *, int);

#endif
