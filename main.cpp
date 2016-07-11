#include <iostream> //.h
#include <fstream>  //.h
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>

using namespace std;

//For school:
//char IDFile[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\IDFile.dat";
//char homeLoc[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\";
//For local:
char IDFile[100] = "MC\\IDFile.dat";
char homeLoc[100] = "MC\\";
class Message {            //each message class contains name of sender and the message
	 public:
		  char name[20], message[1024];
		  void inputMessage() {
				gets(message);
		  }
};

void setID();
void UI1();
char getOption(char maxNumber);
void signup();
void aboutus();

class User {
	 private:
		  int i;      //general purpose to avoid errors for redeclaration and confusion. How many 'i's?
		  //Message m;
		  char username[20];
		  char password[20];
		  //char* chatName(User u);     //fn generates chat name in descending order of the usernames
		  void chatName(User u);
		  void showChats(User u);
		  char chatLoc[100];
	 public:
		  //static int Userno=0;
		  char* getUsername() {
				return username;
		  }
		  void setPass() {
				cout << "\nEnter a password without any special characters or spaces: ";
				gets(password);
		  }
		  void setUName() {
				gets(username);
		  }
		  void openChat(User u);
		  char* getPass(){
				return password;
		  }
		  void UI2();
        void findfriend();
}user1,user2;

void User::findfriend(){
    system("cls");
	//clrscr();
	cout << "Welcome "<< user1.getUsername();
	cout << "\n\t.............................................\n";
	cout << "Select a person: \n";
	int i = 0, friendLoc, f;
	ifstream infile(IDFile, ios::binary);
	ifstream chatID(IDFile, ios::binary);
	User users, u;
	char usersList[200][20], otherUserName[20];
	while(infile.read((char*)&users, sizeof(users))) {
        if(strcmpi(users.getUsername(), user1.getUsername())) { //as long as not self
            strcpy(usersList[i], users.getUsername());
            cout << "\n "<< ++i << ": " << users.getUsername();
        }
	}
	cout << "\nEnter your choice: ";
	friendLoc = getOption('i') - 49;       //gets the original option (ASCII/int conversion)
    strcpy(otherUserName, usersList[friendLoc]);
    cout << "\n" << friendLoc << otherUserName;
    while(chatID.read((char*)&u, sizeof(u))) {
        if(!strcmpi(otherUserName, u.getUsername())) {
            cout << u.getUsername();
            break;
        }
	}
	/*//infile.seekg(((friendLoc-1)*sizeof(users)), ios::beg);
	//infile.read((char*)&u, sizeof(users));*/
	infile.close();
	chatID.close();
	openChat(u);
}

void User::chatName(User otherUser) {
	 int namePos = 0;
	 //char chatFileName[100] = "MinuteChat\\"; //local
	 //char chatFileName[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\"; //school
	 //cout << "Thinking about the file location..." << chatFileName;
	 strcpy(chatLoc, homeLoc);
	 i = 0;
	 char c1[20], c2[20];
	 strcpy(c1, getUsername());
	 strcpy(c2, otherUser.getUsername());
	 do {
		  if(c1[namePos] > c2[namePos]) {
				strcat(chatLoc, getUsername());
				strcat(chatLoc, otherUser.getUsername());
				i = 1;
		  } else if (c2[namePos] > c1[namePos]) {
				strcat(chatLoc, otherUser.getUsername());
				strcat(chatLoc, getUsername());
				i = 1;
		  } else {
				namePos++;
		  }
	 } while(i == 0);
	 strcat(chatLoc, ".cht");
	 cout << "\nChat file is " << chatLoc << "\n";
	 //strcpy(chatLoc, chatFileName);
}
void User::showChats(User otherUser) {
	 ifstream chatFileRead(chatLoc, ios::binary);
	 Message mShow ;
	 cout << "\n";
	 if(!chatFileRead) {
		  cout << "\n\n\t\t\tNo chats\n\n\n";
	 } else {
		  while(chatFileRead.read((char*)&mShow, sizeof(mShow))) {
				//puts(mShow.name);
				cout << mShow.name << ": ";
				cout << mShow.message;
				cout << "\n";
				cout << "____________________________________________________________\n";
		  }
	 }
}
void User::openChat(User otherUser) {
	 i = 0;
	 char opt;
	 system("cls");
	 //clrscr();
	 while(i == 0) {
          system("cls");
		  //clrscr();
		  i = 1;
		  chatName(otherUser);
		  cout << "Chatting with " << otherUser.getUsername() << "\n\n";
		  showChats(otherUser);
		  cout << "\n1. Send message...\n2. Close chat\nAny key to refresh chat\n";
          opt = getch();
		  if(opt == '1') {
				ofstream chatFile(chatLoc, ios::binary|ios::app);
				cout << "\nEnter message: ";
				Message m;
				m.inputMessage();
				strcpy(m.name, getUsername());
				chatFile.write((char*)&m, sizeof(m));
				chatFile.close();
				i = 0;
		  } else if (opt == '2') {
				cout << "2";
				UI2();      //goes back
		  }
		  else {
				cout << "else";
				i = 0;
		  }
	 }
}

