package it.achdjian.paolo.domusviewer.DomusEngineRest;

/**
 * Created by paolo on 14/04/16.
 */
public interface ConnectionObserver {
    void connected();

    void disconnected();
}