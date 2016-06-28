#include <iostream> //.h
#include <fstream>  //.h
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>

using namespace std;
class Message {            //each message class contains name of sender and the message
	 public:
        char *name, message[500];
};

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
		  void openChat(User u);
};
//char* User::chatName(User otherUser) { //fn generates chat name in descending order of the usernames      /***/
void User::chatName(User otherUser) {
	 int namePos = 0;
	 //char* chatFileName/*[100]*/ = "E:\\MinuteChat\\Chats\\";
	 char chatFileName[100] = "MinuteChat\\";
	 //cout << "Thinking about the file location..." << chatFileName;
	 i = 0;
	 char c1[20], c2[20];
	 strcpy(c1, getUsername());
	 strcpy(c2, otherUser.getUsername());
	 int nameLen = strlen(getUsername()) + strlen(otherUser.getUsername()) + strlen(chatFileName);
	 //cout << "\nCopied names as " << c1 << c2;
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
	 strcat(chatFileName, ".chat");
	 chatFileName[nameLen] = '\0';
	 cout << "\nChat file is " << chatFileName << "\n";
	 strcpy(chatLoc, chatFileName);
	 //return chatFileName;
}
void User::showChats(User otherUser, char* loc) {
	 ifstream chatFileRead(loc, ios::binary);
	 Message mShow ;
	 cout << "\n";
	 if(!chatFileRead) {
		  cout << "\n\n\t\t\tNo chats\n\n\n";
	 } else {
		  while(chatFileRead.read((char*)&mShow, sizeof(mShow))) {
				cout << mShow.name << ": ";
				cout << mShow.message;
				cout << "\n";
				cout << "_______________________________________________________\n";
		  }
	 }

}
void User::openChat(User otherUser) {
	 i = 0;
	 char opt;
	 system("cls");
	 //clrscr();
	 while(i == 0) {
		  i = 1;
		  chatName(otherUser);
		  //char* location = chatName(otherUser);
		  cout << "Chatting with " << otherUser.getUsername() << "\n\n";
		  showChats(otherUser, chatLoc);
		  cout << "\n1. Send message...\n2. Close chat\nAny key to refresh chat\n";
		  //getch();
		  cin.get(opt);
		  //getch();
		  //i = 1;
		  if(opt == '1') {
				ofstream chatFile(chatLoc, ios::binary|ios::app);
				cout << "\nEnter message: ";
				Message m;
				cin >> m.message;
				m.name = getUsername();
				chatFile.write((char*)&m, sizeof(m));
				chatFile.close();
				i = 0;
		  } else if (opt == '2') {
				cout << "2";
				//the chat list
		  } else if (opt == '3') {
				cout << "3";
				i = 1;
		  }
		  else {
				cout << "else";
				i = 0;
		  }
	 }

}

class Chat {
};


void login() {

}
void signup() {
}
int getOption(int maxNumber) {
    int num;
    cin >> num;
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
    /*int option = getOption(2);
    if(option == 1) {
        login();
    } else if(option == 2) {
        signup();
    }*/
    User u1, u2;
	 u1.setUName();

	 u1.setPass();
	 u2.setUName();
	 u2.setPass();
	 u1.openChat(u2);
    return 0;
}
