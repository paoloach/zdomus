package it.achdjian.paolo.domusviewer;

import android.support.test.espresso.NoMatchingViewException;
import android.support.test.espresso.ViewAssertion;
import android.view.View;
import android.widget.ImageView;

/**
 * Created by Paolo Achdjian on 03/06/16.
 */
public class ViewBindedFind implements ViewAssertion {
    ImageView imageView;
    @Override
    public void check(View view, NoMatchingViewException noViewFoundException) {
        if (view instanceof ImageView){
            imageView = (ImageView)view;
        } else {
            throw new AssertionError("The view is not a ImageView");
        }
    }
}
