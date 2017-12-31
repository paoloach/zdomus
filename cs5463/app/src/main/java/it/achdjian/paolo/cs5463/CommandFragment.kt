package it.achdjian.paolo.cs5463

import android.arch.lifecycle.ViewModelProviders
import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.RadioButton
import it.achdjian.paolo.cs5463.Constants.CLUSTER_ELECTRICAL_MEASUREMENT
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine

/**
 * Created by Paolo Achdjian on 12/28/17.
 */
class CommandFragment : Fragment() {
    var cmd:Int = 0
    var cluster:Int=CLUSTER_ELECTRICAL_MEASUREMENT

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?,
                              savedInstanceState: Bundle?): View? {
        val rootView = inflater.inflate(R.layout.command, container, false)
        val button = rootView.findViewById<Button>(R.id.execute)
        button.setOnClickListener {
            val data =ViewModelProviders.of(this.activity).get(SmartPlugViewModel::class.java).smartPlug.value
            if (data != null) {
                DomusEngine.postCmd(data.networkAddress, data.endpoint, cluster, cmd)
            }
        }
        rootView.findViewById<RadioButton>(R.id.calibrateVDC).setOnClickListener { cmd = 0x10;cluster=Constants.CLUSTER_ELECTRICAL_MEASUREMENT }
        rootView.findViewById<RadioButton>(R.id.calibrateIDC).setOnClickListener { cmd = 0x11;cluster=Constants.CLUSTER_ELECTRICAL_MEASUREMENT }
        rootView.findViewById<RadioButton>(R.id.calibrateVAC).setOnClickListener { cmd = 0x12;cluster=Constants.CLUSTER_ELECTRICAL_MEASUREMENT }
        rootView.findViewById<RadioButton>(R.id.calibrateIAC).setOnClickListener { cmd = 0x13;cluster=Constants.CLUSTER_ELECTRICAL_MEASUREMENT }
        rootView.findViewById<RadioButton>(R.id.startMeasure).setOnClickListener { cmd = 0x16;cluster=Constants.CLUSTER_ELECTRICAL_MEASUREMENT }
        rootView.findViewById<RadioButton>(R.id.clearStatus).setOnClickListener { cmd = 0x17;cluster=Constants.CLUSTER_ELECTRICAL_MEASUREMENT }
        rootView.findViewById<RadioButton>(R.id.reset).setOnClickListener { cmd = 0x18;cluster=Constants.CLUSTER_ELECTRICAL_MEASUREMENT }
        rootView.findViewById<RadioButton>(R.id.togle).setOnClickListener { cmd = 2;cluster=Constants.ON_OFF_CLUSTER }
        return rootView
    }

    companion object {
        fun newInstance() = CommandFragment()
    }
}