/**
 * Created by Amandrew on 2/6/16.
 */

import java.util.*;
        import java.lang.*;
        import java.io.*;
public class Product implements Serializable {
    private static final String PRODUCT_STRING = "P";
    private static final long serialVersionUID = 1L;
    private String name;
    private Double price;
    private String id;
    private Integer quantity;
    private List <String> waitListOrderIDs = new LinkedList();
    private List <productManufacturer> manufacturers = new LinkedList();

    public Product(String name, Double price) {
        this.name = name;
        this.price = price;
        quantity = 0;
        id = PRODUCT_STRING + (ProductIdServer.instance()).getId();
    }

    public Double getPrice() {
        return price;
    }
    public String getName() {
        return name;
    }
    public String getId() {
        return id;
    }
    public Integer getQuantity() {
        return quantity;
    }
    public Iterator getWaitListOrderIDs(){
        return waitListOrderIDs.iterator();
    }
    public List<String> getWaitlist() { return this.waitListOrderIDs;    }

    public void removeOrderFromWaitlist(String orderID) {
            //remove the Order ID from the waitlist.
            Iterator waitlist =  getWaitListOrderIDs();
            while(waitlist.hasNext()) {
                String wlID = (String) waitlist.next();

                if (wlID.equals(orderID)) {
                    waitlist.remove();
                }
            }

    }
    public void addManufacturer(String manID, Double manPrice) {
        //Andrew 2/23
        productManufacturer newMan = new productManufacturer(manID, manPrice);
        manufacturers.add(newMan);

    }
    public boolean removeproductManufacturer(String manID) {
        //Andrew 2/23

        Iterator manufacturers =  getProductManufacturers();
        while(manufacturers.hasNext()) {
            productManufacturer man = (productManufacturer) manufacturers.next();
            if (man.getManID().equals(manID)) {
                manufacturers.remove();
                return true;
            }
        }
        return false;
    }

    public Iterator getProductManufacturers() {
        return manufacturers.iterator();
    }
    public String toString() {
        return "name " + name + " price " + price + " id " + id;
    }
    public void changeQuantity(Integer amountAdded){
        quantity += amountAdded;
    }
    public void addWaitListOrderID(String orderId){
        waitListOrderIDs.add(orderId);
    }

}
