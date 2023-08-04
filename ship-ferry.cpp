#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

//Used by every function
int opt;
int acc = 0;
int userCount;

//Security Questions
string q1 = "Mother's maiden name? ";
string q2 = "Favorite Movie? ";
string q3 = "Favorite Subject? ";
string q4 = "Dream pet? ";

//For Registration
string usernames[10];
string passwords[10];
string fullname[10];
string address[10];
int age[10];
int bMM[10];
int bDD[10];
int bYY[10];
string ques[10];
string ans[10];
int status[10];

//For Logging In - User
string user;
string pass;

//For Logging In - Admin
string adminUser = "admin";
string adminPass = "admin";
string aUser, aPass;

//To determine if User is Active or Banned
//If Status = 0 == Active, Status = 1 == Banned


//Ship names, Status
int shipCount = 2;
string ships[10] = {"Star Horse Ship", "Posseidon Ship"};
int shipID[10] = {101,102};
int shipStatus[10] = {0,0};

int shipIndex;
int shipLocIndex;

//Ship Sched, Location, Date, Time
int shipLocCount[10] = {3,3};
string shipLoc[10][10] = {
	{"Cebu    ", "Coron   ", "Caticlan"},
	{"Cebu    ", "Coron   ", "Palawan "}
};

//Time for Ship
//int shipTimeDep[10][10] = {
//	{9, 3, 2},
//	{10, 4, 3}
//};
//int shipTimeDepMin[10][10] = {
//	{0, 30, 15},
//	{30, 45, 10}
//};
//Time for Ship Departure
int shipTimeHour[10][10] = {{2, 5, 6}, {3, 6, 7}};
int shipTimeMin[10][10] = {{10, 30, 15}, {30, 45, 10}};

//Date for ship departure per location
string formatter;
int shipMonth[10][10] = {{7, 7, 7}, {7, 7, 7}};
int shipDay[10][10] = {{24, 25, 26}, {25, 26, 27}};
int year = 2023;

//For Comparing the Dates
int currentYear = 2023;
int currentMonth = 7;
int currentDate = 6;

int shipRecSlot[10][10] = {
	{25,20,15},
	{5,0,7}
};
int shipVipSlot[10][10] = {
	{3,4,5},
	{5,6,8}
};

int shipCap[10][10];

// Ticket Price for Reclining Seat
//Senior
int RecSeniorTP[10][10] = {
	{100, 101, 102},
	{103, 104, 105}
};
//Adult
int RecAdultTP[10][10] = {
	{106, 107, 108},
	{101, 110, 111}
};
//Infant
int RecInfantTP[10][10] = {
	{118, 119, 120},
	{121, 122, 123}
};

// Room Price for VIP Room
int VipRoomTP[10][10] = {
	{1000, 2000, 3000},
	{4000, 5000, 6000}
};

//User Tickets Storage
int userTic[10][10][10];

int vipRoom[10][10][10];
int vipOccu[10][10][10];

//Temporary storage for ticket quantity
int quantity[10][10][10];
int totalQuantity[10][10][10];

int vipQuanity[10][10][10];
int vipTotalQuantity[10][10][10];

int price[10][10][10];
int totalPrice[10][10][10];

int vipPrice[10][10][10];
int vipTotalPrice[10][10][10];

//Storage for Tickets per Category
int RecSeniorCount[10][10][10];
int RecAdultCount[10][10][10];
int RecInfantCount[10][10][10];

int vipCount[10][10][10];

//For Van Shipping
int belowVanPrice = 30000;
int aboveVanPrice = 50000;
int quantity20[10][10][10];
int quantity40[10][10][10];
int plateNum20[10][10][10];
int plateNum40[10][10][10];
int vanShipTotal[10][10][10];
int userBVPrice[10][10][10];
int userAVPrice[10][10][10];
int totalQuantity20[10][10][10];
int totalQuantity40[10][10][10];

int overallPrice[10];
int totalOverallPrice[10];

//USER PAYMENT
int userPayment[10];
int userBalance[10];
int userPaid[10];
int userChange[10];

//Functions
void login();
void regUser();

void save();
void load();

//For Admin
void admin();
void manageUser();
void manageShip();
void manageRoute();
void shipSched();
void paymentUser();
void adminAcc();

//For User
void userInt();
void buyTicket();
void ticketManagement();
void ticketStatus();
void schedules();
void userAcc();
void checkOut();
void userReceipt();

//To Change Font Size in Terminal
void setConsoleFontSize(int size) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	fontInfo.dwFontSize.Y = size; // Set the desired font size
	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

//MAIN
int main() {

	//Font Size
	setConsoleFontSize(20);

	system("cls");
	cout<<"=======================================\n";
	cout<<"       Welcome to Ferry Terminal\n";
	cout<<"           Online Booking\n";
	cout<<"=======================================\n";
	cout<<"\n[1] Login\n";
	cout<<"[2] Register\n";
	cout<<"[3] Exit\n\n";
	cout<<"=======================================\n";
	cout<<"\nOption: ";
	cin>>opt;
	cout<<"\n=======================================\n";

	switch(opt) {
		case 1:
			login();
			break;
		case 2:
			regUser();
			break;
		case 3:
			cout<<"\nExiting the program!\n";
			cout<<"\n=======================================\n";
			exit(0);
			break;
		default:
			cout<<"Invalid Option!\n";
			break;
	}

	return 0;
}

void load() {
	ifstream read;
	read.open("shipFile.txt");
	//For User Account
	read >> acc;
	read.ignore(); // Ignore the newline character after count
	for (int i = 0; i < acc; i++) {
		getline(read, usernames[i],','); //In this way, comma is specifies as a delimiter
		getline(read, passwords[i],',');
		getline(read, fullname[i],',');
		getline(read, address[i],',');
		read>> age[i];
		read.ignore();
		read>> bMM[i];
		read.ignore();
		read>> bDD[i];
		read.ignore();
		read>> bYY[i];
		read.ignore();
		read>> status[i];
		read.ignore();
		getline(read, ques[i],',');
		getline(read, ans[i]);
	}

	read >> acc;
	read.ignore();
	for(int i = 0; i < acc; i++) {
		for(int j = 0; j < shipCount; j++) {
			for(int k = 0; k < shipLocCount[j]; k++) {
				read>>RecSeniorCount[i][j][k];
				read.ignore();
				read>>RecAdultCount[i][j][k];
				read.ignore();
				read>>RecInfantCount[i][j][k];
				read.ignore();
				read>>vipRoom[i][j][k];
				read.ignore();
				read>>vipOccu[i][j][k];
				read.ignore();
				read>>vipPrice[i][j][k];
				read.ignore();
				read>>totalQuantity20[i][j][k];
				read.ignore();
				read>>userBVPrice[i][j][k];
				read.ignore();
				read>>totalQuantity40[i][j][k];
				read.ignore();
				read>>userAVPrice[i][j][k];
				read.ignore();
				read>>overallPrice[i];
				read.ignore();
				read>>userPayment[i];
				read.ignore();
				read>>userChange[i];
				read.ignore();
			}
		}
	}

	//For Ships
	read >> shipCount;
	read.ignore();
	for(int j = 0; j < shipCount; j++) {
		read>>shipID[j];
		read.ignore();
		getline(read, ships[j], ',');
		read>>shipLocCount[j];
		read.ignore();
		for(int k = 0; k < shipLocCount[j]; k++) {
			getline(read, shipLoc[j][k], ',');
			read>>shipMonth[j][k];
			read.ignore();
			read>>shipDay[j][k];
			read.ignore();
			read>>shipTimeHour[j][k];
			read.ignore();
			read>>shipTimeMin[j][k];
			read.ignore();
			read>>shipCap[j][k];
			read.ignore();
			read>>shipRecSlot[j][k];
			read.ignore();
			read>>shipVipSlot[j][k];
			read.ignore();
			read>>RecSeniorTP[j][k];
			read.ignore();
			read>>RecAdultTP[j][k];
			read.ignore();
			read>>RecInfantTP[j][k];
			read.ignore();
			read>>VipRoomTP[j][k];
			read.ignore();
		}
	}

	read.close();
}

void save() {
	ofstream write;
	write.open("shipFile.txt");

	//For User Account
	write<< acc <<endl;
	for(int i=0; i<acc; i++) {
		write<<usernames[i]<<",";
		write<<passwords[i]<<",";
		write<<fullname[i]<<",";
		write<<address[i]<<",";
		write<<age[i]<<",";
		write<<bMM[i]<<",";
		write<<bDD[i]<<",";
		write<<bYY[i]<<",";
		write<<status[i]<<",";
		write<<ques[i]<<",";
		write<<ans[i]<<endl;
	}

	//For USER TICKETS
	write<< acc <<endl;
	for(int i = 0; i < acc; i++) {
		for(int j = 0; j < shipCount; j++) {
			for(int k = 0; k < shipLocCount[j]; k++) {
				write<<RecSeniorCount[i][j][k]<<",";
				write<<RecAdultCount[i][j][k]<<",";
				write<<RecInfantCount[i][j][k]<<",";
				write<<vipRoom[i][j][k]<<",";
				write<<vipOccu[i][j][k]<<",";
				write<<vipPrice[i][j][k]<<",";
				write<<totalQuantity20[i][j][k]<<",";
				write<<userBVPrice[i][j][k]<<",";
				write<<totalQuantity40[i][j][k]<<",";
				write<<userAVPrice[i][j][k]<<",";
				write<<overallPrice[i]<<",";
				write<<userPayment[i]<<",";
				write<<userChange[i]<<endl;
			}
		}
		write<<endl;
	}

	//For Ship
	write<<shipCount<<endl;
	for(int j = 0; j < shipCount; j++) {
		write<<shipID[j]<<",";
		write<<ships[j]<<",";
		write<<shipLocCount[j]<<endl;
		for(int k = 0; k < shipLocCount[j]; k++) {
			write<<shipLoc[j][k]<<",";
			write<<shipMonth[j][k]<<",";
			write<<shipDay[j][k]<<",";
			write<<shipTimeHour[j][k]<<",";
			write<<shipTimeMin[j][k]<<",";
			write<<shipCap[j][k]<<",";
			write<<shipRecSlot[j][k]<<",";
			write<<shipVipSlot[j][k]<<",";
			write<<RecSeniorTP[j][k]<<",";
			write<<RecAdultTP[j][k]<<",";
			write<<RecInfantTP[j][k]<<",";
			write<<VipRoomTP[j][k]<<endl;
		}
	}
	write.close();
}

