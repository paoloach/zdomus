package it.achdjian.paolo.domusviewer;

import android.support.test.espresso.NoMatchingViewException;
import android.support.test.espresso.ViewAssertion;
import android.view.View;
import android.widget.ImageView;

/**
 * Created by Paolo Achdjian on 03/06/16.
 */
public class ImageViewActivated implements ViewAssertion {
    private final ImageView imageView;

    public ImageViewActivated(ImageView imageView) {
        this.imageView = imageView;
    }

    @Override
    public void check(View view, NoMatchingViewException noViewFoundException) {
        if (!imageView.isActivated()){
            throw new AssertionError("The ImageView is not a activated");
        }
    }

    public static ViewAssertion imageViewIsActivated(ImageView imageView){
        return new ImageViewActivated(imageView);
    }
}
