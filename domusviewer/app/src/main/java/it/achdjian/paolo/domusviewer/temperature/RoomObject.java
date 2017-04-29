package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.graphics.Color;
import android.opengl.GLES20;
import android.support.annotation.NonNull;

import com.google.common.base.Optional;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.rajawali3d.Object3D;
import org.rajawali3d.bounds.BoundingBox;
import org.rajawali3d.lights.SpotLight;
import org.rajawali3d.materials.Material;
import org.rajawali3d.materials.methods.DiffuseMethod;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.scene.Scene;
import org.rajawali3d.util.ObjectColorPicker;

import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;

/**
 * Created by Paolo Achdjian on 29/08/16.
 */
public class RoomObject {
    public final Object3D object3D;
    private final TempSensorLocationDS tempSensorLocationDS;
    private final TemperatureCache temperatureCache;
    private Scene scene;
    private ObjectColorPicker picker;
    public String name;
    public Material material;
    public SpotLight light;
    public boolean selected;
    public Vector3 mean;
    public TemperatureLabel temperatureLabel;
    public TrashLabel trashLabel;

    public RoomObject(@NonNull Object3D object3D, @NonNull TempSensorLocationDS tempSensorLocationDS, @NonNull TemperatureCache temperatureCache) {
        this.object3D = object3D;
        this.tempSensorLocationDS = tempSensorLocationDS;
        this.temperatureCache = temperatureCache;

        object3D.setBlendingEnabled(true);
        object3D.setDepthTestEnabled(true);
        object3D.setBlendFunc(GLES20.GL_ONE, GLES20.GL_ONE_MINUS_SRC_ALPHA);

        assignName();
        assignDefaultMaterial();
        assignLight();
    }

    public void initScene(@NonNull Scene scene, @NonNull Context context, ObjectColorPicker picker) {
        this.scene = scene;
        this.picker = picker;
        scene.addChild(object3D);
        scene.addLight(light);
        picker.registerObject(object3D);
        if (tempSensorLocationDS.getElement(name) != null) {
            initLabels(context);
        }
    }

    public void initLabels(@NonNull Context context) {
        temperatureLabel = new TemperatureLabel(this, temperatureCache);
        scene.addChild(temperatureLabel);
        trashLabel = new TrashLabel(context, this, Color.BLACK);
        scene.addChild(trashLabel);
        picker.registerObject(trashLabel);
    }

    public Vector3 getMax() {
        BoundingBox boundingBox = object3D.getGeometry().getBoundingBox();
        return boundingBox.getMax();
    }

    public Vector3 getMin() {
        BoundingBox boundingBox = object3D.getGeometry().getBoundingBox();
        return boundingBox.getMin();
    }

    private void assignLight() {
        BoundingBox boundingBox = object3D.getGeometry().getBoundingBox();
        Vector3 childMax = boundingBox.getMax();
        Vector3 childMin = boundingBox.getMin();
        mean = new Vector3((childMax.x + childMin.x) / 2, (childMax.y + childMin.y) / 2, childMax.z - 0.2);
        Vector3 look = new Vector3((childMax.x + childMin.x) / 2, (childMax.y + childMin.y) / 2, childMin.z);
        light = new SpotLight((float) look.x, (float) look.y, (float) look.z);
        light.setCutoffAngle(120);
        light.setColor(1.0f, 1.0f, 1.0f);
        light.setPower(1f);
        light.setPosition(mean);
    }

    private void assignDefaultMaterial() {
        material = new Material(true);
        material.setColor(Rooms.DEFAULT_COLOR);
        material.enableLighting(true);
        material.setDiffuseMethod(new DiffuseMethod.Lambert());
    }

    private void assignName() {
        name = object3D.getName();
        int lastIndex = name.lastIndexOf("_");
        name = name.substring(0, lastIndex);
    }

    @Override
    public String toString() {
        return new ToStringBuilder(this)
                .append("name", name)
                .toString();
    }

    public void select() {
        selected = true;
        Optional<Integer> temperature = temperatureCache.getTemperature(name);
        if (!temperature.isPresent()) {
            material.setColor(Rooms.SELECTED_COLOR);
        } else {
            updateTemp();
        }
    }

    public void deselect() {
        selected = false;
        Optional<Integer> temperature = temperatureCache.getTemperature(name);
        if (!temperature.isPresent()) {
            material.setColor(Rooms.DEFAULT_COLOR);
        } else {
            updateTemp();
        }
    }

    public void updateTemp() {
        if (temperatureLabel != null && material != null) {
            Optional<Integer> temp = temperatureCache.getTemperature(name);
            if (temp.isPresent()) {
                int color = TemperatureColorMap.getColor(temp.get());
                if (selected) {
                    color = ~(color & 0xFFFFFF);
                }
                material.setColor(color);
                material.enableLighting(true);
                material.setDiffuseMethod(new DiffuseMethod.Lambert());
                temperatureLabel.setTemperature(temp.get() / 100.0f, color);
            }
        }
    }


    public void removeTemperature() {
        tempSensorLocationDS.removeTempSensorLocation(name);
        scene.removeChild(temperatureLabel);
        temperatureLabel.destroy();
        temperatureLabel = null;

        scene.removeChild(trashLabel);
        picker.unregisterObject(trashLabel);
        trashLabel.destroy();
        trashLabel = null;
        material.setColor(Rooms.DEFAULT_COLOR);
    }
}
