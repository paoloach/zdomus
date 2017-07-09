package it.achdjian.paolo.domusviewer;

import org.hamcrest.Description;
import org.hamcrest.Matcher;
import org.hamcrest.TypeSafeMatcher;

/**
 * Created by Paolo Achdjian on 03/06/16.
 */
public class ElementMatcher extends TypeSafeMatcher<Element> {
    public final Element expected;

    public ElementMatcher(Element expected) {
        this.expected = expected;
    }


    @Override
    protected boolean matchesSafely(Element item) {
        return item.getNetwork() == expected.getNetwork() && item.getEndpoint() == expected.getEndpoint();
    }

    @Override
    public void describeTo(Description description) {
        description.appendText("Element: ").appendValue(expected);
    }

    public static Matcher isElement(int network, int endpoint){
        return new ElementMatcher(new Element(network,endpoint));
    }
}
