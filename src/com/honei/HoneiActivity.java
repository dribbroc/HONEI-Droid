/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2011 Markus Geveler <markus.geveler@math.tu-dortmund.de>
 * Copyright (c) 2011 Dirk Ribbrock <dirk.ribbrock@math.tu-dortmund.de>
 *
 * This file is part of the HONEI C++ library. HONEI is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * HONEI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

package com.honei;

import android.app.Activity;
import android.os.Bundle;
import android.view.View.*;
import android.view.*;
import android.widget.Button;
import android.content.Context;
import android.widget.Toast;
import android.content.Intent;

public class HoneiActivity extends Activity implements OnClickListener
{
    /** Called when the activity is first created. */
    public void onCreate(Bundle savedInstanceState)
    {
        //get button and set listener
        Button button = (Button)findViewById(R.id.button);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
    }

    public void onClick(View v)
    {
        Context context = getApplicationContext();
        CharSequence text = runTests();
        int duration = Toast.LENGTH_SHORT;

        Toast toast = Toast.makeText(context, text, duration);
        toast.show();
    }

    public void quit(View v)
    {
        finish();
    }

    public void startUnittests(View v)
    {
        Intent intent = new Intent(this, HoneiUnittestActivity.class);
        startActivity(intent);
    }

    public native String runTests();
    static
    {
        System.loadLibrary("honei");
    }

}
