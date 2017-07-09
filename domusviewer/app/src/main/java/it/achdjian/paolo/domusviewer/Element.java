package it.achdjian.paolo.domusviewer;


/**
 * Created by Paolo Achdjian on 02/05/16.
 */
public class Element {
    public final int network;
    public final int endpoint;


    public int getNetwork() {return network;}
    public int getEndpoint() {return  endpoint;}

    public Element(int short_address, int endpoint_id) {
        network = short_address;
        endpoint = endpoint_id;
    }

    public String getName(){
        return "{" + network + ":" + endpoint + "}";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Element element = (Element) o;

        return network == element.network && endpoint == element.endpoint;

    }


    @Override
    public int hashCode() {
        int result = network;
        result = 31 * result + endpoint;
        return result;
    }

    @Override
    public String toString() {
        return new org.apache.commons.lang3.builder.ToStringBuilder(this)
                .append("network", network)
                .append("endpoint", endpoint)
                .toString();
    }
}
