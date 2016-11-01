import sun.util.calendar.LocalGregorianCalendar;

import java.util.Calendar;

/**
 * Created by Andrew on 2/6/16.
 */
public class Transaction {
    private String date;
    private String desc;
    private Double dollarAmt;


    Transaction(String d, String description, double dollar){
        this.date = d;
        this.desc = description;
        this.dollarAmt = dollar;
    }
    public String getDate() {
        return date;
    }

    public Double getDollarAmt() {
        return dollarAmt;
    }

    public String getDesc() {
        return desc;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    public void setDollarAmt(Double dollarAmt) {
        this.dollarAmt = dollarAmt;
    }
}
