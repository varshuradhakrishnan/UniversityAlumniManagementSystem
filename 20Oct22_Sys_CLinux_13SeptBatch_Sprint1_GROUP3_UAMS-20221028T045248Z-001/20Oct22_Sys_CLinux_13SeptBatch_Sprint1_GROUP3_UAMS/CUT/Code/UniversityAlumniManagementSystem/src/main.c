#include <common.h>
#include <main.h>

int main()
{
	int ch, alumni_ch, stu_ch, admin_ch;
	int id;
	while(1){
		system("clear");
		printf("%s", WelcomeMsg);
		printf("%s", MainMenu);
		scanf("%d", &ch);
        switch(ch)
        {
            case 1:
                system("clear");
                printf("%s", AlumniMenu);
                scanf("%d", &alumni_ch);
                switch (alumni_ch)
                {
                    case 1:
                        system("clear");
                        printf("\nSign up\n");
                        if((id = signUpRecs())==0)
                            signUp(0+1);
                        else
                            signUp(id+1);
                        break;
                    case 2:
                        system("clear");
                        printf("\nLog in\n");
                        if(login()==1)
                        {
				printf("%s",AdminMenu);
				scanf("%d", &admin_ch);
				switch (admin_ch)
			        {
			            case 1 :
			                system("clear");
			                printf("Edit alumni");
			                editAlumniInfo();
			                break;
			            case 2:
			                system("clear");
			                printf("Delete alumni");
			                deleteAlumniInfo();
			                break;
			            case 3:
			                printf("\nExit\n");
			                exit(EXIT_SUCCESS);
			                break;
			            default:
			                printf("\nSomething went wrong. Please select the valid choice.");
			                break;
			        }
                        }
                    case 3:
                        printf("\nExit\n");
                        exit(EXIT_SUCCESS);
                        break;
                    default:
                        printf("\nSomething Went Wrong. Please select the valid choice.\n");
                        break;
                }
	    case 2:
	        system("clear");
	        while(1){
			printf("%s", StudentMenu);
			scanf("%d", &stu_ch);
			switch (stu_ch)
			{
		            case 1:
		                system("clear");
		                printf("\nSign up\n");
		                if((id = studSignUpRecs())==0)
		                    studSignUp(0+1);
		                else
		                    studSignUp(id+1);
		                break;
		            case 2:
		                studLogin();
		                break;
		            case 3:
		                printf("\nExit\n");
		                exit(EXIT_SUCCESS);
		                break;
		            default:
		                printf("\nSomething Went Wrong. Please select the valid choice.\n");
		                break;
		        }
                }
            case 3:
                printf("\nExit\n");
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("\nSomething Went Wrong. Please select the valid choice.\n");
                break;
        }
    }
}
