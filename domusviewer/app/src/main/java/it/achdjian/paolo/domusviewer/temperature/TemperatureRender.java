package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.util.Log;
import android.view.MotionEvent;

import com.google.common.util.concurrent.AtomicDouble;

import org.rajawali3d.cameras.Camera;
import org.rajawali3d.cameras.Camera2D;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.renderer.RajawaliRenderer;
import org.rajawali3d.util.ObjectColorPicker;

import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 20/07/16.
 */
public class TemperatureRender extends RajawaliRenderer implements  EndpointObserver{
    private static final double TEMPERATURE_UPDATE = 5;

    private Rooms rooms;
    private final TempSensorLocationDS tempSensorLocationDS;
    private final TemperatureCache temperatures;
    private double time = 0;
    private double nextUpdate = 1;
    private final AtomicDouble nextTempUpdate = new AtomicDouble(0);
    private final Vector3 lookAt = new Vector3(0, 0, -10);
    private final Vector3 cameraPos = new Vector3(0, 0, 20);
    private ObjectColorPicker mPicker;
    private RoomObject roomToUpdate;


    public TemperatureRender(Context context, Rooms rooms, TemperatureCache temperatures, TempSensorLocationDS tempSensorLocationDS) {
        super(context);
        this.rooms = rooms;
        this.tempSensorLocationDS = tempSensorLocationDS;
        this.temperatures = temperatures;
    }

    public TemperatureRender(Context context, boolean registerForResources) {
        super(context, registerForResources);
        tempSensorLocationDS=null;
        temperatures = null;
    }

    @Override
    protected void initScene() {

        mPicker = new ObjectColorPicker(this);

        Camera2D camera2D = new Camera2D();
        rooms.initScene();

        Vector3 max = new Vector3(Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE);
        Vector3 min = new Vector3(Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE);

        for (int i = 0; i < rooms.countRooms(); i++) {
            RoomObject room = rooms.getRoom(0, i);
            if (room != null) {
                getCurrentScene().addChild(room.object3D);
                getCurrentScene().addLight(room.light);
                mPicker.registerObject(room.object3D);
            }
        }
        Vector3 size = rooms.getSize(0);
        Log.d(getClass().getName(), "max: " + max + ", min: " + min + ", size: " + size);
        Camera camera = getCurrentCamera();
        //camera = camera2D;
        camera.setLookAt(lookAt);
        camera.setPosition(cameraPos);
        camera2D.setWidth(size.x);
        camera2D.setHeight(size.y);
        camera2D.setProjectionMatrix(1, 1);
        getCurrentScene().switchCamera(camera);
        mPicker.setOnObjectPickedListener(rooms);

    }

    @Override
    public void onRender(final long elapsedTime, final double deltaTime) {
            time += deltaTime;
        if (time > nextTempUpdate.get()) {
            nextTempUpdate.set(nextTempUpdate.get() + TEMPERATURE_UPDATE);
            for (RoomObject room : rooms.rooms) {
                room.setTemperature(temperatures.getTemperature(room.name));
            }
        } else {
            if (roomToUpdate != null) {
                roomToUpdate.setTemperature(temperatures.getTemperature(roomToUpdate.name));
                roomToUpdate=null;
            }
        }
        if (time > nextUpdate) {
            nextUpdate += 0.1;
        }
        super.onRender(elapsedTime, deltaTime);
    }

    @Override
    public void onOffsetsChanged(float xOffset, float yOffset, float xOffsetStep, float yOffsetStep, int xPixelOffset, int yPixelOffset) {

    }

    @Override
    public void onTouchEvent(MotionEvent event) {
        Log.d(getClass().getName(), "event: " + event.getX() + " , " + event.getY());
    }

    public void getObjectAt(float x, float y) {
        mPicker.getObjectAt(x, y);
    }

    public void notifyFirstTemperature(String room) {
        roomToUpdate = rooms.getRoom(room);
        if (roomToUpdate != null) {
            temperatures.invalidate(roomToUpdate.name);
        }
    }

    @Override
    public void newDevice(ZEndpoint endpoint) {
        String room = tempSensorLocationDS.getRoom(endpoint.short_address, endpoint.endpoint_id);
        if (room != null) {
            temperatures.invalidate(room);
        }
        nextTempUpdate.set(-TEMPERATURE_UPDATE);
    }
}
