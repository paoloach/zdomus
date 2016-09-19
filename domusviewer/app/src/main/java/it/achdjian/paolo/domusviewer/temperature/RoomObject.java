package it.achdjian.paolo.domusviewer.temperature;

import android.opengl.GLES20;

import com.google.common.base.Optional;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.rajawali3d.Object3D;
import org.rajawali3d.bounds.BoundingBox;
import org.rajawali3d.lights.SpotLight;
import org.rajawali3d.materials.Material;
import org.rajawali3d.materials.methods.DiffuseMethod;
import org.rajawali3d.math.vector.Vector3;

/**
 * Created by Paolo Achdjian on 29/08/16.
 */
public class RoomObject {
    public String name;
    public Material material;
    public SpotLight light;
    public Object3D object3D;
    public boolean selected;
    public Optional<Integer> temperature =Optional.absent();

    public RoomObject(Object3D object3D) {

        this.object3D = object3D;

        object3D.setBlendingEnabled(true);
        object3D.setDepthTestEnabled(true);
        object3D.setBlendFunc(GLES20.GL_ONE, GLES20.GL_ONE_MINUS_SRC_ALPHA);

        assignName();
        assignDefaultMaterial();
        assignLight();
    }

    private void assignLight() {
        BoundingBox boundingBox = object3D.getGeometry().getBoundingBox();
        Vector3 childMax = boundingBox.getMax();
        Vector3 childMin = boundingBox.getMin();
        Vector3 mean = new Vector3((childMax.x + childMin.x) / 2, (childMax.y + childMin.y) / 2, childMax.z - 0.2);
        Vector3 look = new Vector3((childMax.x + childMin.x) / 2, (childMax.y + childMin.y) / 2, childMin.z);
        light = new SpotLight((float) look.x, (float) look.y, (float) look.z);
        light.setCutoffAngle(120);
        light.setColor(1.0f, 1.0f, 1.0f);
        light.setPower(1f);
        light.setPosition(mean);
    }

    private void assignDefaultMaterial() {
        material = new Material();
        material.setColor(Rooms.DEFAULT_COLOR);
        material.enableLighting(true);
        material.setDiffuseMethod(new DiffuseMethod.Lambert());
    }

    private void assignName() {
        name = object3D.getName();
        int delim = name.lastIndexOf("_");
        name = name.substring(0, delim);
    }

    @Override
    public String toString() {
        return new ToStringBuilder(this)
                .append("name", name)
                .toString();
    }

    public void select() {
        selected=true;
        if (!temperature.isPresent()) {
            material.setColor(Rooms.SELECTED_COLOR);
        } else {
            setTemperature(temperature);
        }
    }

    public void unselect() {
        selected=false;
        if (!temperature.isPresent()) {
            material.setColor(Rooms.DEFAULT_COLOR);
        } else {
            setTemperature(temperature);
        }
    }

    public void setTemperature(Optional<Integer> temp){
        if (temp.isPresent() && material != null) {
            temperature = temp;
            int color = TemperatureColorMap.getColor(temperature.get());
            if (selected) {
                color = ~(color & 0xFFFFFF);
            }
            material.setColor(color);
        }
    }


}
