package it.achdjian.domusviewer;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.Menu;
import android.view.MenuItem;

import com.badlogic.gdx.backends.android.AndroidFragmentApplication;

import it.achdjian.domusviewer.ScanningActivity.ScanningDialogFragment;
import it.achdjian.domusviewer.common.SharedKeys;
import it.achdjian.domusviewer.domus_engine.DomusEngine;

public class MainActivity extends FragmentActivity implements AndroidFragmentApplication.Callbacks {

	private DomusEngine scannerResult;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

		scannerResult = new DomusEngine(this);

        setContentView(R.layout.activity_main);
        ViewPager viewPager = (ViewPager) findViewById(R.id.pager);
        viewPager.setAdapter(new DomusPagerAdapter(getSupportFragmentManager()));

        String domusEngineLocation = SharedKeys.getDomusEngineLocation(getSharedPreferences(SharedKeys.PREFERENCE_NAME, Context.MODE_PRIVATE));
		ScanningDialogFragment dialogFragment = new ScanningDialogFragment();
		if (!domusEngineLocation.isEmpty()) {
			Bundle bundle = new Bundle();
			bundle.putCharSequence(ScanningDialogFragment.LOCATION, domusEngineLocation);
			dialogFragment.setArguments(bundle);
		}
		dialogFragment.setListener(scannerResult);
		dialogFragment.show(getSupportFragmentManager(), "Scanning");
	}


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void exit() {


    }
}
