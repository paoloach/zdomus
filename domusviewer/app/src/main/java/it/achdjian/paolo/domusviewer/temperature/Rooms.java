package it.achdjian.paolo.domusviewer.temperature;

import android.util.Log;

import org.rajawali3d.Object3D;
import org.rajawali3d.util.OnObjectPickedListener;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Paolo Achdjian on 29/08/16.
 */
public class Rooms implements OnObjectPickedListener {
    public static final int DEFAULT_COLOR = 0xFFC0C0C0;
    public static final int SELECTED_COLOR = 0xFFC0FFFF;
    List<RoomObject> rooms = new ArrayList<>();

    public void addRoom(RoomObject room){
        rooms.add(room);
    }

    @Override
    public void onObjectPicked(Object3D object) {
        Log.d(getClass().getName(), "Pick object: " + object.getName());
        for(RoomObject roomObject: rooms){
            if (roomObject.object3D == object){
                roomObject.select();
            } else {
                roomObject.unselect();
            }
        }
    }

    RoomObject getSelected(){
        for(RoomObject room: rooms){
            if(room.selected){
                return  room;
            }
        }
        return null;
    }
}
