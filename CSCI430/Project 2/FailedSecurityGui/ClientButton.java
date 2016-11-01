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

        System.out.println("Clicked Client Button");
        loginSecurity security = new loginSecurity();
        if (security == null){
            System.out.println("security object creation FAILED");
        }
        LoginState.instance().clear();
        security.doShit();

        (WarehouseContext.instance()).setLogin(WarehouseContext.IsClient);
        LoginState.instance().clear();
        (WarehouseContext.instance()).setClient(security.getUser());
        System.out.println("About to change state");
        (WarehouseContext.instance()).changeState(0);
    }
}