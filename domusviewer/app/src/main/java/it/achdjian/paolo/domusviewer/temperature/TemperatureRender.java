package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.opengl.GLES20;
import android.util.Log;
import android.view.MotionEvent;

import org.rajawali3d.Geometry3D;
import org.rajawali3d.Object3D;
import org.rajawali3d.bounds.BoundingBox;
import org.rajawali3d.cameras.Camera;
import org.rajawali3d.cameras.Camera2D;
import org.rajawali3d.lights.ALight;
import org.rajawali3d.lights.DirectionalLight;
import org.rajawali3d.lights.PointLight;
import org.rajawali3d.lights.SpotLight;
import org.rajawali3d.loader.LoaderOBJ;
import org.rajawali3d.loader.ParsingException;
import org.rajawali3d.materials.Material;
import org.rajawali3d.materials.methods.DiffuseMethod;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.renderer.RajawaliRenderer;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 20/07/16.
 */
public class TemperatureRender extends RajawaliRenderer {
    SpotLight moveLight;
    double min_X, max_X;
    boolean dir;

    private double time = 0;
    private double nextUpdate = 1;
    private Camera2D camera2D;
    private Camera camera;
    private Vector3 size;
    private Object3D mObjectGroup;
    Vector3 lookAt = new Vector3(0, 0, -10);
    Vector3 cameraPos = new Vector3(0, 0, 20);
    private Map<String, ALight> lights = new HashMap<>();

    public TemperatureRender(Context context) {
        super(context);
    }

    public TemperatureRender(Context context, boolean registerForResources) {
        super(context, registerForResources);
    }

    @Override
    protected void initScene() {
        camera2D = new Camera2D();

        LoaderOBJ objParser = new LoaderOBJ(mContext.getResources(), mTextureManager, R.raw.pianoterra2_obj);
        try {
            objParser.parse();
            mObjectGroup = objParser.getParsedObject();
            getCurrentScene().addChild(mObjectGroup);

        } catch (ParsingException e) {
            e.printStackTrace();
        }
        Vector3 max = new Vector3(Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE);
        Vector3 min = new Vector3(Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE);
        Geometry3D geometry = mObjectGroup.getGeometry();

        for (int i = 0; i < mObjectGroup.getNumChildren(); i++) {

            Object3D child = mObjectGroup.getChildAt(i);

            child.setBlendingEnabled(true);
            child.setDepthTestEnabled(true);
            child.setBlendFunc(GLES20.GL_ONE, GLES20.GL_ONE_MINUS_SRC_ALPHA);

            String name = child.getName();
            int delim = name.indexOf("_");
            name = name.substring(0, delim);
            BoundingBox boundingBox = child.getGeometry().getBoundingBox();
            Vector3 childMax = boundingBox.getMax();
            Vector3 childMin = boundingBox.getMin();
            Vector3 mean = new Vector3((childMax.x + childMin.x) / 2, (childMax.y + childMin.y) / 2, childMax.z-0.2);
            Vector3 look = new Vector3((childMax.x + childMin.x) / 2, (childMax.y + childMin.y) / 2, childMin.z);

            if (name.equals("Taverna")){
                Material material = new Material();
                material.setColor(0xFF009900);
                material.enableLighting(true);
                material.setDiffuseMethod(new DiffuseMethod.Lambert());
                child.setMaterial(material);


            }

            SpotLight light = new SpotLight((float)look.x,(float)look.y, (float)look.z);
            moveLight=light;
            min_X = childMin.x;
            max_X = childMax.x;
            light.setCutoffAngle(120);
            light.setColor(1.0f, 1.0f, 1.0f);
            light.setPower(1f);
            light.setPosition(mean);
            getCurrentScene().addLight(light);

            lights.put(name, light);

            max.x = Math.max(max.x, childMax.x);
            max.y = Math.max(max.y, childMax.y);
            max.z = Math.max(max.z, childMax.z);

            min.x = Math.min(min.x, childMin.x);
            min.y = Math.min(min.y, childMin.y);
            min.z = Math.min(min.z, childMin.z);

            Log.d(getClass().getName(), "child: " + name + ", isTransparent: " + child.isTransparent() );
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
    }

    @Override
    public void onRender(final long elapsedTime, final double deltaTime) {
        time += deltaTime;
        if (time > nextUpdate) {
            nextUpdate+=0.1;
//            if (dir){
//                Vector3 position = moveLight.getPosition();
//                position.x += 0.1;
//                if (position.x > max_X){
//                    dir=false;
//                }
//                moveLight.setPosition(position);
//                position=moveLight.getLookAt();
//                position.x +=0.1;
//                moveLight.setLookAt(position);
//            }else {
//                Vector3 position = moveLight.getPosition();
//                position.x -= 0.1;
//                if (position.x < min_X){
//                    dir=true;
//                }
//                moveLight.setPosition(position);
//                position=moveLight.getLookAt();
//                position.x -=0.1;
//                moveLight.setLookAt(position);
//            }
//                cameraPos.x -= 0.1;
//                cameraPos.y -= 0.1;
//            //cameraPos.z -= 0.1;
//                 camera.setPosition(cameraPos);
//                lookAt.x -= 0.1;
//                lookAt.y -= 0.1;
//                camera.setLookAt(lookAt);
/*            size.x += 10;
            size.y += 10;
                camera2D.setWidth(size.x);
                camera2D.setHeight(size.y);
                camera2D.setProjectionMatrix(1,1);
                Log.d(getClass().getName(),"pos: " + cameraPos + " , lookAt: " + lookAt);
  */
        }
        super.onRender(elapsedTime, deltaTime);
    }

    @Override
    public void onOffsetsChanged(float xOffset, float yOffset, float xOffsetStep, float yOffsetStep, int xPixelOffset, int yPixelOffset) {

    }

    @Override
    public void onTouchEvent(MotionEvent event) {

    }

    public void enableLight(String name, boolean isChecked) {
        ALight ligh = lights.get(name);
        if (ligh != null) {
            if (isChecked) {
                ligh.setPower(1);
            } else {
                ligh.setPower(0);
            }
        }
    }
}
