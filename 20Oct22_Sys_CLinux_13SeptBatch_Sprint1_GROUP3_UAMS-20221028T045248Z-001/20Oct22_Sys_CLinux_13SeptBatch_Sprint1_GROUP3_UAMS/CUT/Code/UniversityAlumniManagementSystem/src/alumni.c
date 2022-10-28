#include <common.h>
#include <validations.h>

int signUp(int __id)
{
	SIGNUP *sn = (SIGNUP *)malloc(sizeof(SIGNUP));
	LOGIN *ln = (LOGIN *) malloc(sizeof(LOGIN));
	printf("\n\tEnter your details \n");
	printf("\n\tName: ");
	getchar();
	fgets(sn->name, 19, stdin);
	if(validName(sn->name)==0){
		printf("Enter a valid name : ");
		getchar();
		fgets(sn->name, 19, stdin);
	}
	printf("\n\tAddress: ");
	scanf("%s",sn->addr);
	getchar();
	printf("\n\tPhone no: ");
	scanf("%ld",&sn->phno);
	if(validPhoneno(sn->phno)==0){
		printf("Enter a valid phone number : ");
		scanf("%ld",&sn->phno);
	}
	printf("\n\tYear of Passing: ");
	scanf("%d", &sn->yop);
	printf("\n\tExperience: ");
	scanf("%d", &sn->experience);
	printf("\n\tCompany: ");
	scanf("%s",sn->company);
	sn->uni_id=__id;
	ln->uni_id=__id;
	printf("\n\tUser Name: ");
	scanf("%s", ln->uName);
	printf("\n\tPassword: ");
	scanf("%s",ln->uPasswd);
	if(validPassword(ln->uPasswd)==0){
		printf("Your password should contain atleast 1 special character, small & capital character, and a number.");
		printf("\n\tPassword: ");
		scanf("%s",ln->uPasswd);
	}

	/*
	After validating all the flds write to the file/db
	*/
	signUpWrite(sn, 0);
	loginWrite(ln, 0);
	return 0;
}


int signUpWrite(SIGNUP *sn, int u_id)
{
	FILE *fp;
	int flag =0;
	SIGNUP temp_sn;
	fp = fopen("./data/Users.txt","r+");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	if(u_id==0){
		fseek(fp, 0L, SEEK_END);
		fwrite(sn, sizeof(SIGNUP),1,fp);
	} else {
		while(fread(&temp_sn, sizeof(SIGNUP), 1, fp)){
			if(temp_sn.uni_id==u_id){
				flag = 1;
				break;
			}
		}
		if(flag == 1){
			fseek(fp, -sizeof(SIGNUP), SEEK_CUR);
			fwrite(sn, sizeof(SIGNUP), 1, fp);
		}
	}
	fclose(fp);
	return 0;
}


int signUpRecs()
{
	FILE *fp;
	SIGNUP sn;
	int recCount=0;
	fp = fopen("./data/Users.txt","r");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		return 0;
	}
	while(fread(&sn, sizeof(SIGNUP),1,fp))
		recCount++;
	fclose(fp);
	return recCount;
}


int login()
{
	LOGIN *ln = (LOGIN *) malloc(sizeof(LOGIN));
	int flag=0,ch, u_id=0;
	system("clear");
	printf("\n\t=============LOGIN=============\n");
	printf("\n\tLogin: ");
	scanf("%s", ln->uName);
	printf("\n\tPassword: ");
	scanf("%s", ln->uPasswd);
	if((strcmp(ln->uName, "Admin")==0) && (strcmp(ln->uPasswd,"Admin123")==0)){
		return 1;
	} else {
		flag = loginRead(ln, &u_id);
		if(flag == 1){
			printf("\n\tWelcome to your Profile.\n\t");
			printf("\n\tSuccessfully logged in.\n\t");
			while(1)
			{
				printf("\n\t1. View Profile\n\t2. Edit Profile\n\t3. View Job Profile\n\t4. Post a job\n\t5. Exit\n\tChoice : ");
				scanf("%d", &ch);
				switch(ch)
				{
				    case 1:
					system("clear");
					printf("View Profile");
					viewProfile(u_id);
					break;
				    case 2:
					system("clear");
					printf("Edit Profile");
					editInfo(u_id);
					break;
				    case 3:
					system("clear");
					printf("\n\tView Job Profile\n\t");
					viewJobProfile();
					break;
				    case 4:
					system("clear");
					printf("Post a Job");
					JOB jb;
					postJob(&jb);
					break;
				    case 5:
					system("clear");
					printf("\nExit\n");
					exit(EXIT_SUCCESS);
					break;
				    default:
					printf("\nSomething Went Wrong. Please select the valid choice\n");
					break;
				}
			}
		} else {
			return 0;
		}
	}
}

