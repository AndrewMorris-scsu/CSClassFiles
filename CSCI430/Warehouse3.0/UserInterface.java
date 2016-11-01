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
    private static final int MAKE_PAYMENT_FOR_CLIENT = 7;
    private static final int ACCEPT_SHIPMENT = 8;

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
        System.out.println(MAKE_PAYMENT_FOR_CLIENT + " to make payment for a client");
        System.out.println(ACCEPT_SHIPMENT + " to accept a shipment from a Supplier");

        System.out.println(REMOVE_HOLD + " to  remove a hold on a product");
        System.out.println(PROCESS_HOLD + " to  process holds");
        System.out.println(GET_TRANSACTIONS + " to  print transactions for a client");
        System.out.println(SHOW_MEMBERS + " to  print clients");
        System.out.println(SHOW_BOOKS + " to  print products");
        System.out.println(SHOW_MEMBERS_BOOKS +" to print all products checked out by a client");
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
                    System.out.println("Added Line Item:\n"
                            +"ClientID = "+clientID+"\n"
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
            Iterator waitList = product.getWaitListOrderIDs();
            if (waitList.hasNext()) {
                System.out.println(product.toString());
            }

        }
    }

    public void showOrdersForClient(){
        String clientID = getToken("Enter client ID:");
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
        String clientID = getToken("Enter client ID:");
        Client client = warehouse.searchForClient(clientID);
        Double balance, amount, updatedBalance;

        if (client == null) {
            System.out.println("Could not find that client with the ID "+ clientID);
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

    public void acceptShipment() {
        //Added by Andrew 2/13/16
        String productID = getToken("Enter product ID");
        Product product = warehouse.searchForProduct(productID);

        if (product == null) {
            System.out.println("Product ID not found... ");
            return;
        }

        Integer quantity = getNumber("Enter Quantity:");


        Iterator waitList = product.getWaitListOrderIDs();
        while (waitList.hasNext()) {
            String orderID = (String)waitList.next();


            Order order = warehouse.searchForOrder(orderID);
            //Search line items for PrductID
            lineItem lineToEdit = null;

            Iterator lineItems = order.getLineItems();
            while (lineItems.hasNext() && quantity > 0) {
                lineItem line = (lineItem) lineItems.next();

                if (line.getProductID().equals(productID)) {
                    lineToEdit = line;
                }
            }

            Integer fillOrderQuantity = lineToEdit.getQuantityOrdered() - lineToEdit.getQuantityShipped();
            Integer quantityStart = quantity;
            System.out.print("Need "+ fillOrderQuantity +" items to fulfill order#" + orderID);
            if (!yesOrNo("Would you like to fulfill this order?")) {
                System.out.println("You selected NOT to fulfill waitlisted Order "+ orderID);
            } else {
                //Fulfill the order.

                if (fillOrderQuantity > quantity) {
                    warehouse.addShippedItemsToOrder(quantity, productID, orderID);
                    quantity = 0;

                } else {
                    warehouse.addShippedItemsToOrder(fillOrderQuantity, productID, orderID);
                    quantity = quantityStart - fillOrderQuantity;

                }

            }

        }
        //Add remaining quantity to product
        warehouse.addStock(quantity, productID);



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
        System.out.println("Print Transactions for a client");
        String clientID = getToken("Enter client ID:");
        Client client = warehouse.searchForClient(clientID);
        if (client == null) {
            System.out.println("Could not find Client with ID "+ clientID);
            return;
        }
        System.out.println("Date Description DollarAmount");
        for (Transaction x : client.getTransactions()) {
            System.out.println(x);
        }


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
                System.out.println("File doesn't exist; creating new Warehouse" );
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
                case MAKE_PAYMENT_FOR_CLIENT: makePaymentForClient();
                    break;
                case ACCEPT_SHIPMENT: acceptShipment();
                    break;
/*OLD FUNCTIONALITY:*/

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
