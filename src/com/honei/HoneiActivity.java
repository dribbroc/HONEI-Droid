package com.honei;

import android.app.Activity;
import android.os.Bundle;
import android.view.View.*;
import android.view.*;
import android.widget.Button;
import android.content.Context;
import android.widget.Toast;

public class HoneiActivity extends Activity implements OnClickListener
{
  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    //get button and set listener
    Button button = (Button)findViewById(R.id.button);
    //button.setOnClickListener(this);

    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
  }

  public void onClick(View v)
  {
    Context context = getApplicationContext();
    CharSequence text = "Hello toast!";
    int duration = Toast.LENGTH_SHORT;

    Toast toast = Toast.makeText(context, text, duration);
    toast.show();
  }

}
