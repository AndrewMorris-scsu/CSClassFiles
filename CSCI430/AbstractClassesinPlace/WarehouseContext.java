/**
 * Created by Ross Kostron on 3/20/2016.
 */
import java.util.*;
import java.text.*;
import java.io.*;

public class WarehouseContext extends abstractContext {

    private static Warehouse warehouse;
    private static WarehouseContext context;
    private int currentUser;
    private String clientID;
    private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    public static final int IsClient = 0;
    public static final int IsClerk = 1;
    public static final int IsManager = 2;

    public String getToken(String prompt) {
        do {
            try {
                System.out.println(prompt);
                String line = reader.readLine();
                StringTokenizer tokenizer = new StringTokenizer(line,"\n\r\f");
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

    private void retrieve() {
        try {
            Warehouse tempWarehouse = Warehouse.retrieve();
            if (tempWarehouse != null) {
                System.out.println(" The warehouse has been successfully retrieved from the file WarehouseData \n" );
                warehouse = tempWarehouse;
            } else {
                System.out.println("File doesnt exist; creating new warehouse" );
                warehouse = Warehouse.instance();
            }
        } catch(Exception cnfe) {
            cnfe.printStackTrace();
        }
    }

    public void setLogin(int code)
    {currentUser = code;}

    public void setClient(String uID)
    { clientID = uID;}

    public int getLogin()
    { return currentUser;}

    public String getClient()
    { return clientID;}

    private WarehouseContext() { //constructor
        //System.out.println("In Warehousecontext constructor");
        if (yesOrNo("Look for saved data and  use it?")) {
            retrieve();
        } else {
            warehouse = Warehouse.instance();
        }

        final int CLIENT_STATE = 0;
        final int CLERK_STATE = 1;
        final int MANAGER_STATE = 2;
        final int LOGIN_STATE = 3;

        // set up the FSM and transition table;
        super.setTransitionTable(4,6);
        super.addState(CLIENT_STATE, Clientstate.instance());
        super.addState(CLERK_STATE, ClerkState.instance());
        super.addState(MANAGER_STATE, ManagerState.instance());
        super.addState(LOGIN_STATE, LoginState.instance());

        /* TRANSITIONS
                  * 0: Login as a Client
                  * 1: Login as a Clerk
                  * 2: Login as a Manager
                  * 3: Client Logout
                  * 4: Clerk Logout
                  * 5: Manager Logout
        */


        super.addTransition(0,0,-2); super.addTransition(0,1,-2); super.addTransition(0,2,-2); super.addTransition(0,3, 3); super.addTransition(0,4,1);  super.addTransition(0,5,1);
        super.addTransition(1,0,0);  super.addTransition(1,1,-2); super.addTransition(1,2,-2); super.addTransition(1,3,-2);  super.addTransition(1,4,3);  super.addTransition(1,5,2);
        super.addTransition(2,0,-2); super.addTransition(2,1,1);  super.addTransition(2,2,-2); super.addTransition(2,3,-2);  super.addTransition(2,4,-2); super.addTransition(2,5,3);
        super.addTransition(3,0,0);  super.addTransition(3,1,1);  super.addTransition(3,2,2); super.addTransition(3,3,-1); super.addTransition(3,4,-1);    super.addTransition(3,5,-1);
        currentState = 3;
    }

    public void changeState(int transition)
    {
        //System.out.println("current state " + currentState + " \n ");
        //System.out.println("current User " + currentUser + " \n ");
        super.currentState = super.nextState[currentState][transition];
        //System.out.println("current state " + currentState + " \n \n ");
        //System.out.println("current User " + currentUser + " \n ");
        if (super.currentState == -2)
        {System.out.println("Error has occurred"); terminate();}
        if (super.currentState == -1)
            terminate();

        super.states[currentState].run();
    }



    private void terminate()
    {
        if (yesOrNo("Save data?")) {
            if (warehouse.save()) {
                System.out.println(" The warehouse has been successfully saved in the file WarehouseData \n" );
            } else {
                System.out.println(" There has been an error in saving \n" );
            }
        }
        System.out.println(" Goodbye \n "); System.exit(0);
    }

    public static WarehouseContext instance() {
        if (context == null) {
            //System.out.println("calling constructor");
            context = new WarehouseContext();
        }
        return context;
    }

    public void process(){

        this.getState(currentState).run();
    }

    public static void main (String[] args){
        WarehouseContext.instance().process();
    }




}
