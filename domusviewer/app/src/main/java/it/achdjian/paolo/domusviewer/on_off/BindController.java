package it.achdjian.paolo.domusviewer.on_off;

import android.view.View;
import android.widget.ImageView;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;

import java.util.Map;
import java.util.Set;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.zigbee.ClustersId;

/**
 * Created by Paolo Achdjian on 25/04/16.
 */
@EBean
public class BindController implements OnOffListener {
    public OnOffAdapter switchAdapter = null;
    public OnOffAdapter lightAdapter = null;

    @Bean
    public ElementSelected elementSelected;
    @Bean
    DomusEngine domusEngine;



    @Override
    public void change() {
        if (lightAdapter != null) {
            lightAdapter.invalidate();
        }
        if (switchAdapter != null) {
            switchAdapter.invalidate();
        }
    }

    public void setBindStatus(View result) {
        ImageView bindedImg = (ImageView) result.findViewById(R.id.binded);
        Object tagType = result.getTag(R.id.type);
        Object tagElement = result.getTag(R.id.element_value);
        if (tagType instanceof Integer && tagElement instanceof Element) {
            int typeValue = (Integer) tagType;
            Element element = (Element) tagElement;

            if (elementSelected.selected != null) {
                Map<Element, Set<Element>> elementSetMap;
                if (typeValue == OnOffAdapter.TYPE_LIGHT) {
                    elementSetMap = domusEngine.srcDstBindMap.get(ClustersId.ON_OFF_CLUSTER);
                } else {
                    elementSetMap = domusEngine.dstSrcBindMap.get(ClustersId.ON_OFF_CLUSTER);
                }
                if (elementSetMap != null) {
                    if (elementSetMap.containsKey(elementSelected.selected) && elementSetMap.get(elementSelected.selected).contains(element)) {
                        bindedImg.setActivated(true);
                    } else {
                        bindedImg.setActivated(false);
                    }
                }
            }
        }
    }
}
