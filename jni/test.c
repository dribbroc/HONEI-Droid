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
#include "la.h"

JNIEXPORT jstring JNICALL
Java_com_honei_HoneiActivity_runTests(JNIEnv* env, jobject thiz)

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
            return (*env)->NewStringUTF(env, "ScaledSum Test FAILED!");
    }

    return (*env)->NewStringUTF(env, "All Tests PASSED!");
}