void regUser() {
	do {
//		int checker;
//		do {
		system("cls");
		cout<<"=======================================\n";
		cout<<"                REGISTER\n";
		cout<<"=======================================\n";
		cout<<"\nUsername     : ";
		cin>>usernames[acc];
//			for(int i = 0; i < acc; i++) {
//				if(usernames[acc] == usernames[i]) {
//					cout<<"Username already used!\n";
//					system("pause");
//					checker = 0;
//					break;
//				} else {
//					checker = 1;
//				}
//			}
//		} while(checker == 0);

		cin.ignore();
		cout<<"Password     : ";
		cin>>passwords[acc];
		cin.ignore();

		if(usernames[acc].length() < 8 || passwords[acc].length() < 8) {
			cout<<"Use 8 characters for Username/Password\n";
			cout<<"\n=======================================\n";
			system("pause");
		}

	} while(usernames[acc].length() < 8 || passwords[acc].length() < 8);

	cout<<"Full Name    : ";
	getline(cin, fullname[acc]);
	cout<<"Address      : ";
	getline(cin, address[acc]);
	cout<<"Age          : ";
	cin>>age[acc];
	cout<<"Birthdate: \n";
	cout<<"Month (1-12) : ";
	cin>>bMM[acc];

	if(bMM[acc] < 1 || bMM[acc] > 12) {
		cout<<"Invalid Month!\n";
		system("pause");
		regUser();
	}

	cout<<"Day (1-31)   : ";
	cin>>bDD[acc];

	if(bMM[acc] == 2) {
		if(bDD[acc] < 1 || bDD[acc] > 28) {
			cout<<"Invalid Day!\n";
			system("pause");
			regUser();
		}
	}

	if(bMM[acc] == 4 || bMM[acc] == 6 || bMM[acc] == 9 || bMM[acc] == 11) {
		if(bDD[acc] < 1 || bDD[acc] > 30) {
			cout<<"Invalid Day!\n";
			system("pause");
			regUser();
		}
	}

	cout<<"Year (19XX)  : ";
	cin>>bYY[acc];

	cout<<"---------------------------------------\n";

	if(bYY[acc] < 1923) {
		cout<<"You're a legend, you're still alive.\n";
		system("pause");
		regUser();
	} else if(bYY[acc] >= 1923 || bYY[acc] <= 2006) {

		int realAge = currentYear - bYY[acc];
		if(currentMonth <= bMM[acc]) {
			if(currentDate <= bDD[acc])
				realAge--;
		}
		if(realAge != age[acc]) {
			cout<<"Real Age: "<<realAge;
			cout<<"Please Input Correct Age!\n";
			system("pause");
			regUser();
		}
		cout<<"Real Age: "<<realAge;
	} else {
		cout<<"You're not eligible to create or register an account.\n";
		cout<<"You need to be 18 Years Old or higher.\n";
		system("pause");
		regUser();
	}

	status[acc] = 0;

	cout<<"\n=======================================\n";

	system("pause");
	system("cls");

	bool valid = false;

//	string q1 = "Mother's maiden name? ";
//	string q2 = "Favorite Movie? ";
//	string q3 = "Favorite Subject? ";
//	string q4 = "Dream pet? ";

	cout<<"=======================================\n";
	cout<<"Security Questions: \n";
	cout<<"=======================================\n";

	while(!valid) {
		cout<<"\n[1] "<<q1<<endl;
		cout<<"[2] "<<q2<<endl;
		cout<<"[3] "<<q3<<endl;
		cout<<"[4] "<<q4<<endl<<endl;

		cout<<"=======================================\n";
		cout<<"\nOption: ";
		cin>>opt;
		cin.ignore();

		cout<<"\n=======================================\n";

		if(opt == 1) {
			ques[acc] = q1;
			cout<<"\n[1] "<<q1;
			getline(cin, ans[acc]);
			valid = true;
			break;
		} else if(opt == 2) {
			ques[acc] = q2;
			cout<<"\n[2] "<<q2;
			getline(cin, ans[acc]);
			valid = true;
			break;
		} else if(opt == 3) {
			ques[acc] = q3;
			cout<<"\n[3] "<<q3;
			getline(cin, ans[acc]);
			valid = true;
			break;
		} else if(opt == 4) {
			ques[acc] = q4;
			cout<<"\n[4] "<<q4;
			getline(cin, ans[acc]);
			valid = true;
			break;
		} else {
			cout<<"\nInvalid Input! Choose a correct option!\n";
			break;

		}
	}

	cout<<"\n=======================================\n";

//	fstream file;

//	file.open("sfAccount.txt", ios::out | ios::app);
////	file.open("sfAccount.txt", ios::out);
//	if(file.is_open()) {
//		file<<"LIST OF REGISTERED ACCOUNT/S:\n";
//		for(int i = 0; i <= acc; i++) {
//			file<<"\nFull Name: "<<fullname[i]<<endl;
//			file<<"Username: "<<usernames[i]<<endl;
//			file<<"Password: "<<passwords[i]<<endl;
//			file<<"Address: "<<address[i]<<endl;
//			file<<"Age: "<<age[i]<<endl;
//			file<<"Birthdate: "<<bMM[i]<<" "<<bDD[i]<<" "<<bYY[i]<<endl;
//			file<<"Security Question: "<<ques[i]<<endl;
//			file<<"Security Question Answer: "<<ans[i]<<endl;
//		}
//		file.close();
//	}

	system("pause");
	acc++;
	save();
	login();
}

void login() {

	bool username = false;
	bool passcode=false;
	char forgot;
	string secAns;
	string newPass;
	string conPass;

	while(true) {
		load();
		system("cls");
		cout<<"=======================================\n";
		cout<<"                LOGIN\n";
		cout<<"=======================================\n";

		cout<<"\nEnter username: ";
		cin>>user;

		if(user == adminUser) {
			cout<<"Enter password: ";
			cin>>pass;
			if(pass == adminPass) {
				cout<<"\n=======================================\n";
				system("pause");
				admin();
				break;
			}

		}

		for(int i = 0; i < acc; i++) {
			if(user == usernames[i]) {
				cout<<"Enter password: ";
				cin>>pass;
				username=true;
				userCount = i;
				if(pass == passwords[i]) {
					passcode= true;
					userCount = i;
					if(status[i] == 1) {
						cout<<"This user is banned!\n";
						system("pause");
						login();
					}
					cout<<"\n=======================================\n";
					cout<<"\nLogin Successful!"<<endl;
					cout<<"\n=======================================\n";

					system("pause");
					userInt();

				}

				else {
					cout<<"Incorrect password!\n";
					cout<<"\n--------------------------------------\n";
					cout<<"[Y] Forgot Password or [N]: ";
					cin>>forgot;
					if(forgot == 'y' || forgot == 'Y') {
						cout<<"\nQuestion: "<<ques[i]<<": ";
						cin.ignore();
						cin>>secAns;
						if(secAns == ans[i]) {
							while(true) {
								cout<<"\nEnter new password: ";
								cin>>newPass;
								cout<<"Confirm Password: ";
								cin>>conPass;

								if(newPass == conPass) {
									passwords[i] = conPass;
									cout<<"\n--------------------------------------\n";
									cout<<"Password changed successful!\n";
									cout<<"\n======================================\n";
									save();
									system("pause");
									break;
								} else {
									cout<<"Make sure the password is the same!\n";
								}
							}
						} else {
							cout<<"Wrong Answer!\n";
							login();
						}
					}

					else if(forgot == 'n' || forgot == 'N') {
						login();
					}
					system("pause");
				}
			}
		}
		if(!username) {
			cout<<"Username doesn't exist!\n";
			system("pause");
			login();
		}
	}
}

void userInt() {
	system("cls");
	cout<<"=======================================\n";
	cout<<"\tWELCOME, "<<usernames[userCount]<<endl;
	cout<<"=======================================\n";
	cout<<"[1] Buy Tickets\n";
	cout<<"[2] Ticket Management\n";
	cout<<"[3] Ship Schedules\n";
	cout<<"[4] Manage My Account\n";
	cout<<"[5] Logout\n";
	cout<<"---------------------------------------\n";
	cout<<"Option: ";
	cin>>opt;
	cout<<"\n=======================================\n";
	system("pause");

	switch(opt) {
		case 1:
			buyTicket();
			break;
		case 2:
			ticketManagement();
			break;
		case 3:
			schedules();
			break;
		case 4:
			userAcc();
			break;
		case 5:
			main();
			break;
		default:
			break;
	}
}

