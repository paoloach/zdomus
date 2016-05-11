package it.achdjian.paolo.domusviewer.other;

import android.app.DialogFragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 11/05/16.
 */
public class ZDeviceInfoFragment extends DialogFragment {

    public static final String NETWORK_ID = "network_id";
    public static final String ENDPOINT_ID = "endpoint_id";

    public static ZDeviceInfoFragment newInstance(Element element){
        ZDeviceInfoFragment info = new ZDeviceInfoFragment();

        Bundle args = new Bundle();
        args.putInt(NETWORK_ID, element.network);
        args.putInt(ENDPOINT_ID, element.endpoint);
        info.setArguments(args);
        return info;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.zdevice_info, container, false);

        return view;
    }
}
