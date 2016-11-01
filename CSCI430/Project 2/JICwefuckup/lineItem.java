import java.io.Serializable;

/**
 * Created by Amandrew on 2/6/16.
 */
public class lineItem implements Serializable {
    private String productID;
    private Integer quantityOrdered;
    private Integer quantityShipped;


    public lineItem(String productID, Integer quantity) {
        this.productID = productID;
        this.quantityOrdered = quantity;
        this.quantityShipped = 0;
    }

    public String getProductID() {
        return productID;
    }

    public Integer getQuantityOrdered() {
        return quantityOrdered;
    }

    public Integer getQuantityShipped() {
        return quantityShipped;
    }

    public void setProductID(String productID) {
        this.productID = productID;
    }

    public void setQuantityOrdered(Integer quantityOrdered) {
        this.quantityOrdered = quantityOrdered;
    }

    public void setQuantityShipped(Integer quantityShipped) {
        this.quantityShipped = quantityShipped;
    }

    public String toString() {
        return "ProductID "+productID+ " quantityOrdered "+quantityOrdered+ " quantityShipped "+ quantityShipped;
    }
}