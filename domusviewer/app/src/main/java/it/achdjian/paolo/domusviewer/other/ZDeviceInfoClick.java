package it.achdjian.paolo.domusviewer.other;

import android.support.v4.app.DialogFragment;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.RelativeLayout;

import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 22/06/16.
 */
@EBean
public class ZDeviceInfoClick implements View.OnLongClickListener {
    @RootContext
    AppCompatActivity activity;

    @Override
    public boolean onLongClick(View v) {
        return show(v);
    }

    private boolean show(View v) {
        if (v instanceof RelativeLayout) {
            Object tag = v.getTag(R.id.element_value);
            if (tag instanceof Element) {
                FragmentManager fragmentManager = activity.getSupportFragmentManager();
                FragmentTransaction ft = fragmentManager.beginTransaction();
                Fragment prev = fragmentManager.findFragmentByTag("dialog");
                if (prev != null) {
                    ft.remove(prev);
                }
                ft.addToBackStack(null);

                // Create and show the dialog.
                Element element = (Element) tag;
                DialogFragment newFragment = ZDeviceInfoFragment_.builder().
                        endpointId(element.getEndpoint()).
                        networkId(element.getNetwork()).
                        build();
                newFragment.show(ft, "dialog");
                return true;
            }
        }
        return false;
    }
}
