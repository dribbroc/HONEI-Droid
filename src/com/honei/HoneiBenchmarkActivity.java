/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2011 Markus Geveler <markus.geveler@math.tu-dortmund.de>
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
import android.widget.*;
import android.content.Context;
import android.widget.Toast;
import android.os.AsyncTask;

public class HoneiBenchmarkActivity extends Activity
{
    private TextView tv;
    private class ScaledSumTask extends AsyncTask<Void, String, Integer> {
        protected Integer doInBackground(Void... a) {
            publishProgress("ScaledSum benchmark...\n");
            publishProgress(scaledSumBenchmark());
            publishProgress("DotProduct benchmark...\n");
            publishProgress(dotProductBenchmark());
            publishProgress("Q1 BMDV benchmark...\n");
            publishProgress(productBenchmark());
            return 1;
        }

        protected void onProgressUpdate(String... result)
        {
            tv.append(result[0]);
        }
    }

    /** Called when the activity is first created. */
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.benchmarks);

        tv = (TextView)findViewById(R.id.benchout);
        tv.setText("Running benchmarks:\n");
        new ScaledSumTask().execute();
    }

    public native String scaledSumBenchmark();
    public native String dotProductBenchmark();
    public native String productBenchmark();

    static
    {
        System.loadLibrary("honei");
    }

    public void quit(View v)
    {
        finish();
    }
}
