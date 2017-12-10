package com.clocksystem.code.clock.fragments;

import java.util.Locale;

import com.clocksystem.code.clock.R;

import android.content.Context;
import android.os.Handler;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;


public class FragmentAdapter extends FragmentPagerAdapter {
	
	public static final String TAG = "FragmentAdapter";
	
	// TODO: Total count
	public static final int FRAGMENT_COUNT = 2;
	
    // TODO: Fragment position
    public static final int FRAGMENT_POS_MAIN = 0;
    public static final int FRAGMENT_POS_MAP = 1;


    
    // System
    private Context mContext = null;
    private Handler mHandler = null;
    private IFragmentListener mFragmentListener = null;
    
    private Fragment mMainFragment = null;
    private Fragment mMaps = null;
    public FragmentAdapter(FragmentManager fm, Context c, IFragmentListener l, Handler h) {
		super(fm);
		mContext = c;
		mFragmentListener = l;
		mHandler = h;
	}
    
	@Override
	public Fragment getItem(int position) {
		// getItem is called to instantiate the fragment for the given page.
		Fragment fragment;
		//boolean needToSetArguments = false;
		
		if(position == FRAGMENT_POS_MAIN) {
			if(mMainFragment == null) {
				mMainFragment = new MainFragment(mContext, mFragmentListener, mHandler);
				//needToSetArguments = true;
			}
			fragment = mMainFragment;
			
		} else if(position == FRAGMENT_POS_MAP) {
			if(mMaps == null) {
				mMaps = new Maps(mContext, mFragmentListener);
				//needToSetArguments = true;
			}
			fragment = mMaps;

		}

		else {
			fragment = null;
		}

		
		return fragment;
	}

	@Override
	public int getCount() {
		return FRAGMENT_COUNT;
	}

	@Override
	public CharSequence getPageTitle(int position) {
		Locale l = Locale.getDefault();
		switch (position) {
		case FRAGMENT_POS_MAIN:
			return mContext.getString(R.string.title_lock).toUpperCase(l);
		case FRAGMENT_POS_MAP:
			return mContext.getString(R.string.title_odometer).toUpperCase(l);


		}
		return null;
	}
    
    
}
