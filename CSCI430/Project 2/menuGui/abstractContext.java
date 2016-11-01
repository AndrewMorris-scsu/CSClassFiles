import java.util.LinkedList;
import java.util.List;


public abstract class abstractContext {

    protected int currentState;

    int stateCount, transitionCount;
    int nextState[][];
    protected abstractState states[];

    public abstractContext () {
        //Default Constructor
    }

    protected void setTransitionTable(int numStates, int numTransitions) {
        this.stateCount = numStates;
        this.transitionCount = numTransitions;
        this.nextState = new int[stateCount][transitionCount];
        this.states = new abstractState[numStates];
    }

    public void addTransition(int row, int col, int value) {
        if (row >= stateCount || col >= transitionCount) {
            System.out.println("Error, out of bounds in state table");
        } else {
            nextState[ row ][ col ] = value;
        }
    }

    public void addState(int index, abstractState state) {
        if (index >= stateCount) {
            System.out.println("Cannot add state at index " + index);
        } else {
            states[index] = state;
        }
    }

    public abstractState getState(int x) {
        if (x >= stateCount) {
            System.out.println("Error -- State does not exist");
        }
        return states[x];
    }

    abstract void changeState(int transition);

}