int loginWrite(LOGIN *ln, int u_id)
{
	FILE *fp;
	int flag =0;
	LOGIN temp_ln;
	fp = fopen("./data/login.txt","a+");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	if(u_id==0){
		fseek(fp, 0L, SEEK_END);
		fwrite(ln, sizeof(LOGIN),1,fp);
	} else {
		while(fread(&temp_ln, sizeof(LOGIN), 1, fp)){
			if(temp_ln.uni_id==u_id){
				flag = 1;
				break;
			}
		}
		if(flag == 1){
			fseek(fp, -sizeof(LOGIN), SEEK_CUR);
			fwrite(ln, sizeof(LOGIN), 1, fp);
		}
	}
	fclose(fp);
	return 0;
}


int loginRead(LOGIN *ln, int *u_id)
{
	FILE *fp;
	LOGIN *tln = (LOGIN *) malloc(sizeof(LOGIN));
	int flag = 0;
	fp = fopen("./data/login.txt","r+");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	while(fread(tln, sizeof(LOGIN),1,fp))
	{
		if((strcmp(ln->uName, tln->uName)==0) && (strcmp(ln->uPasswd,tln->uPasswd)==0))
		{
			flag = 1;
			*u_id = tln->uni_id;
			break;
		}	
	}
	fclose(fp);
	return flag;
}	


void viewProfile(int u_id)
{
	FILE *fp;
	SIGNUP *sn = (SIGNUP *)malloc(sizeof(SIGNUP));
	fp = fopen("./data/Users.txt","r");
	printf("\n=========ALUMNI DETAILS==========\n\n\n");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(0);
	} else {
		printf("\t\t\tRECORDS :\n");
		while(fread(sn, sizeof(SIGNUP), 1,fp)){
			if(u_id==sn->uni_id){
				printf("\n\t\t\t Name               :  %s",sn->name);
				printf("\n\t\t\t University no      :  %d",sn->uni_id);
				printf("\n\t\t\t Year of Passing    :  %d",sn->yop);
				printf("\n\t\t\t Mobile No          :  %ld",sn->phno);
				printf("\n\t\t\t Company            :  %s",sn->company);
				printf("\n\t\t\t Experience         :  %d",sn->experience);
				printf("\n\t\t\t Address            :  %s\n",sn->addr);
				break;
			}
		}
	}
	fclose(fp);
}


