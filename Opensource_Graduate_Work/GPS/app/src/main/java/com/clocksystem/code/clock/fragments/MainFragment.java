package com.clocksystem.code.clock.fragments;

import android.app.AlertDialog;
import android.os.Message;
import android.os.Vibrator;
import android.support.v4.app.Fragment;
import android.content.DialogInterface;

import android.text.method.ScrollingMovementMethod;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.util.Base64;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.clocksystem.code.clock.R;

import java.security.Key;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Random;
import java.util.regex.Pattern;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

import static android.content.Context.LAYOUT_INFLATER_SERVICE;


public class MainFragment extends Fragment implements View.OnClickListener {

	private Context mContext = null;
	private IFragmentListener mFragmentListener = null;
	private Handler mActivityHandler = null;

	TextView mTextChat,lockimg;
	EditText pwd;
	EditText pwdcheck;
	Button mBtnLock;
	Button mBtnPub;
	Button mBtnNew;
	Button mBtndel;
	Button mBtnshare;
	public static Button mBtnauto;
	static Button mBtnPubp;
	static Button mBtnvib;
	static Button mBtnCon;
	Random mRand;
	static int sharecheck = 2;
	static int opencheck = 1;
	static int parkingcheck = 0;
	static long[] pattern = {50,50,50,50,50,50,50,50,50,50,50,50,1000};

	public static String connect = new String();
	public String check = new String();
	String checking = new String();
	int[] pubkey;
	String strKey;
	String[] encode = new String[3];
	byte[][] encodedBytes = new byte[3][];

	static public String Odometer;
	static public String[] startsignal = new String[2];

	SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd", Locale.KOREA);
	String str_date = df.format(new Date());

	//AES Ket Crypto
	Key secureKey = new SecretKeySpec("HelloMyNameCLock".getBytes(), "AES");

	public MainFragment(Context c, IFragmentListener l, Handler h) {
		mContext = c;
		mFragmentListener = l;
		mActivityHandler = h;
	}

