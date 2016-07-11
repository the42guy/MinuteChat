#include <iostream.h> //.h
#include <fstream.h>  //.h
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>


//For school:
char IDFile[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\IDFile.dat";
char homeLoc[100] = "\\\\192.168.1.100\\student data\\prateek.a\\MC\\";
//For local:
//char IDFile[100] = "MC\\IDFile.dat";
//char homeLoc[100] = "MC\\";
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
		  char username[20];
		  char password[20];
		  void chatName(User u);
		  void showChats(User u);
		  char chatLoc[100];
	 public:
		  char* getUsername() {
				return username;
		  }
		  void setPass() {
				cout << "\n\tEnter a password without any special characters or spaces: ";
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
}user1;

void User::findfriend(){
    //system("cls");
	clrscr();
	cout << "\tWelcome "<< user1.getUsername();
	cout << "\n\t.............................................\n";
	cout << "\tSelect a person to chat with: \n";
	int i = 0, friendLoc;
	ifstream infile(IDFile, ios::binary);
	ifstream chatID(IDFile, ios::binary);
	User users, u;
	char usersList[200][20], otherUserName[20];
	while(infile.read((char*)&users, sizeof(users))) {
        if(strcmpi(users.getUsername(), user1.getUsername())) { //as long as not self
            strcpy(usersList[i], users.getUsername());
            cout << "\n\t"<< ++i << ": " << users.getUsername();
        }
	}
	cout << "\n\tEnter your choice: ";
	friendLoc = getOption('i') - 49;       //gets the original option (ASCII/int conversion)
    strcpy(otherUserName, usersList[friendLoc]);
    //cout << "\n" << friendLoc << otherUserName; //debug message
    while(chatID.read((char*)&u, sizeof(u))) {
        if(!strcmpi(otherUserName, u.getUsername())) {
            //cout << u.getUsername();  //debug message
            break;
        }
	}
	infile.close();
	chatID.close();
	openChat(u);
}

void User::chatName(User otherUser) {
	 int namePos = 0;
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
	 //cout << "\nChat file is " << chatLoc << "\n";  //debug message
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
				cout << "\t" << mShow.message;
				cout << "\n";
				cout << "\t__________________________________________________________\n";
		  }
	 }
}
void User::openChat(User otherUser) {
	 i = 0;
	 char opt;
	 //system("cls");
	 clrscr();
	 while(i == 0) {
          //system("cls");
		  clrscr();
		  i = 1;
		  chatName(otherUser);
		  cout << "\tYou're chatting with " << otherUser.getUsername() << "\n\n";
		  showChats(otherUser);
		  cout << "\n\t1. Send message...\n\t2. Close chat\n\tAny key to refresh chat\n";
          opt = getch();
		  if(opt == '1') {
				ofstream chatFile(chatLoc, ios::binary|ios::app);
				cout << "\n\tEnter message: ";
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
				i = 0;
		  }
	 }
}

void login() {
	clrscr();
	//system("cls");
	cout << "\tLogging in...\n\n";
	int f = 0;
	cout << "\n\tEnter your username: ";
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
        cout<<"\nNo such username found!";
		cout << "\n\t1. Try again\n\t2. Sign up\n\t3. Go back to main menu.\n\tEnter your option: ";
		char option = getOption('3');
        if(option == '1') {
            login();
		} else if(option == '2') {
            signup();
		} else if(option == '3') {
            UI1();
		}
    } else {
			L1: cout << "\tEnter your password: ";
			char checkpass[20];
			gets(checkpass);
			if (strcmp(checkpass, user1.getPass()) == 0) {
                user1.UI2();
			} else {
                cout<<"\n\tWrong password. Please try again.\n";
				goto L1;
			}
		}
}
void signup() {
	clrscr();
	//system("cls");
	cout<<"\n\tCreating a new user...\n\n";
	setID();
	user1.setPass();
	ofstream writeToID(IDFile, ios::binary|ios::app);
	writeToID.write((char*)&user1, sizeof(user1));
	writeToID.close();
	cout<<"\n\tYour user account has been created! Press any key to continue.";
	getch();
	user1.UI2();
}
void setID() {
	int f = 0;
	cout<<"\n\tEnter a username with no special characters: ";
	user1.setUName();
	User check;
	ifstream IDfile(IDFile, ios::binary);
	while (IDfile.read((char*)&check, sizeof(check))) {
        if (!strcmpi(user1.getUsername(), check.getUsername())) {
            f = 1;
			cout<<"\n\tThat username is already in use! Please try another.\n";
			setID();
        }
	}
	IDfile.close();
}

char getOption(char maxNumber) {
    char num;
    num = getch();
    if(num > maxNumber) {
		  cout << "\tTry entering a number less than " << (maxNumber + 1);
    }
    return num;
}
int main()
{
	 UI1();
	 return 0;
}
void UI1()
{
    //the beginning screen
	clrscr();
	//system("cls");
	cout << "\t\t\t\tWelcome to Minute Chat!";
	cout<<"\n\t....................................................................\n";
	cout << "\n";
	cout << "\n\t1. Login\n\t2. Sign up\n\t3. About \n\tEnter your option: ";
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
	 clrscr();
	 //system("cls");
	 cout << "\tWelcome " << user1.getUsername();
	 cout<<"\n\t.............................................\n";
	 cout << "\n";
	 cout << "\n\t1. Start chat\n\t2. Log out\n\tEnter your option: ";
	 char option = getOption('2');
	 if (option == '1') {
		  user1.findfriend();
	 } else if (option == '2') {
		  UI1();
	 }
}

void aboutus()
{
	clrscr();
	//system("cls");
	int i=0;
	cout << "\t\t\t\tMinute Chat";
	cout << "\n\t........................................................\n";
    cout << "\n";
	cout << "\tMayank Jain and Pratik Anand present ";
	cout << "\n\t.  . .-. . . . . .-. .-. .-. . . .-. .-. ";
	cout << "\n\t|\\/|  |  |\\| | |  |  |-  |   |-| |-|  |  ";
	cout << "\n\t'  ` `-' ' ` `-'  '  `-' `-' ' ` ` '  ' ";
	cout << "\n\tThe most breathtaking chat application you will come across. \n\tMessage your colleagues over LAN and stay connected.\n";
	User u;
	ifstream onfile(IDFile, ios::binary);
	while(onfile.read((char*)&u, sizeof(u))){
        i++;
    }
	cout<<"\n\tWe've connected " << i << " users with Minute Chat.";
}
