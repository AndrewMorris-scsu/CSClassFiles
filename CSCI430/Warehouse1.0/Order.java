import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Amandrew on 2/6/16.
 */
public class Order implements Serializable {
    private static final String ORDER_STRING = "O";
    private String ID;
    private List<lineItem> lineItems = new LinkedList();
    private String clientID;
    private Double totalPrice;

    Order (List<lineItem> lineItems, String clientID, Double totalPrice) {
        this.lineItems.addAll(lineItems);
        this.lineItems = lineItems;
        this.clientID = clientID;
        this.totalPrice = totalPrice;
        ID = ORDER_STRING + (OrderIdServer.instance()).getId();
    }

    public Double getTotalPrice() {
        return this.totalPrice;
    }
    public List<lineItem> getLineItems() {
        return this.lineItems;
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

    public void setTotalPrice(Double totalPrice) {
        this.totalPrice = totalPrice;
    }
}
