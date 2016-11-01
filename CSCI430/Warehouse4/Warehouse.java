/**
 * Created by Jared on 2/6/2016.
 */
import com.sun.org.apache.xpath.internal.operations.Or;
import sun.util.calendar.LocalGregorianCalendar;

import java.text.SimpleDateFormat;
import java.util.*;
import java.io.*;
public class Warehouse implements Serializable {

    private static final long serialVersionUID = 1L;

    private ClientList clientList;
    private ProductList productList;
    private OrderList orderList;
    private ManufacturerList manufacturerList;
    private InvoiceList invoiceList;

    private static Warehouse warehouse;

    private Warehouse() {
        productList = ProductList.instance();
        clientList = ClientList.instance();
        orderList = OrderList.instance();
        invoiceList = InvoiceList.instance();
        manufacturerList = ManufacturerList.instance();
    }
    public static Warehouse instance() {
        if (warehouse == null) {
            ClientIdServer.instance(); // instantiate all singletons
            return (warehouse = new Warehouse());
        } else {
            return warehouse;
        }
    }
    public Product addProduct(String name, double price) {
        Product product = new Product(name, price);
        if (productList.insertProduct(product)) {
            return (product);
        }
        return null;
    }
    public Manufacturer addManufacturer(String name, String phone)   {
        Manufacturer manufacturer = new Manufacturer(name, phone);
        if (manufacturerList.insertManufacturer(manufacturer))  {
            return (manufacturer);
        }
        return null;
    }
    public Client addClient(String name, String address, String phone) {
        Client client = new Client(name, address, phone);
        if (clientList.insertClient(client)) {
            return (client);
        }
        return null;
    }

    public void addProductManufacturer (String productID, String manID, Double price) {

        Product product = searchForProduct(productID);
        product.addManufacturer(manID, price);

    }
    public boolean removeProductManufacturer(String productID, String manID) {
        Product product = searchForProduct(productID); //verified validity
        if (product.removeproductManufacturer(manID)) {
            return true;
        }
        return false;
    }
    public void removeManufacturer(String manID){

        Manufacturer man = searchForManufacturer(manID); //already verified ID exists...
        Iterator products = getProducts();
        while (products.hasNext()) {
            Product product = (Product) products.next();
            Iterator manufacturers = product.getProductManufacturers();
            while (manufacturers.hasNext()) {
                productManufacturer PM = (productManufacturer) manufacturers.next();
                if (manID.equals(PM.getManID())) {
                    product.removeproductManufacturer(manID);
                    break;
                }

            }

        }
        manufacturerList.removeManufacturer(manID);

    }

    public String createOrder(String clientID){

        Order order = new Order(clientID);
        if (orderList.insertOrder(order)){
            return (order.getID());
        }
        return null;
    }

    public Double makePayment(String clientID, Double amount){
        //Jared Kariniemi 2/12/16
        Client client = searchForClient(clientID);
        client.subtractFromBalance(amount);
        Double balance = client.getBalanceDue();

        String dateString = new SimpleDateFormat("dd/MM/yy").format(new Date());
        Transaction trans = new Transaction( dateString , "Payment received", amount);
        client.addTransaction(trans);

        return balance;
    }


    public boolean processOrder(String orderID){
        //ross kostron 2/8/2016
        Order order = searchForOrder(orderID);
        if (order == null ) {
            System.out.println("Order " + orderID + " does not exist in our system");
            return false;
        }

        Client client = searchForClient(order.getClientID());
        Invoice outgoingInvoice = new Invoice();


        if(order.getProcessed() == true){
            System.out.println("Order has been processed");
            return false;
        }

        String dateString = new SimpleDateFormat("dd/MM/yy").format(new Date());
        Transaction trans = new Transaction( dateString , "Processed Order", order.getTotalPrice());
        client.addTransaction(trans);


        double priceShipped = 0.0;
        Iterator lineItems = order.getLineItems();

        while (lineItems.hasNext()) {
            lineItem item = (lineItem) lineItems.next();
            String productID = item.getProductID();
            Product product = warehouse.searchForProduct(productID);
            int orderQty = item.getQuantityOrdered();
            int productQty = product.getQuantity();
            double price = product.getPrice();
            if (productQty >= orderQty) {
                priceShipped += (orderQty * price);
                item.setQuantityShipped(orderQty);
                product.changeQuantity(orderQty * (-1));
                outgoingInvoice.addLineItem(productID, orderQty);
            } else {
                priceShipped += (productQty * price);
                item.setQuantityShipped(productQty);
                product.addWaitListOrderID(orderID);
                product.changeQuantity(productQty * (-1));
                outgoingInvoice.addLineItem(productID, productQty);
            }
        }

        Transaction invoice = new Transaction(dateString, "Invoice", priceShipped);
        outgoingInvoice.setTotalCost(priceShipped);
        client.addTransaction(invoice);
        client.addToBalance(priceShipped);
        order.setProcessed(true);
        invoiceList.insertInvoice(outgoingInvoice);

     return true;
    }

