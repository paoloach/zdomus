package it.achdjian.paolo.domusviewer.temperature;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

/**
 * Created by Paolo Achdjian on 13/09/16.
 */
public interface RoomObserver {
    void selected(@Nullable String selectedRoom);
    void sensorAssignmentChange(@NonNull String roomName);
}
