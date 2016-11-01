import java.io.Serializable;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Andrew on 2/6/16.
 */
public class Order implements Serializable {
    private static final String ORDER_STRING = "O";
    private String ID;
    private List<lineItem> lineItems = new LinkedList();
    private String clientID;
    private Double totalPrice;

    Order ( String clientID) {
        this.clientID = clientID;
        this.totalPrice = 0.0;
        ID = ORDER_STRING + (OrderIdServer.instance()).getId();
    }

    public Double getTotalPrice() {
        return this.totalPrice;
    }
    public Iterator<lineItem> getLineItems() {
        return lineItems.iterator();
    }
    public String getClientID() {
        return this.clientID;
    }
    public String getID() {
        return ID;
    }
    public void setClientID(String clientID) {
        this.clientID = clientID;
    }
    public void setID(String ID) {
        this.ID = ID;
    }
    public void setLineItems(List<lineItem> lineItems) {
        this.lineItems = lineItems;
    }
    public lineItem getLineItemByProduct(String productID) {
        lineItem wantedLine = null;
        for (lineItem line : lineItems) {
            if (line.getProductID().equals(productID)) {
                wantedLine = line;
                break;
            }
        }
        return wantedLine;
    }

    public void addLineItem (String productID, Integer quantity) {
        lineItem newItem = new lineItem(productID, quantity);
        lineItems.add(newItem);
    }
    public void addDollarAmt(Double addedDollars) {
        totalPrice += addedDollars;
    }
    public void setTotalPrice(Double totalPrice) {
        this.totalPrice = totalPrice;
    }



    public String toString() {
        return "orderID:"+ this.ID + " clientID:"+ this.clientID + " price"+ this.totalPrice;
    }
}
