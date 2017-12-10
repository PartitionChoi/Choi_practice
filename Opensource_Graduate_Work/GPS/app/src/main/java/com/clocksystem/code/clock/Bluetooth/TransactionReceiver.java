package com.clocksystem.code.clock.Bluetooth;

import android.os.Handler;


public class TransactionReceiver {
	private static final String TAG = "TransactionReceiver";
	
	private static final int PARSE_MODE_ERROR = 0;
	private static final int PARSE_MODE_WAIT_START_BYTE = 1;
	private static final int PARSE_MODE_WAIT_COMMAND = 2;
	private static final int PARSE_MODE_WAIT_DATA = 3;
	private static final int PARSE_MODE_WAIT_END_BYTE = 4;
	private static final int PARSE_MODE_COMPLETED = 101;
	
	private Handler mHandler = null;
	
	
	
	public TransactionReceiver(Handler h) {
		mHandler = h;
		reset();
	}

	public void reset() {
	}

	public void setByteArray(byte[] buffer, int count) {
		parseStream(buffer, count);
	}

	public Object getObject() {
		// TODO: return what you want
		return null;
	}

	public void parseStream(byte[] buffer, int count) {
		if(buffer != null && buffer.length > 0 && count > 0) {
			for(int i=0; i < buffer.length && i < count; i++) {

				// TODO: parse buffer
				
				
			}	// End of for loop
		}	// End of if()
	}	// End of parseStream()

	
}
