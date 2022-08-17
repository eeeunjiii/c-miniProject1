#define _CRT_SECURE_NO_WARININGS
#include <Windows.h> 
#include <dos.h>
#include <stdio.h>
#include <conio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct account INFO; //���ο� �ڷ��� ����

void getPassword(); //���α׷� ��й�ȣ�� �Է� �޴� �Լ�
void gotoxy(); //��ǥ�࿡ ���� ��ġ�� �����ϴ� �Լ�
void mainmenu(); //���� �޴�
void addAccount(); //������ ���� ������ �޴� �Լ�
void searchAccount(); //������ �˻��ϴ� �Լ�
void showCustomerlist(); //���� ����Ʈ�� ����ϴ� �Լ�
void sendCustomer(); //����ڿ��� �������� û���ϴ� �Լ�
void exitService(); //���񽺸� �����ϴ� �Լ�
void deleteAccount(); //������ �����ϴ� �Լ�
void deleteNode(INFO* remove); //���Ḯ��Ʈ�� �����ϴ� �Լ�
void insertNode(INFO* info); //��� �߰� �Լ�
INFO *searchNode(INFO* info, char name[20], int num); //��� Ž�� �Լ�
void printList(); //���� ��� �Լ�

char answer[20] = {"pass"}; //��й�ȣ
int line = 8; //printList �Լ��� ����� �� line ����
char searchName[20]; //Ž���ϰ��� �ϴ� �̸�
int searchNum; //Ž���ϰ��� �ϴ� �� ��ȣ
int standard = 2020; //���� ���� ������ �Ǵ� ����

COORD coord = { 0,0 };

struct date { 
	int year;
	int month;
	int day;
}; //��¥ ����ü ����(���� ����)

struct account {
	char name[20]; //�� �̸�
	int number; //�� ��ȣ
	int acctNo; //���º�ȣ
	float mobileNo; //�ڵ��� ��ȣ
	char street[100]; //�Ÿ�
	char city[100]; //����
	float unpayment; //�̳���
	float payment; //����
	struct date Date; //���� ����
	struct account* next; //���� ���� ����Ʈ�� �����ϱ� ���� ����ü
}customer; //����ڿ� ���õ� ���� ����ü ���� �� ����

INFO* listhead = NULL; //�Ӹ� ���

