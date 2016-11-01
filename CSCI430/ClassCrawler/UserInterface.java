/**
 * Created by Andrew on 2/6/16.
 */
import java.util.*;
import java.text.*;
import java.io.*;

public class UserInterface {
    private static UserInterface userInterface;
    private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static Warehouse warehouse;
    private static final int EXIT = 0;
    private static final int ADD_CLIENT = 1;
    private static final int ADD_PRODUCT = 2;
    private static final int ADD_ORDER = 3;
    private static final int PROCESS_ORDER = 4;
    private static final int SHOW_WAITLISTED_PRODUCTS = 5;
    private static final int SHOW_ORDERS_FOR_CLIENT = 6;
    
    private static final int RETURN_BOOKS = 5;
    private static final int RENEW_BOOKS = 6;
    private static final int REMOVE_BOOKS = 7;
    private static final int PLACE_HOLD = 8;
    private static final int REMOVE_HOLD = 9;
    private static final int PROCESS_HOLD = 10;
    private static final int GET_TRANSACTIONS = 11;
    private static final int SHOW_MEMBERS = 12;
    private static final int SHOW_BOOKS = 13;
    private static final int SHOW_MEMBERS_BOOKS = 14;
    private static final int SAVE = 15;
    private static final int RETRIEVE = 16;

    private static final int HELP = 99;

    private UserInterface() {
        if (yesOrNo("Look for saved data and  use it?")) {
            retrieve();
        } else {
            warehouse = Warehouse.instance();
        }
    }
    public static UserInterface instance() {
        if (userInterface == null) {
            return userInterface = new UserInterface();
        } else {
            return userInterface;
        }
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
        System.out.println("Enter a number between 0 and 12 as explained below:");
        System.out.println(EXIT + " to Exit\n");
        System.out.println(ADD_CLIENT + " to add a client");
        System.out.println(ADD_PRODUCT + " to add a product");
        System.out.println(ADD_ORDER + " to add an order");
        System.out.println(PROCESS_ORDER +" to process an order");
        System.out.println(SHOW_WAITLISTED_PRODUCTS + " to show products that are on any waitlist");
        System.out.println(SHOW_ORDERS_FOR_CLIENT + " to orders for a client");

        System.out.println(RETURN_BOOKS + " to  return products ");
        System.out.println(RENEW_BOOKS + " to  renew products ");
        System.out.println(REMOVE_BOOKS + " to  remove products");
        System.out.println(PLACE_HOLD + " to  place a hold on a product");
        System.out.println(REMOVE_HOLD + " to  remove a hold on a product");
        System.out.println(PROCESS_HOLD + " to  process holds");
        System.out.println(GET_TRANSACTIONS + " to  print transactions");
        System.out.println(SHOW_MEMBERS + " to  print clients");
        System.out.println(SHOW_BOOKS + " to  print producs");
        System.out.println(SHOW_MEMBERS_BOOKS +" to print all producs checked out by a client");
        System.out.println(SAVE + " to  save data");
        System.out.println(RETRIEVE + " to  retrieve");

        System.out.println(HELP + " for help");
    }

    public void addClient() {
        String name = getToken("Enter client's name");
        String address = getToken("Enter address");
        String phone = getToken("Enter phone");
        Client result;
        result = warehouse.addClient(name, address, phone);
        if (result == null) {
            System.out.println("Could not add client");
        }
        System.out.println(result);
    }

    public void addProduct() {
        Product result;
        do {
            String name = getToken("Enter  name of product");
            String input = getToken("Enter price");
            Double price;
            price = Double.parseDouble(input);

            result = warehouse.addProduct(name, price);
            if (result != null) {
                System.out.println(result);
            } else {
                System.out.println("Product could not be added");
            }
            if (!yesOrNo("Add more products?")) {
                break;
            }
        } while (true);
    }
    //Jared Kariniemi 2/8/16
    public void addOrder() {
        Product result;
        Client aClient;
        String orderID;
        String clientID = getToken("Enter Client ID");
        aClient = warehouse.searchForClient(clientID);
        orderID = warehouse.createOrder(clientID);
        System.out.println("Order ID = "+ orderID);
        if (aClient != null){
            do {
                String pID = getToken("Enter product ID");
                String pNumber = getToken("Enter number desired");
                Integer quantity;
                quantity = Integer.parseInt(pNumber);

                result = warehouse.searchForProduct(pID);
                if (result != null) {
                    System.out.println("About to addLineItem in UI: "
                            +"ClientID ="+clientID+" \n"
                            +"OrderID = "+orderID+"\n"
                            +"quantity = "+ quantity);
                    warehouse.addLineItem(pID, orderID, quantity);
                } else {
                    System.out.println("Product could not be added to order");
                }
                if (!yesOrNo("Add more products?")) {
                    break;
                }
            } while (true);
        }
        else
            System.out.println("Invalid client ID");
    }
    public void processOrder() {
        //ross kostron 2/8/2016
        boolean result;
        String orderID = getToken("Enter order ID");
        result = warehouse.processOrder(orderID);
        if (result) {
            System.out.println("Order processed successfully");
        }
        else{
            System.out.println("Unable to process order!");
        }

    }
    public void renewProducts() {
        System.out.println("Dummy Action");
    }

