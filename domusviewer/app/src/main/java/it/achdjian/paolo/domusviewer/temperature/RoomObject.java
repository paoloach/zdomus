package it.achdjian.paolo.domusviewer.temperature;

import android.opengl.GLES20;

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

    public RoomObject(Object3D object3D) {

        this.object3D = object3D;

        object3D.setBlendingEnabled(true);
        object3D.setDepthTestEnabled(true);
        object3D.setBlendFunc(GLES20.GL_ONE, GLES20.GL_ONE_MINUS_SRC_ALPHA);

        assignName(object3D);
        assignDefaultMaterial(object3D);
        assignLight(object3D);
    }

    private void assignLight(Object3D object3D) {
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

    private void assignDefaultMaterial(Object3D object3D) {
        material = new Material();
        material.setColor(Rooms.DEFAULT_COLOR);
        material.enableLighting(true);
        material.setDiffuseMethod(new DiffuseMethod.Lambert());
        object3D.setMaterial(material);
    }

    private void assignName(Object3D object3D) {
        name = object3D.getName();
        int delim = name.indexOf("_");
        name = name.substring(0, delim);
    }

    @Override
    public String toString() {
        return new ToStringBuilder(this)
                .append("name", name)
                .toString();
    }

    public void select() {
        material.setColor(Rooms.SELECTED_COLOR);
        selected=true;
    }

    public void unselect() {
        material.setColor(Rooms.DEFAULT_COLOR);
        selected=false;
    }


}
