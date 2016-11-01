import sun.util.calendar.LocalGregorianCalendar;

/**
 * Created by Amandrew on 2/6/16.
 */
public class Transaction {
    private LocalGregorianCalendar.Date date;
    private String desc;
    private Double dollarAmt;

    public LocalGregorianCalendar.Date getDate() {
        return date;
    }

    public Double getDollarAmt() {
        return dollarAmt;
    }

    public String getDesc() {
        return desc;
    }

    public void setDate(LocalGregorianCalendar.Date date) {
        this.date = date;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    public void setDollarAmt(Double dollarAmt) {
        this.dollarAmt = dollarAmt;
    }
}
