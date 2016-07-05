#include <iostream> //.h
#include <fstream>  //.h
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>

using namespace std;
class Message {            //each message class contains name of sender and the message
	 public:
		  char name[20], message[2048];
		  void inputMessage() {
				//scanf("%499s", message);
				gets(message);
		  }
};

char userListLocation[100] = "MinuteChat\\users\\list"; //local
//char userList[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\users\\list"; //school

class User {
	 private:
        int i;      //general purpose to avoid errors for redeclaration in loops - after all the alphabet has only 26 characters
		  //Message m;
		  char username[20];
		  char password[20];
		  //char* chatName(User u);     //fn generates chat name in descending order of the usernames
		  void chatName(User u);
		  void showChats(User u, char* c);
		  char chatLoc[100];
	 public:
	     char passToCheck[20];
		  char* getUsername() {
				return username;
		  };
		  void setUName() {
				cout << "\nEnter a username without any special characters or spaces: ";
				gets(username);
		  }
		  void setPass() {
				cout << "\nEnter a password without any special characters or spaces: ";
				gets(password);
		  }
		  int verifyPassword();
		  void openChat(User u);
		  void userArea();
};
int User::verifyPassword() {
    int pM = 0;     //int passwordMatch
    if(strcmpi(passToCheck, password) == 0) {
        pM = 2;
    }
    return pM;
}
void User::chatName(User otherUser) {
	 int namePos = 0;
	 char chatFileName[100] = "MinuteChat\\"; //local
	 //char chatFileName[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\"; //school
	 //cout << "Thinking about the file location..." << chatFileName;
	 i = 0;
	 char c1[20], c2[20];
	 strcpy(c1, getUsername());
	 strcpy(c2, otherUser.getUsername());
	 int nameLen = strlen(getUsername()) + strlen(otherUser.getUsername()) + strlen(chatFileName);
	 do {
		  if(c1[namePos] > c2[namePos]) {
				strcat(chatFileName, getUsername());
				strcat(chatFileName, otherUser.getUsername());
				i = 1;
		  } else if (c2[namePos] > c1[namePos]) {
				strcat(chatFileName, otherUser.getUsername());
				strcat(chatFileName, getUsername());
				i = 1;
		  } else {
				namePos++;
		  }
	 } while(i == 0);
	 strcat(chatFileName, ".cht");
	 cout << "\nChat file is " << chatFileName << "\n";
	 strcpy(chatLoc, chatFileName);
}
void User::showChats(User otherUser, char* loc) {
	 ifstream chatFileRead(loc, ios::binary);
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
void User::userArea() {
    system("cls");
    //clrscr();
    //write here!
    /**
    Code here
    Write a function to read the text file at userListLocation, and display each username, except my own.
    Then link each username to a number and that's it.

    */

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
		  //char* location = chatName(otherUser);
		  cout << "Chatting with " << otherUser.getUsername() << "\n\n";
		  showChats(otherUser, chatLoc);
		  cout << "\n1. Send message...\n2. Close chat\nAny key to refresh chat\n";
          opt = getch();
		  //i = 1;
		  if(opt == '1') {
				ofstream chatFile(chatLoc, ios::binary|ios::app);
				cout << "\nEnter message: ";
				Message m;
				m.inputMessage();
				//cin >> m.message;
				strcpy(m.name, getUsername());
				chatFile.write((char*)&m, sizeof(m));
				chatFile.close();
				i = 0;
		  } else if (opt == '2') {
				cout << "2";
				userArea();
		  }
		  else {
				cout << "else";
				i = 0;
		  }
	 }
}


void login() {
    system("cls");
    //clrscr();
    cout << "Enter your username: ";
    char name[20], uName[20], pass[20];
    gets(uName);
    User u;
    int j = 0;
    ifstream usersListFile(userListLocation);
    while((usersListFile.getline(name, 100, '\n')) && (j == 0)) {
        if(strcmpi(name, uName) == 0) {
            j = 1;
            cout << "Found matching " << name << " with " << uName;
            break;
        }
    }
    if(j == 0) {
        cout << "\nInvalid username, press any key to try again!";
        getch();
        login();
    } else {
        cout << "\nEnter password: ";
        gets(pass);
        char userFileLocation[100] = "MinuteChat\\users\\"; //local
        //char userFile[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\users\\"; //school
        User u;
        strcat(userFileLocation, uName);
        strcat(userFileLocation, ".usr");
        ifstream userFile(userFileLocation, ios::binary);
        userFile.read((char *)&u, sizeof(u));
        strcpy(u.passToCheck, pass);
        if(u.verifyPassword()) {
            cout << "Entering user area...";
            //user logged in, show chat list...
        }
    }
}
void signup() {
    User q;
    q.setUName();
    char name[20];
    int j = 0;
    ifstream usersListFile(userListLocation);
    while((usersListFile.getline(name, 100, '\n')) && (j == 0)) {
        if(strcmpi(name, q.getUsername()) == 0) {
            j = 1;
            cout << "Found existing user with name " << name;
            cout << "\nPress any key to retry";
            getch();
            signup();
        }
    }
    if(j == 0) {
        q.setPass();
        ofstream usersFile(userListLocation, ios::app);
        usersFile << q.getUsername() << "\n";
        char userFileLocation[100] = "MinuteChat\\users\\"; //local
        //char userFile[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\users\\"; //school
        strcat(userFileLocation, q.getUsername());
        strcat(userFileLocation, ".usr");
        ofstream newUserFile(userFileLocation, ios::binary);
        newUserFile.write((char*)&q, sizeof(q));
        newUserFile.close();
    }
}
char getOption(char maxNumber) {
    char num;
    num = getch();
    if(num > maxNumber) {
		  cout << "Try entering a number less than " << (maxNumber + 1);
    } else {
		  //return num;
	 }
	 return num;
}
int main()
{
	 cout << "Welcome to The Chat Application!";
	 cout << "\n";
	 cout << "\n1. Login\n2.Sign up\nEnter your option: ";
    char option = getOption('2');
    if(option == '1') {
        cout << "Logging in...";
        login();
    } else if(option == '2') {
        cout << "Signing up...";
        signup();
    }
	 User u1, u2;
	 /*u1.setUName();
	 u1.setPass();
	 u2.setUName();
	 u2.setPass();
	 u1.openChat(u2);*/
    return 0;
}
