package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.support.annotation.NonNull;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.DTO.WriteAttributeRequest;

/**
 * Created by Paolo Achdjian on 13/07/16.
 */
public class RequestWriteAttribute extends DomusEngineRest  {
    private final WriteAttributeRequest writeAttributeRequest;

    public RequestWriteAttribute(@NonNull SharedPreferences sharedPreferences, @NonNull ConnectionStatus connected, WriteAttributeRequest writeAttributeRequest) {
        super(sharedPreferences, connected);
        this.writeAttributeRequest = writeAttributeRequest;
    }

    @Override
    public void run() {
        JSonWittingAttribute.Attributes attributes = new JSonWittingAttribute.Attributes();
        if (writeAttributeRequest.args instanceof String) {
            attributes.attributes.add(new JSonWittingAttribute(writeAttributeRequest.attributeId,"string",  writeAttributeRequest.args ));
        }
        ObjectMapper mapper = new ObjectMapper();
        try {
            String json = mapper.writeValueAsString(attributes);
            post("/devices/"+writeAttributeRequest.networkId+"/endpoint/"+writeAttributeRequest.endpointId+"/cluster/in/"+writeAttributeRequest.clusterId+"/attributes", json);
        } catch (JsonProcessingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
