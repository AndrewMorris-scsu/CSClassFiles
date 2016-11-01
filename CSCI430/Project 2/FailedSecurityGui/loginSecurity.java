/**
 * Created by Jared on 4/12/2016.
 */
import javax.swing.*;
import java.awt.*;
import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;

public class loginSecurity {
    private static Warehouse warehouse;
    private static WarehouseContext warehouseContext;
    public static JButton submit;
    public static JTextField username;
    public static JTextField password;
    public static JFormattedTextField invalidUsername;
    public static JFormattedTextField invalidPassword;


    public AbstractButton btnLogin;
    private String pass, user;

    public loginSecurity() {
        warehouse = Warehouse.instance();
        System.out.println("loginSecurity constructor");
        //submit = new JButton("submit");
        //username = new JTextField("username", 10);
        //password = new JTextField("password", 10);
        //invalidUsername = new JFormattedTextField("invalid Username");
        //invalidPassword = new JFormattedTextField("invalid Password");
        //btnLogin = new JButton();
        //btnLogin.addActionListener(this);

    }
    public String getUser(){
        return user;
    }


    public void validateLogin(int loginType){

        Client client;
        System.out.println("login validation");

        if (loginType == 0){
            client = warehouse.searchForClient(user);
            if (client == null){
                System.out.println("Invalid client");
            }
        }

        else if (loginType == 1) {
            if (user != "salesclerk" || pass != "salesclerk") {
                System.out.println("Invalid clerk");
            }
        }
        else if (loginType == 2){
            if (user != "manager" || pass != "manager"){
                System.out.println("Invalid manager");
            }

        }
    }

    public void doShit(){
        JFrame frame = new JFrame("Login");
        final JButton btnLogin = new JButton("Click to login");
        final JTextField username = new JTextField("username", 10);
        final JTextField password = new JTextField("password", 10);


        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 100);
        frame.setLayout(new FlowLayout());

        frame.getContentPane().add(username);
        frame.getContentPane().add(password);
        frame.getContentPane().add(btnLogin);

        frame.setVisible(true);
        btnLogin.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("Got the submit login!");
                System.out.println("Username = "+ username.getText());
                System.out.println("Password = "+ password.getText());
                user = username.getText();
                pass = password.getText();

                if (WarehouseContext.instance().currentState() == WarehouseContext.IsManager ) {
                    validateLogin(2);
                } else if (WarehouseContext.instance().currentState() == WarehouseContext.IsClerk) {
                    validateLogin(1);
                } else if (WarehouseContext.instance().currentState() == WarehouseContext.IsClient) {
                    validateLogin(0);
                }
                System.out.println("Before Clear()");
                //clear();
                System.out.println("Before dispose()");
                frame.dispose();
            }
        });



    }


}