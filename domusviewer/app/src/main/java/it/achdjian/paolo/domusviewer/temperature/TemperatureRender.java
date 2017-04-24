package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.support.annotation.NonNull;
import android.util.Log;
import android.view.MotionEvent;

import com.google.common.util.concurrent.AtomicDouble;

import org.rajawali3d.cameras.Camera;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.renderer.Renderer;
import org.rajawali3d.util.ObjectColorPicker;

import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 20/07/16.
 */
public class TemperatureRender extends Renderer implements EndpointObserver {
    private static final double TEMPERATURE_UPDATE = 5;

    private Rooms rooms;
    private final TempSensorLocationDS tempSensorLocationDS;
    private final TemperatureCache temperatures;
    private double time = 0;
    private double nextUpdate = 1;
    private final AtomicDouble nextTempUpdate = new AtomicDouble(0);
    private ObjectColorPicker picker;
    private RoomObject roomToUpdate;
    private double rot = 0;


    public TemperatureRender(@NonNull Context context, @NonNull Rooms rooms, @NonNull TemperatureCache temperatures, @NonNull TempSensorLocationDS tempSensorLocationDS) {
        super(context);
        this.rooms = rooms;
        this.tempSensorLocationDS = tempSensorLocationDS;
        this.temperatures = temperatures;
    }

    public TemperatureRender(@NonNull Context context, boolean registerForResources) {
        super(context, registerForResources);
        tempSensorLocationDS = null;
        temperatures = null;
    }

    @Override
    protected void initScene() {

        picker = new ObjectColorPicker(this);

        rooms.initScene();

        for (int i = 0; i < rooms.countRooms(); i++) {
            RoomObject room = rooms.getRoom(0, i);
            if (room != null) {
                room.initScene(getCurrentScene(), getContext(), picker);

            }
        }
        Vector3 maxRooms = rooms.getMax(0);
        Vector3 minRooms = rooms.getMin(0);
        Log.d(getClass().getName(), "max: " + maxRooms + ", min: " + minRooms );
        Camera camera = getCurrentCamera();
        Vector3 lookAt = new Vector3(0,0, minRooms.z);
        camera.setLookAt(lookAt);
        Vector3 cameraPos = new Vector3((maxRooms.x +minRooms.x)/2,(maxRooms.y +minRooms.y)/2, maxRooms.z + 15);
        camera.setPosition(cameraPos);
        getCurrentScene().switchCamera(camera);
        picker.setOnObjectPickedListener(rooms);
        mSurface.requestRenderUpdate();
    }

    @Override
    public void onRender(final long elapsedTime, final double deltaTime) {
        time += deltaTime;
        rot++;
        if (time > nextTempUpdate.get()) {
            nextTempUpdate.set(nextTempUpdate.get() + TEMPERATURE_UPDATE);
            for (RoomObject room : rooms.rooms) {
                room.setTemperature(temperatures.getTemperature(room.name).orNull());
            }
        } else {
            if (roomToUpdate != null) {
                roomToUpdate.setTemperature(temperatures.getTemperature(roomToUpdate.name).orNull());
                roomToUpdate = null;
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
        picker.getObjectAt(x, y);
    }

    public void notifyFirstTemperature(String room) {
        roomToUpdate = rooms.getRoom(room);
        if (roomToUpdate != null) {
            temperatures.invalidate(roomToUpdate.name);
        }
    }

    @Override
    public void newDevice(ZEndpoint endpoint) {
        String room = tempSensorLocationDS.getRoom(Integer.parseInt(endpoint.short_address, 16), Integer.parseInt(endpoint.endpoint_id, 16));
        if (room != null) {
            temperatures.invalidate(room);
        }
        nextTempUpdate.set(-TEMPERATURE_UPDATE);
    }
}