void editInfo(int u_id)
{
	FILE *fp;
	FILE *pf;
	SIGNUP *sn= (SIGNUP *)malloc(sizeof(SIGNUP));
	SIGNUP *ob= (SIGNUP *)malloc(sizeof(SIGNUP));
	LOGIN *ln = (LOGIN *) malloc(sizeof(LOGIN));
	LOGIN *li= (LOGIN *) malloc(sizeof(LOGIN));
	fp = fopen("./data/Users.txt","r+");
	pf = fopen("./data/login.txt","r+");
	printf("\t\t\t\t=========PRESENT DETAILS==========\n\n\n");
	viewProfile(u_id);
	while(fread(ln, sizeof(LOGIN),1,pf)){
		if(ln->uni_id==u_id){
			printf("\n\t\t\t Username        : %s",ln->uName);
			break;
		}
	}
	printf("\n\n\t\tModify your details:\n ");
	printf("\t\t");
	printf("\n\n");	
	printf("\t\tGive 1 to retain old details\n\n");
	printf("\t\tName        : ");
	getchar();
	fgets(ob->name, 25, stdin);
	printf("\t\tMobile no	: ");
	scanf("%ld",&ob->phno);
	printf("\t\tCompany     : ");
	getchar();
	scanf("%s",ob->company);
	printf("\t\tExperience  : ");
	getchar();
	scanf("%d",&ob->experience);
	printf("\t\tAddress     : ");
	getchar();
	scanf("%s",ob->addr);
	printf("\t\tUsername    : ");
	getchar();
	scanf("%s",li->uName);
	printf("\t\tPassword    : ");
	getchar();
	scanf("%s",li->uPasswd);
	/*GET the record in sn
	*/
	if(getSignupInfo(sn, u_id)==0){
		printf("Records are not copied");
	}
	if(getLoginInfo(ln, u_id)==0){
		printf("Records are not copied");
	}
	//COPYING MODIFIED DETAILS
	if(ob->name[0]!='1'){
		strcpy(sn->name,ob->name);
	}
	
	if(ob->phno != 1){
		sn->phno=ob->phno;
	}
	if(strcmp(ob->company,"1")!=0){
		strcpy(sn->company,ob->company);
	}
	if(ob->experience!=1){
		sn->experience=ob->experience;
	}
	if(strcmp(ob->addr,"1")!=0){
		strcpy(sn->addr,ob->addr);
	}
	if(strcmp(li->uName,"1")!=0){
		strcpy(ln->uName,li->uName);
	}
	if(strcmp(li->uPasswd,"1")!=0)
	{
		if(validPassword(li->uPasswd)==0){
			printf("Your password should contain atleast 1 special character, small & capital character, and a number.");
			printf("\t\tPassword  : ");
			getchar();
			scanf("%s",li->uPasswd);
		}
		strcpy(ln->uPasswd,li->uPasswd);
	}
	signUpWrite(sn, u_id);
	loginWrite(ln, u_id);
	fclose(fp);
	fclose(pf);	
}

int postJob()
{	JOB *jb = (JOB *)malloc(sizeof(JOB));
	printf("\n\tEnter Job details \n");
	printf("\n\tJob Role: ");
	getchar();
	scanf("%[^\n]%*c", jb->jobRole);
	printf("\n\tDate of Post: ");
	getchar();
	scanf("%s",jb->job_dop);
	printf("\n\tJob Skills Required: ");
	getchar();
	fgets(jb->jobSkills, 25, stdin);
	printf("\n\tCompany: ");
	fgets(jb->companyName, 25, stdin);
	printf("\n\tExperience: ");
	scanf("%d",&jb->exp);
	printf("\n\tContact Info: ");
	getchar();
	fgets(jb->contactInfo, 79, stdin);

	jobPostWrite(jb);
	return 0;
}


int jobPostWrite(JOB *jb){
	FILE *fp;
	fp = fopen("./data/job.txt","a+");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	fwrite(jb, sizeof(JOB),1,fp);
	fclose(fp); 
	return 0;
}

int getSignupInfo(SIGNUP *sn, int u_id){
	FILE *fp;
	fp = fopen("./data/Users.txt","r");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(0);
	} else {
		while(fread(sn, sizeof(SIGNUP), 1,fp)){
			if(u_id==sn->uni_id){
				return 1;
			}
		}
	}
	fclose(fp);
	return 0;
}

int getLoginInfo(LOGIN *ln, int u_id){
	FILE *fp;
	fp = fopen("./data/login.txt","r");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(0);
	} else {
		while(fread(ln, sizeof(LOGIN), 1,fp)){
			if(u_id==ln->uni_id){
				return 1;
			}
		}
	}
	fclose(fp);
	return 0;
}
