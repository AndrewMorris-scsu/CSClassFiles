/**
     * Created by Jared on 4/12/2016.
     */
    import javax.swing.*;
    import java.awt.*;
    import java.awt.FlowLayout;
    import java.awt.event.ActionListener;
    import java.awt.event.ActionEvent;
    import javax.swing.JFrame;

    public class Security{

        private static Warehouse warehouse;
        private static WarehouseContext warehouseContext;
        public static JButton submit;
        public static JTextField username;
        public static JTextField password;
        public static JFormattedTextField invalidUsername;
        public static JFormattedTextField invalidPassword;

        private JFrame frame;

        private String pass, user;

        public Security() {
            warehouse = Warehouse.instance();

            submit = new JButton("submit");
            username = new JTextField("username", 10);
            password = new JTextField("password", 10);
            invalidUsername = new JFormattedTextField("invalid Username");
            invalidPassword = new JFormattedTextField("invalid Password");

        }

    public void validate(int loginType){

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
        public void clear() { //clean up stuff
            frame.getContentPane().removeAll();
            frame.paint(frame.getGraphics());
        }
    public void doShit(){
        /*
        setLayout(new FlowLayout());
        Container c = .getContentPane();
        c.setSize(400,400);
        c.setLocation(400, 400);
        c.removeAll();
        c.add(username);
        c.add(password);
        c.setVisible(true);
        c.paint(c.getGraphics());
        */
        //LoginState.instance().clear();
        //frame = WarehouseContext.instance().getFrame();
        System.out.println("In the run method of Security class. Where is the pane!!?!?!?!?!?!?!!?!?!??!?!?!?!?!??!?!");
 /*       frame = new JFrame();
        frame.setSize(400,400);
        frame.setLocation(400, 400);

        frame.getContentPane().removeAll();
        frame.getContentPane().setLayout(new FlowLayout());
        frame.getContentPane().add(username);
        frame.getContentPane().add(password);
        frame.setVisible(true);
        frame.paint(frame.getGraphics());
        System.out.println("Securitizin\'");
*/
        frame = WarehouseContext.instance().getFrame();
        frame.getContentPane().removeAll();
        frame.getContentPane().setLayout(new FlowLayout());
        //frame.getContentPane().add(this.addOrderButton);
        //frame.getContentPane().add(this.showOrderButton);
        //frame.getContentPane().add(this.showClientInvoicesButton);
        //frame.getContentPane().add(this.makePaymentForClientButton);
        //frame.getContentPane().add(this.logoutButton);
        frame.setVisible(true);
        frame.paint(frame.getGraphics());
        System.out.println("In Client State");



        Security.submit.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                user = username.getText();
                pass = password.getText();
            }
        });
    }

    }


/*
    JTextField username, password;
username = new JTextField("username");
        password = new JTextField("password");

        JFrame frame = new JFrame("Validation");
        frame.getContentPane().removeAll();
        frame.getContentPane().setLayout(new FlowLayout());
        frame.getContentPane().add(username);
        frame.getContentPane().add(password);
        frame.setVisible(true);
        frame.paint(frame.getGraphics());
*/