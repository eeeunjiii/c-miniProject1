#define _CRT_SECURE_NO_WARININGS
#include <Windows.h> 
#include <dos.h>
#include <stdio.h>
#include <conio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct account INFO; //새로운 자료형 선언

void getPassword(); //프로그램 비밀번호를 입력 받는 함수
void gotoxy(); //좌표축에 따라 위치를 설정하는 함수
void mainmenu(); //메인 메뉴
void addAccount(); //계정에 대한 정보를 받는 함수
void searchAccount(); //계정을 검색하는 함수
void showCustomerlist(); //계정 리스트를 출력하는 함수
void sendCustomer(); //사용자에게 영수증을 청구하는 함수
void exitService(); //서비스를 종료하는 함수
void deleteAccount(); //계정을 삭제하는 함수
void deleteNode(INFO* remove); //연결리스트를 삭제하는 함수
void insertNode(INFO* info); //노드 추가 함수
INFO *searchNode(INFO* info, char name[20], int num); //노드 탐색 함수
void printList(); //정보 출력 함수

char answer[20] = {"pass"}; //비밀번호
int line = 8; //printList 함수를 사용할 때 line 고정
char searchName[20]; //탐색하고자 하는 이름
int searchNum; //탐색하고자 하는 고객 번호
int standard = 2020; //계정 만료 기준이 되는 연도

COORD coord = { 0,0 };

struct date { 
	int year;
	int month;
	int day;
}; //날짜 구조체 선언(결제 일자)

struct account {
	char name[20]; //고객 이름
	int number; //고객 번호
	int acctNo; //계좌변호
	float mobileNo; //핸드폰 번호
	char street[100]; //거리
	char city[100]; //도시
	float unpayment; //미납액
	float payment; //납액
	struct date Date; //결제 일자
	struct account* next; //다음 연결 리스트를 연결하기 위한 구조체
}customer; //사용자와 관련된 정보 구조체 선언 및 정의

INFO* listhead = NULL; //머리 노드

int main(void) {
	getPassword(); //프로그램 비밀번호를 입력 받는 함수
	return 0;
}
void getPassword() { //담당자만 접근할 수 있도록 패스워드 입력을 받음
	system("cls"); //화면 정리
	char password[20]; //입력받는 비밀번호
	int buffer = 0; //버퍼
	int i = 0; 
	char ch = '\0';
	gotoxy(20, 5);
	printf("Please enter password...\n");
	gotoxy(20, 7);
	while (ch != 13) //enter가 나올 때까지
	{
		ch = _getch(); //비밀번호 입력 받기

		if (ch != 13 && ch != 8) { //enter나 back space가 나오기 전까지
			_putch('*'); //가린 비밀번호 출력
			password[i] = ch;
			i++;
		}
	}
	password[i] = '\0'; //비밀번호 배열의 마지막 = null

	if (strcmp(password, answer) == 0) { //두 비밀번호가 일치한다면
		gotoxy(20, 9);
		printf("Press any key to go to mainmenu");
		_getch(); //입력을 받고
		mainmenu(); //메인 메뉴로 이동
	}
	else { //일치하지 않는다면
		gotoxy(20, 9);
		printf("\awrong password!");
		gotoxy(20, 10);
		printf("Press any key to retry");
		_getch();
		getPassword(); //다시 실행
	}
}
void gotoxy(int x, int y)
{
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void mainmenu() {
	int i = 0; //사용자가 선택하는 서비스 번호

	system("cls"); //화면 정리
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
	scanf("%d", &i); //서비스 번호 입력 받기

	switch (i) { //i와 일치하는 번호의 case로 이동
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
void addAccount() { //계정을 추가하는 함수
	system("cls"); //화면 정리

	char message[5]; //프로그램을 종료할지 선택하는 메시지

	while (1) { //사용자의 정보 입력
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
		insertNode(&customer); //연결 리스트 노드 추가 함수
		gotoxy(20, 18);
		printf("Do you want to stop adding new account?\n");
		gotoxy(20, 19);
		scanf("%s", &message); //메시지 입력

		if (strcmp(message, "yes") == 0) { //yes를 입력하면
			break; //반복문 종료
		}
		else {
			continue; //계속 실행
		}
	}
	mainmenu(); //입력이 끝나면 메인 화면 띄우기
}
void searchAccount() { //계정 검색 (이름, 고객 번호를 입력 받기)

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
void showCustomerlist() { //리스트 출력
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
void sendCustomer() { //영수증 발급
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
		else { //미납액이 없다면
			gotoxy(20, 8);
			printf("Sending the receipt...");
			Sleep(2000);
			gotoxy(20, 9);
			printf("No unpayment");
		}
		gotoxy(20, 11);
		printf("Press any key to go to mainmenu");
		_getch();
		mainmenu(); //메인 메뉴로 이동
	}
	fclose(fp); //파일 닫기

}
void exitService() { //프로그램 종료
	system("cls");
	gotoxy(20, 5);
	printf("CUSTOMER   BILLING   SYSTEM");
	gotoxy(20, 6);
	printf("===========================");
	gotoxy(20, 8);
	printf("end the program...\n\n\n");
}
void insertNode(INFO* info) {
	INFO* temp = (INFO*)malloc(sizeof(INFO)); //구조체 선언

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

	//중간 또는 마지막 노드가 삭제 대상일 경우
	while (cur->next != NULL) { //노드가 NULL이 될 때까지
		if (standard - cur->next->Date.year >= 6) {
			INFO* removeNode = cur->next; //노드 생성 및 주소 저장
			gotoxy(20, 11);
			printf("Deleting account");

			if (removeNode->next != NULL) { //중간 노드를 삭제할 경우
				cur->next = removeNode->next;
			}
			else { //마지막 노드를 삭제할 경우
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
void deleteNode(INFO* remove) { //연결 리스트 할당 해제
	free(remove);
	remove = NULL;
}