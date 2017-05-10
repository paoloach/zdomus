package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.support.annotation.NonNull;
import android.util.Log;
import android.view.MotionEvent;

import com.google.common.util.concurrent.AtomicDouble;

import org.rajawali3d.cameras.Camera;
import org.rajawali3d.math.Matrix4;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.renderer.Renderer;
import org.rajawali3d.util.GLU;
import org.rajawali3d.util.ObjectColorPicker;
import org.rajawali3d.view.SurfaceView;

import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

import static org.rajawali3d.util.GLU.gluProject;

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
    private boolean init=false;
    private int width=0;
    private int height=0;


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
        init=true;
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
        Log.d("RENDER", "max: " + maxRooms + ", min: " + minRooms );
        Camera camera = getCurrentCamera();
        Vector3 lookAt = new Vector3(0,0, minRooms.z);
        camera.setLookAt(lookAt);
        Vector3 cameraPos = new Vector3((maxRooms.x +minRooms.x)/2,(maxRooms.y +minRooms.y)/2, maxRooms.z + 15);
        camera.setPosition(cameraPos);
        getCurrentScene().switchCamera(camera);
        picker.setOnObjectPickedListener(rooms);
        mSurface.requestRenderUpdate();

        adjustCamera();
    }

    private void adjustCamera() {
        final Camera currentCamera = getCurrentCamera();
        double z = currentCamera.getZ();
        Vector3 maxRooms = rooms.getMax(0);
        Vector3 minRooms = rooms.getMin(0);
        while (true) {
            Matrix4 viewMatrix = currentCamera.getViewMatrix();
            Matrix4 projectionMatrix = currentCamera.getProjectionMatrix();

            int[] viewPort = {0, 0, getViewportWidth(), getViewportHeight()};
            double[] posMin = new double[4];
            double[] posMax = new double[4];
            gluProject(minRooms.x, minRooms.y, minRooms.z, viewMatrix.getDoubleValues(), 0, projectionMatrix.getDoubleValues(), 0, viewPort, 0, posMin, 0);

            gluProject(maxRooms.x, maxRooms.y, maxRooms.z, viewMatrix.getDoubleValues(), 0, projectionMatrix.getDoubleValues(), 0, viewPort, 0, posMax, 0);

            double widthObj = posMax[0] - posMin[0];
            double heightObj = posMax[1] - posMin[1];
            if (Math.abs(widthObj-width) < 1 && (height > heightObj)){
                break;
            }
            if (Math.abs(heightObj-height) < 1 && (width > widthObj)){
                break;
            }
            if (widthObj > width){
                z += 0.01;
            } else {
                z -= 0.01;
            }
            currentCamera.setZ(z);
        }
    }

    @Override
    public void onRender(final long elapsedTime, final double deltaTime) {
        time += deltaTime;
        rot++;
        if (time > nextTempUpdate.get()) {
            nextTempUpdate.set(nextTempUpdate.get() + TEMPERATURE_UPDATE);
            for (RoomObject room : rooms.rooms) {
                room.updateTemp();

            }
        } else {
            if (roomToUpdate != null) {
                roomToUpdate.updateTemp();
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

    public void debug(SurfaceView surface) {
        Log.i("RENDER", "surface: {0,0-"+surface.getWidth()+","+ surface.getHeight()+ "}");
        double[] leftTop = getObjectCoordinate(0, 0);
        printListDouble("leftTop", leftTop);
        double[] rightTop = getObjectCoordinate(surface.getWidth(), 0);
        printListDouble("rightTop", rightTop);
        double[] leftBottom = getObjectCoordinate(0, surface.getHeight());
        printListDouble("leftBottom", leftBottom);
        double[] rightBottom = getObjectCoordinate(surface.getWidth(), surface.getHeight());
        printListDouble("rightBottom", rightBottom);
    }

    private void printListDouble(String name, double[] leftTop) {
        StringBuilder builder = new StringBuilder(name).append(" {");
        for (double pos : leftTop) {
            builder.append(pos).append(" , ");
        }
        builder.append("}");
        Log.i("RENDER", builder.toString());
    }

    double [] getObjectCoordinate(float x, float y) {
        Matrix4 viewMatrix = getCurrentCamera().getViewMatrix();
        Matrix4 projectionMatrix = getCurrentCamera().getProjectionMatrix();
        int[] viewPort = {0, 0, getViewportWidth(), getViewportHeight()};
        double[] pos4 = new double[4];

        GLU.gluUnProject(x, getViewportHeight() - y, -3, viewMatrix.getDoubleValues(), 0,
                projectionMatrix.getDoubleValues(), 0, viewPort, 0, pos4, 0);
        return pos4;
    }

    public void onSurfaceViewLayoutChange(int left, int top, int right, int bottom) {
        width = right-left;
        height = bottom-top;
    }
}