    public void showProducts() {
        Iterator allProducts = warehouse.getProducts();
        while (allProducts.hasNext()){
            Product product = (Product)(allProducts.next());
            System.out.println(product.toString());
        }
    }

    public void showClients() {
        Iterator allClients = warehouse.getClients();
        while (allClients.hasNext()){
            Client client = (Client)(allClients.next());
            System.out.println(client.toString());
        }
    }

    public void showOrders() {
        Iterator allOrders = warehouse.getOrders();
        while (allOrders.hasNext()){
            Order order = (Order)(allOrders.next());
            System.out.println(order.toString());
        }
    }
    public void showWaitlistedOrders() {

        Iterator allProducts = warehouse.getProducts();
        System.out.println("The following orders are on a waitlist:");
        while (allProducts.hasNext()){
            Product product = (Product)(allProducts.next());
            if (product.getWaitListOrderIDs().size() > 0) {
                System.out.println(product.toString());
            }

        }
    }

    public void showOrdersForClient(){
        String clientID = getToken("Enter client ID:");
        Client theClient = warehouse.searchForClient(clientID);
        if (theClient != null) {
            Iterator clients = warehouse.getClients();
            Iterator orders = warehouse.getOrders();
            System.out.println("Client " + clientID + " ordered");

            while (clients.hasNext()) {
                Client client = (Client) clients.next();
                while (orders.hasNext()) {
                    Order order = (Order) orders.next();
                    if (client.getId().equals(order.getClientID())) {
                        System.out.println(order.getID());
                    }
                }
            }

        }

    }

/*

    public void showClientsOrders() {
        Client aClient;
        String clientID;

        clientID = getToken("Please provide client ID... ");

        //Call search on Warehouse
        aClient = warehouse.searchForClient(clientID);

        if (aClient == null) {
            System.out.println("Did NOT find Client with the ID :"+clientID); //IMPLEMENT THIS IF-ELSE in Warehouse class..
            return;
        } else {
            System.out.println(aClient.getName() +" Found :");
        }
        aClient.printTransactions();
    }
*/
    public void returnProducts() {
        System.out.println("Dummy Action");
    }
    public void removeProducts() {
        System.out.println("Dummy Action");
    }
    public void placeHold() {
        System.out.println("Dummy Action");
    }
    public void removeHold() {
        System.out.println("Dummy Action");
    }
    public void processHolds() {
        System.out.println("Dummy Action");
    }
    public void getTransactions() {
        System.out.println("Dummy Action");
    }
    private void save() {
        if (Warehouse.save()) {
            System.out.println(" The Warehouse has been successfully saved in the file WarehouseData \n" );
        } else {
            System.out.println(" There has been an error in saving \n" );
        }
    }
    private void retrieve() {
        try {
            Warehouse tempWarehouse = Warehouse.retrieve();
            if (tempWarehouse != null) {
                System.out.println(" The Warehouse has been successfully retrieved from the file WarehouseData \n" );
                warehouse = tempWarehouse;
            } else {
                System.out.println("File doesnt exist; creating new Warehouse" );
                warehouse = Warehouse.instance();
            }
        } catch(Exception cnfe) {
            cnfe.printStackTrace();
        }
    }
    public void process() {
        int command;
        help();
        while ((command = getCommand()) != EXIT) {
            switch (command) {
                case ADD_CLIENT:        addClient();
                    break;
                case ADD_PRODUCT:         addProduct();
                    break;
                case ADD_ORDER:         addOrder();
                    break;
                case PROCESS_ORDER:       processOrder();
                    break;
                case SHOW_WAITLISTED_PRODUCTS: showWaitlistedOrders();
                    break;
                case SHOW_ORDERS_FOR_CLIENT: showOrdersForClient();
                    break;

                case REMOVE_BOOKS:      removeProducts();
                    break;
                case PLACE_HOLD:        placeHold();
                    break;
                case REMOVE_HOLD:       removeHold();
                    break;
                case PROCESS_HOLD:      processHolds();
                    break;
                case GET_TRANSACTIONS:  getTransactions();
                    break;
                case SAVE:              save();
                    break;
                case RETRIEVE:          retrieve();
                    break;
                case SHOW_MEMBERS:	showClients();
                    break;
                case SHOW_BOOKS:	showProducts();
                    break;

                case HELP:              help();
                    break;
            }
        }
    }
    public static void main(String[] s) {
        UserInterface.instance().process();
    }


}
