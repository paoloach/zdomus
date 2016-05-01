package it.achdjian.paolo.domusviewer.zigbee;

/**
 * Created by Paolo Achdjian on 25/04/16.
 */
public class BindRequestData {
    public int nwkSrc;
    public int epSrc;
    public int cluster;
    public int nwkDst;
    public int epDst;

    public BindRequestData(int nwkSrc, int epSrc, int cluster, int nwkDst, int epDst) {
        this.nwkSrc = nwkSrc;
        this.epSrc = epSrc;
        this.cluster = cluster;
        this.nwkDst = nwkDst;
        this.epDst = epDst;
    }
}
