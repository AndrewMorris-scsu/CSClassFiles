/**
 * Created by Ross Kostron on 3/20/2016.
 */
import java.util.*;
import java.text.*;
import java.io.*;
public class ClerkState extends WarehouseState {
    private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static Warehouse warehouse;
    private WarehouseContext context;
    private static ClerkState instance;
    private static final int EXIT = 0;
    private static final int ADD_CLIENT = 1; //function added
    private static final int ADD_PRODUCT = 2; //function added
    private static final int PROCESS_ORDER = 6; //function added
    private static final int SHOW_UNPROCESSED_ORDERS = 7; //function added
    private static final int SHOW_WAITLISTED_PRODUCTS = 8; // function added
    private static final int SHOW_MANUFACTURERS_FOR_A_PRODUCT = 10; //function added
    private static final int ACCEPT_SHIPMENT = 18; //function added
    private static final int GET_TRANSACTIONS = 13; //function added
    private static final int SHOW_CLIENTS = 14; //function added
    private static final int SHOW_PRODUCTS = 16; //  function added
    private static final int SHOW_MANUFACTURERS = 17; //function added

    private static final int CLIENTMENU = 12;
    private static final int SHOW_CLIENTS_WITH_BALANCE = 22;

    private static final int HELP = 99;

    private ClerkState() {
        super();
        warehouse = Warehouse.instance();
        //context = WarehouseContext.instance();
    }

    public static ClerkState instance() {
        if (instance == null) {
            instance = new ClerkState();
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
        System.out.println(ADD_CLIENT + " to add a client");
        System.out.println(ADD_PRODUCT + " to add a product");
        System.out.println(PROCESS_ORDER +" to process an order");
        System.out.println(SHOW_PRODUCTS + " to  print products");
        System.out.println(SHOW_UNPROCESSED_ORDERS + " to display unprocessed orders");
        System.out.println(SHOW_WAITLISTED_PRODUCTS + " to show products that are on any waitlist");
        System.out.println(SHOW_MANUFACTURERS_FOR_A_PRODUCT + " to show manufacturers for a particular product");
        System.out.println(ACCEPT_SHIPMENT + " to accept a shipment from a Supplier");
        System.out.println(GET_TRANSACTIONS + " to print transactions for a client");
        System.out.println(SHOW_CLIENTS + " to print clients");
        System.out.println(SHOW_CLIENTS_WITH_BALANCE + " to show clients with an outstanding balance");
        System.out.println(SHOW_MANUFACTURERS + " to  print manufacturers");

        System.out.println(CLIENTMENU + " to  switch to the client menu");

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
            System.out.println("Need "+ fillOrderQuantity +" items to fulfill order#" + orderID);
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
    public void showManufacturers() {
        Iterator allManufacturers = warehouse.getManufacturers();
        while (allManufacturers.hasNext()){
            Manufacturer manufacturer = (Manufacturer)(allManufacturers.next());
            System.out.println(manufacturer.toString());
        }
    }
    public void showProducts() {
        Iterator allProducts = warehouse.getProducts();
        while (allProducts.hasNext()) {
            Product product = (Product) (allProducts.next());
            System.out.println(product.toString());
        }
    }
    public void clientmenu()  {
        String userID = getToken("Please input the user id: ");
        if (Warehouse.instance().searchForClient(userID) != null){
            (WarehouseContext.instance()).setClient(userID);
            (WarehouseContext.instance()).changeState(0);
        }
        else
            System.out.println("Invalid user id.");
    }

    public void logout() {

        if( WarehouseContext.instance().getLogin() == WarehouseContext.IsManager ) {
            (WarehouseContext.instance()).changeState(5); // exit with a code 0
        } else if ( WarehouseContext.instance().getLogin() == WarehouseContext.IsClerk ) {
            (WarehouseContext.instance()).changeState(4);
        }  else {
            //ERROR
            WarehouseContext.instance().changeState(3);
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
                case PROCESS_ORDER:       processOrder();
                    break;
                case SHOW_UNPROCESSED_ORDERS:   showUnprocessedOrders();
                    break;
                case SHOW_WAITLISTED_PRODUCTS: showWaitlistedOrders();
                    break;
                case SHOW_CLIENTS_WITH_BALANCE: showClientsWithBalance();
                    break;
                case SHOW_MANUFACTURERS_FOR_A_PRODUCT: showManufacturersForAProduct();
                    break;
                case ACCEPT_SHIPMENT: acceptShipment();
                    break;

                case GET_TRANSACTIONS:  getTransactions();
                    break;

                case SHOW_CLIENTS:	showClients();
                    break;
                case SHOW_PRODUCTS:	showProducts();
                    break;
                case SHOW_MANUFACTURERS: showManufacturers();
                    break;
                case CLIENTMENU:          clientmenu();
                    break;
                case HELP:              help();
                    break;
            }
        }
        logout();
    }
    public void run() {
        process();
    }
}
