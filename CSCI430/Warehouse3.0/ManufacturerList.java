import java.io.Serializable;
import java.util.*;
import java.io.*;
/**
 * Created by Andrew on 2/12/16.
 */
public class ManufacturerList implements Serializable {
    private static final long serialVersionUID = 1L;
    private List manufacturers = new LinkedList();
    private static ManufacturerList manufacturerList;
    private ManufacturerList() {
    }
    public static ManufacturerList instance() {
        if (manufacturerList == null) {
            return (manufacturerList = new ManufacturerList());
        } else {
            return manufacturerList;
        }
    }

    public boolean insertManufacturer(Manufacturer maufacturer) {
        manufacturers.add(maufacturer);
        return true;
    }

    public Iterator getManufacturers(){
        return manufacturers.iterator();
    }

    private void writeObject(java.io.ObjectOutputStream output) {
        try {
            output.defaultWriteObject();
            output.writeObject(manufacturerList);
        } catch(IOException ioe) {
            ioe.printStackTrace();
        }
    }
    private void readObject(java.io.ObjectInputStream input) {
        try {
            if (manufacturerList != null) {
                return;
            } else {
                input.defaultReadObject();
                if (manufacturerList == null) {
                    manufacturerList = (ManufacturerList) input.readObject();
                } else {
                    input.readObject();
                }
            }
        } catch(IOException ioe) {
            ioe.printStackTrace();
        } catch(ClassNotFoundException cnfe) {
            cnfe.printStackTrace();
        }
    }
    public String toString() {
        return manufacturers.toString();
    }
}
