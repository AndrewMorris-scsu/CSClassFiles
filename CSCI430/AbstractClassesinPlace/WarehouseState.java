/**
 * Created by Ross Kostron on 3/20/2016.
 */
public abstract class WarehouseState extends abstractState {
    protected static WarehouseContext context;
    protected WarehouseState() {
        //context = LibContext.instance();
    }
    public abstract void run();
}
