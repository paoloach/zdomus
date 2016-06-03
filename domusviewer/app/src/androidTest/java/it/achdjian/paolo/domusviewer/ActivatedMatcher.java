package it.achdjian.paolo.domusviewer;

import android.support.test.espresso.NoMatchingViewException;
import android.support.test.espresso.ViewAssertion;
import android.view.View;

/**
 * Created by Paolo Achdjian on 02/06/16.
 */
public class ActivatedMatcher implements ViewAssertion {
    @Override
    public void check(View view, NoMatchingViewException noViewFoundException) {
        if (!view.isActivated()){
            throw new AssertionError("The view is not selected");
        }
    }

    public static ViewAssertion isActivated(){
        return new ActivatedMatcher();
    }
}
