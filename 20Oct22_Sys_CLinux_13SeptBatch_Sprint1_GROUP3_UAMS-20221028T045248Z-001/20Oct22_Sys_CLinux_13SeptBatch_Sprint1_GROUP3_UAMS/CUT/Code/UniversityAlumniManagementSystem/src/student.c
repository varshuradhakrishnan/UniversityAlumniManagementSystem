#include<common.h>
#include<validations.h>

int studSignUp(int __id)
{
	STUDS *ss = (STUDS *)malloc(sizeof(STUDS));
	STUDL *sl = (STUDL *)malloc(sizeof(STUDL));
	printf("\n\tEnter your details \n");
	printf("\n\tName: ");
	getchar();
	fgets(ss->name, 25, stdin);
	if(validName(ss->name)==0){
		printf("Enter a valid name : ");
		getchar();
		fgets(ss->name, 25, stdin);
	}
	printf("\n\tAddress: ");
	scanf("%s",ss->addre);
	printf("\n\tPhone no: ");
	scanf("%ld",&ss->phono);
	if(validPhoneno(ss->phono)==0){
		printf("Enter a valid phone number : ");
		scanf("%ld",&ss->phono);
	}
	printf("\n\tDepartment: ");
	scanf("%s", ss->dept);
	ss->regno = __id;
	sl->regno = __id;
	printf("\n\tUser Name: ");
	scanf("%s", sl->sName);
	printf("\n\tPassword: ");
	scanf("%s",sl->sPasswd);
	if(validPassword(sl->sPasswd)==0){
		printf("Your password should contain atleast 1 special character, small & capital character, and a number.");
		printf("\n\tPassword: ");
		scanf("%s",sl->sPasswd);
	}
	
	studSignUpWrite(ss, 0);
	studLoginWrite(sl, 0);
	return 0;
}

int studSignUpWrite(STUDS *ss, int u_id)
{
	FILE *fp;
	int flag =0;
	STUDS temp_ss;
	fp = fopen("./data/stuUsers.txt","r+");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	if(u_id==0){
		fseek(fp, 0L, SEEK_END);
		fwrite(ss, sizeof(STUDS),1,fp);
	} else {
		while(fread(&temp_ss, sizeof(STUDS), 1, fp)){
			if(temp_ss.regno==u_id){
				flag = 1;
				break;
			}
		}
		if(flag == 1){
			fseek(fp, -sizeof(STUDS), SEEK_CUR);
			fwrite(ss, sizeof(STUDS), 1, fp);
		}
	}
	fclose(fp);
	return 0;
}


int studSignUpRecs()
{
	FILE *fp;
	STUDS ss;
	int recCount=0;
	fp = fopen("./data/stuUsers.txt","r");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		return 0;
	}
	while(fread(&ss, sizeof(STUDS),1,fp))
		recCount++;
	fclose(fp);
	return recCount;
}


int studLogin()
{
	STUDL *sl = (STUDL *)malloc(sizeof(STUDL));
	int flag=0, ch, u_id =0;
	system("clear");
	printf("\n\t=============LOGIN=============\n");
	printf("\n\tLogin: ");
	scanf("%s", sl->sName);
	printf("\n\tPassword: ");
	scanf("%s", sl->sPasswd);
	
	flag = studLoginRead(sl, &u_id);
	
	if(flag == 1)
	{
		printf("\n\t\t\tWelcome to your Profile.\n");
		printf("\n\t\t\tSuccessfully logged in.\n");
		while(1)
		{
			printf("\n\t1. View Profile\n\t2. Edit Profile\n\t3. View Alumni Details\n\t4. View Job Profile\n\t 5. Exit\n\tChoice : ");
			scanf("%d", &ch);
			switch(ch)
			{
			    case 1:
				system("clear");
				printf("View Profile");
				viewStudProfile(u_id);
				break;
			    case 2:
				system("clear");
				printf("Edit Profile");
				studEditInfo(u_id);
				break;
			    case 3:
				system("clear");
				printf("View Alumni Details");
				viewAlumniDetails();
				break;
			    case 4:
				system("clear");
				printf("View Job Profile");
				viewJobProfile();
				break;
			    case 5:
				system("clear");
				printf("\nExit\n");
				exit(EXIT_SUCCESS);
				break;
			    default:
				printf("\nSomething Went Wrong. Please select the valid choice.\n");
				break;
			}
		}
    	} else {
		return 0;
	}
}

