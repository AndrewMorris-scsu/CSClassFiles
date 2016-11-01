/**
 * Created by Ross Kostron on 3/20/2016.
 */
import java.util.*;
import java.text.*;
import java.io.*;

public class WarehouseContext {
    private int currentState;
    private static Warehouse warehouse;
    private static WarehouseContext context;
    private int currentUser;
    private String clientID;
    private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    public static final int IsClient = 0;
    public static final int IsClerk = 1;
    public static final int IsManager = 2;

    private WarehouseState[] states;
    private int[][] nextState;

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
        states = new WarehouseState[4];
        states[CLIENT_STATE] = Clientstate.instance();
        states[CLERK_STATE] = ClerkState.instance();
        states[MANAGER_STATE] = ManagerState.instance();
        states[LOGIN_STATE]=  LoginState.instance();
        nextState = new int[4][6];

        /* TRANSITIONS
                  * 0: Login as a Client
                  * 1: Login as a Clerk
                  * 2: Login as a Manager
                  * 3: Client Logout
                  * 4: Clerk Logout
                  * 5: Manager Logout
        */

        nextState[0][0] = 0; nextState[0][1] = -2;nextState[0][2] = -2; nextState[0][3] = 3; nextState[0][4] = -2; nextState[0][5] = -2;
        nextState[1][0] = 0; nextState[1][1] = 1; nextState[1][2] = -2; nextState[1][3] = 1; nextState[1][4] = 3;  nextState[1][5] = -2;
        nextState[2][0] = 0;nextState[2][1] = 1; nextState[2][2] =  2; nextState[2][3] = 1; nextState[2][4] = 2;  nextState[2][5] = 3;
        nextState[3][0] = 0; nextState[3][1] = 1; nextState[3][2] =  2; nextState[3][3] = -1;nextState[3][4] = -1; nextState[3][5] = -1;
        currentState = 3;
    }

    public void changeState(int transition)
    {
        //System.out.println("current state " + currentState + " \n ");
        //System.out.println("current User " + currentUser + " \n ");
        currentState = nextState[currentUser][transition];
        //System.out.println("current state " + currentState + " \n \n ");
        //System.out.println("current User " + currentUser + " \n ");
        if (currentState == -2)
        {System.out.println("Error has occurred"); terminate();}
        if (currentState == -1)
            terminate();

        states[currentState].run();
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
        states[currentState].run();
    }

    public static void main (String[] args){
        WarehouseContext.instance().process();
    }




}
