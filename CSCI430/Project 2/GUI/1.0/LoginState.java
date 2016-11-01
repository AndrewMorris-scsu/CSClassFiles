/**
 * Created by Jared on 3/20/2016.
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.text.*;
import java.io.*;
public class LoginState extends WarehouseState implements ActionListener {
    private static final int CLIENT_LOGIN = 0;
    private static final int CLERK_LOGIN = 1;
    private static final int MANAGER_LOGIN = 2;
    private static final int EXIT = 3;
    private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private WarehouseContext context;
    private static LoginState instance;
    //For GUI
    private JFrame frame;
    private AbstractButton clientButton, clerkButton, managerButton, logoutButton;

    private LoginState() {
        super();

        clientButton = ClientButton.instance();
        clerkButton = ClerkButton.instance();
        managerButton = ManagerButton.instance();
        logoutButton = new JButton("logout");

        logoutButton.addActionListener(this);
        ClerkButton.instance().setListener();
        ClientButton.instance().setListener();
        ManagerButton.instance().setListener();

        // context = WarehouseContext.instance();
    }
    public void actionPerformed(ActionEvent event) {
        if (event.getSource().equals(this.clientButton))
        {//System.out.println("user \n");
            this.client();
        } else if ( event.getSource().equals(this.clerkButton) ) {
            this.clerk();
        } else if (event.getSource().equals(this.managerButton) ){
            this.manager();
        } else {
            (WarehouseContext.instance()).changeState(3);
        }

    }

    public void clear() { //clean up stuff
        frame.getContentPane().removeAll();
        frame.paint(frame.getGraphics());
    }

    public static LoginState instance() {
        if (instance == null) {
            instance = new LoginState();
        }
        return instance;
    }

    public int getCommand() {
        do {
            try {
                int value = Integer.parseInt(getToken("Enter command:" ));
                if (value <= EXIT && value >= CLIENT_LOGIN) {
                    return value;
                }
            } catch (NumberFormatException nfe) {
                System.out.println("Enter a number");
            }
        } while (true);
    }

    public String getToken(String prompt) {
        do {
            try {
                System.out.println(prompt);
                String line = reader.readLine();
                StringTokenizer tokenizer = new StringTokenizer(line,"\n\r\f");
                if (tokenizer.hasMoreTokens()) {
                    return tokenizer.nextToken();
                }
            } catch (IOException ioe) {
                System.exit(0);
            }
        } while (true);
    }

    private boolean yesOrNo(String prompt) {
        String more = getToken(prompt + " (Y|y)[es] or anything else for no");
        if (more.charAt(0) != 'y' && more.charAt(0) != 'Y') {
            return false;
        }
        return true;
    }

    private void client(){
        String clientID = getToken("Please input the client id: ");
        if (Warehouse.instance().searchForClient(clientID) != null) {
            (WarehouseContext.instance()).setLogin(WarehouseContext.IsClient);
            (WarehouseContext.instance()).setClient(clientID);
            (WarehouseContext.instance()).changeState(0);
        }
    }

    private void clerk(){
        (WarehouseContext.instance()).setLogin(WarehouseContext.IsClerk);
        (WarehouseContext.instance()).changeState(1);
    }

    private void manager(){
        (WarehouseContext.instance()).setLogin(WarehouseContext.IsManager);
        (WarehouseContext.instance()).changeState(2);
    }

    public void process() {
        int command;
        System.out.println(
                "Please input:\n" +
                        "0: to login as Client\n"+
                        "1: to login as Clerk\n" +
                        "2: to login as Manager\n" +
                        "3: to exit the system\n");

        while ((command = getCommand()) != EXIT) {

            switch (command) {
                case CLIENT_LOGIN:       client();
                    break;
                case CLERK_LOGIN:        clerk();
                    break;
                case MANAGER_LOGIN:      manager();
                    break;
                default:                System.out.println("Invalid choice");

            }
            System.out.println(
                    "Please input:\n" +
                            "0: to login as Client\n"+
                            "1: to login as Clerk\n" +
                            "2: to login as Manager\n" +
                            "3: to exit the system\n"
            );
        }
        (WarehouseContext.instance()).changeState(3);
    }

    public void run() {
        //process();
        frame = WarehouseContext.instance().getFrame();
        frame.getContentPane().removeAll();
        frame.getContentPane().setLayout(new FlowLayout());
        frame.getContentPane().add(this.clientButton);
        frame.getContentPane().add(this.clerkButton);
        frame.getContentPane().add(this.managerButton);
        frame.getContentPane().add(this.logoutButton);
        frame.setVisible(true);
        frame.paint(frame.getGraphics());
        System.out.println("In login state");
    }
}

