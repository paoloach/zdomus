package it.achdjian.paolo.cs5463

import android.arch.lifecycle.Observer
import android.arch.lifecycle.ViewModelProviders
import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import it.achdjian.paolo.cs5463.domusEngine.AttributesListener
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.domusEngine.rest.Attributes
import kotlinx.android.synthetic.main.status_register.*

/**
 * Created by Paolo Achdjian on 12/28/17.
 */
class StatusRegisterFragment : Fragment(), AttributesListener ,Observer<CS5463Data>{
    /**
     * Called when the data is changed.
     * @param t  The new data
     */
    override fun onChanged(t: CS5463Data?) {
        requestStatus()
    }

    override fun newAttributes(attributes: Attributes) {
        attributes.jSonAttribute.filter { it.id == 15 }.forEach {
            val value = it.value
            if (value != null){
                val register = value.toInt()
                activity.runOnUiThread({
                    textDataReady.setChecked((register and 0x800000) != 0)
                    textConvRdy.setChecked((register and 0x100000) != 0)

                    textIOR.setChecked((register and 0x20000) != 0)
                    textVOR.setChecked((register and 0x10000) != 0)
                    textIROR.setChecked((register and 0x4000) != 0)
                    textVROR.setChecked((register and 0x2000) != 0)
                    textEOR.setChecked((register and 0x1000) != 0)
                    textIFAULT.setChecked((register and 0x800) != 0)
                    textVSAG.setChecked((register and 0x400) != 0)
                    textTUP.setChecked((register and 0x80) != 0)
                    textTOD.setChecked((register and 0x40) != 0)
                    textVOD.setChecked((register and 0x10) != 0)
                    textIOD.setChecked((register and 0x8) != 0)

                    textLSD.setChecked((register and 0x4) != 0)
                    textFUP.setChecked((register and 0x2) != 0)
                    textIC.setChecked((register and 0x1) != 0)
                })
            }

        }
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?,
                              savedInstanceState: Bundle?): View? {
        ViewModelProviders.of(this.activity).get(CS5463ViewModel::class.java).data.observe(this,this)
        val rootView = inflater.inflate(R.layout.status_register, container, false)
        DomusEngine.addAttributeListener(this)
        val layout = rootView.findViewById<LinearLayout>(R.id.layout)
        layout.setOnClickListener { requestStatus() }
        return rootView
    }

    override fun onDestroyView() {
        super.onDestroyView()
        DomusEngine.removeAttributeListener(this)
    }

    private fun requestStatus(){
        val data =ViewModelProviders.of(this.activity).get(CS5463ViewModel::class.java).data.value
        if (data != null){
            DomusEngine.getAttribute(data.networkAddress, data.endpoint, 0xFFE, 15)
        }
    }

    companion object {
        fun newInstance() = StatusRegisterFragment()
    }
}