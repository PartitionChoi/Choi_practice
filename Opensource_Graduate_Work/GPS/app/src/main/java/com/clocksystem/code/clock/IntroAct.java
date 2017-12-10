package com.clocksystem.code.clock;


import android.os.*;
import android.content.*;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.view.*;

public class IntroAct extends AppCompatActivity{
    Handler h;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_intro);
        ActionBar actionBar = getSupportActionBar();
        actionBar.hide();
        h= new Handler();
        h.postDelayed(mrun, 1500);
    }

    Runnable mrun = new Runnable(){
        @Override
        public void run(){
            Intent i = new Intent(IntroAct.this, MainActivity.class);
            startActivity(i);
            finish();
            overridePendingTransition(android.R.anim.fade_in, android.R.anim.fade_out);
        }
    };
    @Override
    public void onBackPressed(){
        super.onBackPressed();
        h.removeCallbacks(mrun);
    }
}