void buyTicket() {
	load();
	system("cls");
	cout<<"======================================\n";
	cout<<"Book a Ticket\n";
	cout<<"======================================\n";
	cout<<"Viewing Ship Schedules: \n";
	cout<<"======================================\n";
	for(int i = 0; i < shipCount; i++) {
		cout<<"["<<i+1<<"] "<<ships[i]<<endl;
		cout<<"======================================\n";
		cout<<"Schedules\t\t\tReclining Seat Slots\t\tVIP Room Slots\n";
		cout<<"======================================\n";
		for(int j = 0; j <shipLocCount[i]; j++) {
			cout<<"["<<j+1<<"] "<<shipLoc[i][j]<<" - ";
			cout<<shipMonth[i][j]<<"/"<<shipDay[i][j]<<"/"<<year;
			cout<<" - "<<shipTimeHour[i][j];
			if(shipTimeHour[i][j] < 12 ) {
				formatter = "AM";
			} else if(shipTimeHour[i][j] == 24) {
				shipTimeHour[i][j] -= 12;
				formatter = "AM";
			} else {
				shipTimeHour[i][j] -= 12;
				formatter = "PM";
			}
			if(shipTimeMin[i][j] < 10) {
				cout<<"0";
			}
			cout<<":"<<shipTimeMin[i][j]<<" "<<formatter;

			cout<<"\t\t"<<shipRecSlot[i][j]<<"\t\t"<<shipVipSlot[i][j]<<endl;
		}
		cout<<"======================================\n";
		cout<<endl;
	}
	cout<<"======================================\n";
	system("pause");
	system("cls");
	cout<<"======================================\n";
	cout<<"Choose a Ship: \n";
	cout<<"======================================\n";
	for(int i = 0; i < shipCount; i++) {
		cout<<"["<<i+1<<"] "<<ships[i]<<endl;
	}
	cout<<"[0] Back\n";
	cout<<"--------------------------------------\n";
	cout<<"\nOption: ";
	cin>>opt;
	cout<<"\n======================================\n";

	if(opt == 0) {
		system("pause");
		userInt();
	} else {
		shipIndex = opt - 1;
		if(shipStatus[shipIndex] == 1) {
			cout<<"\nThis Ship is currently Inactive.\n";
			cout<<"Please Choose different Ship/Location.\n";
			cout<<"\n======================================\n";
			system("pause");
			buyTicket();
		}

		if(shipIndex >= 0 && shipIndex < shipCount) {
			system("cls");
			cout<<"======================================\n";
			cout<<ships[shipIndex]<<" - Choose a Location: \n";
			cout<<"======================================\n";
			for(int i = 0; i < shipLocCount[shipIndex]; i++) {
				cout<<"["<<i+1<<"] "<<shipLoc[shipIndex][i]<<endl;
			}
			cout<<"[0] Back\n";
			cout<<"--------------------------------------\n";
			cout<<"\nOption: ";
			cin>>opt;
			cout<<"\n======================================\n";
			if(opt == 0) {
				system("pause");
				userInt();
			} else {
				system("cls");
//				int userCount = acc-1;
				int shipLocIndex = opt - 1;
				if(shipLocIndex >= 0 && shipLocIndex < shipLocCount[shipIndex]) {
					cout<<"======================================\n";
					cout<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<": \n";
					cout<<"======================================\n";
					cout<<"[1] Buy/Book Tickets\n";
					cout<<"[2] Car Shipping\n";
					cout<<"[3] Back\n";
					cout<<"--------------------------------------\n";
					cout<<"\nOption: ";
					cin>>opt;
					cout<<"\n======================================\n";

					// BUY/BOOK TICKET
					if(opt == 1) {
						system("cls");
						cout<<"======================================\n";
						cout<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<": Book Tickets\n";
						cout<<"======================================\n";
						cout<<"[1] Reclining Seat\n";
						cout<<"[2] VIP Room\n";
						cout<<"[3] Back\n";
						cout<<"--------------------------------------\n";
						cout<<"\nOption: ";
						cin>>opt;
						cout<<"\n======================================\n";
						if(opt == 1) {
							//RECLINING SEAT
							if(shipRecSlot[shipIndex][shipLocIndex] < 1) {
								cout<<"Reclining Seat Slot is fully booked.\n";
								cout<<"======================================\n";
								system("pause");
								buyTicket();
							}

							char checker;
							do {
								system("cls");
								cout<<"======================================\n";
								cout<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<" - Book Tickets : Reclining Seat\n";
								cout<<"======================================\n";
								cout<<"[1] Senior ..... "<<RecSeniorTP[shipIndex][shipLocIndex]<<endl;
								cout<<"[2] Adult  ..... "<<RecAdultTP[shipIndex][shipLocIndex]<<endl;
								cout<<"[3] Child  ..... "<<RecInfantTP[shipIndex][shipLocIndex]<<endl;
								cout<<"[4] Back\n";
								cout<<"--------------------------------------\n";
								cout<<"\nOption: ";
								cin>>opt;
								cout<<"\n======================================\n";
								if(opt == 1) {
									do {
										system("cls");
										cout<<"======================================\n";
										cout<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<" - Book Tickets : Reclining Seat: Senior\n";
										cout<<"======================================\n";
										cout<<"Senior Ticket Price: "<<RecSeniorTP[shipIndex][shipLocIndex]<<endl;
										cout<<"Enter Quantity: ";
										cin>>quantity[userCount][shipIndex][shipLocIndex];

										if(quantity[userCount][shipIndex][shipLocIndex] > shipRecSlot[shipIndex][shipLocIndex] ) {
											cout<<"There's only "<<shipRecSlot[shipIndex][shipLocIndex]<<" slots left.\n";
											checker = 'y';
											system("pause");
										} else {
											checker = 'n';
										}
									} while(checker == 'y');

									RecSeniorCount[userCount][shipIndex][shipLocIndex] += quantity[userCount][shipIndex][shipLocIndex];
									price[userCount][shipIndex][shipLocIndex] = quantity[userCount][shipIndex][shipLocIndex] * RecSeniorTP[shipIndex][shipLocIndex];
								} else if(opt == 2) {
									do {
										system("cls");
										cout<<"======================================\n";
										cout<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<" - Book Tickets : Reclining Seat: Senior\n";
										cout<<"======================================\n";
										cout<<"Adult Ticket Price: "<<RecAdultTP[shipIndex][shipLocIndex]<<endl;
										cout<<"Enter Quantity: ";
										cin>>quantity[userCount][shipIndex][shipLocIndex];
										if(quantity[userCount][shipIndex][shipLocIndex] > shipRecSlot[shipIndex][shipLocIndex] ) {
											cout<<"There's only "<<shipRecSlot[shipIndex][shipLocIndex]<<" slots left.\n";
											checker = 'y';
											system("pause");
										} else {
											checker = 'n';
										}
									} while(checker == 'y');

									RecAdultCount[userCount][shipIndex][shipLocIndex] += quantity[userCount][shipIndex][shipLocIndex];
									price[userCount][shipIndex][shipLocIndex] = quantity[userCount][shipIndex][shipLocIndex] * RecAdultTP[shipIndex][shipLocIndex];
								} else if(opt == 3) {
									do {
										system("cls");
										cout<<"======================================\n";
										cout<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<" - Book Tickets : Reclining Seat: Senior\n";
										cout<<"======================================\n";
										cout<<"Infant Ticket Price: "<<RecInfantTP[shipIndex][shipLocIndex]<<endl;
										cout<<"Enter Quantity: ";
										cin>>quantity[userCount][shipIndex][shipLocIndex];
										if(quantity[userCount][shipIndex][shipLocIndex] > shipRecSlot[shipIndex][shipLocIndex] ) {
											cout<<"There's only "<<shipRecSlot[shipIndex][shipLocIndex]<<" slots left.\n";
											checker = 'y';
											system("pause");
										} else {
											checker = 'n';
										}
									} while(checker == 'y');

									RecInfantCount[userCount][shipIndex][shipLocIndex] += quantity[userCount][shipIndex][shipLocIndex];
									price[userCount][shipIndex][shipLocIndex] = quantity[userCount][shipIndex][shipLocIndex] * RecInfantTP[shipIndex][shipLocIndex];
								} else if(opt == 4) {
									system("pause");
									buyTicket();
								} else {
									cout<<"Invalid Input!\n";
									system("pause");
									buyTicket();
								}

								totalQuantity[userCount][shipIndex][shipLocIndex] += quantity[userCount][shipIndex][shipLocIndex];
								totalPrice[userCount][shipIndex][shipLocIndex] += price[userCount][shipIndex][shipLocIndex];

								cout<<"TOTAL QUANTITY: "<<totalQuantity[userCount][shipIndex][shipLocIndex]<<endl;
								cout<<"TOTAL PRICE: "<<totalPrice[userCount][shipIndex][shipLocIndex]<<endl;
								cout<<"Senior: "<<RecSeniorCount[userCount][shipIndex][shipLocIndex]<<endl;
								cout<<"Adult: "<<RecAdultCount[userCount][shipIndex][shipLocIndex]<<endl;
								cout<<"Infant: "<<RecInfantCount[userCount][shipIndex][shipLocIndex]<<endl;

								shipRecSlot[shipIndex][shipLocIndex] -=  quantity[userCount][shipIndex][shipLocIndex];

								cout << "Quantity Left: " << shipRecSlot[shipIndex][shipLocIndex] << endl;

								save();

								cout<<"\n======================================\n";
								cout<<"[1] Check Out\n";
								cout<<"[2] Book More\n";
								cout<<"[3] Back\n";
								cout<<"--------------------------------------\n";
								cout<<"\nOption: ";
								cin>>opt;
								cout<<"\n======================================\n";

								switch(opt) {
									case 1:
										checkOut();
										break;
									case 2:
										break;
									case 3:
										system("pause");
										buyTicket();
										break;
									default:
										cout<<"Invalid Input!\n";
										system("pause");
										userInt();
										break;
								}
							} while(opt == 2);


						} else if(opt == 2) {
							//VIP ROOM
							if(shipVipSlot[shipIndex][shipLocIndex] < 1) {
								cout<<"VIP Room Slot is fully booked.\n";
								cout<<"======================================\n";
								system("pause");
								buyTicket();
							}
							int occupants;
							int pax;
							int vipTotal;
							int roomCount;
							do {
								char checker;
								do {
									system("cls");
									cout<<"======================================\n";
									cout<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<" - VIP Room\n";
									cout<<"======================================\n";
									cout<<"VIP Room (Up to 5 Pax): "<<VipRoomTP[shipIndex][shipLocIndex]<<" Pesos"<<endl;
									cout<<"======================================\n";
									cout<<"* 2 Double Deck\n";
									cout<<"* Air Conditioned\n";
									cout<<"* Free Breakfast Meal\n";
									cout<<"* Smart TV\n";
									cout<<"======================================\n";
									cout<<"How many rooms to be booked: ";
									cin>>roomCount;
									if(roomCount > shipVipSlot[shipIndex][shipLocIndex]) {
										cout<<"There's only "<<shipVipSlot[shipIndex][shipLocIndex]<<" slots left.\n";
										if(shipVipSlot[shipIndex][shipLocIndex] == 0) {
											system("pause");
											buyTicket();
										} else {
											checker = 'y';
										}
										system("pause");
									} else {
										checker = 'n';
									}
								} while(checker == 'y');

								cout<<"Enter Number of Occupants: ";
								cin>>occupants;
								pax = 5;
								vipTotal = roomCount*pax;
								//8       //2 * 5 = 10

								if(roomCount > occupants) {
									cout<<"You cant book rooms without enough occupants!\n";
									system("pause");
								}

								if(occupants <= vipTotal && roomCount <= occupants) {

									vipOccu[userCount][shipIndex][shipLocIndex] += occupants;
									vipRoom[userCount][shipIndex][shipLocIndex] = roomCount;

									vipPrice[userCount][shipIndex][shipLocIndex] = VipRoomTP[shipIndex][shipLocIndex] * vipRoom[userCount][shipIndex][shipLocIndex];

									cout<<"Price is: "<<vipPrice[userCount][shipIndex][shipLocIndex]<<endl;


									shipVipSlot[shipIndex][shipLocIndex] -=  vipRoom[userCount][shipIndex][shipLocIndex];

									cout << "Quantity Left: " << shipVipSlot[shipIndex][shipLocIndex] << endl;

									save();

									cout<<"You Booked "<<vipRoom[userCount][shipIndex][shipLocIndex]<<" VIP Rooms with "<<vipOccu[userCount][shipIndex][shipLocIndex]<<" occupants.\n";
									cout<<"======================================\n";
									cout<<"Book Successfully!\n";
									cout<<"======================================\n";
									cout<<"\n======================================\n";
									cout<<"[1] Check Out\n";
									cout<<"[2] Book More\n";
									cout<<"[3] Back\n";
									cout<<"--------------------------------------\n";
									cout<<"\nOption: ";
									cin>>opt;
									cout<<"\n======================================\n";

									switch(opt) {
										case 1:
											checkOut();
											break;
										case 2:
											buyTicket();
											break;
										case 3:
											system("pause");
											buyTicket();
											break;
										default:
											cout<<"Invalid Input!\n";
											system("pause");
											buyTicket();
											break;
									}
								}

								if(occupants > vipTotal && roomCount <= occupants) {
									cout<<"Sorry, we have limit for each room.\n";
									cout<<"We need you to confirm your booking.\n";
									system("pause");
								}

							} while(occupants > vipTotal || roomCount > occupants || opt == 2);


						} else if(opt == 3) {
							system("pause");
							buyTicket();

						} else {
							cout<<"Invalid Input!\n";
							system("pause");
							buyTicket();
						}

					} else if(opt == 2) {
						//CAR SHIPPING
						do {
							system("cls");
							cout<<"======================================\n";
							cout<<"Car Shipping: \n";
							cout<<"======================================\n";
							cout<<"[1] 20ft below Van "<<belowVanPrice<<endl;
							cout<<"[2] 40ft about Van "<<aboveVanPrice<<endl;
							cout<<"[3] Back\n";
							cout<<"--------------------------------------\n";
							cout<<"\nOption: ";
							cin>>opt;
							cout<<"\n======================================\n";
							if(opt == 1) {
								system("cls");
								cout<<"======================================\n";
								cout<<"Car Shipping: 20ft below Van: \n";
								cout<<"======================================\n";
								cout<<"Enter quantity of 20ft below van: ";
								cin>>quantity20[userCount][shipIndex][shipLocIndex];

								for(int i = 0; i < quantity20[userCount][shipIndex][shipLocIndex]; i++) {
									cout<<"Enter Plater Number for vehicle no."<<i+1<<": ";
									cin>>plateNum20[userCount][shipIndex][i];
								}

								totalQuantity20[userCount][shipIndex][shipLocIndex] += quantity20[userCount][shipIndex][shipLocIndex];

								userBVPrice[userCount][shipIndex][shipLocIndex] += quantity20[userCount][shipIndex][shipLocIndex] * belowVanPrice;

							} else if(opt == 2) {
								system("cls");
								cout<<"======================================\n";
								cout<<"Car Shipping: 40ft above Van: \n";
								cout<<"======================================\n";
								cout<<"Enter quantity of 40ft above van: ";
								cin>>quantity40[userCount][shipIndex][shipLocIndex];

								for(int i = 0; i < quantity40[userCount][shipIndex][shipLocIndex]; i++) {
									cout<<"Enter Plater Number for vehicle no."<<i+1<<": ";
									cin>>plateNum40[userCount][shipIndex][i];
								}

								totalQuantity40[userCount][shipIndex][shipLocIndex]+= quantity40[userCount][shipIndex][shipLocIndex];

								userAVPrice[userCount][shipIndex][shipLocIndex] += quantity40[userCount][shipIndex][shipLocIndex] * aboveVanPrice;
							} else if(opt == 3) {
								system("pause");
								buyTicket();
							} else {
								cout<<"Invalid Input!\n";
								system("pause");
								buyTicket();
							}

//							if(totalQuantity20[userCount][shipIndex][shipLocIndex] > 0) {
//								cout<<"20ft below Van Shipping: "<<totalQuantity20[userCount][shipIndex][shipLocIndex]<<endl;
//							}

							vanShipTotal[userCount][shipIndex][shipLocIndex] = userBVPrice[userCount][shipIndex][shipLocIndex] + userAVPrice[userCount][shipIndex][shipLocIndex];
							cout<<"Total Balance for Van Shipping: "<<vanShipTotal[userCount][shipIndex][shipLocIndex]<<endl;

							save();

							cout<<"\n======================================\n";
							cout<<"[1] Check Out\n";
							cout<<"[2] Book More\n";
							cout<<"[3] Back\n";
							cout<<"--------------------------------------\n";
							cout<<"\nOption: ";
							cin>>opt;
							cout<<"\n======================================\n";

							switch(opt) {
								case 1:
									checkOut();
									break;
								case 2:
									break;
								case 3:
									system("pause");
									buyTicket();
									break;
								default:
									cout<<"Invalid Input!\n";
									system("pause");
									buyTicket();
									break;
							}
						} while(opt == 2);
					} else if(opt == 3) {

					} else {

					}
				}

			}

		}
	}
}


