package it.achdjian.paolo.domusviewer;

import android.content.Intent;
import android.content.res.Resources;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.support.design.widget.TabLayout;
import android.support.v4.view.ViewPager;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EActivity;
import org.androidannotations.annotations.OptionsItem;
import org.androidannotations.annotations.OptionsMenu;
import org.androidannotations.annotations.ViewById;

import it.achdjian.paolo.domusviewer.DomusEngineRest.ConnectionObserver;
import it.achdjian.paolo.domusviewer.other.ActivityManager;
import it.achdjian.paolo.domusviewer.setting.SettingActivity;

@EActivity(R.layout.activity_main)
@OptionsMenu(R.menu.menu_main)
public class MainActivity extends AppCompatActivity implements ConnectionObserver {
    @Bean
    DomusEngine domusEngine;
    @Bean
    ActivityManager activityManager;

    @ViewById(R.id.container)
    ViewPager mViewPager;
    @ViewById(R.id.tabs)
    TabLayout tabLayout;
    @ViewById(R.id.toolbar)
    Toolbar toolbar;

    /**
     * The {@link ViewPager} that will host the section contents.
     */
    private ActionBar actionBar;

    @AfterViews
    protected void afterView() {
        initConstants();
        setSupportActionBar(toolbar);
        SectionsPagerAdapter mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager());
        mViewPager.setAdapter(mSectionsPagerAdapter);
        tabLayout.setupWithViewPager(mViewPager);

        actionBar = getSupportActionBar();

        domusEngine.addConnectionObserver(this);
    }

    private void initConstants() {
        Resources resources = getResources();
        Constants.DOMUS_ENGINE_ADDRESS = resources.getString(R.string.server_address_key);
    }


//    @Override
//    public boolean onCreateOptionsMenu(Menu menu) {
//        getMenuInflater().inflate(R.menu.menu_main, menu);
//        return true;
//    }

    @OptionsItem(R.id.action_settings)
    void startSettingActivity() {
        Intent intent = new Intent(this, SettingActivity.class);
        startActivity(intent);
    }

//    @Override
//    public boolean onOptionsItemSelected(MenuItem item) {
//        int id = item.getItemId();
//        if (id == R.id.action_settings) {
//            Intent intent = new Intent(this, SettingActivity.class);
//            startActivity(intent);
//            return true;
//        }
//
//        return super.onOptionsItemSelected(item);
//    }

    @Override
    public void connected() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                actionBar.setBackgroundDrawable(new ColorDrawable(Color.GREEN));
            }
        });
    }

    @Override
    public void disconnected() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                actionBar.setBackgroundDrawable(new ColorDrawable(Color.RED));
            }
        });
    }

}
