package it.achdjian.paolo.cs5463.Register

import android.util.Log
import android.widget.ListView
import it.achdjian.paolo.cs5463.Register.RegistersWithValues.*
import it.achdjian.paolo.cs5463.domusEngine.AttributesListener
import it.achdjian.paolo.cs5463.domusEngine.rest.Attributes
import it.achdjian.paolo.cs5463.domusEngine.rest.JSonAttribute
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 12/27/17.
 */
@Singleton
class RegistersValue @Inject constructor(val register2View: Register2View): AttributesListener {
    private val values = HashMap<RegistersWithValues,Double>()
    private var toRefresh: ListView? = null

    init {
        values[CURRENT_DC_OFFSET] = 0.0
        values[CURRENT_GAIN] = 1.0
        values[VOLTAGE_DC_OFFSET] = 0.0
        values[VOLTAGE_GAIN] = 1.0
        values[CURRENT_AC_OFFSET] = 0.0
        values[VOLTAGE_AC_OFFSET] = 0.0
        values[CURRENT_INSTANTANEUS] = 0.0
        values[VOLTAGE_INSTANTANEUS] = 0.0
        values[POWER_INSTANTANEUS] = 0.0

        values[ACTIVE_POWER] = 0.0
        values[RMS_CURRENT] = 0.0
        values[RMS_VOLTAGE] = 0.0

        values[REACTIVE_POWER_AVERAGE] = 0.0
        values[INSTANTANEOUS_REACTIVE_POWER] = 0.0
        values[PEAK_CURRENT] = 0.0
        values[PEAK_VOLTAGE] = 0.0
    }

    operator fun get(register: RegistersWithValues):Double{
        if (values.containsKey(register)){
            val value = values[register]
            if (value != null)
                return value
        }

        return 0.0
    }

    override fun newAttributes(attributes: Attributes) {
        for (attribute in attributes.jSonAttribute) {
            for (register in RegistersWithValues.values()) {
                if (register.index == attribute.id){
                    when(register.type){
                        RegisterType.TYPE_1 -> values[register] = calcType1(attribute)
                        RegisterType.TYPE_2 -> values[register] = calcType2(attribute)
                        RegisterType.TYPE_3 -> values[register] = calcType3(attribute)
                    }
                    Log.i("COM", "new register value: " + values[register])
                    val view = register2View[register]
                    if(view != null)
                        view.post({view.setText(values[register].toString());view.invalidate()})
                }
            }
        }
    }

    private fun calcType2(attribute: JSonAttribute): Double {
        val str = attribute.value
        if (str != null) {
            var value = str.toDouble()
            if (value > 8388608){
                value = value-16777215
            }
            value = value / 8388608
            return value
        }
        return 0.0
    }

    private fun calcType3(attribute: JSonAttribute): Double{
        val str = attribute.value
        if (str != null) {
            var value = str.toDouble()
            value = value / 4194304
            return value
        }
        return 0.0
    }

    private fun calcType1(attribute: JSonAttribute): Double{
        val str = attribute.value
        if (str != null) {
            var value = str.toDouble()
            value = value / 16777216
            return value
        }
        return 0.0
    }

    fun addListView(listView: ListView?) {
        toRefresh = listView
    }

}