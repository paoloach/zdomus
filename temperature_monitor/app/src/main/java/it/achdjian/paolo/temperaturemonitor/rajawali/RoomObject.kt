package it.achdjian.paolo.temperaturemonitor.rajawali

import org.rajawali3d.Object3D
import org.rajawali3d.lights.SpotLight
import org.rajawali3d.materials.Material
import org.rajawali3d.materials.methods.DiffuseMethod
import org.rajawali3d.math.vector.Vector3
import org.rajawali3d.scene.Scene
import org.rajawali3d.util.ObjectColorPicker

/**
 * Created by Paolo Achdjian on 7/4/17.
 */
class RoomObject (val object3D: Object3D){
    val DEFAULT_COLOR = 0xFFC0C0C0.toInt()
    val SELECTED_COLOR = 0xFFC0FFFF.toInt()
    val name: String
    var material: Material = Material()
    val light: SpotLight
    lateinit var scene: Scene
    lateinit var picker: ObjectColorPicker

    init {
        name =object3D.name.substring(0,object3D.name.lastIndexOf("_"))
        initMaterial()
        val boundingBox = object3D.geometry.boundingBox
        val childMax = boundingBox.max
        val childMin = boundingBox.min
        val mean = Vector3((childMax.x + childMin.x) / 2, (childMax.y + childMin.y) / 2, childMax.z - 0.2)
        val look = Vector3((childMax.x + childMin.x) / 2, (childMax.y + childMin.y) / 2, childMin.z)
        light = SpotLight(look.x.toFloat(), look.y.toFloat(), look.z.toFloat())
        light.cutoffAngle = 120f
        light.setColor(1.0f, 1.0f, 1.0f)
        light.power = 1f
        light.position = mean
    }

    private fun initMaterial() {
        material.color = DEFAULT_COLOR
        material.enableLighting(true)
        material.diffuseMethod = DiffuseMethod.Lambert()
    }


    fun init3D(currentScene: Scene, picker: ObjectColorPicker) {
        object3D.material = material
        scene = currentScene
        this.picker=picker
        scene.addChild(object3D)
        scene.addLight(light)
        picker.registerObject(object3D)
    }

    fun updateTemp(){

    }

}