	private static final String TAG = "MainFragment";

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_main_dummy, container, false);
		startsignal[0] = "start!";
		connect = null;

		mTextChat = (TextView) rootView.findViewById(R.id.text_terminal);
		mTextChat.setMaxLines(1000);
		mTextChat.setVerticalScrollBarEnabled(true);
		mTextChat.setMovementMethod(new ScrollingMovementMethod());

		lockimg = (TextView) rootView.findViewById(R.id.Lockimg);

		mBtnNew = (Button) rootView.findViewById(R.id.button_new);
		mBtnNew.setOnClickListener(this);

		mBtnshare = (Button) rootView.findViewById(R.id.button_share);
		mBtnshare.setOnClickListener(this);

		mBtnLock = (Button) rootView.findViewById(R.id.button_lock);
		mBtnLock.setOnClickListener(this);

		mBtnPub = (Button) rootView.findViewById(R.id.button_public);
		mBtnPub.setOnClickListener(this);

		mBtndel = (Button) rootView.findViewById(R.id.button_pubdel);
		mBtndel.setOnClickListener(this);

		mBtnPubp = (Button) rootView.findViewById(R.id.button_pubp);
		mBtnPubp.setOnClickListener(this);

		mBtnCon = (Button) rootView.findViewById(R.id.button_connect);
		mBtnCon.setOnClickListener(this);

		mBtnvib = (Button) rootView.findViewById(R.id.button_auto);
		mBtnvib.setOnClickListener(this);

		mBtnauto = (Button) rootView.findViewById(R.id.button_auto);
		mBtnauto.setOnClickListener(this);


		lockimg.setBackgroundResource(R.drawable.connectlost);

		return rootView;
	}

	public static void BluetoothCheck() {
		if (connect == "connect") {
			mBtnCon.performClick();
			opencheck = 1;
		}else if(connect == "parking")
		{
            parkingcheck = 1;
			mBtnPubp.performClick();
		}
	}
	public static void Bluetoothlost(){
		new Thread(new Runnable() {
			@Override
			public void run() {
				Message msg = handler.obtainMessage();
				handler.sendMessage(msg);
			}
		}).start();
	}

	static final Handler handler = new Handler(){
		public void handleMessage(Message msg){
			if((connect =="lost" && startsignal[1] == "start!") || sharecheck == 3)
				mBtnvib.performClick();
		}
	};

	@Override
	public void onClick(View v) {
			switch (v.getId()) {
				case R.id.button_connect:
						if(opencheck ==1 ) {
							onCheck();
						}
						else{
							Toast.makeText(getActivity(), "Not connect CLOCK.", Toast.LENGTH_SHORT).show();
						}
					break;
				case R.id.button_new:
					if (startsignal[0].toString().equals(startsignal[1])) {
						showMod();
					} else {
						Toast.makeText(getActivity(), "Not connect CLOCK.", Toast.LENGTH_SHORT).show();
					}
					break;
				case R.id.button_share:
					if (sharecheck == 1) {
						showShare();
					} else if (sharecheck == 2) {
						Toast.makeText(getActivity(), "Not share CLOCK.", Toast.LENGTH_SHORT).show();
					} else if (sharecheck == 3){
						if (mFragmentListener != null)
							mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, ";" + encode[1], null, null);
						else
							return;
					}
					break;
				case R.id.button_lock:
					if (startsignal[0].toString().equals(startsignal[1])) {
						if (opencheck == 2) {
							if (mFragmentListener != null)
								mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, "<", null, null);
							else
								return;
						}else if (opencheck == 1){
							if (mFragmentListener != null)
								mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, ">", null, null);
							else
								return;
						}
					} else {
						Toast.makeText(getActivity(), "Not connect CLOCK.", Toast.LENGTH_SHORT).show();
					}
				case R.id.button_public:
					if (startsignal[0].toString().equals(startsignal[1])) {
						showPublic();
					} else {
						Toast.makeText(getActivity(), "Not connect CLOCK.", Toast.LENGTH_SHORT).show();
					}
					break;
				case R.id.button_pubdel:
					if (startsignal[0].toString().equals(startsignal[1])) {
						if (mFragmentListener != null)
							mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, ".", null, null);
						else
							return;
					} else {
						Toast.makeText(getActivity(), "Not connect CLOCK.", Toast.LENGTH_SHORT).show();
					}
					break;
				case R.id.button_pubp:
					if(parkingcheck ==1 ) {
						showPubp();
					}
					else{
						Toast.makeText(getActivity(), "Not connect Parking system.", Toast.LENGTH_SHORT).show();
					}
					break;
				case R.id.button_vib:
					lockimg.setBackgroundResource(R.drawable.connectlost);
					onAlert();
				case R.id.button_auto:
					if (startsignal[0].toString().equals(startsignal[1]) || checking == "share") {
						if (mFragmentListener != null)
							mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, "}", null, null);
						else
							return;
					}else
					{
						Toast.makeText(getActivity(), "Not connect CLOCK.", Toast.LENGTH_SHORT).show();
					}
				break;
			}
	}

	public void onAlert() { // ? 로 구분
		Context hContext = getActivity().getApplicationContext();
		AlertDialog.Builder aDialog = new AlertDialog.Builder(getActivity());
		aDialog.setTitle("Connection Lost!");
		aDialog.setMessage("You're away from your bike,\nand you're not connected.");
		final Vibrator vibrator = (Vibrator) getActivity().getSystemService(Context.VIBRATOR_SERVICE);
		vibrator.vibrate(pattern,0);
		aDialog.setNeutralButton("I'll go find it.", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				mBtnCon.setEnabled(true);
				mBtnNew.setEnabled(true);
				mBtnPub.setEnabled(true);
				mBtnLock.setEnabled(true);
				mBtndel.setEnabled(true);
				mBtnshare.setEnabled(true);
				mBtnauto.setEnabled(true);
				connect = null;
				startsignal[1] = null;
				vibrator.cancel();
			}
		});
		aDialog.show();
	}

	private static final int NEW_LINE_INTERVAL = 1000;
	private long mLastReceivedTime = 0L;

	// Show messages from remote
	public void showMessage(String message) {
		if (message != null && message.length() > 0) {
			long current = System.currentTimeMillis();
			if (current - mLastReceivedTime > NEW_LINE_INTERVAL) {
				mTextChat.append("\n");
			}
			if (checking=="ok")
			{
					if (message.equals("?")) {
						startsignal[1] = "start!";
						Toast.makeText(getActivity(), "Signed, Sir. \nWelcome!!", Toast.LENGTH_SHORT).show();
						mBtnshare.setEnabled(false);
						mBtnCon.setEnabled(false);
						mBtnPubp.setEnabled(false);
						lockimg.setBackgroundResource(R.drawable.locked_icon);
					} else {
						startsignal[1] = null;
						Toast.makeText(getActivity(), "Don't Connected.", Toast.LENGTH_SHORT).show();
						onCheck();
					}
					checking = null;
			}

			if(message.equals("{"))
			{
				Toast.makeText(getActivity(), "Signed, Sir.\nSucceced!!", Toast.LENGTH_SHORT).show();
			}
			if(message.equals("<")){
				Toast.makeText(getActivity(), "OK, Locked.", Toast.LENGTH_SHORT).show();
				opencheck = 1;
				lockimg.setBackgroundResource(R.drawable.locked_icon);
			}
			if(message.equals(">")){
				Toast.makeText(getActivity(), "OK, Unlocked.", Toast.LENGTH_SHORT).show();
				opencheck = 2;
				lockimg.setBackgroundResource(R.drawable.unlocked_icon);

			}
			if(message.equals(",")){
				Toast.makeText(getActivity(), "Signed, Sir. \n Key number is " + strKey, Toast.LENGTH_SHORT).show();

			}
			if(message.equals(";")){
				Toast.makeText(getActivity(), "Good bye My dude. ;(", Toast.LENGTH_SHORT).show();
				sharecheck = 2;
				lockimg.setBackgroundResource(R.drawable.users_lock);
			}
			if(message.equals("."))
			{
				Toast.makeText(getActivity(), "OK, Sir.\nShare key has been destroyed.", Toast.LENGTH_SHORT).show();
			}
			if (checking=="share") {
				if(message.equals(":")) {
					Toast.makeText(getActivity(), "Enjoy My dude. :)", Toast.LENGTH_SHORT).show();
					sharecheck = 3;
					mBtnshare.setEnabled(true);
					mBtnNew.setEnabled(false);
					mBtnPub.setEnabled(false);
					mBtnLock.setEnabled(false);
					mBtndel.setEnabled(false);
					lockimg.setBackgroundResource(R.drawable.users_lock);
				}
			}
			if(parkingcheck == 1 && message.equals("?"))
			{
				Toast.makeText(getActivity(), "Signed, admin.\nUse that.", Toast.LENGTH_SHORT).show();
				mBtnPubp.setEnabled(true);
			}
			if(message.equals("("))
			{
				mBtnauto.setText("Auto Lock OFF");
			}
			if(message.equals(")"))
			{
				mBtnauto.setText("Auto Lock ON");
			}
			int scrollamout = mTextChat.getLayout().getLineTop(mTextChat.getLineCount()) - mTextChat.getHeight();
			if (scrollamout > mTextChat.getHeight())
				mTextChat.scrollTo(0, scrollamout);
			mLastReceivedTime = current;
		}
	}



	public void onCheck() { // ? 로 구분
		Context hContext = getActivity().getApplicationContext();
		LayoutInflater inflater = (LayoutInflater) hContext.getSystemService(LAYOUT_INFLATER_SERVICE);
		View layout = inflater.inflate(R.layout.custom_dialog, null);

		pwd = (EditText) layout.findViewById(R.id.text);

		AlertDialog.Builder aDialog = new AlertDialog.Builder(getActivity());
		aDialog.setTitle("Insert your password.");
		aDialog.setMessage("Enter the password.\nFirst password is '1234'.");
		aDialog.setView(layout);
		aDialog.setPositiveButton("Sign", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				//1234값이면 "Wup57K5gmI17acAusJYG1g==" 초기값 전송
				Encoding(pwd.getText().toString(), 0);
				if (mFragmentListener != null)
					mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, "?" + encode[0], null, null);
				else
					return;
				Toast.makeText(getActivity(), "Crypto Algorithm comparing...", Toast.LENGTH_SHORT).show();
				checking = "ok";
			}
		});
		aDialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
			}
		});
		aDialog.setNeutralButton("Share", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				showShare();
			}
		});
		aDialog.show();
	}

	public void showShare() { // ' 으로 구분
		Context hContext = getActivity().getApplicationContext();
		LayoutInflater inflater = (LayoutInflater) hContext.getSystemService(LAYOUT_INFLATER_SERVICE);
		View layout = inflater.inflate(R.layout.custom_dialog, null);

		pwd = (EditText) layout.findViewById(R.id.text);

		AlertDialog.Builder aDialog = new AlertDialog.Builder(getActivity());
		aDialog.setTitle("Insert Share key");
		aDialog.setMessage("Enter the password.\n(4-digit number.)");
		aDialog.setView(layout);

		aDialog.setPositiveButton("Sign", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				Encoding(pwd.getText().toString(), 1);
					if (mFragmentListener != null)
						mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, ":" + encode[1], null, null);
					else
						return;
					Toast.makeText(getActivity(), "Share Key Comparing.....", Toast.LENGTH_SHORT).show();
					checking = "share";

			}
		});
		aDialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
			}
		});
		aDialog.show();
	}


	public void showMod() {
		Context hContext = getActivity().getApplicationContext();
		LayoutInflater inflater = (LayoutInflater) hContext.getSystemService(LAYOUT_INFLATER_SERVICE);
		View layout = inflater.inflate(R.layout.newpw_dialog, null);

		pwd = (EditText) layout.findViewById(R.id.text);
		pwdcheck = (EditText) layout.findViewById(R.id.text1);

		AlertDialog.Builder aDialog = new AlertDialog.Builder(getActivity());
		aDialog.setTitle("Modify your Password");
		aDialog.setMessage("You can modify a password.\n");
		aDialog.setView(layout);

		aDialog.setPositiveButton("Sign", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				if (pwd.getText().toString().equals(pwdcheck.getText().toString())) {
					Encoding(pwd.getText().toString(), 0);
					if (mFragmentListener != null)
						mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, "{" + encode[0], null, null);
					else
						return;
				} else {
					Toast.makeText(getActivity(), "Invalid input.", Toast.LENGTH_SHORT).show();
				}
			}
		});
		aDialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
			}
		});
		aDialog.show();
	}


	public void showPublic() {
		mRand = new Random();
		pubkey = new int[5];
		Context hContext = getActivity().getApplicationContext();

			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					pubkey[i] = (mRand.nextInt(9) + 0) * 1000;
				} else if (i == 1) {
					pubkey[i] = (mRand.nextInt(9) + 0) * 100;
				} else if (i == 2) {
					pubkey[i] = (mRand.nextInt(9) + 0) * 10;
				} else {
					pubkey[i] = (mRand.nextInt(9) + 0);
				}
				pubkey[4] += pubkey[i];
			}
			if (pubkey[4] < 1000)
				strKey = "0" + String.valueOf(pubkey[4]);
			else if (pubkey[4] < 100)
				strKey = "00" + String.valueOf(pubkey[4]);
			else if (pubkey[4] < 10)
				strKey = "000" + String.valueOf(pubkey[4]);
			else
				strKey = String.valueOf(pubkey[4]);
			Encoding(strKey, 1);
			if (mFragmentListener != null)
				mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, "," + encode[1], null, null);
			else
				return;

		AlertDialog.Builder aDialog = new AlertDialog.Builder(getActivity());
		aDialog.setTitle("Your Share key is.....");
		aDialog.setMessage("Show Your Share key !!\n"+strKey);
			aDialog.setNeutralButton("OK, Checked it.", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int which) {

				}
			});
		aDialog.show();
	}

	public void showPubp() {
		Context hContext = getActivity().getApplicationContext();
		LayoutInflater inflater = (LayoutInflater) hContext.getSystemService(LAYOUT_INFLATER_SERVICE);
		View layout = inflater.inflate(R.layout.public_dialog, null);

		pwd = (EditText) layout.findViewById(R.id.text);
		pwdcheck = (EditText) layout.findViewById(R.id.text1);

		AlertDialog.Builder aDialog = new AlertDialog.Builder(getActivity());
		aDialog.setTitle("Public Cycle parking system.");
		aDialog.setMessage("Insert your Identity information.\n");
		aDialog.setView(layout);

		aDialog.setPositiveButton("Sign", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				if (pwd.getText().toString().length() == 11 && Pattern.matches("^[0-9]+$", pwd.getText().toString())) {
					Encoding(pwdcheck.getText().toString(), 2);
					if (mFragmentListener != null)
						mFragmentListener.OnFragmentCallback(IFragmentListener.CALLBACK_SEND_MESSAGE, 0, 0, "?" + pwd.getText().toString() + encode[2] + str_date, null, null);
					else
						return;

				} else {
					Toast.makeText(getActivity(), "Invalid input.", Toast.LENGTH_SHORT).show();
				}
			}
		});
		aDialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
			}
		});
		aDialog.show();
	}

	public void Encoding(String Key, int i) {
		try {
			Cipher c = Cipher.getInstance("AES");
			c.init(Cipher.ENCRYPT_MODE, secureKey);
			encodedBytes[i] = c.doFinal(Key.getBytes());
			encode[i] = Base64.encodeToString(encodedBytes[i], 0);
		} catch (Exception e) {
			Log.e(TAG, "AES encryption error");
		}
	}
}

