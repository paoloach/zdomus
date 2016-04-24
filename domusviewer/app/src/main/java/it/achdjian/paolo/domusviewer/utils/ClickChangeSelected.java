package it.achdjian.paolo.domusviewer.utils;

import android.view.View;

import static android.view.View.*;

/**
 * Created by Paolo Achdjian on 21/04/16.
 */
public class ClickChangeSelected implements OnClickListener {
    @Override
    public void onClick(View v) {
        if (v.isSelected())
            v.setSelected(false);
        else
            v.setSelected(true);
    }
}
