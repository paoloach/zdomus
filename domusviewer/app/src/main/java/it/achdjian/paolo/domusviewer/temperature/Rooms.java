package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

import org.androidannotations.annotations.AfterInject;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;
import org.rajawali3d.Object3D;
import org.rajawali3d.bounds.BoundingBox;
import org.rajawali3d.loader.LoaderOBJ;
import org.rajawali3d.loader.ParsingException;
import org.rajawali3d.materials.textures.TextureManager;
import org.rajawali3d.math.Matrix4;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.renderer.Renderer;
import org.rajawali3d.util.OnObjectPickedListener;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;

import static org.rajawali3d.util.GLU.gluProject;

/**
 * Created by Paolo Achdjian on 29/08/16.
 */
@EBean(scope = EBean.Scope.Singleton)
public class Rooms implements OnObjectPickedListener {
    public static final int DEFAULT_COLOR = 0xFFC0C0C0;
    public static final int SELECTED_COLOR = 0xFFC0FFFF;

    @RootContext
    Context context;
    @Bean
    TempSensorLocationDS tempSensorLocationDS;
    @Bean
    TemperatureCache temperatureCache;

    public final List<RoomObject> rooms = new ArrayList<>();
    private final List<List<String>> planes = new ArrayList<>();
    private final List<RoomObserver> roomObservers = new ArrayList<>();

    private Renderer render;

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
                RoomObject room = new RoomObject(child, tempSensorLocationDS,temperatureCache );
                rooms.add(room);
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
    public Vector3 getMin(int planeIndex) {
        if (planeIndex < 0 || planeIndex >= planes.size()) {
            throw new RuntimeException("Plane index out of range: " + planeIndex);
        }

        List<String> planeRooms = planes.get(planeIndex);
        Vector3 min = new Vector3(Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE);

        for (String roomName : planeRooms) {
            RoomObject room = getRoom(roomName);

            if (room != null) {
                BoundingBox boundingBox = room.object3D.getGeometry().getBoundingBox();
                Vector3 childMin = boundingBox.getMin();

                min.x = Math.min(min.x, childMin.x);
                min.y = Math.min(min.y, childMin.y);
                min.z = Math.min(min.z, childMin.z);
            }
        }
        return min;
    }

    @NonNull
    public Vector3 getMax(int planeIndex) {
        if (planeIndex < 0 || planeIndex >= planes.size()) {
            throw new RuntimeException("Plane index out of range: " + planeIndex);
        }

        List<String> planeRooms = planes.get(planeIndex);
        Vector3 max = new Vector3(Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE);

        for (String roomName : planeRooms) {
            RoomObject room = getRoom(roomName);

            if (room != null) {
                BoundingBox boundingBox = room.object3D.getGeometry().getBoundingBox();
                Vector3 childMax = boundingBox.getMax();
                max.x = Math.max(max.x, childMax.x);
                max.y = Math.max(max.y, childMax.y);
                max.z = Math.max(max.z, childMax.z);
            }
        }
        return max;
    }

    @Override
    public void onObjectPicked(@NonNull Object3D object) {
        RoomObject roomSelected = null;
        for (RoomObject roomObject : rooms) {
            if (roomObject.object3D == object) {
                roomObject.select();
                roomSelected = roomObject;
            }
            if (roomObject.trashLabel == object) {
                Log.d(getClass().getName(), "Remove sensor of " + roomObject.name);
                roomObject.removeTemperature();
                for (RoomObserver roomObserver : roomObservers) {
                    roomObserver.sensorAssignmentChange(roomObject.name);
                }
            }
        }
        if (roomSelected != null) {
            debugRoom(roomSelected, roomSelected.getMin());
            debugRoom(roomSelected, roomSelected.getMax());

            for (RoomObject roomObject : rooms) {
                if (roomObject != roomSelected) {
                    roomObject.deselect();
                }
            }
            for (RoomObserver roomObserver : roomObservers) {
                roomObserver.selected(roomSelected.name);
            }
        }
    }

    private void debugRoom(RoomObject roomSelected, Vector3 min) {
        Matrix4 viewMatrix = render.getCurrentCamera().getViewMatrix();
        Matrix4 projectionMatrix = render.getCurrentCamera().getProjectionMatrix();
        int[] viewPort = {0, 0, render.getViewportWidth(), render.getViewportHeight()};
        double[] pos4 = new double[4];
        gluProject(min.x ,min.y, min.z,viewMatrix.getDoubleValues(),0, projectionMatrix.getDoubleValues(), 0, viewPort,0,pos4, 0);
        printListDouble(roomSelected.name, pos4);
    }


    private void printListDouble(String name, double[] leftTop) {
        StringBuilder builder = new StringBuilder(name).append(" {");
        for (double pos : leftTop) {
            builder.append(pos).append(" , ");
        }
        builder.append("}");
        Log.i("RENDER", builder.toString());
    }

    @Override
    public void onNoObjectPicked() {

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
        Log.e(getClass().getName(), "Room " + room + " not found");
        return null;
    }

    public void initScene(getCurrentScene(), getContext(), picker) {
        for (RoomObject room : rooms) {
            room.object3D.setMaterial(room.material);
        }
    }

    public void addObserver(RoomObserver observer) {
        roomObservers.add(observer);
    }

    public void removeObserver(RoomObserver observer) {
        roomObservers.remove(observer);
    }


    public void setRenderer(TemperatureRender renderer) {
        this.render = renderer;
    }
}
