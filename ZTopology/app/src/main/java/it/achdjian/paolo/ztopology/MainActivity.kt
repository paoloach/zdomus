package it.achdjian.paolo.ztopology

import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import it.achdjian.paolo.ztopology.domusEngine.ConnectionObserver

class MainActivity : AppCompatActivity(), ConnectionObserver {
    override fun connected() {
        Log.i("ZIGBEE COM", "connected")
        runOnUiThread({ supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.GREEN)) })
        DomusEngine.getDevices()
    }

    override fun disconnected() {
        runOnUiThread({ supportActionBar?.setBackgroundDrawable(ColorDrawable(Color.RED)) })

    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        DomusEngine.startEngine();
    }
}
