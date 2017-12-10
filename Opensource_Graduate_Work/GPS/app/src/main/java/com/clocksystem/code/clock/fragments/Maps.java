package com.clocksystem.code.clock.fragments;


import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.location.Location;
import android.os.Bundle;
import android.provider.Settings;
import android.support.v4.app.Fragment;
import android.support.v7.app.AlertDialog;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.clocksystem.code.clock.R;
import com.clocksystem.code.clock.Utils.AppSettings;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolylineOptions;
import com.google.maps.android.ui.IconGenerator;


import android.content.Context;
import android.widget.TextView;

import java.text.DateFormat;
import java.util.Date;


public class Maps extends Fragment implements
		LocationListener,
		GoogleApiClient.ConnectionCallbacks,
		GoogleApiClient.OnConnectionFailedListener, View.OnClickListener {

	private Context mContext = null;
	private IFragmentListener mFragmentListener = null;

	public Maps(Context c, IFragmentListener l) {
		mContext = c;
		mFragmentListener = l;
	}

	private static final String TAG = "Maps";
	private static final long INTERVAL = 1000 * 20 * 1; //1 minute
	private static final	long FASTEST_INTERVAL = 1000 * 20 * 1; // 1 minute
	boolean isGPSEnabled = false;

		LocationRequest mLocationRequest;
		GoogleApiClient mGoogleApiClient;
		Location mCurrentLocation;
		String mLastUpdateTime;
		GoogleMap googleMap;
		LatLng nextLatLng = null;
		Button mBtnRide;
		Button mBtnStop;
		TextView mTextTerm;
		public static int ridestart = 0;

	protected void createLocationRequest() {
		mLocationRequest = new LocationRequest();
		mLocationRequest.setInterval(INTERVAL);
		mLocationRequest.setFastestInterval(FASTEST_INTERVAL);
		mLocationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
	}


	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)  {
		AppSettings.initializeAppSettings(mContext);
		View rootView = inflater.inflate(R.layout.fragment_settings,container, false);
		ridestart = 0;
		Log.d(TAG, "onCreate ...............................");

		if (!isGooglePlayServicesAvailable()) {
			getActivity().finish();
		}
		createLocationRequest();
		mGoogleApiClient = new GoogleApiClient.Builder(getActivity())
				.addApi(LocationServices.API)
				.addConnectionCallbacks(this)
				.addOnConnectionFailedListener(this)
				.build();



		SupportMapFragment fm = (SupportMapFragment) getChildFragmentManager()
				.findFragmentById(R.id.map);
		googleMap = fm.getMap();
		googleMap.getUiSettings().setZoomControlsEnabled(true);

		mBtnRide = (Button) rootView.findViewById(R.id.button_Ride);
		mBtnRide.setOnClickListener(this);

		mBtnStop = (Button) rootView.findViewById(R.id.button_Stop);
		mBtnStop.setOnClickListener(this);

		mTextTerm = (TextView) rootView.findViewById(R.id.Graph);
		mTextTerm.setMaxLines(1);
		mTextTerm.setVerticalScrollBarEnabled(true);
		mTextTerm.setMovementMethod(new ScrollingMovementMethod());

		return rootView;
	}

	public void onClick(View v) {
		switch(v.getId()) {
			case R.id.button_Ride:
				mGoogleApiClient.connect();
				if(mFragmentListener != null)
					mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, "[", null,null);
				else
					return;
				ridestart = 1;
				onResume();
				break;
			case R.id.button_Stop:
				if(mFragmentListener != null)
					mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, "]", null,null);
				else
					return;
				ridestart = 0;
				onStop();
				break;
		}
	}

	private static final int NEW_LINE_INTERVAL = 1000;
	private long mLastReceivedTime = 0L;

	// Show messages from remote
	public void showMessage(String message) {
		if (message != null && message.length() > 0) {
			long current = System.currentTimeMillis();
			if (current - mLastReceivedTime > NEW_LINE_INTERVAL) {
			}
			if(ridestart==1) {
				mTextTerm.append(message);
			}
			int scrollamout = mTextTerm.getLayout().getLineTop(mTextTerm.getLineCount()) - mTextTerm.getHeight();
			if (scrollamout > mTextTerm.getHeight())
				mTextTerm.scrollTo(0, scrollamout);
			mLastReceivedTime = current;
		}
	}

	@Override
	public void onStart() {
		super.onStart();
		Log.d(TAG, "onStart fired ..............");
		mGoogleApiClient.connect();
	}

	@Override
	public void onStop() {
		super.onStop();
		Log.d(TAG, "onStop fired ..............");
		mGoogleApiClient.disconnect();
		Log.d(TAG, "isConnected ...............: " + mGoogleApiClient.isConnected());
	}

	private boolean isGooglePlayServicesAvailable() {
		int status = GooglePlayServicesUtil.isGooglePlayServicesAvailable(getActivity());
		if (ConnectionResult.SUCCESS == status) {
			return true;
		} else {
			GooglePlayServicesUtil.getErrorDialog(status, getActivity(), 0).show();
			return false;
		}
	}

	@Override
	public void onConnected(Bundle bundle) {
		Log.d(TAG, "onConnected - isConnected ...............: " + mGoogleApiClient.isConnected());
	}

	protected void startLocationUpdates() {
		LocationServices.FusedLocationApi.requestLocationUpdates(
				mGoogleApiClient, mLocationRequest, this);
		Log.d(TAG, "Location update started ..............: ");
	}

	@Override
	public void onConnectionSuspended(int i) {

	}

	@Override
	public void onConnectionFailed(ConnectionResult connectionResult) {
		Log.d(TAG, "Connection failed: " + connectionResult.toString());
		showSettingsAlert();
	}

	@Override
	public void onLocationChanged(Location location) {
		Log.d(TAG, "Firing onLocationChanged..............................................");
		mCurrentLocation = location;
		mLastUpdateTime = DateFormat.getTimeInstance().format(new Date());
		addMarker();
	}

	private void addMarker() {
		PolylineOptions polyoptions = new PolylineOptions();
		MarkerOptions options = new MarkerOptions();
		IconGenerator iconFactory = new IconGenerator(getActivity());
		iconFactory.setStyle(IconGenerator.STYLE_RED);
		options.icon(BitmapDescriptorFactory.fromBitmap(iconFactory.makeIcon(mLastUpdateTime)));
		options.anchor(iconFactory.getAnchorU(), iconFactory.getAnchorV());

		polyoptions.width(10);
		polyoptions.color(Color.RED);
		LatLng currentLatLng = new LatLng(mCurrentLocation.getLatitude(), mCurrentLocation.getLongitude());
		polyoptions.add(currentLatLng);
		options.position(currentLatLng);
		if (nextLatLng != null) {
			polyoptions.add(nextLatLng);
		}
		Marker mapMarker = googleMap.addMarker(options);
		long atTime = mCurrentLocation.getTime();
		mLastUpdateTime = DateFormat.getTimeInstance().format(new Date(atTime));
		mapMarker.setTitle(mLastUpdateTime);
		Log.d(TAG, "Marker added.............................");
		googleMap.moveCamera(CameraUpdateFactory.newLatLngZoom(currentLatLng,
				19));
		googleMap.addPolyline(polyoptions);
		Log.d(TAG, "Zoom done.............................");
		nextLatLng = new LatLng(mCurrentLocation.getLatitude(), mCurrentLocation.getLongitude());
	}

	@Override
	public void onPause() {
		super.onPause();
		stopLocationUpdates();
	}

	private void stopLocationUpdates() {
		if (mGoogleApiClient != null) {
			mGoogleApiClient.unregisterConnectionCallbacks(this);
			mGoogleApiClient.unregisterConnectionFailedListener(this);
			if (mGoogleApiClient.isConnected()) {
				LocationServices.FusedLocationApi
						.removeLocationUpdates(mGoogleApiClient, this);
				mGoogleApiClient.disconnect();
			}
		}
		Log.d(TAG, "Location update stopped .......................");
	}

	@Override
	public void onResume() {
		super.onResume();
		if (mGoogleApiClient.isConnected()) {
			startLocationUpdates();
			Log.d(TAG, "Location update resumed .....................");
		}
	}

	public void showSettingsAlert(){
		AlertDialog.Builder aDialog = new AlertDialog.Builder(getActivity());
		aDialog.setTitle("GPS Disconnect");
		aDialog.setMessage("Failed to connect GPS.\nDo you want to Connect?");
		aDialog.setPositiveButton("Settings", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog,int which) {
				Intent intent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
				getActivity().startActivity(intent);
			}
		});
		aDialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				dialog.cancel();
			}
		});
		AlertDialog alertDialog = aDialog.create();
		aDialog.show();
	}

}
