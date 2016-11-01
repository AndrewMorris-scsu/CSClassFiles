import java.io.Serializable;

/**
 * Created by Amandrew on 2/12/16.
 */
public class Manufacturer implements Serializable {

    private String id;
    private String name;
    private String phone;
    public String MANUFACTURER_STRING = "M";
    Manufacturer (String name, String phone) {
        this.name = name;
        this.phone = phone;
        id = MANUFACTURER_STRING + (ManufacturerIdServer.instance()).getId();
    }
    public String getName() {
        return name;
    }

    public String getPhone() {
        return phone;
    }

    public String getID() {
        return id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }
    public String toString() {
        return "id "+id+ " name "+ name + " phone " + phone;

    }
}
