import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;
import java.io.*;
public class Loginstate extends LibState implements ActionListener{
  private static final int CLERK_LOGIN = 0;
  private static final int USER_LOGIN = 1;
  private static final int EXIT = 2;
  private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));  
  private LibContext context;
  private JFrame frame;
  private static Loginstate instance;
  private AbstractButton userButton, clerkButton, logoutButton;
  private Loginstate() {
      super();
      userButton = new JButton("user");
      clerkButton = ClerkButton.instance();
      logoutButton = new JButton("logout");
      userButton.addActionListener(this);
      logoutButton.addActionListener(this);
      ClerkButton.instance().setListener();
  }

  public static Loginstate instance() {
    if (instance == null) {
      instance = new Loginstate();
    }
    return instance;
  }

  public void actionPerformed(ActionEvent event) {
    if (event.getSource().equals(this.userButton)) 
       {//System.out.println("user \n"); 
         this.user();}
    else if (event.getSource().equals(this.logoutButton)) 
       (LibContext.instance()).changeState(2);
  } 

 

  public void clear() { //clean up stuff
    frame.getContentPane().removeAll();
    frame.paint(frame.getGraphics());   
  }  


  private void user(){
    String userID = JOptionPane.showInputDialog(
                     frame,"Please input the user id: ");
    if (Library.instance().searchMembership(userID) != null){
      (LibContext.instance()).setLogin(LibContext.IsUser);
      (LibContext.instance()).setUser(userID);  
       clear();
      (LibContext.instance()).changeState(1);
    }
    else 
      JOptionPane.showMessageDialog(frame,"Invalid user id.");
  } 


  public void run() {
   
   frame = LibContext.instance().getFrame();
   frame.getContentPane().removeAll();
   frame.getContentPane().setLayout(new FlowLayout());
   frame.getContentPane().add(this.userButton);
   frame.getContentPane().add(this.clerkButton);
   frame.getContentPane().add(this.logoutButton);
   frame.setVisible(true);
   frame.paint(frame.getGraphics()); 
  }
}
