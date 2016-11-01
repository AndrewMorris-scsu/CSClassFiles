/**
 * Created by Ross Kostron on 3/20/2016.
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.text.*;
import java.io.*;
public class ManagerState extends WarehouseState implements ActionListener{
    private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private static Warehouse warehouse;
    private WarehouseContext context;
    private static ManagerState instance;
    private static final int EXIT = 0;
    private static final int ADD_MANUFACTURER = 4;
    private static final int ADD_PRODUCT_MANUFACTURER = 5;
    private static final int CLERKMENU = 12;

    private static final int HELP = 99;

    private JFrame frame;
    private AbstractButton
            addManufacturerButton,
            addProductManufacturerButton,
            clerkButton,

            logoutButton;

    private ManagerState() {
        super();
        warehouse = Warehouse.instance();
        //context = WarehouseContext.instance();
        warehouse = Warehouse.instance();
        //context = WarehouseContext.instance();
        addManufacturerButton = new JButton("Add Manufacturer");
        addProductManufacturerButton = new JButton("Add Product Manufacturer");
        clerkButton = new JButton("Login as Clerk");

        logoutButton = new JButton("logout");

        addManufacturerButton.addActionListener(this);
        addProductManufacturerButton.addActionListener(this);
        clerkButton.addActionListener(this);

        logoutButton.addActionListener(this);
    }


    public void actionPerformed(ActionEvent event) {

        if (event.getSource().equals(this.addManufacturerButton))
            addManufacturer();
        else if (event.getSource().equals(this.addProductManufacturerButton))
            addProductManufacturer();
        else if (event.getSource().equals(this.clerkButton))
            clerkmenu();
        else {
            System.out.println("Logout");
            this.logout();
        }

    }

    public void clear() { //clean up stuff
        frame.getContentPane().removeAll();
        frame.paint(frame.getGraphics());
    }



    public static ManagerState instance() {
        if (instance == null) {
            instance = new ManagerState();
        }
        return instance;
    }

    public String getToken(String prompt) {
        do {
            try {
                System.out.println(prompt);
                String line = reader.readLine();
                StringTokenizer tokenizer = new StringTokenizer(line, "\n\r\f");
                if (tokenizer.hasMoreTokens()) {
                    return tokenizer.nextToken();
                }
            } catch (IOException ioe) {
                System.exit(0);
            }
        } while (true);
    }

    private boolean yesOrNo(String prompt) {
        String more = getToken(prompt + " (Y|y)[es] or anything else for no");
        if (more.charAt(0) != 'y' && more.charAt(0) != 'Y') {
            return false;
        }
        return true;
    }

    public int getNumber(String prompt) {
        do {
            try {
                String item = getToken(prompt);
                Integer num = Integer.valueOf(item);
                return num.intValue();
            } catch (NumberFormatException nfe) {
                System.out.println("Please input a number ");
            }
        } while (true);
    }

    public Calendar getDate(String prompt) {
        do {
            try {
                Calendar date = new GregorianCalendar();
                String item = getToken(prompt);
                DateFormat df = SimpleDateFormat.getDateInstance(DateFormat.SHORT);
                date.setTime(df.parse(item));
                return date;
            } catch (Exception fe) {
                System.out.println("Please input a date as mm/dd/yy");
            }
        } while (true);
    }

    public int getCommand() {
        do {
            try {
                int value = Integer.parseInt(getToken("Enter command:" + HELP + " for help"));
                if (value >= EXIT && value <= HELP) {
                    return value;
                }
            } catch (NumberFormatException nfe) {
                System.out.println("Enter a number");
            }
        } while (true);
    }

    public void help() {
        System.out.println("Enter a number between 0 and 20 or 99 as explained below:");
        System.out.println(EXIT + " to Exit\n");
        System.out.println(ADD_MANUFACTURER + " to add an manufacturer");
        System.out.println(ADD_PRODUCT_MANUFACTURER + " to add product manufacturer");
        System.out.println(CLERKMENU + " to switch to the clerk menu");
        System.out.println(HELP + " for help");
    }

    public void addManufacturer()   {
        //Jared 3/20/16
        Manufacturer manufacturer;
        String name = getToken("Enter  name of manufacturer");
        String phone = getToken("Enter phone number");

        manufacturer = warehouse.addManufacturer(name, phone);
        if (manufacturer != null) {
            System.out.println(manufacturer);
        }
        else {
            System.out.println("Manufacturer could not be added");
        }
    }
    public void addProductManufacturer()    {
        String id = getToken("Enter manufacturer ID");
        Manufacturer manufacturer = warehouse.searchForManufacturer(id);
        if (manufacturer == null) {
            System.out.println("Manufacturer with ID "+id+" does not exist..");
            return;
        }
        String pid = getToken("Enter product id to which manufacturer is to be added");
        Product product = warehouse.searchForProduct(pid);
        if (product == null) {
            System.out.println("Product with ID "+pid+" does not exist..");
            return;
        }
        String price = getToken("Enter manufacturer's price for product");
        double productPrice;
        productPrice = Double.parseDouble(price);
        warehouse.addProductManufacturer(pid, id, productPrice);
    }
    public void clerkmenu()  {

            (WarehouseContext.instance()).changeState(1);

    }

    public void logout() {
        if (WarehouseContext.instance().getLogin() == WarehouseContext.IsManager) {
            (WarehouseContext.instance()).changeState(5); // exit with a code 0
        } else {
            //ERROR
            WarehouseContext.instance().changeState(0);
        }
    }

    public void process() {
        int command;
        help();
        while ((command = getCommand()) != EXIT) {
            switch (command) {
                case ADD_MANUFACTURER:        addManufacturer();
                    break;
                case ADD_PRODUCT_MANUFACTURER:         addProductManufacturer();
                    break;
                case CLERKMENU:          clerkmenu();
                    break;
                case HELP:              help();
                    break;
            }
        }
        logout();
    }
    public void run() {

        //process();
        frame = WarehouseContext.instance().getFrame();
        frame.getContentPane().removeAll();
        frame.getContentPane().setLayout(new FlowLayout());
        frame.getContentPane().add(this.addManufacturerButton);
        frame.getContentPane().add(this.addProductManufacturerButton);
        frame.getContentPane().add(this.clerkButton);
        frame.getContentPane().add(this.logoutButton);
        frame.setVisible(true);
        frame.paint(frame.getGraphics());
        System.out.println("In Manager State");
    }
}
