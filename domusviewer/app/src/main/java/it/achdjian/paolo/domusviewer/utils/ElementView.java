package it.achdjian.paolo.domusviewer.utils;

import android.content.Context;
import android.graphics.Color;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.other.IdentifyListener;
import it.achdjian.paolo.domusviewer.other.ZDeviceInfoClick;

/**
 * Created by Paolo Achdjian on 30/08/16.
 */
public class ElementView {
    public View view;
    public RelativeLayout infoLayout;
    public Element element;

    public ElementView(Context activity, ZDeviceInfoClick zDeviceInfoClick, IdentifyListener identifyListener, ViewGroup parent, int layoutId, Element element, View oldView) {
        this.element = element;
        if (oldView == null) {
            LayoutInflater inflater = LayoutInflater.from(activity);
            view = inflater.inflate(layoutId, parent, false);
        } else {
            view = oldView;
        }

        TextView mainText = (TextView) view.findViewById(R.id.mainText);
        if (view.getId() != R.id.info_layout) {
            infoLayout = (RelativeLayout) view.findViewById(R.id.info_layout);
        } else {
            infoLayout = (RelativeLayout) view;
        }
        infoLayout.setLongClickable(false);
        infoLayout.setOnLongClickListener(zDeviceInfoClick);
        infoLayout.setTag(R.id.element_value, element);
        infoLayout.setTag(R.id.element_view, this);

        mainText.setTextColor(Color.BLACK);
        mainText.setText(String.format("%04X:%02X",element.network, element.endpoint));

        view.setTag(R.id.element_value, element);
        view.setTag(R.id.element_view, this);
        Button IButton = (Button) view.findViewById(R.id.identifyBt);
        IButton.setTag(element);
        IButton.setOnClickListener(identifyListener);
    }

    public void selected(boolean actived){
        infoLayout.setActivated(actived);
    }

    public boolean isSelected(){
        return infoLayout.isActivated();
    }

    public void setOnClickListener(View.OnClickListener listener) {
        view.setOnClickListener(listener);
    }

    public void setTagType(int type){
        view.setTag(R.id.type, type);
    }
}
