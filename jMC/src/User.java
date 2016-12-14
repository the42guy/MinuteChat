import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;
import static java.lang.System.out;

/**
 * Created by Pratik on 9/13/2016.
 */
public class User {
    //couple of general purpose scanners
    private Scanner s, fileReader;


    User() {

    }
    User(String username, String password) {                                                    //so that empty users can be created to deal with IO checks/sign ups etc
        this.username = username;
        this.password = password;
        unique = false;
    }

    private String username, password, chatname;
    boolean unique;                                         //used to check whether the user is a file loaded (true) or a temp (false)
    private static String rootLoc = "E:/MinuteChatJ/";
    private static String usernameFile = "dat/names.dat";
    private int usernameHash;
    ArrayList<User> chatters = new ArrayList<User>();

    abstract class Message {
        /**
         * @JAVADOC
         * Abstract class to let the user enter the message, provide name and then send it to the other user.
         * Conversely, also lets the user to read message by giving a name.
         * */
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
            File f = null;
            try {
                f = new File(chatFile);
                BufferedWriter b = new BufferedWriter(new FileWriter(f, true));
                b.newLine();
                b.write(message);
                b.flush();
                b.close();
            } catch (IOException e) {
                out.println("User chat file IO error");
            }
        }
        public void clear() {
            this.name = null;
            this.chatFile = null;
        }
    }


    /*private void signUp() {
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
            this.username = unameEntered;
            out.print("\nEnter password: ");
            String pwordEntered = s.nextLine();
            if(checkUserProperty(unameEntered, "password", pwordEntered)) {
                out.println("True!");
                loggedIn();
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
    }*/

    /*private boolean checkUserProperty(String username, String whatToCheck, String valueOfTheChecked) {
        /**
         * @JAVADOC
         * checkUserProperty - to check, for a given username, whether the field saved in the file is the same as the 3rd argument
         * Opens up the user's file and then obtains uHash and pHash
         * Then uses switch to save the hash in whatToCheck/2nd argument
         * Then simply compares 2nd argument and 3rd argument
         * */
        /*boolean isItRight = false;
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
                        //I don't know... An exception to throw?
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
            outputFile = new File(rootLoc + usernameFile);                      //adds username to the username file
            //FileOutputStream cFile = new FileOutputStream(outputFile);
            bw = new BufferedWriter(new FileWriter(outputFile, true));          //true for append
            bw.newLine();
            bw.write(getUsername());
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
    }*/

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
        boolean found = false;
        found = checkUsername(username, rootLoc + usernameFile);
        if(found) {
            out.printf("Username \"%s\" already exists.\n", username);
            setUsername();
        } else {
            out.printf("Username set as \"%s\"\n", username);
            this.username = username;
            this.usernameHash = username.hashCode();
        }
    }
}
