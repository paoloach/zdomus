package it.achdjian.paolo.domusviewer.DomusEngineRest;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by paolo on 14/04/16.
 */
public class ConnectionStatus {
    private boolean connected=false;
    private List<ConnectionObserver> observers= new ArrayList<>();

    public boolean isConnected(){
        return connected;
    }

    public void setConnected(boolean connected){
        if(this.connected != connected) {
            this.connected = connected;
            for (ConnectionObserver observer : observers) {
                if (connected) {
                    observer.connected();
                } else {
                    observer.disconnected();
                }
            }
        }
    }

    public void addObserver(ConnectionObserver observer){
        observers.add(observer);
    }

    public void removeObserver(ConnectionObserver observer){
        observers.remove(observer);
    }


}
