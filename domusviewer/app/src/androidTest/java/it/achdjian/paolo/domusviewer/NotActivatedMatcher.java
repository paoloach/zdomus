package it.achdjian.paolo.domusviewer;

import android.support.test.espresso.NoMatchingViewException;
import android.support.test.espresso.ViewAssertion;
import android.view.View;

/**
 * Created by Paolo Achdjian on 02/06/16.
 */
public class NotActivatedMatcher implements ViewAssertion {
    @Override
    public void check(View view, NoMatchingViewException noViewFoundException) {
        if (view.isActivated()){
            throw new AssertionError("The view is not selected");
        }
    }

    public static ViewAssertion isNotActivated(){
        return new NotActivatedMatcher();
    }
}
