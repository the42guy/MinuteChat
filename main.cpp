#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;
struct Message {            //each message struct contains name of sender and the message
    char* name, message;
};

class User {
    private:
        int i;      //general purpose to avoid errors for redeclaration in loops - after all the alphabet has only 26 characters
        //Message m;
        char username[20];
        char password[20];
        char* chatName(User u);     //fn generates chat name in descending order of the usernames
        void showChats(User u, char* c);
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
char* User::chatName(User otherUser) { //fn generates chat name in descending order of the usernames
    int namePos = 0;
    char chatFileName[100] = "E:\\MinuteChat\\Chats\\";
    //cout << "Thinking about the file location..." << chatFileName;
    i = 0;
    char c1[20], c2[20];
    strcpy(c1, getUsername());
    strcpy(c2, otherUser.getUsername());
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
    cout << "\nChat file is " << chatFileName << "\n";
    return chatFileName;
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
            cout << "_______________________________________________________";
        }
    }

}
void User::openChat(User otherUser) {
    i = 0;
    system("cls");
    while(i == 0) {
        i = 1;
        char* location = chatName(otherUser);
        cout << "Chatting with " << otherUser.getUsername() << "\n\n";
        showChats(otherUser, location);
        cout << "\n1. Send message...\n2. Close chat\nAny key to refresh chat";
        int opt;
        cin >> opt;
        //i = 1;
        if(opt == 1) {
            ofstream chatFile(chatName(otherUser), (ios::binary|ios::app));
            cout << "\nEnter message: ";
            Message m;
            cin >> m.message;
            m.name = getUsername();
            chatFile.write((char*)&m, sizeof(m));
            chatFile.close();
            i = 0;
        } else if (opt == 2) {
            //the chat list
        } else {
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
        cout << "Try entering a number less than " << maxNumber + 1;
    } else {
        return num;
    }
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
