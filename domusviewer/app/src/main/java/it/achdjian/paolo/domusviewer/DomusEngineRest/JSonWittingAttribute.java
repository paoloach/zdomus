package it.achdjian.paolo.domusviewer.DomusEngineRest;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * Created by Paolo Achdjian on 13/07/16.
 */
public class JSonWittingAttribute {

    public static class Attributes {
        public List<JSonWittingAttribute> attributes = new ArrayList<>();
    };

    public JSonWittingAttribute(){

    }
    public JSonWittingAttribute(int id, String type, Object data){
        this.id = id;
        this.type = type;
        this.data = data;
    }
    public int id;
    public String type;
    public Object data;
}
