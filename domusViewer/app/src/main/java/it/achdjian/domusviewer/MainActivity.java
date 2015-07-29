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

public class MainActivity extends FragmentActivity implements AndroidFragmentApplication.Callbacks {

    /**
     * The {@link android.support.v4.view.PagerAdapter} that will provide
     * fragments for each of the sections. We use a
     * {@link FragmentPagerAdapter} derivative, which will keep every
     * loaded fragment in memory. If this becomes too memory intensive, it
     * may be best to switch to a
     * {@link android.support.v4.app.FragmentStatePagerAdapter}.
     */
    DomusPagerAdapter domusPagerAdapter;

    /**
     * The {@link ViewPager} that will host the section contents.
     */
    ViewPager mViewPager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ViewPager viewPager = (ViewPager) findViewById(R.id.pager);
        viewPager.setAdapter(new DomusPagerAdapter(getSupportFragmentManager()));




        String domusEngineLocation = SharedKeys.getDomusEngineLocation(getSharedPreferences(SharedKeys.PREFERENCE_NAME, Context.MODE_PRIVATE));
		if (domusEngineLocation.isEmpty()) {
            ScanningDialogFragment dialogFragment = new ScanningDialogFragment();
            dialogFragment.show(getSupportFragmentManager(), "Scanning");
//			Intent scanningIntent = new Intent(this, ScanningActivity.class);
//			this.startActivity(scanningIntent);
		} else {
            ScanningDialogFragment dialogFragment = new ScanningDialogFragment();

            Bundle bundle = new Bundle();
            bundle.putCharSequence(ScanningDialogFragment.LOCATION, domusEngineLocation);

            dialogFragment.setArguments(bundle);

            dialogFragment.show(getSupportFragmentManager(), "Scanning");
		}
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
