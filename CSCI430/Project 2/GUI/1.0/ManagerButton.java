import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;
import java.io.*;
public class ManagerButton extends JButton implements ActionListener{
    private static ManagerButton instance;

    private ManagerButton() {
        super("Manager");
    }

    public static ManagerButton instance() {
        if (instance == null) {
            instance = new ManagerButton();
        }
        return instance;
    }

    public void setListener(){
        //System.out.println("In clerkButton setListener\n");
        this.addActionListener(this);
    }

    public void actionPerformed(ActionEvent event) {
        //System.out.println("In clerk \n");
        (WarehouseContext.instance()).setLogin(WarehouseContext.IsManager);
        LoginState.instance().clear();
        (WarehouseContext.instance()).changeState(2);
    }
}