// Movie ticket booking using C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //for sleep function
#include <ctype.h> //for using toupper function
struct record
{
	char name[50];
	char genre[10];
	int code;
	int price;
} addlist;
struct oldrecord 
{
	char person_name[50];
	long long int mobile_number;
	int seat_reserved;
	int total_ticketprice;
	char movie_name[50];
}test;
void add_movie();
void view();
void book();
void reserved_list();
void delete_movie();
void cancel();
int code_exists(FILE *fs, int code);
char re_add[1];
char choose[1];
int main()
{
	char ch,choice;
	int select=0;
	FILE *fp;
retry:
	system("COLOR 09");
	printf("\t\t\t\t**************************************************\n");
	printf("\t\t\t\t\t\t====================\n");
	printf("\t\t\t\t\t\tMOVIE TICKET BOOKING\n");
	printf("\t\t\t\t\t\t====================\n");
	printf("\t\t\t\t**************************************************\n");
	printf("\n\t\t\t\t1. Admin");
	printf("\n\t\t\t\t2. User");
	printf("\n\n\t\tEnter your choice : ");
	scanf("%d", &select);
	switch (select)
	{
	case 1:
		char uname[30], pwd[25], un[30], pw[25];
		char x;
		fp = fopen("Password.txt", "r");
		if (fp == NULL)
		{
			printf("\nError! File not found");
		}
		fscanf(fp, "%s%s", uname, pwd);
	flag:
		fflush(stdin);
		printf("\n\t\tEnter username : ");
		gets(un);
		fflush(stdin);
		printf("\n\t\tEnter password : ");
		gets(pw);
		// comparing the username and password given by the user
		if ((strcmp(uname, un) == 0) && (strcmp(pwd, pw) == 0))
		{
			//printf("\n\t\tLogin successful!!!");
			printf("\n");
			printf("\n\t\t\t\t\t\tLogging in . . . .");
			sleep(3);
			system("cls");
		menu:
			printf("\n");
			printf("\t\t\t\t\t__________ADMIN OPTIONS__________\n");
			printf("\n");
			printf("\n\t\t\t\tPress A. to add movie");
			printf("\n\t\t\t\tPress B. to show movie list");
			printf("\n\t\t\t\tPress C. to delete movie ");
			printf("\n\t\t\t\tPress D. to view reserved movie details ");
			printf("\n\t\t\t\tPress E. to go back to main menu");
			printf("\n\t\t\t\tPress F. to exit ");
		again:
			fflush(stdin);
			printf("\n\n\t\tEnter your choice : ");
			scanf("%c", &choice);
			//same as strupr and requires ctype.h header file
			choice=toupper(choice);
			switch (choice)
			{
			case 'A':
				add_movie();
				goto menu;
				break;
			case 'B':
				view();
				goto menu;
				break;
			case 'C':
				delete_movie();
				goto menu;
				break;
			case 'D':
				reserved_list();
				goto menu;
			case 'E':
				system("cls");
				goto retry;
				break;
			case 'F':
				exit(0);
			default:
				printf("\n\t\tWrong choice.");
				printf("\n\t\tEnter correct choice.");
				goto again;
			}
		}
		else
		{
			printf("\n\t\tWrong username or password.");
			printf("\n\n\t\tDo you want to try again?");
			fflush(stdin);
			printf("\n\t\tPress 'Y' to continue or 'N' to exit : ");
			x = getchar();
			{
				if (x == 'y' || x == 'Y')
				{
					system("cls");
					goto flag;
				}
				else
				{
					exit(0);
				}
			}
		}
		break;
	case 2:
	label:
		system("cls");
		printf("\n\t\t\t\t\t__________USER OPTIONS__________");
		printf("\n");
		printf("\n\t\t\t\tPress A. to View Movie List");
		printf("\n\t\t\t\tPress B. to Book Ticket");
		printf("\n\t\t\t\tPress C. to Cancel Ticket");
		printf("\n\t\t\t\tPress D. to Go Back to Main Menu");
		printf("\n\t\t\t\tPress E. to Exit");
		fflush(stdin);
		printf("\n\n\t\tEnter your choice : ");
		scanf("%c", &ch);
		ch=toupper(ch);
		switch (ch)
		{
		case 'A':
			view();
			goto label;
			break;
		case 'B':
			book();
			goto label;
			break;
		case 'C':
			cancel();
			goto label;
			break;
		case'D':
			system("cls");
			goto retry;
			break;	
		case 'E':
			exit(0);
		default:
			printf("\n\t\tWrong choice.");
			printf("\n\t\tEnter correct choice.");
			goto label;
		}
	default:
		printf("\n\t\tInvalid input.");
		printf("\n\t\tEnter the correct choice.");
		printf("\n\n");
		goto retry;
	}
	return 0;
}
void add_movie()
{
	FILE *fs;
re_movie:
	fs = fopen("Details.txt", "r+");
	if (fs == NULL)
	{
		printf("\nError! File not found");
		exit(0);
	}
	fflush(stdin);
	printf("\n\t\tEnter movie name: ");
	gets(addlist.name);
	fflush(stdin);
	printf("\n\t\tEnter movie genre: ");
	gets(addlist.genre);
	fflush(stdin);
re_code:
	printf("\n\t\tEnter movie code: ");
	scanf("%d", &addlist.code);
	if (code_exists(fs, addlist.code))
	{
		printf("\n\t\tThe movie with code %d already exists. Try another code.", addlist.code);
		sleep(2);
		goto re_code;
	}
	printf("\n\t\tEnter movie ticket price: ");
	scanf("%d", &addlist.price);
	fflush(stdin);
	printf("\n");
	fseek(fs, 0, SEEK_END);
	fwrite(&addlist, sizeof(struct record), 1, fs);
	fclose(fs);
	printf("\n\t\tMovie added successfully.");
	sleep(1);
	printf("\n");
	printf("\n\t\tDo you want to add another movie?[Y/N] : ");
	scanf("%c", &re_add);
	strlwr(re_add);
	if (strcmp(re_add, "y") == 0)
	{
		goto re_movie;
	}
	system("cls");
}
void view()
{
	FILE *fs;
	fs = fopen("Details.txt", "r");
	if (fs == NULL)
	{
		printf("\n\t\tError! File not found");
		exit(0);
	}
	system("cls");
	printf("\n");
	printf("\t\t\t\t______________List of ongoing movies details______________\n\n ");
	printf("\t\t%-55s %-15s %-15s %-15s\n\n", "Movie Name", "Movie Genre", "Movie Code", "Ticket Price");
	printf("\n");
	printf("\t\t_________________________________________________________________________________________________");
	printf("\n");
	while (fread(&addlist, sizeof(struct record), 1, fs) == 1)
	{
		printf("\t\t %-55s %-15s %-15d %-15d", addlist.name, addlist.genre,addlist.code, addlist.price);
		printf("\n");
		printf("\t\t_________________________________________________________________________________________________");
		printf("\n");
	}
	fclose(fs);
	fflush(stdin);
	getchar();
	system("cls");
}
void delete_movie()
{
	int found = 0, search =0;
	FILE *fp, *fs;
	fs = fopen("Details.txt", "r");
	if (fs == NULL)
	{
		printf("\n\t\tError! File not found");
		exit(0);
	}
	system("cls");
	printf("\n");
	printf("\t\t\t\t______________List of ongoing movies details______________\n\n ");
	printf("\t\t%-55s %-15s %-15s %-15s\n\n", "Movie Name", "Movie Genre", "Movie Code", "Ticket Price");
	printf("\n");
	printf("\t\t_________________________________________________________________________________________________");
	printf("\n");
	while (fread(&addlist, sizeof(struct record), 1, fs) == 1)
	{
		printf("\t\t %-55s %-15s %-15d %-15d", addlist.name, addlist.genre,addlist.code, addlist.price);
		printf("\n");
		printf("\t\t_________________________________________________________________________________________________");
		printf("\n");
	}
	fclose(fs);
re_delete:
	printf("\n\n\t\tEnter the code of movie you want to delete : ");
	scanf("%d", &search);
	fp = fopen("Details.txt", "r");
	if (fp == NULL)
	{
		printf("\nFile not found.");
		exit(0);
	}
	fs = fopen("Temp.txt", "w+");
	if (fs == NULL)
	{
		printf("\nFile not found.");
		exit(0);
	}
	while (fread(&addlist, sizeof(struct record), 1, fp))
	{
		if (addlist.code != search)
		{
			fwrite(&addlist, sizeof(struct record), 1, fs);
		}
		else
		{
			found = 1;
		}
	}
	fclose(fp);
	fclose(fs);
	remove("Details.txt");
	rename("temp.txt", "Details.txt");
	if (found == 1)
	{
		printf("\n\t\tMovie with code %d is deleted successfully.", search);
	}
	else
	{
		printf("\n\t\tMovie with code %d not found.", search);
	}
	found=0;
	sleep(1);
	printf("\n");
	fflush(stdin);
	printf("\n\t\tDo you want to delete another movie?[Y/N] : ");
	scanf("%c", &choose);
	strlwr(choose);
	if(strcmp(choose,"y") == 0)
	{
		goto re_delete;
	}
	system("cls");
}
int code_exists(FILE *fs, int code)
{
	struct record read_record;
	int code_found = 0;
	while (fread(&read_record, sizeof(struct record), 1, fs))
	{
		if (read_record.code == code)
		{
			code_found = 1;
			rewind(fs);
			return code_found;
		}
	}
	return code_found;
}
void book()
{
	struct record check;
	int movie_code=0; 
	int check1=0;
	FILE *fs,*fp,*ufp;
	fs = fopen("Details.txt", "r");
	if (fs == NULL)
	{
		printf("\n\t\tError! File not found");
		exit(0);
	}
	system("cls");
	printf("\n");
	printf("\t\t\t\t______________List of ongoing movies details______________\n\n ");
	printf("\t\t%-55s %-15s %-15s %-15s\n\n", "Movie Name", "Movie Genre", "Movie Code", "Ticket Price");
	printf("\n");
	printf("\t\t______________________________________________________________________________________________________");
	printf("\n");
	while (fread(&addlist, sizeof(struct record), 1, fs) == 1)
	{
		printf("\t\t %-55s %-15s %-15d %-15d", addlist.name, addlist.genre, addlist.code, addlist.price);
		printf("\n");
		printf("\t\t______________________________________________________________________________________________________");
		printf("\n");
	}
code:
	printf("\n\n\t Enter movie code you want to book ticket for : ");
	scanf("%d",&movie_code);
	
	fp = fopen("Details.txt","r");
	if(fp == NULL)
	{
		printf("Error! File does not found !");
		exit(0);
	}
	
	ufp=fopen("oldTransaction.txt","r+");
	if(ufp == NULL)
	{
		printf("FIle not Found");
	}
	else
	{
		
		while (fread(&addlist, sizeof(struct record), 1, fp) == 1)
		{
			if(addlist.code==movie_code)
			{	
				check=addlist;
				check1=1;
			}
	
		}
	}
	if(check1==1)
	{	
		printf("\n\t Record Found\n");
		printf("\n\t\tCode : %d",check.code);
		printf("\n\t\tMovie name : %s",check.name);
		printf("\n\t\tMovie genre : %s",check.genre);
		printf("\n\t\tPrice of ticket: %d",check.price);
	}
	else
	{
		printf("\n\t\tWrong choice. Please enter code of available movie.");
		goto code;
	}
	printf("\n\n\t\t\t\t* _________________Fill Your Details_______________  *\n");
	fflush(stdin);
	printf("\n\t\t Name : ");
	gets(test.person_name);
	fflush(stdin);
	printf("\n\t\t Mobile number : ");
	scanf("%lld",&test.mobile_number);

	ticketrewind:
	printf("\n\t\t Total number of tickets : ");
	scanf("%d",&test.seat_reserved);
	if(test.seat_reserved>10)
	{
		printf("\n\t->Sorry! You can't reserve above 10tickets at once. Try again.");
		goto ticketrewind;
	}
	test.total_ticketprice = check.price * test.seat_reserved;
	printf("\n\t\tYour total expense for %d ticket is %d.",test.seat_reserved,test.total_ticketprice);
	strcpy(test.movie_name,check.name);
	fseek(ufp, 0, SEEK_END);
	fwrite(&test, sizeof(struct oldrecord), 1, ufp);
	printf("\n\n\t\t\t\t\t ***YOUR SEATS ARE RESERVED! ENJOY YOUR MOVIE!!*** \n");
	printf("\n\n\t\t\tRecord inserted sucessfully.");
	printf("\n");
	fflush(stdin);
	getchar();
	system("cls");

	fclose(fs);
	fclose(fp);
	fclose(ufp);
}
void reserved_list()
{
	FILE *fp;
	fp = fopen("oldTransaction.txt","r");
	if(fp == NULL)
	{
		printf("File does not found !");
		exit(0);
	}
		system("cls");
		printf("\n");
		printf("\t\t\t\t______________List of reserved movies details______________\n\n\n ");
		printf("\t\t%-25s %-25s %-25s %-20s %-20s \n\n", "Customer Name", " Customer Phone Number", "Total Seats Reserved", "Total price","Movie Name");
		printf("\n");
		printf("\t\t____________________________________________________________________________________________________________________________________\n\n");
	
		while (fread(&test, sizeof(struct oldrecord), 1, fp) == 1)
		{
			printf("\t\t%-25s %-25lld %-25d %-20d %-20s ", test.person_name, test.mobile_number,test.seat_reserved, test.total_ticketprice,test.movie_name);
			printf("\n");
			printf("\t\t____________________________________________________________________________________________________________________________________\n\n");
		}
	fclose(fp);
	fflush(stdin);
	getchar();
	system("cls");
}
void cancel()
{
	system("cls");
	int found=0;
	long long int cancel_code;
	FILE *fp,*fs;
	fp = fopen("oldTransaction.txt","r");
	if(fp == NULL)
	{
		printf("File does not found !");
		exit(0);
	}
	fs = fopen("Backup.txt", "w+");
	if (fs == NULL)
	{
		printf("\nFile not found.");
		exit(0);
	}

	printf("\n\t\tEnter your phone number: ");
	scanf("%lld",&cancel_code);
	while (fread(&test, sizeof(struct oldrecord), 1, fp))
	{
		if (test.mobile_number != cancel_code)
		{
			fwrite(&test, sizeof(struct oldrecord), 1, fs);
		}
		else
		{
			found = 1;
		}
	}
	fclose(fp);
	fclose(fs);
	remove("oldTransaction.txt");
	rename("Backup.txt", "oldTransaction.txt");
	if (found == 1)
	{
		printf("\n\t\tMovie reservation has been cancelled successfully.");
	}
	else
	{
		printf("\n\t\tMovie reservation not found.");
	}
	found=0;
	fflush(stdin);
	getchar();
	system("cls");
}