void checkOut() {
	system("cls");
	cout<<"======================================\n";
	cout<<"Book a Ticket\n";
	cout<<"======================================\n";
	cout<<"Tickets Bought: \n";
	cout<<"--------------------------------------\n";
	overallPrice[userCount] = 0;
	for(int i = 0; i < shipCount; i++) {
		for(int j = 0; j < shipLocCount[i]; j++) {
			if(RecSeniorCount[userCount][i][j] > 0 || RecAdultCount[userCount][i][j] > 0 || RecInfantCount[userCount][i][j] > 0 || vipRoom[userCount][i][j] > 0 || totalQuantity20[userCount][i][j] > 0 || totalQuantity40[userCount][i][j] > 0) {
				cout<<ships[i]<<"-"<<shipLoc[i][j]<<endl;
				if(RecSeniorCount[userCount][i][j] > 0) {
					cout<<"Senior: "<<RecSeniorCount[userCount][i][j]<<" tickets. "<< RecSeniorCount[userCount][i][j] * RecSeniorTP[i][j] <<" Pesos.\n";
				}
				if(RecAdultCount[userCount][i][j] > 0) {
					cout<<"Adult: "<<RecAdultCount[userCount][i][j]<<" tickets."<< RecAdultCount[userCount][i][j] * RecAdultTP[i][j] <<" Pesos.\n";;
				}
				if(RecInfantCount[userCount][i][j] >0) {
					cout<<"Infant: "<<RecInfantCount[userCount][i][j]<<" tickets."<< RecInfantCount[userCount][i][j] * RecInfantTP[i][j] <<" Pesos.\n";;
				}
				if(vipRoom[userCount][i][j] > 0) {
					cout<<"VIP Room: "<<vipRoom[userCount][i][j]<<endl;
					cout<<"Room Occupants: "<<vipOccu[userCount][i][j]<<endl;
					cout<<"Room Price: "<<vipPrice[userCount][i][j]<<endl;
				}
				if(totalQuantity20[userCount][i][j] > 0) {
					cout<<"20ft below Van Shipping: "<<totalQuantity20[userCount][i][j]<<endl;
					cout<<"Price: "<<userBVPrice[userCount][i][j]<<endl;
				}
				if(totalQuantity40[userCount][i][j] > 0) {
					cout<<"40ft below Van Shipping: "<<totalQuantity40[userCount][i][j]<<endl;
					cout<<"Price: "<<userAVPrice[userCount][i][j]<<endl;
				}
				cout<<"--------------------------------------\n";
			}
			overallPrice[userCount] += (RecSeniorCount[userCount][i][j] * RecSeniorTP[i][j]) + (RecAdultCount[userCount][i][j] * RecAdultTP[i][j]) + (RecInfantCount[userCount][i][j] * RecInfantTP[i][j] + (vipPrice[userCount][i][j]) + (userBVPrice[userCount][i][j]) + (userAVPrice[userCount][i][j]));
		}
	}
	userBalance[userCount] = overallPrice[userCount];
	cout<<"Total Price: "<<overallPrice[userCount]<<endl;
	save();
	cout<<"[1] Pay Now\n";
	cout<<"[2] Back\n";

	cout<<"Option: ";
	cin>>opt;

	if(opt == 1) {
		do {
			cout<<"Enter Payment: ";
			cin>>userPayment[userCount];
			if(userPayment[userCount] < userBalance[userCount]) {
				cout<<"Your payment is not enough!\n";
			} else {
				if(userBalance[userCount] == 0) {
					cout<<"You don't have any tickets to pay!\n";
					system("pause");
					userInt();
				} else {
					cout<<"Please wait for the admin to confirm your payment.\n";
					save();
					system("pause");
					userInt();
				}
			}
		} while(userPayment[userCount] < userBalance[userCount]);
	} else if(opt == 2) {
		system("pause");
		userInt();
	} else {
		cout<<"Invalid Option!\n";
		system("pause");
		checkOut();
	}
	save();
}