void login() {
	//clrscr();
	system("cls");
	cout << "\t\tWelcome to The Chat Application!";
	cout << "\n\t................................................\n";
	int f = 0;
	cout << "\nEnter your username: ";
	char enterID[20];
	gets(enterID);
	ifstream userFile(IDFile, ios::binary);
	while(userFile.read((char*)&user1, sizeof(user1))) {
		if (!strcmp(enterID, user1.getUsername())) {
			f = 1;
			break;
		}
	}
	userFile.close();
    if (f == 0) {
        cout<<"\n No such ID found!";
		cout << "\n1. Try again\n2. Sign up\n3. Go back to main menu.\n Enter your option: ";
		char option = getOption('3');
        if(option == '1') {
            login();
		} else if(option == '2') {
            signup();
		} else if(option == '3') {
            UI1();
		}
    } else {
			L1: cout << "Enter your password: ";
			char checkpass[20];
			gets(checkpass);
			if (strcmp(checkpass, user1.getPass()) == 0) {
                user1.UI2();
			} else {
                cout<<"\n --Wrong password. Please try again.--\n";
				goto L1;
			}
		}
}
void signup() {
	//clrscr();
	system("cls");
	cout<<"\nCreating new user ...\n";
	setID();
	user1.setPass();
	ofstream writeToID(IDFile, ios::binary|ios::app);
	writeToID.write((char*)&user1, sizeof(user1));
	writeToID.close();
	cout<<"\n ---Your user account has been created. Press any key to continue.---";
	getch();
	user1.UI2();
}
void setID() {
	int f = 0;
	cout<<"\nEnter a username with no special characters: ";
	user1.setUName();
	User check;
	ifstream IDfile(IDFile, ios::binary);
	while (IDfile.read((char*)&check, sizeof(check))) {
        if (!strcmpi(user1.getUsername(), check.getUsername())) {
            f = 1;
			cout<<"\n--- That username is already in use. Please try another. ---\n";
			setID();
        }
	}
	//UserNo++;
	IDfile.close();
}

char getOption(char maxNumber) {
    char num;
    num = getch();
    if(num > maxNumber) {
		  cout << "Try entering a number less than " << (maxNumber + 1);
    }
    return num;
}
int main()
{
	/*char chatFileName[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\";
	strcat(chatFileName, "IDfile.dat");
	ifstream in(chatFileName, ios::binary);
	User u;
	while(in.read((char*)&u, sizeof(u))) {
		cout  << u.getUsername() << "\n";
	}*/
	 UI1();
	 return 0;
}
void UI1()
{
    //the beginning screen
	//clrscr();
	system("cls");
	cout << "\t\tWelcome to The Chat Application!";
	cout<<"\n\t................................................\n";
	cout << "\n";
	cout << "\n   1. Login\n   2. Sign up\n   3. About \nEnter your option: ";
	char option = getOption('3');
	if(option == '1') {
        login();
	} else if (option == '2') {
        signup();
	} else if (option == '3'){
        aboutus();
	}
}
void User::UI2(){
    //logged in screen
	 //clrscr();
	 system("cls");
	 cout << "Welcome " << user1.getUsername();
	 cout<<"\n\t.............................................\n";
	 cout << "\n";
	 cout << "\n1. Start chat\n2. Log out\nEnter your option: ";
	 char option = getOption('2');
	 if (option == '1') {
		  user1.findfriend();
	 } else if (option == '2') {
		  UI1();
	 }
}

void aboutus()
{
	//clrscr();
	system("cls");
	int i=0;
	cout << "\t\tThe Chat Application!";
	cout<<"\n\t................................................\n";
    cout << "\n";
	cout<<"Mayank Jain and Pratik Anand present to you \n\tMinute Chat\nThe most breathtaking chat application you will come across. Message your colleagues over LAN and stay connected.\n";
	User u;
	ifstream onfile(IDFile, ios::binary);
	while(onfile.read((char*)&u,sizeof(u))){
        i++;
    }
	cout<<"\nCurrently there are " << i << " users on Minute Chat.";
}