int main(void) {
	getPassword(); //���α׷� ��й�ȣ�� �Է� �޴� �Լ�
	return 0;
}
void getPassword() { //����ڸ� ������ �� �ֵ��� �н����� �Է��� ����
	system("cls"); //ȭ�� ����
	char password[20]; //�Է¹޴� ��й�ȣ
	int buffer = 0; //����
	int i = 0; 
	char ch = '\0';
	gotoxy(20, 5);
	printf("Please enter password...\n");
	gotoxy(20, 7);
	while (ch != 13) //enter�� ���� ������
	{
		ch = _getch(); //��й�ȣ �Է� �ޱ�

		if (ch != 13 && ch != 8) { //enter�� back space�� ������ ������
			_putch('*'); //���� ��й�ȣ ���
			password[i] = ch;
			i++;
		}
	}
	password[i] = '\0'; //��й�ȣ �迭�� ������ = null

	if (strcmp(password, answer) == 0) { //�� ��й�ȣ�� ��ġ�Ѵٸ�
		gotoxy(20, 9);
		printf("Press any key to go to mainmenu");
		_getch(); //�Է��� �ް�
		mainmenu(); //���� �޴��� �̵�
	}
	else { //��ġ���� �ʴ´ٸ�
		gotoxy(20, 9);
		printf("\awrong password!");
		gotoxy(20, 10);
		printf("Press any key to retry");
		_getch();
		getPassword(); //�ٽ� ����
	}
}
void gotoxy(int x, int y)
{
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void mainmenu() {
	int i = 0; //����ڰ� �����ϴ� ���� ��ȣ

	system("cls"); //ȭ�� ����
	gotoxy(20, 5);
	printf("CUSTOMER   BILLING   SYSTEM");
	gotoxy(20, 6);
	printf("===========================");
	gotoxy(20, 8);
	printf("1.  add new account");
	gotoxy(20, 9);
	printf("2.  seacrh customer account");
	gotoxy(20, 10);
	printf("3.  check customer account list");
	gotoxy(20, 11);
	printf("4.  delete customer account");
	gotoxy(20, 12);
	printf("5.  send receipt to customer");
	gotoxy(20, 13);
	printf("6.  exit\n");
	gotoxy(20, 15);
	printf("What service do you want?  ");
	gotoxy(20, 16);
	scanf("%d", &i); //���� ��ȣ �Է� �ޱ�

	switch (i) { //i�� ��ġ�ϴ� ��ȣ�� case�� �̵�
	case 1 :
		addAccount();
		break;

	case 2 :
		searchAccount();
		break;

	case 3 :
		showCustomerlist();
		break;

	case 4:
		deleteAccount();
		break;

	case 5 :
		sendCustomer();
		break;

	case 6 :
		exitService();
		break;
	}
}
void addAccount() { //������ �߰��ϴ� �Լ�
	system("cls"); //ȭ�� ����

	char message[5]; //���α׷��� �������� �����ϴ� �޽���

	while (1) { //������� ���� �Է�
		system("cls");
		gotoxy(20, 8);
		printf("name : ");
		scanf("%s", customer.name); 
		gotoxy(20, 9);
		printf("number : ");
		scanf("%d", &customer.number);
		gotoxy(20, 10);
		printf("account : ");
		scanf("%d", &customer.acctNo);
		gotoxy(20, 11);
		printf("mobile number : ");
		scanf("%f", &customer.mobileNo);
		gotoxy(20, 12);
		printf("street : ");
		scanf("%s", customer.street);
		gotoxy(20, 13);
		printf("city : ");
		scanf("%s", customer.city);
		gotoxy(20, 14);
		printf("payment : ");
		scanf("%f", &customer.payment);
		gotoxy(20, 15);
		printf("unpayment : ");
		scanf("%f", &customer.unpayment);
		gotoxy(20, 16);
		printf("payment date : ");
		scanf("%d %d %d", &customer.Date.year, &customer.Date.month, &customer.Date.day);
		insertNode(&customer); //���� ����Ʈ ��� �߰� �Լ�
		gotoxy(20, 18);
		printf("Do you want to stop adding new account?\n");
		gotoxy(20, 19);
		scanf("%s", &message); //�޽��� �Է�

		if (strcmp(message, "yes") == 0) { //yes�� �Է��ϸ�
			break; //�ݺ��� ����
		}
		else {
			continue; //��� ����
		}
	}
	mainmenu(); //�Է��� ������ ���� ȭ�� ����
}
void searchAccount() { //���� �˻� (�̸�, �� ��ȣ�� �Է� �ޱ�)

	while (1) {
		system("cls");
		gotoxy(20, 5);
		printf("CUSTOMER   BILLING   SYSTEM");
		gotoxy(20, 6);
		printf("===========================");
		gotoxy(20, 8);
		printf("customer name : ");
		scanf("%s", searchName);
		gotoxy(20, 9);
		printf("customer number : ");
		scanf("%d", &searchNum);

		INFO* found = searchNode(&customer, searchName, searchNum);

		if (found != NULL) {
			gotoxy(20, 11);
			printf("name : %s", found->name);
			gotoxy(20, 12);
			printf("number : %d", found->number);
			gotoxy(20, 13);
			printf("account : %d", found->acctNo);
			gotoxy(20, 14);
			printf("mobile number : %f", found->mobileNo);
			gotoxy(20, 15);
			printf("street : %s", found->street);
			gotoxy(20, 16);
			printf("city : %s", found->city);
			gotoxy(20, 17);
			printf("payment : %f", found->payment);
			gotoxy(20, 18);
			printf("unpayment : %f", found->unpayment);
			gotoxy(20, 19);
			printf("payment date : %d / %d / %d", found->Date.year, found->Date.month, found->Date.day);
			gotoxy(20, 21);
			printf("Search is done. Press any key to go to mainmenu");
			_getch();
			mainmenu();
			break;
		}
		else {
			gotoxy(20, 11);
			printf("NO Data. Press any key to go to mainmenu");
			_getch();
			mainmenu();
			break;
		}
	}
}
void showCustomerlist() { //����Ʈ ���
	char check[5];

	printList();
	gotoxy(20, line++);
	printf("Do you want to go to mainmenu?");
	gotoxy(20, line++);
	scanf("%s", check);
	line = 8;

	if (strcmp(check, "yes") == 0) {
		mainmenu();
	}
}
void sendCustomer() { //������ �߱�
	system("cls");
	gotoxy(20, 5);
	printf("CUSTOMER   BILLING   SYSTEM");
	gotoxy(20, 6);
	printf("===========================");

	FILE* fp = fopen("receipt1.txt", "w");

	INFO* send = listhead;

	while (send != NULL) {
		if (send->unpayment > 0) {
			gotoxy(20, 8);
			printf("Sending the receipt...");
			Sleep(2000);
			gotoxy(20, 9);
			printf("Send receipt!");

			fprintf(fp, "%s\n\n", "CUSTOMER RECEIPT");
			fputs("name : ", fp);
			fprintf(fp, "%s\n", send->name);
			fputs("number : ", fp);
			fprintf(fp, "%d\n", send->number);
			fputs("account number : ", fp);
			fprintf(fp, "%d\n", send->acctNo);
			fputs("mobile number : ", fp);
			fprintf(fp, "%f\n", send->mobileNo);
			fputs("street : ", fp);
			fprintf(fp, "%s\n", send->street);
			fputs("city : ", fp);
			fprintf(fp, "%s\n", send->city);
			fputs("payment : ", fp);
			fprintf(fp, "%f\n", send->payment);
			fputs("unpayment : ", fp);
			fprintf(fp, "%f\n", send->unpayment);
			fputs("date : ", fp);
			fprintf(fp, "%d %d %d\n", send->Date.year, send->Date.month, send->Date.day);

			send = send->next;
		}
		else { //�̳����� ���ٸ�
			gotoxy(20, 8);
			printf("Sending the receipt...");
			Sleep(2000);
			gotoxy(20, 9);
			printf("No unpayment");
		}
		gotoxy(20, 11);
		printf("Press any key to go to mainmenu");
		_getch();
		mainmenu(); //���� �޴��� �̵�
	}
	fclose(fp); //���� �ݱ�

}
void exitService() { //���α׷� ����
	system("cls");
	gotoxy(20, 5);
	printf("CUSTOMER   BILLING   SYSTEM");
	gotoxy(20, 6);
	printf("===========================");
	gotoxy(20, 8);
	printf("end the program...\n\n\n");
}
void insertNode(INFO* info) {
	INFO* temp = (INFO*)malloc(sizeof(INFO)); //����ü ����

	strcpy(temp->name, info->name);
	strcpy(temp->street, info->street);
	strcpy(temp->city, info->city);
	temp->acctNo = info->acctNo;
	temp->number = info->number;
	temp->mobileNo = info->mobileNo;
	temp->payment = info->payment;
	temp->unpayment = info->unpayment;
	temp->Date.year = info->Date.year;
	temp->Date.month = info->Date.month;
	temp->Date.day = info->Date.day;

	temp->next = listhead;
	listhead = temp;
}
INFO* searchNode(INFO* info, char name[20], int num) {
	
	INFO* search = listhead;

	while (search != NULL) {
		if ((strcmp(search->name, name)==0)&&(search->number == num)) {
			return search;
		}
		search = search->next;
	}
	return NULL;
}
void printList() {
	system("cls");
	INFO* print = listhead;

	gotoxy(20, 5);
	printf("CUSTOMER ACCOUNT LIST");
	gotoxy(20, 6);
	printf("=====================");

	while (print != NULL) {
		gotoxy(20, line++);
		printf("name : %s", print->name);
		gotoxy(20, line++);
		printf("number : %d", print->number);
		gotoxy(20, line++);
		printf("account : %d", print->acctNo);
		gotoxy(20, line++);
		printf("mobile number : %f", print->mobileNo);
		gotoxy(20, line++);
		printf("street : %s", print->street);
		gotoxy(20, line++);
		printf("city : %s", print->city);
		gotoxy(20, line++);
		printf("payment : %f", print->payment);
		gotoxy(20, line++);
		printf("unpayment : %f", print->unpayment);
		gotoxy(20, line++);
		printf("payment date : %d / %d / %d", print->Date.year, print->Date.month, print->Date.day);
		gotoxy(20, line++);
		print = print->next;
	}
}
void deleteAccount() {
	system("cls");
	gotoxy(20, 5);
	printf("CUSTOMER   BILLING   SYSTEM");
	gotoxy(20, 6);
	printf("===========================");

	if (listhead == NULL) {
		gotoxy(20, 8);
		printf("No data");
	}
	INFO* cur = listhead;
	if (standard - cur->Date.year >= 6) {
		gotoxy(20, 8);
		printf("Deleting account...");

		listhead = cur->next;
		deleteNode(cur);

		gotoxy(20, 9);
		printf("Deleting is done. Press any key to go to mainmenu");
		_getch();
		mainmenu();
	}

	//�߰� �Ǵ� ������ ��尡 ���� ����� ���
	while (cur->next != NULL) { //��尡 NULL�� �� ������
		if (standard - cur->next->Date.year >= 6) {
			INFO* removeNode = cur->next; //��� ���� �� �ּ� ����
			gotoxy(20, 11);
			printf("Deleting account");

			if (removeNode->next != NULL) { //�߰� ��带 ������ ���
				cur->next = removeNode->next;
			}
			else { //������ ��带 ������ ���
				cur->next = NULL;
				deleteNode(removeNode);
				gotoxy(20, 11);
				printf("Deleting is done. Press any key to go to mainmenu");
				_getch();
				mainmenu();
			}
			cur = cur->next;
		}
	}
	gotoxy(20, 8);
	printf("No deleted data");
	gotoxy(20, 9);
	printf("Press any key to go to mainmenu");
	_getch();
	mainmenu();

}
void deleteNode(INFO* remove) { //���� ����Ʈ �Ҵ� ����
	free(remove);
	remove = NULL;
}