void userReceipt() {
	system("cls");
	cout<<"=============================================\n";
	cout<<"RECEIPT: \n";
	cout<<"=============================================\n";
	cout<<"Name: "<<usernames[userCount]<<endl;
	cout<<"---------------------------------------\n";
	overallPrice[userCount] = 0;
	for(int i = 0; i < shipCount; i++) {
		for(int j = 0; j < shipLocCount[i]; j++) {
			if(RecSeniorCount[userCount][i][j] > 0 || RecAdultCount[userCount][i][j] > 0 || RecInfantCount[userCount][i][j] > 0 || vipRoom[userCount][i][j] > 0 || totalQuantity20[userCount][i][j] > 0 || totalQuantity40[userCount][i][j] > 0) {
				cout<<ships[i]<<"-"<<shipLoc[i][j]<<endl;
				if(RecSeniorCount[userCount][i][j] > 0) {
					cout<<"Senior: "<<RecSeniorCount[userCount][i][j]<<" tickets. "<< RecSeniorCount[userCount][i][j] * RecSeniorTP[i][j] <<" Pesos.\n";
				}
				if(RecAdultCount[userCount][i][j] > 0) {
					cout<<"Adult: "<<RecAdultCount[userCount][i][j]<<" tickets."<< RecAdultCount[userCount][i][j] * RecAdultTP[i][j] <<" Pesos.\n";;
				}
				if(RecInfantCount[userCount][i][j] >0) {
					cout<<"Infant: "<<RecInfantCount[userCount][i][j]<<" tickets."<< RecInfantCount[userCount][i][j] * RecInfantTP[i][j] <<" Pesos.\n";;
				}
				if(vipRoom[userCount][i][j] > 0) {
					cout<<"VIP Room: "<<vipRoom[userCount][i][j]<<endl;
					cout<<"Room Occupants: "<<vipOccu[userCount][i][j]<<endl;
					cout<<"Room Price: "<<vipPrice[userCount][i][j]<<endl;
				}
				if(totalQuantity20[userCount][i][j] > 0) {
					cout<<"20ft below Van Shipping: "<<totalQuantity20[userCount][i][j]<<endl;
					cout<<"Price: "<<userBVPrice[userCount][i][j]<<endl;
				}
				if(totalQuantity40[userCount][i][j] > 0) {
					cout<<"40ft below Van Shipping: "<<totalQuantity40[userCount][i][j]<<endl;
					cout<<"Price: "<<userAVPrice[userCount][i][j]<<endl;
				}
				cout<<"--------------------------------------\n";
			}
			overallPrice[userCount] += (RecSeniorCount[userCount][i][j] * RecSeniorTP[i][j]) + (RecAdultCount[userCount][i][j] * RecAdultTP[i][j]) + (RecInfantCount[userCount][i][j] * RecInfantTP[i][j] + (vipPrice[userCount][i][j]) + (userBVPrice[userCount][i][j]) + (userAVPrice[userCount][i][j]));
		}
	}
	cout<<"=============================================\n";
	cout<<"Total Price: "<<overallPrice[userCount]<<endl;
	cout<<"=============================================\n";
	cout<<"Payment: "<<userPayment[userCount]<<endl;
	cout<<"=============================================\n";
	userChange[userCount] = userPayment[userCount] - overallPrice[userCount];
	cout<<"Changed: "<<userChange[userCount]<<endl;
	cout<<"=============================================\n";
	cout<<"HAVE A NICE DAY, COME AGAIN!\n";
	cout<<"=============================================\n";
	//RESET ALL THE VALUE TO 0 AFTER GETTING THE RECEIPT
	for(int i = 0; i < shipCount; i++) {
		for(int j = 0; j < shipLocCount[i]; j++) {
			RecSeniorCount[userCount][i][j] = 0;
			RecAdultCount[userCount][i][j] = 0;
			RecInfantCount[userCount][i][j] = 0;
			vipRoom[userCount][i][j] = 0;
			vipOccu[userCount][i][j] = 0;
			vipPrice[userCount][i][j]= 0;
			totalQuantity20[userCount][i][j]= 0;
			userBVPrice[userCount][i][j]= 0;
			totalQuantity40[userCount][i][j]= 0;
			userAVPrice[userCount][i][j]= 0;
			overallPrice[userCount] = 0;
		}
	}
	userPayment[userCount] = 0;
	userChange[userCount] = 0;
	userPaid[userCount] = 0;
	save();
	system("pause");
	userInt();
}

void ticketManagement() {
	system("cls");
	cout<<"=============================================\n";
	cout<<"Ticket Management: \n";
	cout<<"=============================================\n";
	cout<<"[1] Checkout\n";
	cout<<"[2] Ticket Status\n";
	cout<<"[3] Back\n";
	cout<<"---------------------------------------\n";
	cout<<"Option: ";
	cin>>opt;
	cout<<"\n=======================================\n";
	if(opt == 1) {
		checkOut();
	} else if(opt == 2) {
		ticketStatus();
	} else if(opt == 3) {
		system("pause");
		userInt();
	} else {
		cout<<"Invalid Input!\n";
		system("pause");
		userInt();
	}
}

void ticketStatus() {
	system("cls");
	cout<<"=======================================\n";
	cout<<"Ticket Status: \n";
	cout<<"=======================================\n";
	//if userPaid == 1, Its accepted or the money is equal to the balance
	//if == 2, the user has change, or the payment is bigger than the balance
	if(userPaid[userCount] == 1) {
		cout<<"Your order has been accepted!\n";
		cout<<"Please wait for your receipt!\n";
		cout<<"Please take a picture of your receipt!\n";
		system("pause");
		userReceipt();
	} else if(userPaid[userCount] == 2) {
		cout<<"Your order has been accepted!\n";
		cout<<"Please wait for your receipt!\n";
		cout<<"Please take a picture of your receipt!\n";
		cout<<"Show this receipt and"<<endl;
		cout<<"Get your change in the counter!\n";
		system("pause");
		userReceipt();
	} else {
		cout<<"Payment is not enough!\n";
		cout<<"Payment Declined!\n";
		cout<<"Please wait for admin to confirm your payment!\n";
	}
	system("pause");
	userInt();
}

void schedules() {
	system("cls");
	cout<<"=============================================\n";
	cout<<"Ship Schedules: \n";
	for(int i = 0; i < shipCount; i++) {
		cout<<"=============================================\n";
		cout<<"["<<i+1<<"] "<<ships[i]<<endl;
		cout<<"=============================================\n";
		cout<<"Location \t\tDeparture Date & Time \n";
		cout<<"=============================================\n";
		for(int j = 0; j <shipLocCount[i]; j++) {
			cout<<"["<<j+1<<"] "<<shipLoc[i][j]<<" : \t\t";
			cout<<shipMonth[i][j]<<"/"<<shipDay[i][j]<<"/"<<year;
			cout<<" - ";
			if(shipTimeHour[i][j] < 12) {
				formatter = "AM";
			} else {
				if(shipTimeHour[i][j] > 12) {
					shipTimeHour[i][j] -= 12;
				}
				formatter = "PM";
			}
			cout<<shipTimeHour[i][j]<<":";
			if(shipTimeMin[i][j] < 10) {
				cout<<"0";
			}
			cout<<shipTimeMin[i][j]<<" "<<formatter<<endl;

		}
		cout<<"=============================================\n";
		cout<<"\n";
	}
	system("pause");
	userInt();
}

void userAcc() {
	system("cls");
	cout<<"=======================================\n";
	cout<<"Manage My Account: \n";
	cout<<"=======================================\n";
	cout<<"Full Name         : "<<fullname[userCount]<<endl;
	cout<<"Username          : "<<usernames[userCount]<<endl;
	cout<<"Password          : "<<passwords[userCount]<<endl;
	cout<<"Address           : "<<address[userCount]<<endl;
	cout<<"Age               : "<<age[userCount]<<endl;
	cout<<"Birthdate         : "<<bMM[userCount]<<"/"<<bDD[userCount]<<"/"<<bYY[userCount]<<endl;
	cout<<"=======================================\n";
	cout<<"[1] Update Profile: \n";
	cout<<"[2] Back\n";
	cout<<"---------------------------------------\n";
	cout<<"Option: ";
	cin>>opt;
	cout<<"\n=======================================\n";
	if(opt == 1) {
		system("cls");
		cout<<"=======================================\n";
		cout<<"Edit Account: \n";
		cout<<"=======================================\n";
		cout<<"[1] Full Name         : "<<fullname[userCount]<<endl;
		cout<<"[2] Username          : "<<usernames[userCount]<<endl;
		cout<<"[3] Password          : "<<passwords[userCount]<<endl;
		cout<<"[4] Address           : "<<address[userCount]<<endl;
		cout<<"---------------------------------------\n";
		cout<<"Choose what do you want to edit: ";
		cin>>opt;
		cin.ignore();
		cout<<"=======================================\n";

		switch(opt) {
			case 1:
				cout<<"\n=======================================\n";
				cout<<"Full Name: \n";
				cout<<"=======================================\n";
				cout<<"Enter new Name: ";
				getline(cin, fullname[userCount]);
				break;
			case 2:
				do {
					cout<<"\n=======================================\n";
					cout<<"Username: \n";
					cout<<"=======================================\n";
					cout<<"Enter new username: ";
					cout<<usernames[userCount]<<endl;
					cin>>usernames[userCount];

					if(usernames[userCount].length() < 8) {
						cout<<"Use 8 characters for Username/Password\n";
						cout<<"\n=======================================\n";
						system("pause");
					}
				} while(usernames[userCount].length() < 8);
				break;
			case 3:
				do {
					cout<<"\n=======================================\n";
					cout<<"Password: \n";
					cout<<"=======================================\n";
					cout<<"Enter new password: ";
					cin>>passwords[userCount];
					
					if(passwords[userCount].length() < 8) {
						cout<<"Use 8 characters for Username/Password\n";
						cout<<"\n=======================================\n";
						system("pause");
					}
				}while(passwords[userCount].length() < 8);

				break;
			case 4:
				cout<<"\n=======================================\n";
				cout<<"Address: \n";
				cout<<"=======================================\n";
				cout<<"Enter new address: ";
				cin>>address[userCount];
				break;
			default:
				cout<<"Invalid Input!\n";
				system("pause");
				userAcc();
				break;
		}
		save();
		cout<<"=======================================\n";
		cout<<"Changes Successfully Saved!\n";
		cout<<"=======================================\n";

	} else if(opt == 2) {
		system("pause");
		userInt();
	} else {

	}
	system("pause");
	userAcc();
}


void admin() {
	system("cls");
	cout<<"=======================================\n";
	cout<<"                ADMIN\n";
	cout<<"=======================================\n";
	cout<<"[1] Manage User Accounts\n";
	cout<<"[2] Manage Ships\n";
	cout<<"[3] Ship Schedule Management\n";
	cout<<"[4] Manage Admin Account\n";
	cout<<"[5] User Payment\n";
	cout<<"[6] Logout\n";
	cout<<"---------------------------------------\n";
	cout<<"\nOption: ";
	cin>>opt;
	cout<<"\n=======================================\n";
	system("pause");

	switch(opt) {
		case 1:
			manageUser();
			break;
		case 2:
			manageShip();
			break;
		case 3:
			shipSched();
			break;
		case 4:
			adminAcc();
			break;
		case 5:
			paymentUser();
			break;
		case 6:
			main();
			break;
		default:
			break;
	}
}

