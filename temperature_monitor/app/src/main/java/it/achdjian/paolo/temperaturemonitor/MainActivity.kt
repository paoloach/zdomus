package it.achdjian.paolo.temperaturemonitor


import android.content.Intent
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.os.Bundle
import android.os.Handler
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import it.achdjian.paolo.temperaturemonitor.dagger.TemperatureApplication
import it.achdjian.paolo.temperaturemonitor.domusEngine.*
import it.achdjian.paolo.temperaturemonitor.rajawali.Rooms
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureRender
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureSurface
import it.achdjian.paolo.temperaturemonitor.settings.SettingActivity
import it.achdjian.paolo.temperaturemonitor.ui.*
import kotlinx.android.synthetic.main.temperature_layout.*
import javax.inject.Inject

open class MainActivity : AppCompatActivity(), View.OnLayoutChangeListener, ConnectionObserver {
    @Inject
    lateinit var renderer: TemperatureRender
    @Inject
    lateinit var surface: TemperatureSurface
    @Inject
    lateinit var rooms: Rooms
    @Inject
    lateinit var domusEngine: DomusEngine
    @Inject
    lateinit var connectionStatus: ConnectionStatus
    @Inject
    lateinit var zElementAdapter: ZElementAdapter
    @Inject
    lateinit var assignController: AssignController
    @Inject
    lateinit var deassignController: DeassignController
    @Inject
    lateinit var temperatureCache: TemperatureCache
    @Inject
    lateinit var assigningButtons: AssigningButtons
    @Inject
    lateinit var initRoom: InitRoom
    @Inject
    lateinit var listViewShowing: ListViewShowing
    @Inject
    lateinit var swipeListView: SwipeListView
    @Inject
    lateinit var powerUpdateView: PowerUpdateView
    @Inject
    lateinit var powerNodeCache: PowerNodeCache


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        (application as TemperatureApplication).component.inject(this)
        connectionStatus.addObserver(this)
        domusEngine.startEngine()
        setContentView(R.layout.temperature_layout)
        assigningButtons.deassign = deassign
        assigningButtons.assigning = assign
        rajaBase.addView(surface)
        rajaBase.addOnLayoutChangeListener(this)
        surface.requestRenderUpdate()
        tempLV.adapter = zElementAdapter
        powerUpdateView.listView = tempLV
        domusEngine.addListener(zElementAdapter)
        assign.setOnClickListener(assignController)
        deassign.setOnClickListener(deassignController)
        deassignController.listView = tempLV
        assignController.listView = tempLV
        listViewShowing.listView = tempLV
        listViewShowing.uiHandler=Handler()
        domusEngine.addAttributeListener(temperatureCache)
        domusEngine.addListener(initRoom)
        domusEngine.addListener(listViewShowing)
        domusEngine.addListener(powerUpdateView)
        domusEngine.addListener(powerNodeCache)
        surface.setOnTouchListener(swipeListView)
        swipeListView.listView = tempLV
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        if (item.itemId == R.id.action_settings) {
            val intent = Intent(this, SettingActivity::class.java)
            startActivity(intent)
            return true
        }

        return super.onOptionsItemSelected(item)
    }

    override fun onLayoutChange(v: View, left: Int, top: Int, right: Int, bottom: Int, oldLeft: Int, oldTop: Int, oldRight: Int, oldBottom: Int) {
        renderer.onSurfaceViewLayoutChange(left, top, right, bottom)
        renderer.onResume()
    }

    override fun connected() {
        Log.i("ZIGBEE COM", "connected")
        runOnUiThread({ supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.GREEN)) })
        domusEngine.getDevices()
    }

    override fun disconnected() {
        runOnUiThread({ supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.RED)) })
    }
}
