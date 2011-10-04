package com.honei;

import android.app.Activity;
import android.os.Bundle;
import android.view.View.*;
import android.view.*;
import android.widget.Button;

public class HoneiActivity extends Activity implements OnClickListener
{
  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    //get button and set listener
    Button button = (Button)findViewById(R.id.button);
    button.setOnClickListener(this);

    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
  }

  public void onClick(View v)
  {

  }

}