int studLoginWrite(STUDL *sl, int u_id)
{
	FILE *fp;
	int flag =0;
	STUDL temp_sl;
	fp = fopen("./data/stuLogin.txt","a+");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	if(u_id==0){
		fseek(fp, 0L, SEEK_END);
		fwrite(sl, sizeof(STUDL),1,fp);
	} else {
		while(fread(&temp_sl, sizeof(STUDL), 1, fp)){
			if(temp_sl.regno==u_id){
				flag = 1;
				break;
			}
		}
		if(flag == 1){
			fseek(fp, -sizeof(STUDL), SEEK_CUR);
			fwrite(sl, sizeof(STUDL), 1, fp);
		}
	}
	fclose(fp);
	return 0;
}


int studLoginRead(STUDL *sl, int *u_id)
{
	FILE *fp;
	STUDL *tsl = (STUDL *) malloc(sizeof(STUDL));
	int flag = 0;
	fp = fopen("./data/stuLogin.txt","r+");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	while(fread(tsl, sizeof(STUDL),1,fp))
	{
		if((strcmp(sl->sName, tsl->sName)==0) && (strcmp(sl->sPasswd,tsl->sPasswd)==0))
		{
			flag = 1;
			*u_id = tsl->regno;
			break;
		}	
	}
	fclose(fp);
	return flag;
}

void viewStudProfile(int u_id)
{
	FILE *fp;
	STUDS *ss = (STUDS *)malloc(sizeof(STUDS));
	fp = fopen("./data/stuUsers.txt","r");
	printf("\t\t\t\t=========STUDENT DETAILS==========\n\n\n");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(0);
	} else {
		printf("\t\t\tRECORDS :\n");
		while(fread(ss, sizeof(STUDS), 1,fp)){
			if(u_id==ss->regno){
				printf("\n\t\t\t Name               :  %s",ss->name);
				printf("\n\t\t\t Registration no    :  %d",ss->regno);
				printf("\n\t\t\t Mobile No          :  %ld",ss->phono);
				printf("\n\t\t\t Department         :  %s",ss->dept);
				printf("\n\t\t\t Address            :  %s",ss->addre);
				break;
			}
		}
	}
	fclose(fp);
}

