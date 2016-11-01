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

public class Clientstate extends WarehouseState implements ActionListener {
    private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static Warehouse warehouse;
    private WarehouseContext context;
    private static Clientstate instance;
    private static final int EXIT = 0;
    private static final int ADD_ORDER = 3;
    private static final int SHOW_ORDERS_FOR_CLIENT = 9;
    private static final int MAKE_PAYMENT_FOR_CLIENT = 11;
    private static final int SHOW_CLIENT_INVOICES = 15;
    private static final int SHOW_PRODUCTS = 16;
    private static final int HELP = 99;

    private JFrame frame;
    private AbstractButton addOrderButton,
                            showOrderButton,
                            showClientInvoicesButton,
                            makePaymentForClientButton,
                            logoutButton;

    private Clientstate() {
        super();
        warehouse = Warehouse.instance();
        //context = WarehouseContext.instance();
        addOrderButton = new JButton("Add Order");//
        showOrderButton = new JButton("Show Orders");//
        showClientInvoicesButton = new JButton("Show Invoices");//
        makePaymentForClientButton = new JButton("Make Payment");
        logoutButton = new JButton("logout");

        addOrderButton.addActionListener(this);//
        showOrderButton.addActionListener(this);//
        showClientInvoicesButton.addActionListener(this);//
        makePaymentForClientButton.addActionListener(this);
        logoutButton.addActionListener(this);


    }
    //Stuff for GUI


    public void actionPerformed(ActionEvent event) {
        if (event.getSource().equals(this.addOrderButton))
        {//System.out.println("user \n");
            this.addOrder();
        } else if ( event.getSource().equals(this.showOrderButton) ) {
            this.showOrdersForClient();
        } else if (event.getSource().equals(this.showClientInvoicesButton) ){
            this.showClientInvoices();
        } else if (event.getSource().equals(this.makePaymentForClientButton)){
            this.makePaymentForClient();
        } else {
            System.out.println("Logout");
            this.logout();
        }

    }

    public void clear() { //clean up stuff
        frame.getContentPane().removeAll();
        frame.paint(frame.getGraphics());
    }



    //End new stuff for gui




    public static Clientstate instance() {
        if (instance == null) {
            instance = new Clientstate();
        }
        return instance;
    }

