package it.achdjian.paolo.domusviewer;

import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;

import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import static android.support.test.espresso.Espresso.onData;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static it.achdjian.paolo.domusviewer.ActivatedMatcher.isActivated;
import static it.achdjian.paolo.domusviewer.ElementMatcher.isElement;
import static it.achdjian.paolo.domusviewer.ImageViewActivated.imageViewIsActivated;
import static it.achdjian.paolo.domusviewer.NotActivatedMatcher.isNotActivated;
import static org.hamcrest.CoreMatchers.not;

/**
 * Created by Paolo Achdjian on 02/06/16.
 */
@RunWith(AndroidJUnit4.class)
public class OnOffTabTest {

    @Rule
    public ActivityTestRule<MainActivity_> mActivityRule =
            new ActivityTestRule<>(MainActivity_.class);

    @Test
    public void clickOnMainTextSelectRow() {
        onData(isElement(1235, 7))
                .inAdapterView(withId(R.id.lights))
                .onChildView(withId(R.id.mainText))
                .perform(click())
                .check(isActivated());
    }

    @Test
    public void clickOnLowerTextSelectRow() {
        onData(isElement(1235, 7))
                .inAdapterView(withId(R.id.lights))
                .onChildView(withId(R.id.lowerText))
                .perform(click())
                .check(isActivated());
    }

    @Test
    public void clickOnInfoLayoutSelectRow() {
        onData(isElement(1235, 7))
                .onChildView(withId(R.id.info_layout))
                .inAdapterView(withId(R.id.lights))
                .perform(click())
                .check(isActivated());
    }

    @Test
    public void clickBindSelect() {
        ViewBindedFind viewBindedFind = new ViewBindedFind();

        onData(isElement(1235, 7))
                .onChildView(withId(R.id.info_layout))
                .inAdapterView(withId(R.id.lights))
                .perform(click());
        onData(isElement(1234, 4))
                .onChildView(withId(R.id.binded))
                .inAdapterView(withId(R.id.switches))
                .check(isActivated());
    }

    @Test
    public void clickBindSelectDeselect() {
        ViewBindedFind viewBindedFind = new ViewBindedFind();

        onData(isElement(1235, 7))
                .onChildView(withId(R.id.info_layout))
                .inAdapterView(withId(R.id.lights))
                .perform(click());
        onData(isElement(1234, 4))
                .onChildView(withId(R.id.binded))
                .inAdapterView(withId(R.id.switches))
                .check(isActivated());

        onData(isElement(1234, 4))
                .onChildView(withId(R.id.info_layout))
                .inAdapterView(withId(R.id.switches))
                .perform(click());
        onData(isElement(1234, 4))
                .onChildView(withId(R.id.binded))
                .inAdapterView(withId(R.id.switches))
                .check(isNotActivated());
        onData(isElement(1235, 7))
                .onChildView(withId(R.id.binded))
                .inAdapterView(withId(R.id.lights))
                .check(isActivated());
        onData(isElement(1235, 11))
                .onChildView(withId(R.id.binded))
                .inAdapterView(withId(R.id.lights))
                .check(isActivated());
    }


}
