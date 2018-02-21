package it.achdjian.paolo.ztopology.activities

import android.content.Intent
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.preference.PreferenceManager
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import it.achdjian.paolo.ztopology.*
import it.achdjian.paolo.ztopology.domusEngine.ConnectionObserver
import it.achdjian.paolo.ztopology.domusEngine.ConnectionStatus
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest
import it.achdjian.paolo.ztopology.settings.SettingActivity
import it.achdjian.paolo.ztopology.zigbee.TopologyManager
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity(), ConnectionObserver {
    override fun connected() {
        Log.i("ZIGBEE COM", "connected")
        runOnUiThread({ supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.GREEN)) })
        DomusEngine.addCallback(TopologyManager as LqiInfoCallback)
        TopologyManager.start()
    }

    override fun disconnected() {
        runOnUiThread({ supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.RED)) })

    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        DomusEngineRest.address = PreferenceManager.getDefaultSharedPreferences(this).getString("DomusEngineAddress", "192.168.1.121:8080")
        ConnectionStatus.addObserver(this)
        DomusEngine.startEngine();
    }


    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId){
            R.id.action_settings -> {
                val intent = Intent(this, SettingActivity::class.java)
                startActivity(intent)
                return true
            }
        }
        return super.onOptionsItemSelected(item)
    }

    override fun onDestroy() {
        super.onDestroy()
        TopologyManager.removeView(topology)
    }
}
