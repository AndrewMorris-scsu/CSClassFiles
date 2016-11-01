/**
 * Created by Jared on 2/6/2016.
 */
import javax.sql.rowset.spi.TransactionalWriter;
import java.util.*;
import java.io.*;

public class Client implements Serializable {
    private static final long serialVersionUID = 1L;
    private String name;
    private String address;
    private String phone;
    private String id;
    private Double balanceDue;
    private static final String CLIENT_STRING = "C";

    private List<Transaction> transactions = new LinkedList();
    public  Client (String name, String address, String phone) {
        this.name = name;
        this.address = address;
        this.phone = phone;
        this.balanceDue = 0.0;
        id = CLIENT_STRING + (ClientIdServer.instance()).getId();
    }

    public String getName() {
        return name;
    }
    public String getPhone() {
        return phone;
    }
    public String getAddress() {
        return address;
    }
    public String getId() {
        return id;
    }
    public Double getBalanceDue() {
        return balanceDue;
    }

    public void setName(String newName) {
        name = newName;
    }
    public void setAddress(String newAddress) {
        address = newAddress;
    }
    public void setPhone(String newPhone) {
        phone = newPhone;
    }

    /*     MUTATORS FOR BALANCE    */
    public void addToBalance(Double amount) {
        balanceDue+=amount;
    }
    public void subtractFromBalance (Double amount) {
        balanceDue -=amount;
    }

    public boolean equals(String id) {
        return this.id.equals(id);
    }
    public String toString() {
        String string = "Client name " + name + " address " + address + " id " + id + "phone " + phone;
        return string;
    }

    public void addTransaction(Transaction t ){
        //Jared Kariniemi 2/12/16
        transactions.add(t);
    }

    public List<Transaction> getTransactions() {
            return transactions;
    }


}
