/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
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

#include <jni.h>
#include <string.h>
#include <stdio.h>
#include "la.h"

JNIEXPORT jstring JNICALL
Java_com_honei_HoneiActivity_runTests(JNIEnv* env, jobject thiz)

{
    char text[9999];
    strcpy(text, "Running tests:\n");
    int failed = 0;

    {
        jsize size = 200;
        double r[size];
        double x[size];
        double y[size];
        double a = 3;
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            r[i] = 4711;
            x[i] = 3.413 + i;
            y[i] = -56.7 - i;
        }
        scaled_sum(r, x, y, a, size);
        for (i = 0 ; i < size ; ++i)
        {
            if (r[i] != y[i] + x[i] * a)
            {
                strcat(text, "ScaledSum Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "ScaledSum Test PASSED!\n");
        }
    }
    {
        jsize size = 200;
        double r[size];
        double x[size];
        double y[size];
        double z[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            r[i] = 4711;
            x[i] = 3.413 + i;
            y[i] = -56.7 - i;
            z[i] = 0.12;
        }
        scaled_sum3(r, x, y, z, size);
        for (i = 0 ; i < size ; ++i)
        {
            if (r[i] != y[i] + x[i] * z[i])
            {
                strcat(text, "ScaledSum3 Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "ScaledSum3 Test PASSED!\n");
        }
    }
    {
        jsize size = 200;
        double r[size];
        double x[size];
        double a = 41.781;
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            r[i] = 4711;
            x[i] = 3.413 + i;
        }
        scale(r, x, a, size);
        for (i = 0 ; i < size ; ++i)
        {
            if (r[i] != x[i] * a)
            {
                strcat(text, "Scale Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "Scale Test PASSED!\n");
        }
    }
    {
        jsize size = 200;
        double x[size];
        double y[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            x[i] = 5;
            y[i] = 3;
        }
        double r = dot_product(x, y, size);
        if (r != (5 * 3 * size))
        {
            strcat(text, "DotProduct Test FAILED!\n");
            ++failed;
        }
        else
            strcat(text, "DotProduct Test PASSED!\n");
    }
    {
        jsize size = 200;
        double x[size];
        double y[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            x[i] = 5;
        }
        double r = norm_l2_false(x, size);
        if (r != (5 * 5 * size))
        {
            strcat(text, "Norm L2 false Test FAILED!\n");
            ++failed;
        }
        else
            strcat(text, "Norm L2 false Test PASSED!\n");
    }
    {
        jsize size = 200;
        double x[size];
        double y[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            x[i] = 5;
        }
        double r = norm_l2_true(x, size);
        if (r != sqrt(5 * 5 * size))
        {
            strcat(text, "Norm L2 true Test FAILED!\n");
            ++failed;
        }
        else
            strcat(text, "Norm L2 true Test PASSED!\n");
    }
    {
        jsize size = 200;
        double r[size];
        double x[size];
        double y[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            r[i] = 4711;
            x[i] = 3.413 + i;
            y[i] = -56.7 - i;
        }
        sum(r, x, y, size);
        for (i = 0 ; i < size ; ++i)
        {
            if (r[i] != x[i] + y[i])
            {
                strcat(text, "Sum Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "Sum Test PASSED!\n");
        }
    }
    {
        jsize size = 200;
        double r[size];
        double x[size];
        double y[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            r[i] = 4711;
            x[i] = 3.413 + i;
            y[i] = -56.7 - i;
        }
        difference(r, x, y, size);
        for (i = 0 ; i < size ; ++i)
        {
            if (r[i] != x[i] - y[i])
            {
                strcat(text, "Difference Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "Difference Test PASSED!\n");
        }
    }
    {
        jsize size = 200;
        double r[size];
        double x[size];
        double y[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            r[i] = 4711;
            x[i] = 3.413 + i;
            y[i] = -56.7 - i;
        }
        element_product(r, x, y, size);
        for (i = 0 ; i < size ; ++i)
        {
            if (r[i] != x[i] * y[i])
            {
                strcat(text, "ElementProduct Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "ElementProduct Test PASSED!\n");
        }
    }

    strcat(text, "==============\n");
    strcat(text, "==============\n");

    if(failed == 0)
        strcat(text, "All Tests PASSED");
    else
    {
        char sfailed[10];
        sprintf(sfailed,"%d",failed);
        strcat(text, sfailed);
        strcat(text, " Tests FAILED");
    }

    return (*env)->NewStringUTF(env, text);
}
