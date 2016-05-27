/*
	Name   : Shiv Pratap Singh
	Course : Programming Techniques in C
	Project: Library Management System
*/
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<dos.h>
#include<conio.h>
#include<ctype.h>

#define ADMIN "shiv"
#define PASS "password"


/*=====================================================Global===================================================*/

struct userMenu
{
	int bookID;
	int bookQty;
	char bookName[80];
	char bookAuthor[80];
	char bookCatg[80];
	float bookPrice;
}bookSTC;

struct userMember
{
	char userName[80];
	char userAdd[80];
	char userMem[80];
	char userCon[80];
	char userVal[80];
}userSTC;

struct admin
{
	char adminName[80];
	char adminPass[80];
}adminSTC;

struct login
{
	char userName[80];
	char passWord[80];
};

FILE *fp;
FILE *fu;
FILE *chkmem;
FILE *fop;
FILE *opMem;

char ch;
char str[100];
char userID[80];

int des = 0;

int loginMenu(struct login test);
void userlogin();
void console();
void gotoxy(int,int);
void clear();
void delay(int);
void design(int,int);
void border();
void closeAll();
void addBooks();
void issueNewBook();
void viewBookList();
void viewIssuedBook();
void searchBook();
void userMenu();
void viewAcc();
void userReturn();
void addMember();
void deleteMember();
void adminMenu();


/*======================================================Display====================================================*/

void console()
{
	system("mode CON: COLS=140 LINES=40");
}

COORD coord = { 0, 0 };

