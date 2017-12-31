package it.achdjian.paolo.cs5463

import android.arch.lifecycle.ViewModelProviders
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import it.achdjian.paolo.cs5463.Constants.TEST_DEVICE
import it.achdjian.paolo.cs5463.Constants.ZCL_HA_DEVICEID_SMART_PLUG
import it.achdjian.paolo.cs5463.Register.LoadRegister
import it.achdjian.paolo.cs5463.dagger.CS5463Application
import it.achdjian.paolo.cs5463.dagger.CS5463Module
import it.achdjian.paolo.cs5463.dagger.DaggerMainActivityComponent
import it.achdjian.paolo.cs5463.dagger.MainActivityModule
import it.achdjian.paolo.cs5463.domusEngine.ConnectionObserver
import it.achdjian.paolo.cs5463.domusEngine.ConnectionStatus
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.domusEngine.NewSmartPlugDeviceListener
import it.achdjian.paolo.cs5463.zigbee.ZDevices
import kotlinx.android.synthetic.main.activity_main.*
import javax.inject.Inject


class MainActivity : AppCompatActivity(), ConnectionObserver, NewSmartPlugDeviceListener, AdapterView.OnItemSelectedListener {

    lateinit var adapter: ArrayAdapter<CharSequence>

    @Inject
    lateinit var mSectionsPagerAdapter: SectionsPageAdapter
    @Inject
    lateinit var loadRegister: LoadRegister

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val app = application as CS5463Application
        if (app != null) {
            DaggerMainActivityComponent.builder()
                    .mainActivityModule(MainActivityModule(this))
                    .cS5463Module(CS5463Module(app)).build().inject(this)
        }
        val viewModel = ViewModelProviders.of(this).get(CS5463ViewModel::class.java)
        viewModel.data.observe(this, loadRegister)

        setContentView(R.layout.activity_main)
        setSupportActionBar(toolbar)
        supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.RED))
        adapter = ArrayAdapter(this, android.R.layout.simple_spinner_item)
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        devices.adapter = adapter
        devices.onItemSelectedListener = this
        ConnectionStatus.addObserver(this)
        DomusEngine.addListener(this)
        DomusEngine.startEngine()

        container.adapter = mSectionsPagerAdapter

    }


    override fun connected() {
        Log.i("ZIGBEE COM", "connected")
        runOnUiThread({ supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.GREEN)) })
        DomusEngine.getDevices()
    }

    override fun disconnected() {
        runOnUiThread({ supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.RED)) })
    }

    override fun newSmartPlugDevice(shortAddr: Int, endpointId: Int) {
        runOnUiThread({ adapter.add(shortAddr.toString(16)) })
    }

    /**
     * Callback method to be invoked when the selection disappears from this
     * view. The selection can disappear for instance when touch is activated
     * or when the adapter becomes empty.
     *
     * @param parent The AdapterView that now contains no selected item.
     */
    override fun onNothingSelected(parent: AdapterView<*>?) {
    }

    /**
     *
     * Callback method to be invoked when an item in this view has been
     * selected. This callback is invoked only when the newly selected
     * position is different from the previously selected position or if
     * there was no selected item.
     *
     * Impelmenters can call getItemAtPosition(position) if they need to access the
     * data associated with the selected item.
     *
     * @param parent The AdapterView where the selection happened
     * @param view The view within the AdapterView that was clicked
     * @param position The position of the view in the adapter
     * @param id The row id of the item that is selected
     */
    override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
        val networkId = adapter.getItem(position).toString().toInt(16)
        ZDevices.get(networkId)
                .endpoints
                .values
                .forEach{
                    if (it?.device_id == TEST_DEVICE){
                        ViewModelProviders.of(this).get(CS5463ViewModel::class.java).data.postValue(CS5463Data(networkId, it.endpoint_id))
                    }
                    if (it?.device_id == ZCL_HA_DEVICEID_SMART_PLUG){
                        Log.i("SmartPlug", "Selected networkID: " + networkId)
                        ViewModelProviders.of(this).get(SmartPlugViewModel::class.java).smartPlug.postValue(SmartPlugData(networkId, it.endpoint_id))
                    }
                }
    }
}
