package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

import org.androidannotations.annotations.AfterInject;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;
import org.rajawali3d.Object3D;
import org.rajawali3d.bounds.BoundingBox;
import org.rajawali3d.loader.LoaderOBJ;
import org.rajawali3d.loader.ParsingException;
import org.rajawali3d.materials.textures.TextureManager;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.util.OnObjectPickedListener;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 29/08/16.
 */
@EBean(scope = EBean.Scope.Singleton)
public class Rooms implements OnObjectPickedListener {
    public static final int DEFAULT_COLOR = 0xFFC0C0C0;
    public static final int SELECTED_COLOR = 0xFFC0FFFF;

    @RootContext
    Context context;

    public final List<RoomObject> rooms = new ArrayList<>();
    private final List<List<String>> planes = new ArrayList<>();
    private final List<SelectedRoomObserver> roomObservers = new ArrayList<>();

    @AfterInject
    public void init() {
        planes.add(new ArrayList<String>());
        planes.get(0).add("Taverna");
        planes.get(0).add("Scale_taverna");
        planes.get(0).add("Sottoscala");
        planes.get(0).add("Ingresso-Garage");
        planes.get(0).add("Lavanderia");


        LoaderOBJ objParser = new LoaderOBJ(context.getResources(), TextureManager.getInstance(), R.raw.pianoterra2_obj);
        try {
            objParser.parse();
            Object3D mObjectGroup = objParser.getParsedObject();
            Log.d(getClass().getName(), "num objects: " + mObjectGroup.getNumChildren());
            for (int i = 0; i < mObjectGroup.getNumChildren(); i++) {
                Object3D child = mObjectGroup.getChildAt(i);
                rooms.add(new RoomObject(child));

            }
        } catch (ParsingException e) {
            e.printStackTrace();
        }
    }


    public int countRooms() {
        return rooms.size();
    }

    @Nullable
    public RoomObject getRoom(int planeIndex, int index) {
        if (planeIndex < 0 || planeIndex >= planes.size()) {
            throw new RuntimeException("Plane index out of range: " + planeIndex);
        }
        List<String> planeRooms = planes.get(planeIndex);
        if (index < 0 || index >= planeRooms.size()) {
            throw new RuntimeException("Index out of range: " + index);
        }
        return getRoom(planeRooms.get(index));
    }

    @NonNull
    public Vector3 getSize(int planeIndex) {
        if (planeIndex < 0 || planeIndex >= planes.size()) {
            throw new RuntimeException("Plane index out of range: " + planeIndex);
        }

        List<String> planeRooms = planes.get(planeIndex);
        Vector3 max = new Vector3(Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE);
        Vector3 min = new Vector3(Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE);

        for (String roomName : planeRooms) {
            RoomObject room = getRoom(roomName);

            if (room != null) {
                BoundingBox boundingBox = room.object3D.getGeometry().getBoundingBox();
                Vector3 childMax = boundingBox.getMax();
                Vector3 childMin = boundingBox.getMin();

                max.x = Math.max(max.x, childMax.x);
                max.y = Math.max(max.y, childMax.y);
                max.z = Math.max(max.z, childMax.z);

                min.x = Math.min(min.x, childMin.x);
                min.y = Math.min(min.y, childMin.y);
                min.z = Math.min(min.z, childMin.z);
            }
        }
        return new Vector3(max.x - min.x, max.y - min.y, max.z - min.z);
    }

    @Override
    public void onObjectPicked(Object3D object) {
        Log.d(getClass().getName(), "Pick object: " + object.getName());
        String roomSelected=null;
        for (RoomObject roomObject : rooms) {
            if (roomObject.object3D == object) {
                roomObject.select();
                roomSelected = roomObject.name;
            } else {
                roomObject.unselect();
            }
        }
        for (SelectedRoomObserver roomObserver : roomObservers) {
            roomObserver.selected(roomSelected);
        }
    }

    @Nullable
    RoomObject getSelected() {
        for (RoomObject room : rooms) {
            if (room.selected) {
                return room;
            }
        }
        return null;
    }

    @Nullable
    public RoomObject getRoom(@NonNull String room) {
        for (RoomObject roomObject : rooms) {
            if (roomObject.name.equals(room)) {
                return roomObject;
            }
        }
        Log.e(getClass().getName(),"Room " + room + " not found");
        return null;
    }

    public void initScene() {
        for (RoomObject room : rooms) {
            room.object3D.setMaterial(room.material);
        }
    }

    public void addObserver(SelectedRoomObserver observer) {
        roomObservers.add(observer);
    }

    public void removeObserver(SelectedRoomObserver observer) {
        roomObservers.remove(observer);
    }
}