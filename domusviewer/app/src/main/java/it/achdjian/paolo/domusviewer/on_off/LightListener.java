package it.achdjian.paolo.domusviewer.on_off;

import android.support.annotation.NonNull;

/**
 * Created by Paolo Achdjian on 25/04/16.
 */
public interface LightListener {
    void changeLight(@NonNull OnOffAdapter.Element element, boolean selected);
}
