package it.achdjian.paolo.ztopology.activities.node

import android.content.Context
import android.content.res.Resources
import android.support.v7.widget.ThemedSpinnerAdapter
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import it.achdjian.paolo.ztopology.DeviceCallback
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.EndpointCallback
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.domusEngine.rest.Device
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint
import it.achdjian.paolo.ztopology.zigbee.deviceIdName
import kotlinx.android.synthetic.main.list_item.view.*

/**
 * Created by Paolo Achdjian on 2/21/18.
 */
class EndpointAdapter(context: Context, val networkId: Int) :
    ArrayAdapter<String>(context, R.layout.list_item) , DeviceCallback,
    EndpointCallback , ThemedSpinnerAdapter {

    private val mDropDownHelper: ThemedSpinnerAdapter.Helper =
        ThemedSpinnerAdapter.Helper(context)
    private val endpoints = ArrayList<ZEndpoint>()


    override fun getDropDownViewTheme(): Resources.Theme? = mDropDownHelper.dropDownViewTheme

    override fun setDropDownViewTheme(theme: Resources.Theme?) {
        mDropDownHelper.dropDownViewTheme = theme
    }

    init {
        DomusEngine.getDevice(networkId)
    }

    override fun newDevice(response: Device) {
        response.endpoints.forEach { DomusEngine.getEndpoint(response.networkId, it) }
    }

    override fun deviceTimeout(networkId: Int) {
    }

    override fun newEndpoint(response: ZEndpoint) {
        endpoints.add(response)
        add(deviceIdName(response.deviceId))
    }


    override fun getDropDownView(position: Int, convertView: View?, parent: ViewGroup): View {
        val view: View

        if (convertView == null) {
            // Inflate the drop down using the helper's LayoutInflater
            val inflater = mDropDownHelper.dropDownViewInflater
           // view = inflater.inflate(R.layout.endpoint_label, parent, false)
            view = inflater.inflate(R.layout.list_item, parent, false)
        } else {
            view = convertView
        }

        val endpoint = endpoints.get(position)
        view.text1.text = deviceIdName(endpoint.deviceId)

        return view
    }


}