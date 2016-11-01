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
    private static final int ADD_MANUFACTURER = 4;
    private static final int ADD_PRODUCT_MANUFACTURER = 5;
    private static final int PROCESS_ORDER = 6;
    private static final int SHOW_UNPROCESSED_ORDERS = 7;
    private static final int SHOW_WAITLISTED_PRODUCTS = 8;
    private static final int SHOW_ORDERS_FOR_CLIENT = 9;
    private static final int SHOW_MANUFACTURERS_FOR_A_PRODUCT = 10;
    private static final int MAKE_PAYMENT_FOR_CLIENT = 11;
    private static final int ACCEPT_SHIPMENT = 12;
    private static final int GET_TRANSACTIONS = 13;
    private static final int SHOW_CLIENTS = 14;
    private static final int SHOW_CLIENT_INVOICES = 15;
    private static final int SHOW_PRODUCTS = 16;
    private static final int SHOW_MANUFACTURERS = 17;
    private static final int SAVE = 18;
    private static final int RETRIEVE = 19;
    private static final int REMOVE_MANUFACTURER = 20;
    private static final int REMOVE_PRODUCT_MANUFACTURER = 21;
    private static final int SHOW_CLIENTS_WITH_BALANCE = 22;

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
        System.out.println("Enter a number between 0 and 20 or 99 as explained below:");
        System.out.println(EXIT + " to Exit\n");
        System.out.println(ADD_CLIENT + " to add a client");
        System.out.println(ADD_PRODUCT + " to add a product");
        System.out.println(ADD_ORDER + " to add an order");
        System.out.println(ADD_MANUFACTURER + " to add a manufacturer");
        System.out.println(REMOVE_MANUFACTURER + " to remove a manufacturer");
        System.out.println(ADD_PRODUCT_MANUFACTURER + " to add a manufacturer to a product");
        System.out.println(REMOVE_PRODUCT_MANUFACTURER + "to remove a manufacturer from a product");
        System.out.println(PROCESS_ORDER +" to process an order");
        System.out.println(SHOW_UNPROCESSED_ORDERS + " to display unprocessed orders");
        System.out.println(SHOW_WAITLISTED_PRODUCTS + " to show products that are on any waitlist");
        System.out.println(SHOW_ORDERS_FOR_CLIENT + " to orders for a client");
        System.out.println(SHOW_MANUFACTURERS_FOR_A_PRODUCT + " to show manufacturers for a particular product");
        System.out.println(MAKE_PAYMENT_FOR_CLIENT + " to make payment for a client");
        System.out.println(ACCEPT_SHIPMENT + " to accept a shipment from a Supplier");
        System.out.println(GET_TRANSACTIONS + " to print transactions for a client");
        System.out.println(SHOW_CLIENTS + " to print clients");
        System.out.println(SHOW_CLIENT_INVOICES + " to print a client's invoices");
        System.out.println(SHOW_CLIENTS_WITH_BALANCE + " to show clients with an outstanding balance");
        System.out.println(SHOW_PRODUCTS + " to  print products");
        System.out.println(SHOW_MANUFACTURERS + " to  print manufacturers");
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

    public void addManufacturer()   {
        //Jared 3/10/16
        Manufacturer manufacturer;
        String name = getToken("Enter  name of manufacturer");
        String phone = getToken("Enter phone number");

        manufacturer = warehouse.addManufacturer(name, phone);
        if (manufacturer != null) {
            System.out.println(manufacturer);
        }
        else {
            System.out.println("Manufacturer could not be added");
        }
    }
    public void removeManufacturer() {
        String manufacturerID = getToken("Enter Manufacturer ID");
        Manufacturer man = warehouse.searchForManufacturer(manufacturerID);
        if (man == null) {
            System.out.println("Could not find that ID...\n Exiting...");
        }
        else {

            warehouse.removeManufacturer(manufacturerID);
        }

    }
    public void addProductManufacturer()    {
        String id = getToken("Enter manufacturer ID");
        Manufacturer manufacturer = warehouse.searchForManufacturer(id);
        if (manufacturer == null) {
            System.out.println("Manufacturer with ID "+id+" does not exist..");
            return;
        }
        String pid = getToken("Enter product id to which manufacturer is to be added");
        Product product = warehouse.searchForProduct(pid);
        if (product == null) {
            System.out.println("Product with ID "+id+" does not exist..");
            return;
        }
        String price = getToken("Enter manufacturer's price for product");
        double productPrice;
        productPrice = Double.parseDouble(price);
        warehouse.addProductManufacturer(pid, id, productPrice);
    }
    public void removeProductManufacturer() {
        String id = getToken("Enter Product ID");
        Product product = warehouse.searchForProduct(id);
        if (product == null) {
            System.out.println("Could NOT find that product ID...");
        } else {
            Iterator manufacturers = product.getProductManufacturers();

            while (manufacturers.hasNext()){
                productManufacturer productmanufacturer = (productManufacturer) manufacturers.next();
                System.out.println(""+productmanufacturer);
            }
            String manID = getToken("Enter Manufacturer to remove... ");
            Manufacturer manufacturer = warehouse.searchForManufacturer(manID);
            if (manufacturer == null) {
                System.out.println("That manufacturer does NOT exist in our system.. ");
            } else {
                if (warehouse.removeProductManufacturer(id, manID)) {
                    System.out.println("Manufacturer Successfully removed from product");
                } else {
                    System.out.println("Manufacturer is NOT a supplier for product: "+id);
                }
            }
        }
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

    public void showUnprocessedOrders() {
        Iterator unprocessedOrders = warehouse.getOrders();
        while (unprocessedOrders.hasNext()){
            Order order = (Order)(unprocessedOrders.next());
            if (order.getProcessed() == false){
                System.out.println(order.toString());
            }
        }
    }

    public void showProducts() {
        Iterator allProducts = warehouse.getProducts();
        while (allProducts.hasNext()){
            Product product = (Product)(allProducts.next());
            System.out.println(product.toString());
        }
    }

    public void showManufacturers() {
        Iterator allManufacturers = warehouse.getManufacturers();
        while (allManufacturers.hasNext()){
            Manufacturer manufacturer = (Manufacturer)(allManufacturers.next());
            System.out.println(manufacturer.toString());
        }
    }

    public void showClients() {
        Iterator allClients = warehouse.getClients();
        while (allClients.hasNext()){
            Client client = (Client)(allClients.next());
            System.out.println(client.toString());
        }
    }

    public void showClientsWithBalance() {
        Iterator clients = warehouse.getClients();
        while(clients.hasNext()) {
            Client client = (Client) clients.next();
            if (client.getBalanceDue() > 0.0) {
                System.out.println("Client " +client.getId()+ " owes "+ client.getBalanceDue());
            }
        }
    }

    public void showClientInvoices(){
        Iterator allInvoices =warehouse.getInvoices();
        while(allInvoices.hasNext()) {
            System.out.println(allInvoices.next());
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

    public void showManufacturersForAProduct() {
        //by Jared 3/10/16
        String productID = getToken("Enter product ID");
        Product product = warehouse.searchForProduct(productID);

        if (product == null){
            System.out.println("Could not find product with the ID " + productID);
            return;
        }

        Iterator manufacturers = product.getProductManufacturers();

        while (manufacturers.hasNext()){
            productManufacturer productmanufacturer = (productManufacturer) manufacturers.next();
            System.out.println(""+productmanufacturer);
        }
    }
    public void makePaymentForClient () {
        //By Andrew 2/12/16
        String clientID = getToken("Enter client ID:");
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
        while (waitList.hasNext() && quantity > 0) {
            String orderID = (String)waitList.next();


            Order order = warehouse.searchForOrder(orderID);
            //Search line items for ProductID
            lineItem lineToEdit = null;

            Iterator lineItems = order.getLineItems();
            while (lineItems.hasNext()) {
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
                case ADD_MANUFACTURER:  addManufacturer();
                    break;
                case ADD_PRODUCT_MANUFACTURER:  addProductManufacturer();
                    break;
                case REMOVE_PRODUCT_MANUFACTURER: removeProductManufacturer();
                    break;
                case REMOVE_MANUFACTURER: removeManufacturer();
                    break;
                case PROCESS_ORDER:       processOrder();
                    break;
                case SHOW_UNPROCESSED_ORDERS:   showUnprocessedOrders();
                    break;
                case SHOW_WAITLISTED_PRODUCTS: showWaitlistedOrders();
                    break;
                case SHOW_ORDERS_FOR_CLIENT: showOrdersForClient();
                    break;
                case SHOW_CLIENTS_WITH_BALANCE: showClientsWithBalance();
                    break;
                case SHOW_MANUFACTURERS_FOR_A_PRODUCT: showManufacturersForAProduct();
                    break;
                case MAKE_PAYMENT_FOR_CLIENT: makePaymentForClient();
                    break;
                case ACCEPT_SHIPMENT: acceptShipment();
                    break;
/*OLD FUNCTIONALITY:*/

                case GET_TRANSACTIONS:  getTransactions();
                    break;
                case SAVE:              save();
                    break;
                case RETRIEVE:          retrieve();
                    break;
                case SHOW_CLIENTS:	showClients();
                    break;
                case SHOW_CLIENT_INVOICES: showClientInvoices();
                case SHOW_PRODUCTS:	showProducts();
                    break;
                case SHOW_MANUFACTURERS: showManufacturers();
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
