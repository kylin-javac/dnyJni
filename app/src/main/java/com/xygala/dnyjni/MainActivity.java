package com.xygala.dnyjni;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {
    private Futils futils;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv = (TextView) findViewById(R.id.sample_text);
        futils= new Futils();
        tv.setText(futils.stringFromJNI());
    }


}
