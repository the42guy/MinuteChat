import java.io.*;
import java.util.Scanner;
import static java.lang.System.out;

/**
 * Created by Pratik on 20-Oct-16.
 */
public class IO {
    private static String rootLocation = "E:/MinuteChatJ/";
    private static String chatLocation = "chat/";
    private static String dataLocation = "dat/";
    private File usersListFile;
    private RandomAccessFile usersFileRAF;
    IO() {
        usersListFile = new File(rootLocation + dataLocation + "names.dat");
        try{
            if(usersListFile.exists()) {
                out.printf("\nOkay to go, user list file exists!\n");
                usersFileRAF = new RandomAccessFile(usersListFile, "rw");
            } else {
                out.printf("\nUser list file does not exists!");
                System.exit(1);
            }
        } catch(FileNotFoundException f) {
            out.printf("\nFileNotFoundException: %s", f.getMessage());
        }
    }
    boolean isEmpty(String s) {
        boolean empty = true;
        if((s.equalsIgnoreCase("")) || (s == null)) {
            empty = false;
        }
        return empty;
    }
    IO(String rootLocation, String chatLocation, String dataLocation) {
        this.rootLocation = isEmpty(rootLocation) ? this.rootLocation : rootLocation;
        this.chatLocation = isEmpty(chatLocation) ? this.chatLocation : chatLocation;
        this.dataLocation = isEmpty(dataLocation) ? this.dataLocation : dataLocation;
        usersListFile = new File(rootLocation + dataLocation + "names.dat");
        try{
            Scanner usersFileScanner = new Scanner(usersListFile);
        } catch(FileNotFoundException f) {
            out.printf("\nFileNotFoundException: %s", f.getMessage());
        }
    }

    private boolean userExists(User u) {
        boolean exists = false;
        User u2;
        try {
            usersFileRAF.seek(0);
            while((usersFileRAF.length() > usersFileRAF.getFilePointer()) && (!exists)) {
                if(u.getUsername().equalsIgnoreCase(usersFileRAF.readLine())) {
                    exists = true;
                }
            }
        } catch (IOException e) {
            out.printf("\nIOException: &s", e.getMessage());
        }

        return exists;
    }

    public boolean signIn(User u) {
        boolean success = false;
        if(!u.unique) {         //a newly created user
            out.printf("\nAtleast the user is unique");
            if(userExists(u)) {
                out.printf("\nAtleast the user exists");
                try {
                    File userFile = new File(rootLocation + dataLocation + u.getUsernameHash());
                    Scanner s = new Scanner(userFile);
                    int i = 0;
                    String s1, s2, hashNeeded;
                    hashNeeded = u.getUsernameHash() + u.getPasswordHash() + "";
                    hashNeeded = hashNeeded.hashCode() + "";
                    s1 = s.nextLine();
                    s2 = s.nextLine();
                    out.printf("\nChecking the user file for \n%s vs %s\n%s vs %s\n", u.getUsername(), s1, hashNeeded, s2);
                    if((s1.equals(u.getUsername())) && (s2.equals(hashNeeded))) {
                        success = true;
                    }
                } catch (FileNotFoundException f) {
                    out.printf("\nFileNotFoundException: %s", f.getMessage());
                }
            }
        } else {
            out.printf("\nWhat if the user is unique, that is a pre-existing user?");
        }
        return success;
    }

    public boolean signUp(User u) {
        boolean success = false;
        if(!u.unique) {         //a newly created user
            if(userExists(u)) {
                out.printf("\nUser exists!");
            } else {
                try {
                    //Write username to the list
                    BufferedWriter bw = new BufferedWriter(new FileWriter(usersListFile, true));
                    bw.newLine();
                    bw.write(u.getUsername());
                    bw.flush();
                    bw.close();
                    //Generate user file and put in the basic information
                    File userFile = new File(rootLocation + dataLocation + u.getUsernameHash());
                    userFile.createNewFile();
                    BufferedWriter userWriter = new BufferedWriter(new FileWriter(userFile));
                    userWriter.write(u.getUsername());
                    userWriter.newLine();
                    String data = u.getUsernameHash() + u.getPasswordHash() + "";
                    data = data.hashCode() + "";
                    userWriter.write(data);
                    userWriter.flush();
                    userWriter.close();
                    out.printf("\nWriting the following to the user file: \n%s\n%s", u.getUsername(), data);
                    //...and it was all successful
                    success = true;
                } catch(IOException e) {
                    out.printf("\nIOException: %s", e.getMessage());
                }
            }
        } else {
            out.printf("\nWhat if the user is unique, that is a pre-existing user?");
        }
        return success;
    }

    private void updateUserFile() {
        //invoked after new chat or just before logout?
    }

    public String generateChatName(User u1, User u2) {
        int i = 0;
        String fileName = "";
        do {
            if (u2.getUsername().charAt(i) > u1.getUsername().charAt(i)) {
                fileName += u2.getUsername() + u1.getUsername();
            } else if (u2.getUsername().charAt(i) < u1.getUsername().charAt(i)) {
                fileName += u1.getUsername() + u2.getUsername();
            } else {
                i++;
            }
        } while (fileName.equals(""));
        fileName += ".chat";
        return fileName;
    }
}
