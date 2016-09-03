package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.graphics.Path;
import android.util.Log;
import android.view.MotionEvent;

import com.google.common.base.Optional;
import com.google.common.cache.CacheBuilder;
import com.google.common.cache.LoadingCache;

import org.rajawali3d.Object3D;
import org.rajawali3d.bounds.BoundingBox;
import org.rajawali3d.cameras.Camera;
import org.rajawali3d.cameras.Camera2D;
import org.rajawali3d.loader.LoaderOBJ;
import org.rajawali3d.loader.ParsingException;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.renderer.RajawaliRenderer;
import org.rajawali3d.util.ObjectColorPicker;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.TimeUnit;

import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 20/07/16.
 */
public class TemperatureRender extends RajawaliRenderer {
    private static final double TEMPERATURE_UPDATE = 5;
    private static Map<Integer,Integer> MAP_TEMP_COLOR = new HashMap<>();
    static {
        MAP_TEMP_COLOR.put(13,0xFF0000E0);
        MAP_TEMP_COLOR.put(14,0xFF0000C0);
        MAP_TEMP_COLOR.put(15,0xFF0000A0);
        MAP_TEMP_COLOR.put(16,0xFF000080);
        MAP_TEMP_COLOR.put(17,0xFF000060);
        MAP_TEMP_COLOR.put(18,0xFF000040);
        MAP_TEMP_COLOR.put(19,0xFF008020);
        MAP_TEMP_COLOR.put(20,0xFF00FA00);
        MAP_TEMP_COLOR.put(21,0xFF19E100);
        MAP_TEMP_COLOR.put(22,0xFF32C800);
        MAP_TEMP_COLOR.put(23,0xFF4BAF00);
        MAP_TEMP_COLOR.put(24,0xFF649600);
        MAP_TEMP_COLOR.put(25,0xFF7D7D00);
        MAP_TEMP_COLOR.put(26,0xFF966400);
        MAP_TEMP_COLOR.put(27,0xFFAF4B00);
        MAP_TEMP_COLOR.put(28,0xFFC83200);
        MAP_TEMP_COLOR.put(29,0xFFE11900);
        MAP_TEMP_COLOR.put(30,0xFFFA0000);
    }
    private Rooms rooms;
    private LoadingCache<String, Optional<Integer>> temperatures;
    double min_X, max_X;

    private double time = 0;
    private double nextUpdate = 1;
    private double nextTempUpdate=0;
    private Camera2D camera2D;
    private Camera camera;
    private Vector3 size;
    private Object3D mObjectGroup;
    Vector3 lookAt = new Vector3(0, 0, -10);
    Vector3 cameraPos = new Vector3(0, 0, 20);
    private ObjectColorPicker mPicker;


    public TemperatureRender(Context context, Rooms rooms, TemperatureCacheLoader temperatures) {
        super(context);
        this.rooms = rooms;
        this.temperatures = CacheBuilder.newBuilder()
                .expireAfterWrite(1, TimeUnit.MINUTES)
                .build(temperatures);
    }

    public TemperatureRender(Context context, boolean registerForResources) {
        super(context, registerForResources);
    }

    @Override
    protected void initScene() {

        mPicker = new ObjectColorPicker(this);

        camera2D = new Camera2D();

        LoaderOBJ objParser = new LoaderOBJ(mContext.getResources(), mTextureManager, R.raw.pianoterra2_obj);
        try {
            objParser.parse();
            mObjectGroup = objParser.getParsedObject();
            Log.d(getClass().getName(), "num objects: " + mObjectGroup.getNumChildren());

        } catch (ParsingException e) {
            e.printStackTrace();
            return;
        }
        Vector3 max = new Vector3(Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE);
        Vector3 min = new Vector3(Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE);

        for (int i = 0; i < mObjectGroup.getNumChildren(); i++) {
            Object3D child = mObjectGroup.getChildAt(i);
            getCurrentScene().addChild(child);

            RoomObject room = new RoomObject(child);

            BoundingBox boundingBox = child.getGeometry().getBoundingBox();
            Vector3 childMax = boundingBox.getMax();
            Vector3 childMin = boundingBox.getMin();

            min_X = childMin.x;
            max_X = childMax.x;
            getCurrentScene().addLight(room.light);

            max.x = Math.max(max.x, childMax.x);
            max.y = Math.max(max.y, childMax.y);
            max.z = Math.max(max.z, childMax.z);

            min.x = Math.min(min.x, childMin.x);
            min.y = Math.min(min.y, childMin.y);
            min.z = Math.min(min.z, childMin.z);

            mPicker.registerObject(child);
            rooms.addRoom(room);

            Log.d(getClass().getName(), "room: " + room);
        }
        size = new Vector3(max.x - min.x, max.y - min.y, max.z - min.z);
        Log.d(getClass().getName(), "max: " + max + ", min: " + min + ", size: " + size);
        camera = getCurrentCamera();
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
        if (time > nextTempUpdate){
            nextTempUpdate += TEMPERATURE_UPDATE;
            for(RoomObject room: rooms.rooms){
                Optional<Integer> temp = temperatures.getUnchecked(room.name);
                if (temp.isPresent()){
                    Integer color;
                    if (temp.get() < 13){
                        color = 0xFF0000FF;
                    } else if (temp.get() > 30){
                        color = 0xFFFF0000;
                    } else {
                        color = MAP_TEMP_COLOR.get(temp.get());
                    }
                    room.material.setColor(color);
                }
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
}
