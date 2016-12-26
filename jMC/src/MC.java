/**
 * Created by Pratik on 9/13/2016.
 */
public class MC {
    public static void main(String[] args) {
        IO io = new IO();
        User u = new User("qwerty22623", "passwordfdfd");
        System.out.printf("\nUser sign up success: %s\n" , io.signUp(u));
        System.out.printf("\nUser sign in success: %s\n" , io.signIn(u));
    }
}
