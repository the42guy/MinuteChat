import java.io.*;
import java.util.Scanner;

import static java.lang.System.*;

/**
 * Created by Pratik on 7/4/2016.
 */
public class User {
    //couple of general purpose scanners
    private Scanner s, fileReader;
    User(boolean newUser) {
        out.printf("User constructor called");
        s = new Scanner(System.in);
        if(newUser) {
            signUp();                                                                                                       //new user must want to sign up, right?
        } else {
            signIn();
        }

    }

    class Message {
        private String chatFile;
        public String name;
        private String message;
        public String getMessage() {
            return message;
        }
        public void enterMessage() {
            message = s.nextLine();
        }
        public void readMessage() {

        }
        public void sendMessage() {

        }
    }
    private String username, password, chatname;
    private static String rootLoc = "E:/MinuteChatJ/";
    private static String usernameFile = "dat/names.dat";
    private int usernameHash;

    private void signUp() {
        out.println("\n\nSign Up");
        out.print("Enter username: ");
        setUsername();
        out.print("Enter password: ");
        setPassword();
        if(writeUserFile()) {
            out.println("Successfully signed up");
            checkUserFile();
        }
    }

    private void signIn() {
        out.println("\n\nSign In");
        out.print("Enter username: ");
        String unameEntered = s.nextLine();
        if(checkUsername(unameEntered, rootLoc + usernameFile)) {
            out.print("\nEnter password: ");
            String pwordEntered = s.nextLine();
            if(checkUserEntity(unameEntered, "password", pwordEntered)) {
                out.println("True!");
            } else {
                out.println("Wrong password");
            }
        } else {
            out.println("The username doesn't exist yet.");
        }

    }

    private boolean checkUserFile() {
        boolean fileExists = false;
        File userFile = new File(rootLoc + "dat/" + getUsernameHash());
        try {
            fileReader = new Scanner(userFile);
            out.println("Reading file...");
            String uHash, pHash;
            //username, password and the contents are all string.
            uHash = fileReader.nextLine();
            pHash = fileReader.nextLine();
            if(uHash.equalsIgnoreCase("" + getUsernameHash())) {
                out.println("Username is OK: " + uHash);
            }
            if(pHash.equalsIgnoreCase("" + getPasswordHash())) {
                out.println("Password is OK: " + pHash);
            } else {
                out.println(uHash + "; " + pHash + "\n" + getUsernameHash() + "; " + getPasswordHash());
            }
        } catch (IOException e) {
            out.println("IOE: " + e.getMessage());
        }

        return fileExists;
    }

    private boolean checkUserEntity(String username, String whatToCheck, String valueOfTheChecked) {
        /**
         * @JAVADOC
         * checkUserEntity - to check, for a given username, whether the field saved in the file is the same as the 3rd argument
         * Opens up the user's file and then obtains uHash and pHash
         * Then uses switch to save the hash in whatToCheck/2nd argument
         * Then simply compares 2nd argument and 3rd argument
         * */
        boolean isItRight = false;
        if(checkUsername(username, rootLoc + usernameFile)) {
            File userFile = new File(rootLoc + "dat/" + username.hashCode());
            String uHash = "", pHash = "";
            try {
                fileReader = new Scanner(userFile);
                uHash = fileReader.nextLine();
                pHash = fileReader.nextLine();
            } catch (IOException e) {
                out.println("IOE: " + e.getMessage());
            } finally {
                switch (whatToCheck) {
                    case "username":
                        whatToCheck = uHash;
                        break;
                    case "password":
                        whatToCheck = pHash;
                        break;
                    default:
                        //I don't know...
                        break;
                }
            }
            if(whatToCheck.equalsIgnoreCase("" + valueOfTheChecked.hashCode())) {
                isItRight = true;
            }
        }
        return isItRight;
    }

    private boolean writeUserFile() {
        boolean wasSuccessful = true;
        File outputFile;
        BufferedWriter bw = null;
        try {
            outputFile = new File(rootLoc + usernameFile);
            //FileOutputStream cFile = new FileOutputStream(outputFile);
            bw = new BufferedWriter(new FileWriter(outputFile, true));  //true for append
            bw.write(getUsername());
            bw.newLine();
            bw.flush();
        } catch (FileNotFoundException e) {
            wasSuccessful = false;
            out.println("Usernames file not found!\n FileNotFoundException: " + e.getMessage());
        } catch (IOException i) {
            wasSuccessful = false;
            out.println("IOException: " + i.getMessage());
        } finally {
            if(bw != null) try {
                bw.close();
                if(wasSuccessful) {
                    File userFile = new File(rootLoc + "dat/" + getUsernameHash());
                    userFile.createNewFile();
                    bw = new BufferedWriter(new FileWriter(userFile));
                    bw.write(""+getUsernameHash());
                    bw.newLine();
                    bw.write(""+getPasswordHash());
                    bw.newLine();
                    bw.flush();
                    bw.close();
                    out.println("Wrote username and password hashes as: " + getUsernameHash() + "; " + getPasswordHash());
                }
            } catch (IOException i2) {
                //file problems...
            }
        }
        return wasSuccessful;
    }

    public int getPasswordHash() {
        return password.hashCode();
    }

    public String getUsername() {
        return username;
    }

    public int getUsernameHash() {
        return username.hashCode();
    }

    private void setPassword() {
        String password = s.nextLine();
        if(password.contains(this.getUsername())) {
            out.println("Password can not contain the username.");
            setPassword();
        } else if(password.length() < 8) {
            out.println("Password needs to be longer.");
            setPassword();
        } else {
            this.password = password;
        }
    }

    private boolean checkUsername(String usernameToCheck, String fileLocation) {
        File usernameListFile = new File(fileLocation);
        boolean found = false;
        try {
            fileReader = new Scanner(usernameListFile);
            while(fileReader.hasNextLine()) {
                if(usernameToCheck.equalsIgnoreCase(fileReader.nextLine())) {
                    found = true;
                    break;
                }
            }
        } catch (FileNotFoundException e) {
            out.printf("IO Error\nUsernames file not found\n");
            System.exit(1);
        }
        return found;
    }

    private void setUsername() {
        String username = s.nextLine();
        //String hashUser = "" + (getUsernameHash());
        File inFile;
        boolean found = false;
        /***
         * @TODO:
         * replace workflow with checkUsername()
         */

        try {
            inFile = new File(rootLoc + usernameFile);
            fileReader = new Scanner(inFile);
            while(fileReader.hasNextLine()) {
                if(username.equalsIgnoreCase(fileReader.nextLine())) {
                    found = true;
                    break;
                }
            }
            if(found) {
                out.printf("Username \"%s\" already exists.\n", username);
                setUsername();
            } else {
                out.printf("Username set as \"%s\"\n", username);
                this.username = username;
                this.usernameHash = username.hashCode();
            }
        } catch (FileNotFoundException e) {
            out.printf("IO Error\nUsernames file not found\n");
            System.exit(1);
            //e.printStackTrace();
        }
    }

    public void generateChatName(User theOtherUser) {
        int i = 0;
        String fileName = chatname;
        do {
            if (theOtherUser.getUsername().charAt(i) > this.getUsername().charAt(i)) {
                fileName += theOtherUser.getUsername() + this.getUsername();
            } else if (theOtherUser.getUsername().charAt(i) < this.getUsername().charAt(i)) {
                fileName += this.getUsername() + theOtherUser.getUsername();
            } else {
                i++;
            }
        } while (fileName.equals("MinuteChatJ\\"));
        fileName += ".chat";
        this.chatname = fileName;
        out.println(fileName);
    }

    public void showChats(User theOtherUser) {

    }
}
