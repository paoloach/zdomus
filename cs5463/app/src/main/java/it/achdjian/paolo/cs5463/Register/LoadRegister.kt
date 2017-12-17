package it.achdjian.paolo.cs5463.Register

import android.app.Activity
import android.arch.lifecycle.Observer
import android.view.View
import it.achdjian.paolo.cs5463.CS5463Data
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 11/23/17.
 */
@Singleton
class LoadRegister @Inject constructor(val domusEngine: DomusEngine) : View.OnClickListener, Observer<CS5463Data> {
    private var cs5463Data: CS5463Data? = null
    private var networkId: Int? = null


    /**
     * Called when the data is changed.
     * @param t  The new data
     */
    override fun onChanged(t: CS5463Data?) {
        cs5463Data = t
        networkId = t?.networkAddress
    }

    /**
     * Called when a view has been clicked.
     *
     * @param v The view that was clicked.
     */
    override fun onClick(v: View) {
        if (v.tag is RegistersWithValues) {
            load((v.tag as RegistersWithValues).index)
        }
    }

    fun load(index: Int): Double {
        val data = cs5463Data
        if (data != null) {
            domusEngine.getAttribute(data.networkAddress, data.endpoint, 0xFFFE, index)
        }
        return 0.0
    }
}