package it.achdjian.domusviewer.ScanningActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ProgressBar;

import it.achdjian.domusviewer.R;
import it.achdjian.domusviewer.common.SharedKeys;

public class ScanningActivity extends AppCompatActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Intent intent = getIntent();
		Bundle extras = intent.getExtras();
		CharSequence startingLocation = extras.getCharSequence(ScanningDialogFragment.LOCATION);
		setContentView(R.layout.fragment_scanning);

		Runnable runnable;
		if (startingLocation != null){
			runnable = new CheckingDomusEngine(this);
		} else {
			final ProgressBar progressBar = (ProgressBar) findViewById(R.id.progressBar);
			runnable = new ScanningRunnable(new Handler(), progressBar, getSharedPreferences(SharedKeys.PREFERENCE_NAME, Context.MODE_PRIVATE),this);
		}
		new Thread(runnable).start();

	}


	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.scanning_activity, menu);
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
}