void manageUser() {
	system("cls");
	cout<<"======================================\n";
	cout<<"\tManage User Accounts\n";
	cout<<"======================================\n";
	cout<<"Account Number    Name\t\tStatus\n";
	cout<<"--------------------------------------\n";
	for(int i = 0; i < acc; i++) {
		cout<<"      "<<i+1<<"\t\t"<<usernames[i]<<"\t";
		if(status[i] == 0) {
			cout<<"Active\n";
		} else {
			cout<<"Banned\n";
		}
	}
	cout<<"======================================\n";
	int selected;
	cout<<"[1] Ban\n";
	cout<<"[2] Unban\n";
	cout<<"[3] Back\n";
	cout<<"--------------------------------------\n";
	cout<<"Option: ";
	cin>>opt;
	cout<<"--------------------------------------\n";
	if(opt == 1) {
		cout<<"Enter Account Number: ";
		cin>>opt;
		cout<<"--------------------------------------\n";
		selected = opt - 1;
		if(status[selected] == 0) {
			cout<<usernames[selected]<<" is now banned!\n";
			status[selected] = 1;
		} else {
			cout<<usernames[selected]<<" is already banned!\n";
		}
		cout<<"======================================\n";
	} else if(opt == 2) {
		cout<<"Enter Account Number: ";
		cin>>opt;
		cout<<"--------------------------------------\n";
		selected = opt - 1;
		if(status[selected] == 1) {
			cout<<usernames[selected]<<" is now unbanned!\n";
			status[selected] = 0;
		} else {
			cout<<usernames[selected]<<" is already active!\n";
		}
		cout<<"======================================\n";
	} else {
		admin();
	}
	save();
	system("pause");
	manageUser();
}

