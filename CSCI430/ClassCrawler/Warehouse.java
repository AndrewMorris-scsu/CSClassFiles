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
    /*
    public static final int BOOK_NOT_FOUND  = 1;
    public static final int BOOK_NOT_ISSUED  = 2;
    public static final int BOOK_HAS_HOLD  = 3;
    public static final int BOOK_ISSUED  = 4;
    public static final int HOLD_PLACED  = 5;
    public static final int NO_HOLD_FOUND  = 6;
    public static final int OPERATION_COMPLETED= 7;
    public static final int OPERATION_FAILED= 8;
    public static final int NO_SUCH_MEMBER = 9;
    */
    private ClientList clientList;
    private ProductList productList;
    private OrderList orderList;

    private static Warehouse warehouse;

    private Warehouse() {
        productList = ProductList.instance();
        clientList = ClientList.instance();
        orderList = OrderList.instance();
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
    public Client addClient(String name, String address, String phone) {
        Client client = new Client(name, address, phone);
        if (clientList.insertClient(client)) {
            return (client);
        }
        return null;
    }
    public String createOrder(String clientID){

        List<lineItem> aList = null;
        Order order = new Order(clientID);
        if (orderList.insertOrder(order)){
            return (order.getID());
        }
        return null;
    }


    public boolean processOrder(String orderID){
        //ross kostron 2/8/2016
        Order order = searchForOrder(orderID);
        Client client = searchForClient(order.getClientID());
        if(order == null || client == null){
            return false;
        }

        String dateString = new SimpleDateFormat("dd/MM/yy").format(new Date());
        Transaction trans = new Transaction( dateString , "Processed Order", order.getTotalPrice());
        client.addTransaction(trans);


        double priceShipped = 0.0;

        for(lineItem item : order.getLineItems()) {
            Product product = warehouse.searchForProduct(item.getProductID());
            int orderQty = item.getQuantityOrdered();
            int productQty = product.getQuantity();
            double price = product.getPrice();
            if (productQty >= orderQty) {
                priceShipped += (orderQty * price);
                item.setQuantityShipped(orderQty);
                product.changeQuantity(orderQty * (-1));
            } else {
                priceShipped += (productQty * price);
                item.setQuantityShipped(productQty);
                product.addWaitListOrderID(orderID);
                product.changeQuantity(productQty * (-1));
            }
        }

        Transaction invoice = new Transaction(dateString, "Invoice", priceShipped);
        client.addTransaction(invoice);
        client.addToBalance(order.getTotalPrice());

     return true;
    }

    public Iterator getProducts() {
        return productList.getProducts();
    }

    public Iterator getClients() {
        return clientList.getClients();
    }

    public Iterator getOrders() { return  orderList.getOrders();   }

    public void addLineItem(String pID, String orderID, Integer quantity){
        Order foundOrder;
        foundOrder = searchForOrder(orderID);

        if (foundOrder != null){
            System.out.println("Found order is NOT equal to NULL");
            foundOrder.addLineItem(pID,quantity);
        }
        else
            System.out.println("invalid order ID");
    }

    public Client searchForClient(String clientID) {
        Client foundClient = null;
        Iterator allClients = getClients();
        boolean notFound = true;

        while (allClients.hasNext()) {
            Client temp = (Client)allClients.next();

            if (temp.getId().equals(clientID)) {
                notFound = false;
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

    public static Warehouse retrieve() {
        try {
            FileInputStream file = new FileInputStream("WarehouseData");
            ObjectInputStream input = new ObjectInputStream(file);
            input.readObject();
            ClientIdServer.retrieve(input);
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
