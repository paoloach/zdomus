package it.achdjian.paolo.temperaturemonitor


import android.content.Intent
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import it.achdjian.paolo.temperaturemonitor.dagger.TemperatureApplication
import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.ConnectionObserver
import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.ConnectionStatus
import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.WhoAreYou
import it.achdjian.paolo.temperaturemonitor.rajawali.Rooms
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureRender
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureSurface
import it.achdjian.paolo.temperaturemonitor.settings.SettingActivity
import kotlinx.android.synthetic.main.temperature_layout.*
import javax.inject.Inject

open class MainActivity : AppCompatActivity() ,View.OnLayoutChangeListener, ConnectionObserver {


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


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        (application as TemperatureApplication).component.inject(this)
        connectionStatus.addObserver(this)
        setContentView(R.layout.temperature_layout)
        rajaBase.addView(surface)
        rajaBase.addOnLayoutChangeListener(this)
        surface.requestRenderUpdate()
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem):Boolean {
        if (item.itemId == R.id.action_settings) {
            val intent = Intent(this, SettingActivity::class.java)
            startActivity(intent)
            return true
        }

        return super.onOptionsItemSelected(item)
    }

    override fun onLayoutChange(v: View, left: Int, top: Int, right: Int, bottom: Int, oldLeft: Int, oldTop: Int, oldRight: Int, oldBottom: Int) {
        renderer.onSurfaceViewLayoutChange(left, top, right, bottom)
        onResume()
        Log.d("RENDER", "left: $left, top: $top, right: $right, bottom: $bottom")
    }

    override fun connected() {
        runOnUiThread({supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.GREEN))})
    }

    override fun disconnected() {
        runOnUiThread({supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.RED))})
    }
}