void manageShip() {
	system("cls");
	cout<<"======================================\n";
	cout<<"Manage Ships:\n";
	cout<<"======================================\n";
	cout<<"[1] View Ships\n";
	cout<<"[2] Add Ships\n";
	cout<<"[3] Manage Ship Status\n";
	cout<<"[4] Manage Ship Route\n";
	cout<<"[5] Back\n";
	cout<<"--------------------------------------\n";
	cout<<"\nOption: ";
	cin>>opt;
	cin.ignore();
	cout<<"\n======================================\n";

	switch(opt) {
		case 1:
			load();
			system("cls");
			cout<<"================================================\n";
			cout<<"List of Ships:\n";
			cout<<"================================================\n";
			cout<<"Ship ID\t\tShip Name\t\tCapacity\n";
			cout<<"------------------------------------------------\n";

			for (int i = 0; i < shipCount; i++) {
				int totalCapacity = 0;
				for (int j = 0; j < shipLocCount[i]; j++) {
					shipCap[i][j] = shipRecSlot[i][j] + shipVipSlot[i][j];
					totalCapacity += shipCap[i][j];
				}
				cout << shipID[i] << "\t\t" << ships[i] << "\t\t" << totalCapacity << endl;
			}
			cout<<"================================================\n";
			system("pause");
			manageShip();
		case 2:
			system("cls");
			cout<<"======================================\n";
			cout<<"Add Ships:\n";
			cout<<"======================================\n";
			cout<<"Name of the Ship: ";
			getline(cin, ships[shipCount]);
			cout<<"--------------------------------------\n";
			shipID[shipCount] = shipID[shipCount - 1] + 1;

			int routeCount;
			cout<<"How many Route/s does this ship have? ";
			cin>>routeCount;
			cout<<"--------------------------------------\n";
			cin.ignore();

			for(int i = 0; i < routeCount; i++) {
				cout<<"Add Ship Route/s: ";
				getline(cin, shipLoc[shipCount][i]);
				cout<<"--------------------------------------\n";
			}

			for(int i = 0; i < routeCount; i++) {
				cout<<shipLoc[shipCount][i]<<endl;
				cout<<"======================================\n";
				cout<<"Enter Reclining Seat Slot: ";
				cin>>shipRecSlot[shipCount][i];
				cin.ignore();
				cout<<"--------------------------------------\n";
				cout<<"Set Fare for Senior Ticket Price : ";
				cin>>RecSeniorTP[shipCount][i];
				cout<<"Set Fare for Adult Ticket Price  : ";
				cin>>RecAdultTP[shipCount][i];
				cout<<"Set Fare for Infant Ticket Price : ";
				cin>>RecInfantTP[shipCount][i];
				cout<<"\n======================================\n";
				cout<<"Enter VIP Room Slot: ";
				cin>>shipVipSlot[shipCount][i];
				cin.ignore();
				cout<<"--------------------------------------\n";
				cout<<"Set VIP Room Price: ";
				cin>>VipRoomTP[shipCount][i];
				cout<<"--------------------------------------\n";
				shipLocCount[shipCount]++;
				cout<<"======================================\n";

				do {
					cout<<"Enter Ship Date of Departure: "<<endl;
					cout<<"Month : ";
					cin>>shipMonth[shipCount][i];

					//Ship date should not be earlier than current date 7/6/2023

					if(shipMonth[shipCount][i] < 7) {
						cout<<"The date should not be earlier than current date!\n";
//						system("pause");
//						manageShip();
					} else if(shipMonth[shipCount][i] > 12) {
						cout<<"Invalid Month!\n";
//						system("pause");
//						manageShip();
					}

					else {
						cout<<"Date  : ";
						cin>>shipDay[shipCount][i];
//					if(shipMonth[shipCount][i] == 2) {
//						if(shipDay[shipCount][i] < 1 || shipDay[shipCount][i] > 28) {
//							cout<<"Invalid Day!\n";
//							system("pause");
//							manageShip();
//						}
//					}
						if(shipMonth[shipCount][i] == 7 && shipDay[shipCount][i] < 7) {
							cout<<"The date should not be earlier than current date!\n";
//								manageShip();

						} else {
							if(shipMonth[shipIndex][shipLocCount[shipIndex]] == 9) {
								if(shipDay[shipIndex][shipLocCount[shipIndex]] < 1 || shipDay[shipIndex][shipLocCount[shipIndex]] > 30) {
									cout<<"Invalid Day!\n";
//								system("pause");
//								manageShip();
								}
							}
							cout<<"======================================\n";
							cout<<"Departure date is on: "<<shipMonth[shipCount][i]<<"/"<<shipDay[shipCount][i]<<"/"<<year<<endl;
							cout<<"======================================\n";
							cout<<"Enter Ship Departure Time: \n";
							cout<<"======================================\n";
							do {
								cout<<"Enter Hour (Enter a 24-Hour Format): ";
								cin>>shipTimeHour[shipCount][i];

								if(shipTimeHour[shipCount][i] < 0 || shipTimeHour[shipCount][i] > 24) {
									cout<<"Invalid Hour!\n";
//							system("pause");
//							manageShip();
								}
							} while(shipTimeHour[shipCount][i] < 0 || shipTimeHour[shipCount][i] > 24);


							if(shipTimeHour[shipCount][i] < 12 ) {
								formatter = "AM";
							} else if(shipTimeHour[shipCount][i] == 24) {
								shipTimeHour[shipCount][i] -= 12;
								formatter = "AM";
							} else {
								if(shipTimeHour[shipCount][i] > 12) {
									shipTimeHour[shipCount][i] -= 12;
								}
								formatter = "PM";
							}

							cout<<"Enter Minute: ";
							cin>>shipTimeMin[shipCount][i];

							if(shipTimeMin[shipCount][i] < 0 || shipTimeMin[shipCount][i] > 60) {
								cout<<"Invalid Minute!\n";
//							system("pause");
//							manageShip();
							} else {
								cout<<"======================================\n";
								cout<<"The Time is: "<<shipTimeHour[shipCount][i]<<":";
								if(shipTimeMin[shipCount][i] < 10) {
									cout<<"0";
								}

								cout<<shipTimeMin[shipCount][i]<<" "<<formatter<<endl;
								cout<<"======================================\n";
								break;

							}
						}
					}
//					cin.clear();
				} while(true);
			}

			for (int i =0; i < routeCount; i++) {
				int recliningSeats = shipRecSlot[shipCount][i];
				int vipRooms = shipVipSlot[shipCount][i];
				shipCap[shipCount][i] = recliningSeats + vipRooms;
			}



			shipCount++;
			save();

//			for(int i = 0; i < shipCount; i++) {
//				int totalCapacity = 0;
//				for(int j = 0; j < shipLocCount[i]; j++) {
//					totalCapacity += shipCap[i][j];
//				}
//				cout << shipID[i] << "\t\t" << ships[i] << "\t\t" << totalCapacity << endl;
//			}


//
//			for(int i = 0; i < shipCount; i++) {
//				cout<<shipID[i] << "\t\t" << ships[i]<<endl;
//				for(int j = 0; j < shipLocCount[i]; j++) {
//					cout << shipLoc[i][j] << " "<<shipCap[i][j]<<endl;
//				}
//			}

			system("pause");
			manageShip();

		case 3:
			load();
			system("cls");
			cout<<"======================================\n";
			cout<<"List of Ships:\n";
			cout<<"======================================\n";
			cout<<"Ship ID\t\tShip Name\t\tStatus\n";
			cout<<"--------------------------------------\n";
			for(int i = 0; i < shipCount; i++) {
				cout<<shipID[i]<<"\t\t"<<ships[i]<<"\t\t";
				if(shipStatus[i] == 0) {
					cout<<"Active\n";
				} else {
					cout<<"Inactive\n";
				}
			}
			cout<<"--------------------------------------\n";
			cout<<"[0] Back\n";
			cout<<"--------------------------------------\n";
			cout<<"Enter Ship ID to Select: ";
			cin>>opt;
			cout<<"\n======================================\n";

			if(opt == 0) {
				system("pause");
				admin();
			} else {
				//To select the index of ships
				shipIndex = opt - 101;
				if(shipIndex >= 0 && shipIndex < shipCount) {
					cout<<"Change Ship Status: \n";
					cout<<"[1] Active\n";
					cout<<"[2] Inactive\n";
					cout<<"--------------------------------------\n";
					cout<<"\nOption: ";
					cin>>opt;
					cout<<"\n--------------------------------------\n";
					if(opt == 1) {
						if(shipStatus[shipIndex] == 0) {
							cout<<ships[shipIndex]<<" is already Active!\n";
						} else {
							cout<<ships[shipIndex]<<"is now Active!\n";
							shipStatus[shipIndex] = 0;
						}
					} else {
						if(shipStatus[shipIndex] == 1) {
							cout<<ships[shipIndex]<<"is already Inactive!\n";
						} else {
							cout<<ships[shipIndex]<<"is now Inactive!\n";
							shipStatus[shipIndex] = 1;
						}
					}
					cout<<"======================================\n";

				} else {
					cout<<"Invalid Input!";
				}
				system("pause");
				manageShip();
			}
		case 4:
			system("cls");
			cout<<"======================================\n";
			cout<<"Manage Ship Route:\n";
			cout<<"======================================\n\n";
			for(int i = 0; i < shipCount; i++) {
				cout<<"["<<i+1<<"] "<<ships[i]<<endl;
			}
			cout<<"--------------------------------------\n";
			cout<<"[0] Back\n";
			cout<<"--------------------------------------\n";
			cout<<"\nOption: ";
			cin>>opt;
			cout<<"\n======================================\n";
			if(opt == 0) {
				system("pause");
				admin();
			} else {
				shipIndex = opt - 1;
				if(shipIndex >= 0 && shipIndex < shipCount) {
					system("cls");
					cout<<"======================================\n";
					cout<<ships[shipIndex]<<": \n";
					cout<<"======================================\n";
					cout<<"[1] Add Route\n";
					cout<<"[2] Edit Route\n";
					cout<<"[3] View Route\n";
					cout<<"[4] Back\n";
					cout<<"--------------------------------------\n";
					cout<<"\nOption: ";
					cin>>opt;
					cout<<"\n======================================\n";
					if(opt == 1) {

						system("cls");
						cout<<"======================================\n";
						cout<<"Add Route: "<<ships[shipIndex];
						cout<<"======================================\n";
						cout<<"Set Route Name: ";
						cin>>shipLoc[shipIndex][shipLocCount[shipIndex]];


						cout<<"Enter Reclining Seat Slot: ";
						cin>>shipRecSlot[shipIndex][shipLocCount[shipIndex]];
						cout<<"----------------\n";
						cout<<"Set Fare for Senior Ticket Price: ";
						cin>>RecSeniorTP[shipIndex][shipLocCount[shipIndex]];
						cout<<"Set Fare for Adult Ticket Price: ";
						cin>>RecAdultTP[shipIndex][shipLocCount[shipIndex]];
						cout<<"Set Fare for Infant Ticket Price: ";
						cin>>RecInfantTP[shipIndex][shipLocCount[shipIndex]];
						cout<<"----------------\n";
						cout<<"\n==========================\n";
						cout<<"Enter VIP Room Slot";
						cin>>shipVipSlot[shipIndex][shipLocCount[shipIndex]];
						cout<<"----------------\n";
						cout<<"Set VIP Room Price: ";
						cin>>VipRoomTP[shipIndex][shipLocCount[shipIndex]];
						cout<<"----------------\n";

						do {
							cout<<"Enter Ship Date of Departure: "<<endl;
							cout<<"Month : ";
							cin>>shipMonth[shipIndex][shipLocCount[shipIndex]];

							//Ship date should not be earlier than current date 7/6/2023

							if(shipMonth[shipIndex][shipLocCount[shipIndex]] < 7) {
								cout<<"The date should not be earlier than current date!\n";
//						system("pause");
//						manageShip();
							} else if(shipMonth[shipIndex][shipLocCount[shipIndex]] > 12) {
								cout<<"Invalid Month!\n";
//						system("pause");
//						manageShip();
							}

							else {
								cout<<"Date  : ";
								cin>>shipDay[shipIndex][shipLocCount[shipIndex]];
//					if(shipMonth[shipCount][i] == 2) {
//						if(shipDay[shipCount][i] < 1 || shipDay[shipCount][i] > 28) {
//							cout<<"Invalid Day!\n";
//							system("pause");
//							manageShip();
//						}
//					}
								if(shipMonth[shipIndex][shipLocCount[shipIndex]] == 7 && shipDay[shipIndex][shipLocCount[shipIndex]] < 7) {
									cout<<"The date should not be earlier than current date!\n";
//								manageShip();

								} else {
									if(shipMonth[shipIndex][shipLocCount[shipIndex]] == 9) {
										if(shipDay[shipIndex][shipLocCount[shipIndex]] < 1 || shipDay[shipIndex][shipLocCount[shipIndex]] > 30) {
											cout<<"Invalid Day!\n";
//								system("pause");
//								manageShip();
										}
									}
									cout<<"======================================\n";
									cout<<"Departure date is on: "<<shipMonth[shipIndex][shipLocCount[shipIndex]]<<"/"<<shipDay[shipIndex][shipLocCount[shipIndex]]<<"/"<<year<<endl;
									cout<<"======================================\n";
									cout<<"Enter Ship Departure Time: \n";
									cout<<"======================================\n";
									do {
										cout<<"Enter Hour (Enter a 24-Hour Format): ";
										cin>>shipTimeHour[shipIndex][shipLocCount[shipIndex]];

										if(shipTimeHour[shipIndex][shipLocCount[shipIndex]] < 0 || shipTimeHour[shipIndex][shipLocCount[shipIndex]] > 24) {
											cout<<"Invalid Hour!\n";
//							system("pause");
//							manageShip();
										}
									} while(shipTimeHour[shipIndex][shipLocCount[shipIndex]] < 0 || shipTimeHour[shipIndex][shipLocCount[shipIndex]] > 24);


									if(shipTimeHour[shipIndex][shipLocCount[shipIndex]] < 12 ) {
										formatter = "AM";
									} else if(shipTimeHour[shipIndex][shipLocCount[shipIndex]] == 24) {
										shipTimeHour[shipIndex][shipLocCount[shipIndex]] -= 12;
										formatter = "AM";
									} else {
										if(shipTimeHour[shipIndex][shipLocCount[shipIndex]] > 12) {
											shipTimeHour[shipIndex][shipLocCount[shipIndex]] -= 12;
										}
										formatter = "PM";
									}

									cout<<"Enter Minute: ";
									cin>>shipTimeMin[shipIndex][shipLocCount[shipIndex]];

									if(shipTimeMin[shipIndex][shipLocCount[shipIndex]] < 0 || shipTimeMin[shipIndex][shipLocCount[shipIndex]] > 60) {
										cout<<"Invalid Minute!\n";
//							system("pause");
//							manageShip();
									} else {
										cout<<"======================================\n";
										cout<<"The Time is: "<<shipTimeHour[shipIndex][shipLocCount[shipIndex]]<<":";
										if(shipTimeMin[shipIndex][shipLocCount[shipIndex]] < 10) {
											cout<<"0";
										}

										cout<<shipTimeMin[shipIndex][shipLocCount[shipIndex]]<<" "<<formatter<<endl;
										cout<<"======================================\n";
										break;

									}
								}
							}
//					cin.clear();
						} while(true);

						shipCap[shipIndex][shipLocCount[shipIndex] ] = shipRecSlot[shipIndex][shipLocCount[shipIndex]] + shipVipSlot[shipIndex][shipLocCount[shipIndex]];

						cout<<"Capacity for new location: "<<shipCap[shipIndex][shipLocCount[shipIndex]]<<endl;
						shipLocCount[shipIndex]++;
						save();

					} else if(opt == 2) {
						system("cls");
						cout<<"======================================\n";
						cout<<"Edit Route: "<<ships[shipIndex]<<endl;
						cout<<"======================================\n";
						for(int i = 0; i < shipLocCount[shipIndex]; i++) {
							cout<<"["<<i+1<<"] "<<shipLoc[shipIndex][i]<<endl;
						}
						cout<<"[0] Back\n";
						cout<<"--------------------------------------\n";
						cout<<"\nOption: ";
						cin>>opt;
						cout<<"\n======================================\n";
						if(opt == 0) {
							system("pause");
							admin();
						} else {
							int shipLocIndex = opt - 1;
//							if(shipLocIndex >= 0 && shipLocIndex < shipCount)
							if(shipLocIndex >= 0 && shipLocIndex < shipLocCount[shipIndex]) {
								system("cls");
								cout<<"======================================\n";
								cout<<"Edit Route: "<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<endl;
								cout<<"======================================\n";
								cout<<"[1] Edit Route Name "<<endl;
								cout<<"[2] Edit Reclining Seat Ticket Price "<<endl;
								cout<<"[3] Edit VIP Room Price "<<endl;
								cout<<"[4] Back "<<endl;
								cout<<"--------------------------------------\n";
								cout<<"\nOption: ";
								cin>>opt;
								cin.ignore();
								cout<<"\n======================================\n";
								if(opt == 1) {
									system("cls");
									cout<<"======================================\n";
									cout<<"Edit Route Name: "<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<endl;
									cout<<"======================================\n";
									cout<<"Enter New Route Name: ";
									getline(cin, shipLoc[shipIndex][shipLocIndex]);
									save();
								} else if(opt == 2) {
									system("cls");
									cout<<"======================================\n";
									cout<<"Edit Reclining Seat Ticket Price: "<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<endl;
									cout<<"======================================\n";
									cout<<"Current Ticket Price for "<<shipLoc[shipIndex][shipLocIndex]<<endl;
									cout<<"======================================\n";
									cout<<"\nSenior: "<<RecSeniorTP[shipIndex][shipLocIndex]<<endl;
									cout<<"Adult: "<<RecAdultTP[shipIndex][shipLocIndex]<<endl;
									cout<<"Infant: "<<RecInfantTP[shipIndex][shipLocIndex]<<endl;
									cout<<"======================================\n";
									cout<<"Enter new Ticket Price: ";
									cout<<"Senior: ";
									cin>>RecSeniorTP[shipIndex][shipLocIndex];
									cout<<"Adult: ";
									cin>>RecAdultTP[shipIndex][shipLocIndex];
									cout<<"Infant: ";
									cin>>RecInfantTP[shipIndex][shipLocIndex];
									cout<<"======================================\n";
									cout<<"Tickets Updated Successfully!\n";
									save();

								} else if(opt == 3) {
									system("cls");
									cout<<"======================================\n";
									cout<<"Edit VIP Room Ticket Price: "<<ships[shipIndex]<<shipLoc[shipIndex][shipLocIndex]<<endl;
									cout<<"======================================\n";
									cout<<"Current Room Price for "<<shipLoc[shipIndex][shipLocIndex]<<endl;
									cout<<"======================================\n";
									cout<<"Room Price: "<<VipRoomTP[shipIndex][shipLocIndex]<<endl;
									cout<<"======================================\n";
									cout<<"Enter new Room Price: ";
									cin>>VipRoomTP[shipIndex][shipLocIndex];
									cout<<"======================================\n";
									cout<<"Tickets Updated Successfully!\n";
									save();

								} else if(opt == 4) {

								} else {

								}
							}
						}
						cout<<"======================================\n";
						system("pause");
						manageShip();
					} else if(opt ==3) {
						system("cls");
						cout<<"======================================\n";
						cout<<"View Route: "<<ships[shipIndex]<<endl;
						cout<<"======================================\n";
						for(int i = 0; i < shipLocCount[shipIndex]; i++) {
							cout<<"- "<<shipLoc[shipIndex][i]<<endl;
						}

						system("pause");
						manageShip();
					} else if(opt ==4) {
						system("pause");
						manageShip();
					} else {
						cout<<"Invalid Input!\n";
						system("pause");
						manageShip();
					}
				}

			}

		case 5:
			system("pause");
			admin();
	}
}


