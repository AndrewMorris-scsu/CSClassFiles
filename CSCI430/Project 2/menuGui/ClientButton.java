import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;
import java.io.*;
public class ClientButton extends JButton implements ActionListener{
    private static ClientButton instance;

    private ClientButton() {
        super("Client");
    }

    public static ClientButton instance() {
        if (instance == null) {
            instance = new ClientButton();
        }
        return instance;
    }

    public void setListener(){
        //System.out.println("In clientButton setListener\n");
        this.addActionListener(this);
    }

    public void actionPerformed(ActionEvent event) {
        //System.out.println("In client \n");
        (WarehouseContext.instance()).setLogin(WarehouseContext.IsClient);
        LoginState.instance().clear();
        (WarehouseContext.instance()).changeState(0);
    }
}