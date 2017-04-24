package it.achdjian.paolo.domusviewer.utils;

import android.database.DataSetObserver;
import android.os.Handler;

import java.util.HashSet;
import java.util.Set;

/**
 * Created by Paolo Achdjian on 24/04/17.
 */

public class UiObservers {
    private Handler handler;
    private Set<DataSetObserver> observers= new HashSet<>();

    public UiObservers(){
        handler = new Handler();
    }

    public void add(DataSetObserver observer){
        observers.add(observer);
    }

    public void remove(DataSetObserver observer){
        observers.remove(observer);
    }

    public void removeAll(){
        observers.clear();
    }

    public void onChangeNotify(){
        handler.post(new Runnable() {
            @Override
            public void run() {
                for(DataSetObserver observer: observers){
                    observer.onChanged();
                }
            }
        });
    }

    public void onInvalidatedNotify(){
        handler.post(new Runnable() {
            @Override
            public void run() {
                for(DataSetObserver observer: observers){
                    observer.onInvalidated();
                }
            }
        });
    }

}