void studEditInfo(int u_id)
{
	FILE *fp;
	FILE *pf;
	STUDS *ss = (STUDS *)malloc(sizeof(STUDS));
	STUDS *ob = (STUDS *)malloc(sizeof(STUDS));
	STUDL *sl = (STUDL *)malloc(sizeof(STUDL));
	STUDL *li = (STUDL *)malloc(sizeof(STUDL));
	fp = fopen("./data/stuUsers.txt","r+");
	pf = fopen("./data/stuLogin.txt","r+");
	printf("\t\t\t\t=========PRESENT DETAILS==========\n\n\n");
	viewStudProfile(u_id);
	while(fread(sl, sizeof(STUDL),1,pf)){
		if(sl->regno==u_id){
			printf("\n\t\t\t Username          :  %s",sl->sName);
			break;
		}
	}
	printf("\n\n\t\tModify your details:\n ");
	printf("\t\t");
	printf("\n\n");	
	printf("\t\t Give 1 to retain old details\n\n");
	printf("\t\tName		: ");
	getchar();
	scanf(" %[^\n]",ob->name);
	printf("\t\tMobile no	: ");
	getchar();
	scanf("%ld",&ob->phono);
	printf("\t\tDepartment  : ");
	getchar();
	scanf("%s",ob->dept);
	printf("\t\tAddress     : ");
	getchar();
	scanf("%s",ob->addre);
	printf("\t\tUsername    : ");
	getchar();
	scanf("%s",li->sName);
	printf("\t\tPassword    : ");
	getchar();
	scanf("%s",li->sPasswd);
	/*GET the record in sn
	*/
	if(getSsignupInfo(ss, u_id)==0){
		printf("Records are not copied");
	}
	if(getSloginInfo(sl, u_id)==0){
		printf("Records are not copied");
	}

	//COPYING MODIFIED DETAILS
	if(strcmp(ob->name,"1")!=0){
		strcpy(ss->name,ob->name);
	}
	if(ob->phono != 1){
		ss->phono=ob->phono;
	}
	if(strcmp(ob->dept,"1")!=0){
		strcpy(ss->dept,ob->dept);
	}
	if(strcmp(ob->addre,"1")!=0){
		strcpy(ss->addre,ob->addre);
	}
	if(strcmp(li->sName,"1")!=0){
		strcpy(sl->sName,li->sName);
	}
	if(strcmp(li->sPasswd,"1")!=0)
	{
		if(validPassword(li->sPasswd)==0){
			printf("Your password should contain atleast 1 special character, small & capital character, and a number.");
			printf("\t\tPassword  : ");
			getchar();
			scanf("%s",li->sPasswd);
		}
		strcpy(sl->sPasswd,li->sPasswd);
	}
	studSignUpWrite(ss, u_id);
	studLoginWrite(sl, u_id);	
    	fclose(fp);
	fclose(pf);
}

int viewAlumniDetails()
{
	FILE *fp;
	SIGNUP *sn = (SIGNUP *)malloc(sizeof(SIGNUP));
	int a, f = 0;
	printf("\n\n\n\t\t\t\tAlumini Details\n\n");
	printf("\n\t\tEnter the Registration number to be searched : ");
	scanf("%d",&a);
	fp = fopen("./data/Users.txt","r");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(0);
	} 
	else 
	{
		while(fread(sn,sizeof(SIGNUP),1,fp))
		{
			if(a==sn->uni_id)
			{
				f = 1;
				break;
			}
		}
		if(f==1){
			viewProfile(sn->uni_id);
		} else {
			printf("\n\n\t\t Alumni Record Not Found !!");
		}
	}
	fclose(fp);
	return 0;
}

void viewJobProfile(){
	FILE *fp;
	JOB *jb = (JOB *)malloc(sizeof(JOB));
	fp = fopen("./data/job.txt", "r");
	printf("\n=============JOB PROFILE============\n\n\n");
	if(fp == NULL){
		printf("Unable to open the file");
		exit(0);
	} else {
		printf("\t\t\tRECORDS\n");
	}
	while(fread(jb, sizeof(JOB),1,fp)){
        printf("\n\t\t\t Job Role            :  %s",jb->jobRole);
        printf("\n\t\t\t Date of Post        :  %s",jb->job_dop);
	printf("\n\t\t\t Job Skills Required :  %s",jb->jobSkills);
        printf("\n\t\t\t Company             :  %s",jb->companyName);
        printf("\n\t\t\t Experience          :  %d",jb->exp);
        printf("\n\t\t\t Contact info        :  %s\n",jb->contactInfo);
	}
	fclose(fp);
}

int getSsignupInfo(STUDS *ss, int u_id){
	FILE *fp;
	fp = fopen("./data/stuUsers.txt","r");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(0);
	} else {
		while(fread(ss, sizeof(STUDS), 1,fp)){
			if(u_id==ss->regno){
				return 1;
			}
		}
	}
	fclose(fp);
	return 0;
}

int getSloginInfo(STUDL *sl, int u_id){
	FILE *fp;
	fp = fopen("./data/stuLogin.txt","r");
	if(fp == NULL)
	{
		printf("Unable to open the file");
		exit(0);
	} else {
		while(fread(sl, sizeof(STUDL), 1,fp)){
			if(u_id==sl->regno){
				return 1;
			}
		}
	}
	fclose(fp);
	return 0;
}