    public String getToken(String prompt) {
        do {
            try {
                System.out.println(prompt);
                String line = reader.readLine();
                StringTokenizer tokenizer = new StringTokenizer(line, "\n\r\f");
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

    public int getNumber(String prompt) {
        do {
            try {
                String item = getToken(prompt);
                Integer num = Integer.valueOf(item);
                return num.intValue();
            } catch (NumberFormatException nfe) {
                System.out.println("Please input a number ");
            }
        } while (true);
    }

    public Calendar getDate(String prompt) {
        do {
            try {
                Calendar date = new GregorianCalendar();
                String item = getToken(prompt);
                DateFormat df = SimpleDateFormat.getDateInstance(DateFormat.SHORT);
                date.setTime(df.parse(item));
                return date;
            } catch (Exception fe) {
                System.out.println("Please input a date as mm/dd/yy");
            }
        } while (true);
    }

    public int getCommand() {
        do {
            try {
                int value = Integer.parseInt(getToken("Enter command:" + HELP + " for help"));
                if (value >= EXIT && value <= HELP) {
                    return value;
                }
            } catch (NumberFormatException nfe) {
                System.out.println("Enter a number");
            }
        } while (true);
    }

    public void help() {
        System.out.println("Enter a number between 0 and 20 or 99 as explained below:");
        System.out.println(EXIT + " to Exit\n");
        System.out.println(ADD_ORDER + " to add an order");
        System.out.println(SHOW_ORDERS_FOR_CLIENT + " to show orders for a client");
        System.out.println(MAKE_PAYMENT_FOR_CLIENT + " to make a payment for a client");
        System.out.println(SHOW_CLIENT_INVOICES + " to print a client's invoices");
        System.out.println(SHOW_PRODUCTS + " to print products");
        System.out.println(HELP + " for help");
    }

    public void addOrder() {
        Product result;
        Client aClient;
        String orderID;
        String clientID = WarehouseContext.instance().getClient();
        aClient = warehouse.searchForClient(clientID.replaceAll("\\ +", ""));
        if (aClient == null) {
            System.out.println("Invalid client ID");
            return;
        }
        orderID = warehouse.createOrder(clientID);
        System.out.println("Order ID = " + orderID);

        do {
            String pID = getToken("Enter product ID");
            result = warehouse.searchForProduct(pID);
            if (result != null) {
                String pNumber = getToken("Enter number desired");
                Integer quantity;
                quantity = Integer.parseInt(pNumber);

                System.out.println("Added Line Item:\n"
                        + "ClientID = " + clientID + "\n"
                        + "OrderID = " + orderID + "\n"
                        + "quantity = " + quantity);
                warehouse.addLineItem(pID, orderID, quantity);
            } else {
                System.out.println("Product could not be added to order");
            }

            if (!yesOrNo("Add more products?")) {
                break;
            }
        } while (true);
    }
    public void showOrdersForClient(){
        String clientID = WarehouseContext.instance().getClient();
        Client theClient = warehouse.searchForClient(clientID);
        if (theClient != null) {

            Iterator orders = warehouse.getOrders();
            System.out.println("Client " + clientID + " ordered");

            while (orders.hasNext()) {
                Order order = (Order) orders.next();
                if (clientID.equals(order.getClientID())) {
                    System.out.println(order.getID());
                }
            }

        } else {
            System.out.println("Could not find client with ID:["+ clientID+"]");
        }

    }
    public void makePaymentForClient () {
        //By Andrew 2/12/16
        String clientID = WarehouseContext.instance().getClient();
        Client client = warehouse.searchForClient(clientID);
        Double balance, amount, updatedBalance;

        if (client == null) {
            System.out.println("Could not find client with the ID "+ clientID);
            return;
        }

        balance = client.getBalanceDue();

        if (balance > 0.0) {
            System.out.println("Current balance: \n" + balance.toString());
        } else {
            System.out.println("This client has NO outstanding balance");
            return;
        }

        amount = Double.parseDouble(getToken("Enter Payment Amount"));

        int attempts = 3;
        while (amount > balance && attempts > 0) {
            System.out.println(attempts + " attempts left.. ");
            System.out.println("PAYMENT EXCEEDS AMOUNT OWED");
            amount = Double.parseDouble(getToken("Please enter a payment amount that does not exceed the"
                    + "client's balance\n Current balance is: "+balance.toString()+"\n:"));
            --attempts;
        }
        updatedBalance = warehouse.makePayment(clientID, amount);
        System.out.println("Updated Balance: \n" + updatedBalance);

    }
    public void showClientInvoices(){
        Iterator allInvoices =warehouse.getInvoices();
        while(allInvoices.hasNext()) {
            System.out.println(allInvoices.next());
        }
    }
    public void showProducts() {
        Iterator allProducts = warehouse.getProducts();
        while (allProducts.hasNext()) {
            Product product = (Product) (allProducts.next());
            System.out.println(product.toString());
        }
    }

    public void logout() {

        if( WarehouseContext.instance().getLogin() == WarehouseContext.IsManager ) {
            (WarehouseContext.instance()).changeState(5); // exit with a code 0
        } else if ( WarehouseContext.instance().getLogin() == WarehouseContext.IsClerk ) {
            (WarehouseContext.instance()).changeState(4);
        } else if ( WarehouseContext.instance().getLogin() == WarehouseContext.IsClient) {
            (WarehouseContext.instance()).changeState(3);
        } else {
            //ERROR
            WarehouseContext.instance().changeState(0);
        }

    }

    public void process() {
        int command;
        help();
        while ((command = getCommand()) != EXIT) {
            switch (command) {
                case ADD_ORDER:        addOrder();
                    break;
                case SHOW_ORDERS_FOR_CLIENT:         showOrdersForClient();
                    break;
                case MAKE_PAYMENT_FOR_CLIENT:      makePaymentForClient();
                    break;
                case SHOW_CLIENT_INVOICES:      showClientInvoices();
                    break;
                case SHOW_PRODUCTS:      showProducts();
                break;
                case HELP:              help();
                    break;
            }
        }
        logout();
    }
    public void run() {
        //process();
        frame = WarehouseContext.instance().getFrame();
        frame.getContentPane().removeAll();
        frame.getContentPane().setLayout(new FlowLayout());
        frame.getContentPane().add(this.addOrderButton);
        frame.getContentPane().add(this.showOrderButton);
        frame.getContentPane().add(this.showClientInvoicesButton);
        frame.getContentPane().add(this.makePaymentForClientButton);
        frame.getContentPane().add(this.logoutButton);
        frame.setVisible(true);
        frame.paint(frame.getGraphics());
        System.out.println("In Client State");
    }
}