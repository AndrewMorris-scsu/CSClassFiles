import java.io.Serializable;

/**
 * Created by Amandrew on 2/23/16.
 */
public class productManufacturer implements Serializable {
    private String manID;
    private Double price;

    public productManufacturer (String manID, Double price) {
        this.manID = manID;
        this.price = price;
    }

    public Double getPrice() {
        return price;
    }
    public String getManID() {
        return manID;
    }

    public void setManID(String manID) {
        this.manID = manID;
    }

    public void setPrice(Double price) {
        this.price = price;
    }

    public String toString() {
        return "manufacturerID "+manID+ " price " +price;
    }
}
