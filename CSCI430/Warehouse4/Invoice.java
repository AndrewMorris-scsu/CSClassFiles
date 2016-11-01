import java.io.Serializable;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Jared on 2/6/16.
 */
public class Invoice implements Serializable {
    private Double totalCost;
    private List<lineItem> lineItems = new LinkedList();

    Invoice(){
        this.totalCost = 0.0;
    }

    public double getTotalCost() { return totalCost; }
    public Iterator<lineItem> getLineItems() {
        return lineItems.iterator();
    }

    public void setTotalCost(double totalCost){ this.totalCost = totalCost; }
    public void setLineItems(List<lineItem> lineItems) {
        this.lineItems = lineItems;
    }

    public void addLineItem (String productID, Integer quantity) {
        lineItem newItem = new lineItem(productID, quantity);
        lineItems.add(newItem);
    }

    public String toString() {
        return " price"+ this.totalCost;
    }
}