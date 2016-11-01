/**
 * Created by Amandrew on 2/6/16.
 */
public class lineItem {
    private String productID;
    private Integer quantityOrdered;
    private Integer quantityShipped;

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
}
