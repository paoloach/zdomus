package it.achdjian.paolo.domusviewer.temperature;

import android.support.annotation.Nullable;

/**
 * Created by Paolo Achdjian on 13/09/16.
 */
public interface SelectedRoomObserver {
    void selected(@Nullable String selectedRomm);
}