void shipSched() {
	system("cls");
	cout<<"======================================\n";
	cout<<"\tShip Schedule Management\n";
	cout<<"======================================\n";
	cout<<"Ship List:\n";
	for(int i = 0; i < shipCount; i++) {
		cout<<"["<<i+1<<"]"<<" "<<ships[i]<<endl;
	}
	cout<<"[0] Back\n";
	cout<<"--------------------------------------\n";
	cout<<"\nOption: ";
	cin>>opt;
	cout<<"\n======================================\n";

	if(opt == 0) {
		system("pause");
		admin();
	} else if(opt-1 <= shipCount && opt-1 >= 0) {
		int shipIndex = opt - 1;
		if(shipIndex >= 0 && shipIndex < shipCount) {
			system("cls");
			cout<<"======================================\n";
			cout<<ships[shipIndex]<<endl;
			cout<<"--------------------------------------\n";
//			schedOpt:
			cout<<"[1] Edit Schedule\n";
			cout<<"[2] View Schedule\n";
			cout<<"[3] Back\n";
			cout<<"--------------------------------------\n";
			cout<<"\nOption: ";
			cin>>opt;
			cout<<"\n======================================\n";
			if(opt == 1) {
				load();
				system("cls");
				cout<<"======================================\n";
				cout<<"Edit Schedule: \n";
				cout<<"======================================\n";
				for(int i = 0; i < shipLocCount[shipIndex]; i++) {
					cout<<"["<<i+1<<"] "<<shipLoc[shipIndex][i]<<endl;
				}
				cout<<"[0] Back\n";
				cout<<"--------------------------------------\n";
				cout<<"\nOption: ";
				cin>>opt;
				cout<<"\n======================================\n";
				if(opt == 0) {
					system("pause");
					admin();
				} else if(opt-1 <= shipLocCount[shipIndex] && opt-1 >= 0) {
					int shipLocIndex = opt - 1;
					cout<<ships[shipIndex]<<" - "<<shipLoc[shipIndex][shipLocIndex]<<endl;
					cout<<"--------------------------------------\n";
					cout<<"Enter Date for Ship Departure: \n";
					cout<<"--------------------------------------\n";
					cout<<"Enter Month: ";
					cin>>shipMonth[shipIndex][shipLocIndex];
					cout<<"Enter Date: ";
					cin>>shipDay[shipIndex][shipLocIndex];
					cout<<"--------------------------------------\n";
					cout<<"Date of Departure for: "<<ships[shipIndex]<<" is on: "<<shipMonth[shipIndex][shipLocIndex]<<"/"<<shipDay[shipIndex][shipLocIndex]<<"/"<<year<<endl;

					cout<<"--------------------------------------\n";
					cout<<"Enter Time for Ship Departure: \n";
					cout<<"--------------------------------------\n";
					cout<<"Enter Hour (Enter a 24-Hour Format): ";
					cin>>shipTimeHour[shipIndex][shipLocIndex];

					if(shipTimeHour[shipIndex][shipLocIndex] < 0 || shipTimeHour[shipIndex][shipLocIndex] > 24) {
						cout<<"Invalid Hour!\n";
						system("pause");
						shipSched();
					}

					if(shipTimeHour[shipIndex][shipLocIndex] < 12) {
						formatter = "AM";
					} else {
						if(shipTimeHour[shipIndex][shipLocIndex] > 12) {
							shipTimeHour[shipIndex][shipLocIndex] -= 12;
						}
						formatter = "PM";
					}

					cout<<"Enter Minute: ";
					cin>>shipTimeMin[shipIndex][shipLocIndex];

					if(shipTimeMin[shipIndex][shipLocIndex] < 0 || shipTimeMin[shipIndex][shipLocIndex] > 60) {
						cout<<"Invalid Minute!\n";
						system("pause");
						shipSched();
					}

					cout<<"The Time is: "<<shipTimeHour[shipIndex][shipLocIndex]<<":";

					if(shipTimeMin[shipIndex][shipLocIndex] < 10) {
						cout<<"0";
					}

					cout<<shipTimeMin[shipIndex][shipLocIndex]<<" "<<formatter<<endl;

					cout<<"\n======================================\n";
					cout<<"New Schedule has been set!\n";
					save();
				}
			} else if(opt == 2) {
				load();
				system("cls");
				cout<<"======================================\n";
				cout<<"View Schedules: "<<ships[shipIndex];
				cout<<"\n======================================\n";
				cout<<"Schedules\n";
				cout<<"--------------------------------------\n";
				for(int i = 0; i < shipLocCount[shipIndex]; i++) {
					cout<<"["<<i+1<<"] "<<shipLoc[shipIndex][i]<<" - "<<shipMonth[shipIndex][i]<<"/"<<shipDay[shipIndex][i]<<"/"<<year<<endl;
				}
			} else if(opt == 3) {
				system("pause");
				shipSched();
			} else {
				cout<<"Invalid Input!\n";
//				goto schedOpt;
				system("pause");
				shipSched();
			}
		}
	}
	cout<<"\n======================================\n";
	system("pause");
	shipSched();
}

void paymentUser() {
	load();
	system("cls");
	cout<<"=======================================\n";
	cout<<"Manage User Payment: \n";
	cout<<"=======================================\n";
	cout<<"List of User Payments: Balance\t\tPayment\n";
	cout<<"--------------------------------------\n";
	for(int i = 0; i < acc; i++) {
		if(userPayment[i] > 0) {
			cout<<"["<<i+1<<"] "<<usernames[i];
			cout<<"\t\t"<<overallPrice[i]<<"\t\t"<<userPayment[i]<<endl;
		}
	}
	cout<<"[0] Back\n";
	cout<<"--------------------------------------\n";
	cout<<"\nOption: ";
	cin>>opt;
	cout<<"\n======================================\n";
	if(opt == 0) {
		system("pause");
		admin();
	} else {
		int userSelected = opt - 1;
		cout<<"[1] Accept\n";
		cout<<"[2] Decline\n";
		cout<<"[3] Back\n";
		cout<<"--------------------------------------\n";
		cout<<"\nOption: ";
		cin>>opt;
		cout<<"\n======================================\n";
		if(opt == 1) {
			if(userPayment[userSelected] == userBalance[userSelected]) {
				cout<<"Payment Accepted!\n";
//				cout<<"Please check your ticket status!\n";
				userPaid[userSelected] = 1;
			} else if(userPayment[userSelected] > userBalance[userSelected]) {
				cout<<"Payment Accepted!\n";
//				cout<<"Please check your ticket status!\n";
//				cout<<"And get you change in the counter!\n";
				userPaid[userSelected] = 1;
			} else {
				cout<<"Payment Declined!\n";
				cout<<"Payment is not enough!\n";
				userPaid[userSelected] = 0;
			}
		} else if(opt == 2) {
			cout<<"Payment Declined!\n";
			userPayment[userSelected] = 0;
			userPaid[userSelected] = 0;
		} else if(opt == 3) {
			system("pause");
			admin();
		} else {
			cout<<"Invalid Input!\n";
			system("pause");
			admin();
		}
	}
	save();
	system("pause");
	admin();
}

void adminAcc() {
	system("cls");
	cout<<"=======================================\n";
	cout<<"Manage Admin Account: \n";
	cout<<"=======================================\n";
	cout<<"Username: "<<adminUser<<endl;
	cout<<"Password: "<<adminPass<<endl;
	cout<<"---------------------------------------\n";
	cout<<"[1] Update Profile\n";
	cout<<"[2] Back\n";
	cout<<"---------------------------------------\n";
	cout<<"Option: ";
	cin>>opt;
	cout<<"=======================================\n";
	system("pause");
	if(opt == 1) {
		system("cls");
		cout<<"=======================================\n";
		cout<<"Update Admin Profile: \n";
		cout<<"=======================================\n";
		cout<<"[1] Username\n";
		cout<<"[2] Password\n";
		cout<<"---------------------------------------\n";
		cout<<"Option: ";
		cin>>opt;
		cout<<"=======================================\n";
		if(opt == 1) {
			cout<<"Enter Old Admin Username: ";
			cin>>aUser;
			cout<<"---------------------------------------\n";
			if(aUser == adminUser) {
				cout<<"Enter New Admin Username: ";
				cin>>adminUser;
				cout<<"---------------------------------------\n";
				cout<<"Changes Saved!\n";
				cout<<"The Admin Username has been changed to: "<<adminUser<<endl;
				cout<<"=======================================\n";
			}
		} else if(opt == 2) {
			cout<<"Enter Old Admin Password: ";
			cin>>aPass;
			cout<<"---------------------------------------\n";
			if(aPass == adminPass) {
				cout<<"Enter New Admin Password: ";
				cin>>adminPass;
				cout<<"---------------------------------------\n";
				cout<<"Changes Saved!\n";
				cout<<"The Admin Password has been changed to: "<<adminPass<<endl;
				cout<<"=======================================\n";
			}
		} else {
			cout<<"Invalid Input!\n";
			cout<<"=======================================\n";
			system("pause");
			adminAcc();
		}
	} else if(opt == 2) {
		system("pause");
		cout<<"=======================================\n";
		admin();
	} else {
		cout<<"Invalid Input!\n";
		cout<<"=======================================\n";
	}
	system("pause");
	admin();
}

