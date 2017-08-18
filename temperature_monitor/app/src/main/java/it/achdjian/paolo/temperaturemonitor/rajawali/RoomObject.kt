package it.achdjian.paolo.temperaturemonitor.rajawali

import it.achdjian.paolo.temperaturemonitor.TemperatureCache
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
class RoomObject(val object3D: Object3D, val cache: TemperatureCache) {
    companion object {
        val DEFAULT_COLOR = 0xFFC0C0C0.toInt()
        val SELECTED_COLOR = 0xFFC0FFFF.toInt()
    }
    val name: String = object3D.name.substring(0, object3D.name.lastIndexOf("_"))
    var material: Material = Material()
    var selected = false
    var light: SpotLight
    val mean: Vector3
    val max: Vector3
    val min: Vector3
    var temperatureLabel: TemperatureLabel?=null
    var selectedColor: Int = SELECTED_COLOR
    var unselectedColor: Int = DEFAULT_COLOR
    lateinit var scene: Scene
    lateinit var picker: ObjectColorPicker

    init {
        initMaterial()
        val boundingBox = object3D.geometry.boundingBox
        max = boundingBox.max
        min = boundingBox.min
        mean = Vector3((max.x + min.x) / 2, (max.y + min.y) / 2, max.z - 0.2)

        val look = Vector3((max.x + min.x) / 2, (max.y + min.y) / 2, min.z)
        light = SpotLight(look.x.toFloat(), look.y.toFloat(), look.z.toFloat())
        light.cutoffAngle = 120f
        light.setColor(1.0f, 1.0f, 1.0f)
        light.power = 1f
        light.position = mean
    }

    fun initLabels() {
        if (temperatureLabel == null) {
            temperatureLabel = TemperatureLabel(this)
            scene.addChild(temperatureLabel)
        }
    }


    private fun initMaterial() {
        material.color = DEFAULT_COLOR
        material.enableLighting(true)
        material.diffuseMethod = DiffuseMethod.Lambert()
    }


    fun init3D(currentScene: Scene, picker: ObjectColorPicker) {
        object3D.material = material
        scene = currentScene
        this.picker = picker
        scene.addChild(object3D)
        scene.addLight(light)
        picker.registerObject(object3D)
    }

    fun updateTemp() {
        if (temperatureLabel != null ) {
            val temp = cache.getTemperature(name)
            if (temp.isPresent) {
                unselectedColor = TemperatureColorMap.getColor(temp.get())
                selectedColor = (unselectedColor and 0xFFFFFF).inv()
                if (selected) {
                    material.color = selectedColor
                } else {
                    material.color  = unselectedColor
                }
                material.enableLighting(true)
                material.diffuseMethod = DiffuseMethod.Lambert()
                temperatureLabel?.setTemperature(temp.get() / 100.0f, unselectedColor)
            }
        }
    }

    fun select() {
        selected = true
        material.color = selectedColor
    }

    fun deselect() {
        selected = false
        material.color = unselectedColor
    }

    fun removeLabels() {
        if (temperatureLabel != null) {
            scene.removeChild(temperatureLabel)
            temperatureLabel?.destroy()
            temperatureLabel = null
            unselectedColor = DEFAULT_COLOR
            selectedColor = SELECTED_COLOR
        }

    }


}
