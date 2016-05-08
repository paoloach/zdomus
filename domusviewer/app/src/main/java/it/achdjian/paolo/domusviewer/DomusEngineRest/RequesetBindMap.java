package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import it.achdjian.paolo.domusviewer.Element;

/**
 * Created by Paolo Achdjian on 02/05/16.
 */
public class RequesetBindMap extends DomusEngineRest {
    private final Map<Integer, Map<Element, Set<Element>>> srcDstBindMap;
    private final Map<Integer, Map<Element, Set<Element>>> dstSrcBindMap;

    public RequesetBindMap(SharedPreferences sharedPreferences, ConnectionStatus connected, Map<Integer, Map<Element, Set<Element>>> srcDstBindMap, Map<Integer, Map<Element, Set<Element>>> dstSrcBindMap) {
        super(sharedPreferences,connected);
        this.srcDstBindMap = srcDstBindMap;
        this.dstSrcBindMap = dstSrcBindMap;
    }

    @Override
    public void run() {
        String body = get("/binds");
        if (body != null) {
            if (!body.isEmpty()) {
                ObjectMapper mapper = new ObjectMapper();
                try {
                    List<JSonBinds> binds = mapper.readValue(body, new TypeReference<List<JSonBinds>>() { });
                    for (JSonBinds bind : binds) {
                        Element srcKey = new Element(bind.sourceAddr, bind.sourceEndpoint);
                        Element dstKey = new Element(bind.destAddr, bind.destEndpoint);

                        if (!srcDstBindMap.containsKey(bind.cluster)){
                            srcDstBindMap.put(bind.cluster, Collections.synchronizedMap(new HashMap<Element, Set<Element>>()));
                        }
                        Map<Element, Set<Element>> srcElementMap = srcDstBindMap.get(bind.cluster);

                        if(!srcElementMap.containsKey(srcKey)){
                            srcElementMap.put(srcKey, new HashSet<Element>());
                        }
                        srcElementMap.get(srcKey).add(dstKey);

                        if (!dstSrcBindMap.containsKey(bind.cluster)){
                            dstSrcBindMap.put(bind.cluster, Collections.synchronizedMap(new HashMap<Element, Set<Element>>()));
                        }
                        Map<Element, Set<Element>> dstElementMap = dstSrcBindMap.get(bind.cluster);
                        if(!dstElementMap.containsKey(dstKey)){
                            dstElementMap.put(dstKey, new HashSet<Element>());
                        }
                        dstElementMap.get(dstKey).add(srcKey);

                    }
                } catch (IOException e) {
                     e.printStackTrace();
                }
            }
        }
    }
}
