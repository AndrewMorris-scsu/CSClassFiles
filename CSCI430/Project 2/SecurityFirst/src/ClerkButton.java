import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;
import java.io.*;
public class ClerkButton extends JButton implements ActionListener{
    private static ClerkButton instance;
    private JButton userButton, clerkButton, logoutButton;
    private ClerkButton() {
        super("Clerk");
    }

    public static ClerkButton instance() {
        if (instance == null) {
            instance = new ClerkButton();
        }
        return instance;
    }

    public void setListener(){
        //System.out.println("In clerkButton setListener\n");
        this.addActionListener(this);
    }

    public void actionPerformed(ActionEvent event) {
        //System.out.println("In clerk \n");
        Security security = new Security();
        security.doShit();
        security.validate(0);
        (WarehouseContext.instance()).setLogin(WarehouseContext.IsClerk);
        LoginState.instance().clear();
        (WarehouseContext.instance()).changeState(1);
    }
}