void gotoxy(int x, int y)
{
	coord.X = x; 
	coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear()
{
	system("cls");
}

void delay(int msec)
{
	Sleep(msec);
}

void closeAll()
{
	fclose(fp);
	fclose(fu);
	fclose(chkmem);
	fclose(fop);
	fclose(opMem);
}

void design(int limit,int select)
{
	char ch =220;
	
	if(select == 1)
		for(des = 0 ; des < limit ; des++)
				printf("%c",ch);
	else if(select == 2)
		for(des = 0 ; des < limit ; des++)
				printf(" ");
	else if(select == 3)
		for(des = 0 ; des < limit ; des++)
				printf("||");
}

void border()
{
	int i = 0;
	char ch;

	console();
	//clear();

	for(i = 1; i < 138;i++)
	{
		ch = 219;
		gotoxy(i,1);
		//design(1,1);
		printf("%c",ch);
		gotoxy(i,38);
		//design(1,1);
		printf("%c",ch);
	}
		
	for(i = 1; i < 39;i++)
	{
		ch = 219;
		gotoxy(1,i);
		//design(1,3);
		printf("%c",ch);
		gotoxy(138,i);
		//design(1,3);
		printf("%c",ch);
	}

}

/*==================================================End Of Display==================================================*/

/*======================================================LogIN=======================================================*/


int loginMenu(struct login test)
{

	char neww[100] = { 0 };
	char user[100], c;
	int p = 0, f = 0, i;

	for (i = 0; i<3; i++)
	{
		p = 0;
		f = 0;
		clear();
		border();
		gotoxy(50, 8);
		delay(100);
		printf("..Log In..\n\n");
		gotoxy(40,10);
		design(30,1);
		gotoxy(40,25);
		design(30,1);
		gotoxy(40, 15);
		delay(100);
		printf("UserName :\t");
		scanf("%s", &user);
		delay(100);
		gotoxy(40, 20);
		printf("Password :\t");
		do
		{
			c = getch();
			if (isprint(c))
			{
				neww[p++] = c;
				printf("*");
			}
			else if (c == 8 && p)
			{
				neww[p--] = '\0';
			}
		} while (c != 13);
		if (!strcmp(neww, test.passWord) && !strcmp(test.userName, user))
		{
			gotoxy(40, 27);
			delay(100);
			printf("    Authentication Successful!\a\n");
			getch();
			f = 1;
			break;
		}
		else
		{
			gotoxy(40, 27);
			delay(100);
			printf("Incorrect UserName or Password!\a");
			gotoxy(40, 28);
			printf("Attempt:%d",i+1);
			getch();
		}
	}
	if (f == 1)
		return 1;
	else
		return 0;
}

void userlogin()
{
	char log = 'y';
	clear();
	border();
	gotoxy(50, 8);
	delay(100);
	printf("..Log In..\n\n");
	gotoxy(40,10);
	design(30,1);
	gotoxy(40,25);
	design(30,1);
	gotoxy(40,17);
	delay(100);
	printf("User ID:\t");
	scanf("%s", &userID);
	
	strcat(userID, ".txt");

	chkmem = fopen(userID, "r");
	
	if (chkmem == NULL)
	{
		gotoxy(42,27);
		printf("You Are not registered yet!");
		gotoxy(42,29);
		printf("Contact Your Administrator!\n");
		getch();
		main();
	}
	else
	{
		fclose(chkmem);
		userMenu();
	}

}


/*===================================================End Of Login==================================================*/


/*=======================================================Book======================================================*/


void addBooks()
{
	char save;
	
	fp = fopen("book.txt", "r");
	
	clear();
	border();
	
	if (fp == NULL)
	{
		gotoxy(55,15);
		printf("Creating DataBase!\a");
		getch();
		delay(100);
		fp = fopen("book.txt", "w");
		fclose(fp);
		fp = fopen("book.txt", "r");
	}
	gotoxy(55,15);
	printf("Opening DataBase!\a");
	getch();
	clear();
	//border();
	printf("\n\n");
	gotoxy(53, 2);
	printf(".Book Details.\n\n");
	printf("ID\t\tName\t\tAuthor\t\tCatagory\t\tPrice\t\tQuantity\t\tTime\t\t\tDate\n");
	design(140,1);
	printf("\n\n");
	
	while (1)
	{
		ch = fgetc(fp);
		if (ch == EOF)
			break;
		printf("%c", ch);
	}
	
	getch();
	fclose(fp);
	
	fp = fopen("book.txt", "a+w");
	
	if (fp == NULL)
	{
		gotoxy(55,15);
		printf("Can't Open Database!\a");
		delay(100);
		exit(1);
	}
	
	clear();
	border();
	gotoxy(48, 8);
	delay(100);
	printf(".Enter Details.\n\n");
	gotoxy(40,10);
	design(35,1);
	gotoxy(40,25);
	design(35,1);
	gotoxy(40,12);
	delay(100);
	printf("Book ID       : ");
	scanf("%d", &bookSTC.bookID);
	gotoxy(40,14);
	printf("Book Name     : ");
	scanf("%s", &bookSTC.bookName);
	gotoxy(40,16); 
	printf("Author        : ");
	scanf("%s", &bookSTC.bookAuthor);
	gotoxy(40,18);
	printf("Book Category : ");
	scanf("%s", &bookSTC.bookCatg);
	gotoxy(40,20);
	printf("Price         : ");
	scanf("%f", &bookSTC.bookPrice);
	gotoxy(40,22);
	printf("Quantity      : ");
	scanf("%d", &bookSTC.bookQty);
	gotoxy(42,27);
	printf("Save Book Details.(Y/N)\n");
	save = getch();
	
	if (save == 'Y' || save == 'y')
	{
		fprintf(fp, "%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t\t%d\t\t%s\t\t%s", bookSTC.bookID, bookSTC.bookName, bookSTC.bookAuthor, bookSTC.bookCatg, bookSTC.bookPrice, bookSTC.bookQty, __TIME__, __DATE__);
		fprintf(fp, "\n");
	}
	
	fclose(fp);

}


void issueNewBook()
{
	char flagc = 'N';
	char save;
	
	clear();
	border();
	gotoxy(47, 8);
	delay(100);
	printf(".Enter Details.\n\n");
	gotoxy(40,10);
	design(30,1);
	gotoxy(40,25);
	design(30,1);
	gotoxy(40,17);
	delay(100);
	printf("User ID:\t");
	scanf("%s", &userID);

	strcat(userID, "issue.txt");
	
	fu = fopen(userID, "r");
	fp = fopen("book.txt", "r");

	if (fu == NULL)
	{
		gotoxy(42,27);
		printf("User Not Yet Registered!\a");
		delay(100);
		getch();
		return 0;
	}

	if (fp == NULL)
	{
		gotoxy(42,27);
		printf("Can't Open Database!\a");
		delay(100);
		exit(1);
	}
	
	fclose(fu);
	fu = fopen(userID, "a+w");
	
	printf("\n\n");
	clear();
	//border();
	gotoxy(53, 2);
	printf(".Book Details.\n\n");
	printf("ID\t\tName\t\tAuthor\t\tCatagory\t\tPrice\t\tQuantity\t\tTime\t\t\tDate\n");
	design(140,1);
	
	while (1)
	{
		ch = fgetc(fp);
		if (ch == EOF)
			break;
		printf("%c", ch);
	}
	
	getch();
	fclose(fp);
	
	do
	{
		clear();
		border();
		gotoxy(48, 8);
		delay(100);
		printf(".Enter Details.\n\n");
		design(40,2);
		design(35,1);
		gotoxy(40,25);
		design(35,1);
		gotoxy(40,12);
		delay(100);
		printf("Book ID       : ");
		scanf("%d", &bookSTC.bookID);
		gotoxy(40,14);
		printf("Book Name     : ");
		scanf("%s", &bookSTC.bookName);
		gotoxy(40,16); 
		printf("Author        : ");
		scanf("%s", &bookSTC.bookAuthor);
		gotoxy(40,18);
		printf("Book Category : ");
		scanf("%s", &bookSTC.bookCatg);
		gotoxy(40,20);
		printf("Price         : ");
		scanf("%f", &bookSTC.bookPrice);
		gotoxy(40,22);
		printf("Quantity      : ");
		scanf("%d", &bookSTC.bookQty);
		gotoxy(42,27);
		printf("Save Issue Details.(Y/N): ");
		
		save = getch();
		
		if (save == 'Y' || save == 'y')
		{
			fprintf(fu, "%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t\t%d\t\t%s\t\t%s", bookSTC.bookID, bookSTC.bookName, bookSTC.bookAuthor, bookSTC.bookCatg, bookSTC.bookPrice, bookSTC.bookQty, __TIME__, __DATE__);
			fprintf(fu, "\n");
		}
		
		gotoxy(42,27);
		printf("                         ");
		gotoxy(42,27);
		printf("Issue More books.(Y/N): ");
		flagc = getch();

	} while (flagc == 'Y' || flagc == 'y');
	
	fclose(fu);

}

void viewBookList()
{
	int i = 3;
	int j = 3;
	
	clear();
	border();
	fp = fopen("book.txt", "r");
	
	if (fp == NULL)
	{
		gotoxy(55,15);
		printf("Database Not Found!\a");
		getch();
		exit(1);
	}
	gotoxy(55,15);
	printf("Opening DataBase!\a");
	getch();	
	clear();
	//border();
	printf("\n\n");
	design(58,2);
	printf(".Book Details.\n\n");
	printf("ID\t\tName\t\tAuthor\t\tCatagory\t\tPrice\t\tQuantity\t\tTime\t\t\tDate\n");
	design(140,1);
	printf("\n\n");			
	
	while (1)
	{

		ch = fgetc(fp);
		if (ch == EOF)
			break;
		printf("%c", ch);
	}
	
	getch();
	fclose(fp);

}

void viewIssuedBook()
{
	clear();
	border();
	gotoxy(47, 8);
	delay(100);
	printf(".Enter Details.\n\n");
	gotoxy(40,10);
	design(30,1);
	gotoxy(40,25);
	design(30,1);
	gotoxy(40,17);
	delay(100);
	printf("User ID : ");
	scanf("%s", &userID);
	
	strcat(userID, "issue.txt");
	fp = fopen(userID, "r");
	
	if (fp == NULL)
	{
		gotoxy(42,27);
		printf("No Issue Data Found!\a");
		getch();
		return 0;
	}
	clear();
	border();
	gotoxy(55,15);
	printf("Opening DataBase!\a");
	getch();
	clear();
	//border();
	gotoxy(53, 2);
	printf(".Issued Book Details.\n\n\n");
	printf("ID\t\tName\t\tAuthor\t\tCatagory\t\tPrice\t\tQuantity\t\tTime\t\t\tDate\n");
	design(140,1);
	printf("\n\n");		
	
	while (1)
	{
		ch = fgetc(fp);
		if (ch == EOF)
			break;
		printf("%c", ch);
	}
	
	getch();
	fclose(fp);

}

void searchBook()
{
	char ch[80];
	char str[80];
	int f = 0;

	fp = fopen("book.txt", "r");

	clear();
	border();
	gotoxy(50, 8);
	delay(100);
	printf("  .Search.\n\n");
	gotoxy(40,10);
	design(30,1);
	gotoxy(40,25);
	design(30,1);
	gotoxy(40,17);
	delay(100);
	printf("Book Name : ");
	scanf("%s", &str);

	if (fp == NULL)
	{
		gotoxy(42,27);
		printf("Can't Open the database!\a");
		delay(100);
		exit(1);
	}

	while (1)
	{
		fscanf(fp, "%s", &ch);
		if (strcmp(str, ch) == 0)
		{
			f = 1;
			break;
		}
		if (feof(fp))
			break;
	}
	if(f == 1)
	{
		gotoxy(45,27);
		printf("Book Found in Records.\n");
		getch();
	}
	else
	{
		gotoxy(45,27);
		printf("                      \n");
		gotoxy(45,27);
		printf("Book Not Found.\n");
		getch();
	}
	fclose(fp);
	
}

/*====================================================End of Book==================================================*/


/*==================================================User==========================================================*/

void userMenu()
{
	char choice;

	do
	{
		clear();
		border();
		closeAll();
		gotoxy(48,5);
		printf(".Member Menu.\n");
		gotoxy(40,8);
		design(30,1);
		gotoxy(40,28);
		design(30,1);
		gotoxy(40,12);
		printf("1. View Issued Books\n");
		gotoxy(40,14);
		printf("2. Return Book\n");
		gotoxy(40,16);
		printf("3. View Available Books\n");
		gotoxy(40,18);
		printf("4. Search for a Book\n");
		gotoxy(40,20);
		printf("5. View Account Details\n");
		gotoxy(40,22);
		printf("0. Log Out\n");
		gotoxy(40,30);
		printf("Enter Your Choice: ");

		choice = getche();

		switch (choice)
		{
		case '1': {
					  viewIssuedBook();
					  break;
		}

		case '2': {
					  userReturn();
					  break;
		}

		case '3': {
					  viewBookList();
					  break;
		}

		case '4': {
					  searchBook();
					  break;
		}

		case '5': {
					  viewAcc();
					  break;
		}

		case '0': {
					  break;
		}

		default: printf("Wrong Choice!");
		}
	} while (choice != '0');
}

void viewAcc()
{
	char chu;
	int j = 0;
	int i = 0;

	clear();
	border();
	gotoxy(47, 8);
	delay(100);
	printf(".Enter Details.\n\n");
	gotoxy(40,10);
	design(30,1);
	gotoxy(40,25);
	design(30,1);
	gotoxy(40,17);
	delay(100);
	printf("User ID:\t");
	scanf("%s", &userID);

	strcat(userID, ".txt");
	clear();
	border();
	
	fop = fopen(userID, "r");
	
	if (fop == NULL)
	{
		gotoxy(42,27);
		printf("Member Details Not Found!");
		delay(100);
		exit(1);
	}
	
	gotoxy(50, 8);
	delay(100);
	printf(".Member Details.\n\n");
	gotoxy(40,10);
	design(35,1);
	gotoxy(40,25);
	design(35,1);
	gotoxy(40,12);
	delay(100);
	j = 12;
	i = 41;

	while (1)
	{
		chu = fgetc(fop);

		if (chu == EOF)
			break;

			if (chu == '\n')
		{
			j = j+2;
			gotoxy(40,j);
			i = 40;
		}

		gotoxy(++i,j);
		printf("%c", chu);
	}

	getch();
	fclose(fop);

}

void userReturn()
{
	char bookID[80];
	char userTemp[80];
	char ch[80];
	char date[80];
	char mon[80];
	char day[80];
	char year[80];

	clear();
	border();
	gotoxy(50, 8);
	delay(100);
	printf(".Enter Details.\n\n");
	gotoxy(40,10);
	design(30,1);
	gotoxy(40,25);
	design(30,1);
	gotoxy(40,13);
	delay(100);
	printf("User ID    : ");
	scanf("%s", &userID);
	strcpy(userTemp, userID);
	gotoxy(40,16);
	delay(100);
	printf("Book ID    : ");
	scanf("%s", &bookID);
	gotoxy(40,19);
	delay(100);
	printf("Issue Date : ");
	scanf("%s %s %s", &mon, &day, &year);

	strcat(userID, "Issue.txt");
	strcat(userTemp, "Temp.txt");

	fp = fopen(userID, "r");
	fu = fopen(userTemp, "a+w");

	if (fp == NULL)
	{
		gotoxy(42,27);
		printf("No Book Had Been Issued!");
		delay(100);
		exit(1);
	}
	if (fu == NULL)
	{
		gotoxy(42,27);
		printf("Can't Create Temp. File!");
		delay(100);
		exit(1);
	}

	while (1)
	{
		fscanf(fp, "%s", &ch);

		if (strcmp(bookID, ch) == 0)
		{
			do
			{
				fscanf(fp, "%s", &ch);
			} while (strcmp(ch, year) != 0);
		}
		else if (feof(fp))
			break;
		else
			fprintf(fu, "%s\t", ch);
	}

	if (strcmp(day, __DATE__) <= 0)
	{
		gotoxy(45,27);
		printf("No Fine");
		getch();
	}
	else
	{
		gotoxy(45,27);
		printf("\nFine is Rs. %.2f",strcmp(day, __DATE__));
		getch();
	}

	fclose(fp);
	fclose(fu);
	remove(userID);
	rename(userTemp, userID);

}

/*===========================================================End Of User===============================================*/

/*=================================================================Admin===============================================*/


void addMember()
{
	char save = 'y';
	char userTemp[80];
	char mName[80];

	clear();
	border();
	gotoxy(50, 8);
	delay(100);
	printf(".Enter Details.\n\n");
	gotoxy(40,10);
	design(30,1);
	gotoxy(40,25);
	design(30,1);
	gotoxy(40,12);
	delay(100);
	printf("User ID       : ");
	scanf("%s", &userID);
	strcpy(userTemp, userID);
	gotoxy(40,14);
	printf("Name          : ");
	scanf("%s %s", &userSTC.userName, &mName);
	gotoxy(40,16);
	printf("Address       : ");
	scanf("%s", &userSTC.userAdd);
	gotoxy(40,18);
	printf("Membership    : ");
	scanf("%s", &userSTC.userMem);
	gotoxy(40,20);
	printf("Contact No.   : ");
	scanf("%s", &userSTC.userCon);
	gotoxy(40,22);
	printf("Acc. Validity : ");
	scanf("%s", &userSTC.userVal);
	gotoxy(42,27);
	printf("Save Member details.(Y/N): ");

	save = getch();

	if (save == 'Y' || save == 'y')
	{
		strcat(userID, ".txt");
		opMem = fopen(userID, "w");
		fprintf(opMem, "User ID           :\t");
		fprintf(opMem, "%s", userTemp);
		fprintf(opMem, "\nName            :\t");
		fprintf(opMem, "%s %s", userSTC.userName, mName);
		fprintf(opMem, "\nAddress         :\t");
		fprintf(opMem, "%s", userSTC.userAdd);
		fprintf(opMem, "\nMembership      :\t");
		fprintf(opMem, "%s", userSTC.userMem);
		fprintf(opMem, "\nContact No.     :\t");
		fprintf(opMem, "%s", userSTC.userCon);
		fprintf(opMem, "\nAcc. Validity   :\t");
		fprintf(opMem, "%s", userSTC.userVal);

		fclose(opMem);
	}

}

void deleteMember()
{
	char del = 'n';

	clear();
	border();
	gotoxy(47, 8);
	delay(100);
	printf(".Enter Details.\n\n");
	gotoxy(40,10);
	design(35,1);
	gotoxy(40,25);
	design(35,1);
	gotoxy(40,17);
	delay(100);
	printf("User ID       : ");
	scanf("%s", &userID);
	gotoxy(42,27);
	printf("Delete Member Details.(Y/N): ");
	del = getche();

	if (del == 'Y' || del == 'y')
	{
		strcat(userID, ".txt");
		remove(userID);
	}

}

void adminMenu()
{
	char achoice;

	do
	{
		clear();
		border();
		gotoxy(50,5);
		printf(".Admin Menu.");
		gotoxy(40,8);
		design(30,1);
		gotoxy(40,28);
		design(30,1);
		gotoxy(40,12);		
		printf("1. Add New Book\n");
		gotoxy(40,14);
		printf("2. Issue a Book\n");
		gotoxy(40,16);
		printf("3. Add a New Member\n");
		gotoxy(40,18);
		printf("4. View Available Books\n");
		gotoxy(40,20);
		printf("5. Search for a Book\n");
		gotoxy(40,22);
		printf("6. Close Account\n");
		gotoxy(40,24);
		printf("0. Log Out\n");
		gotoxy(40,30);
		printf("Enter Choice:\t");		

		achoice = getch();

		switch (achoice)
		{
		case '1': {
					  addBooks();
					  break;
		}

		case '2': {
					  issueNewBook();
					  break;
		}

		case '3': {
					  addMember();
					  break;
		}

		case '4': {
					  viewBookList();
					  break;
		}

		case '5': {
					  searchBook();
					  break;
		}

		case '6': {
					  deleteMember();
					  break;
		}

		case '0': {
					  //main();
					  break;
		}

		default: printf("\nWrong Choice!");
			break;
		}
	} while (achoice != '0');

}


/*==========================================================End Of Admin===============================================*/

/*=============================================================Main===================================================*/



int main()
{
	int flag = 0;
	struct login admin;
	char loginChoice ;

	clear();
	console();
	border();
	gotoxy(50,10);
	printf(".Select Entry Level.\n\n");
	gotoxy(50,12);
	design(20,1);
	printf("\n");
	gotoxy(50,16);
	printf("1. Administrator\n");
	gotoxy(50,18);
	printf("2. Member\n");
	gotoxy(50,20);
	printf("0. Exit\n");
	gotoxy(50,24);
	design(20,1);
	gotoxy(50,26);
	printf("Enter choice:\t");
	
	loginChoice = getch();
	
	switch (loginChoice)
	{
	case '1':   {
				  strcpy(admin.userName, ADMIN);
				  strcpy(admin.passWord, PASS);
				  flag = loginMenu(admin);
				  if (flag == 1)
					  adminMenu();
				  break;
	}

	case '2':	{
				userlogin();
				break;
	}

	case '0': 	{
					clear();
					border();
					gotoxy(62,3);
					printf("Credits\n\n");
					gotoxy(60,6);
					design(12,1);
					gotoxy(50,10);
					printf("Design by: Shiv Pratap Singh");
					gotoxy(50,15);
					printf("Email    : shiv.safari@gmail.com");
					gotoxy(50,20);
					printf("Contact  : www.facebook.com/TechArtWork\n");
					delay(2000);
					clear();
					border();
					gotoxy(60,15);
					printf("Thank You\n");
					gotoxy(60,17);
					design(9,1);
					delay(1000);
					exit(0);
	}

	default:  printf("\nWrong Choice\n");
		break;
	}
	main();
	return 0;

}


/*=================================================================End Of Main========================================*/