    public void addShippedItemsToOrder(Integer quantity, String productID, String orderID) {

        Order order = searchForOrder(orderID);
        Product product = searchForProduct(productID);
        Client client = searchForClient(order.getClientID());
        lineItem line = order.getLineItemByProduct(productID);

        line.setQuantityShipped( (line.getQuantityShipped() + quantity));
        if (line.getQuantityShipped() == line.getQuantityOrdered()) {
            product.removeOrderFromWaitlist(orderID);
        }
        Double total = product.getPrice() * quantity;
        client.addToBalance(total);

        String dateString = new SimpleDateFormat("dd/MM/yy").format(new Date());
        Transaction trans = new Transaction(dateString, "Waitlisted Item "+ productID +" shipped", total);
        Invoice outgoingInvoice = new Invoice();
        outgoingInvoice.setTotalCost(total);
        outgoingInvoice.addLineItem(productID, quantity);
        invoiceList.insertInvoice(outgoingInvoice);
        client.addTransaction(trans);

    }

    public void addStock(Integer quantity, String productID) {
        Product product = searchForProduct(productID);
        product.changeQuantity(quantity);
    }


    public Iterator getProducts() {
        return productList.getProducts();
    }

    public Iterator getManufacturers()  { return manufacturerList.getManufacturers(); }

    public Iterator getClients() {
        return clientList.getClients();
    }

    public Iterator getOrders() { return  orderList.getOrders();   }

    public Iterator getInvoices() { return invoiceList.getInvoices(); }

    public void addLineItem(String pID, String orderID, Integer quantity){
        Order foundOrder;
        foundOrder = searchForOrder(orderID);
        Product product = null;

        if (foundOrder != null){
            System.out.println("Found order is NOT equal to NULL");
            foundOrder.addLineItem(pID,quantity);
            product = searchForProduct(pID);
            if (product == null) {
                System.out.println("INVALID PRODUCT ID WHEN ADDING TRANSACTION");
                return;
            }

            foundOrder.addDollarAmt(product.getPrice() * quantity);
        }
        else
            System.out.println("invalid order ID");
    }

    public Client searchForClient(String clientID) {
        Client foundClient = null;
        Iterator allClients = getClients();

        while (allClients.hasNext()) {
            Client temp = (Client)allClients.next();

            if (temp.getId().equals(clientID)) {
                foundClient = temp;
                break;
            }
        }

        return foundClient;
    }

    public Product searchForProduct(String ProductID) {
        Product foundProduct = null;
        Iterator allProducts = getProducts();
        boolean notFound = true;

        while (allProducts.hasNext()) {
            Product temp = (Product)allProducts.next();

            if (temp.getId().equals(ProductID)) {
                notFound = false;
                foundProduct = temp;
                break;
            }
        }

        return foundProduct;
    }

    public Order searchForOrder(String orderID){
        //ross kostron 28/2016
        Order foundOrder = null;
        Iterator allOrders = getOrders();

        while(allOrders.hasNext()){
            Order temp = (Order)allOrders.next();

            if(temp.getID().equals(orderID)){
                foundOrder = temp;
                break;
            }
        }
        return foundOrder; //null if not found
    }

    public Manufacturer searchForManufacturer(String manID) {
        //ross kostron 28/2016
        Manufacturer foundManufacturer = null;
        Iterator allManufacturers = getManufacturers();

        while(allManufacturers.hasNext()){
            Manufacturer temp = (Manufacturer)allManufacturers.next();

            if(temp.getID().equals(manID)){
                foundManufacturer = temp;
                break;
            }
        }
        return foundManufacturer; //null if not found
    }

    public static Warehouse retrieve() {
        try {
            FileInputStream file = new FileInputStream("WarehouseData");
            ObjectInputStream input = new ObjectInputStream(file);
            input.readObject();
            ClientIdServer.retrieve(input);
            ProductIdServer.retrieve(input);
            OrderIdServer.retrieve(input);
            ManufacturerIdServer.retrieve(input);
            return warehouse;
        } catch(IOException ioe) {
            ioe.printStackTrace();
            return null;
        } catch(ClassNotFoundException cnfe) {
            cnfe.printStackTrace();
            return null;
        }
    }
    public static  boolean save() {
        try {
            FileOutputStream file = new FileOutputStream("WarehouseData");
            ObjectOutputStream output = new ObjectOutputStream(file);
            output.writeObject(warehouse);
            output.writeObject(ClientIdServer.instance());
            output.writeObject(ProductIdServer.instance());
            output.writeObject(OrderIdServer.instance());
            output.writeObject(ManufacturerIdServer.instance());
            return true;
        } catch(IOException ioe) {
            ioe.printStackTrace();
            return false;
        }
    }
    private void writeObject(java.io.ObjectOutputStream output) {
        try {
            output.defaultWriteObject();
            output.writeObject(warehouse);
        } catch(IOException ioe) {
            System.out.println(ioe);
        }
    }
    private void readObject(java.io.ObjectInputStream input) {
        try {
            input.defaultReadObject();
            if (warehouse == null) {
                warehouse = (Warehouse) input.readObject();
            } else {
                input.readObject();
            }
        } catch(IOException ioe) {
            ioe.printStackTrace();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
    public String toString() {
        return productList + "\n" + clientList;
    }

}
