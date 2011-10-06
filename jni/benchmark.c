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
#include <sys/time.h>

#include "la.h"

JNIEXPORT jstring JNICALL
Java_com_honei_HoneiBenchmarkActivity_scaledSumBenchmark(JNIEnv* env, jobject thiz)
{
    jsize size = 2000000;
    double * r = (double*) malloc (size * sizeof(double));
    double * x = (double*) malloc (size * sizeof(double));
    double * y = (double*) malloc (size * sizeof(double));
    double a = 3;
    jsize i;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = 4711;
        x[i] = 3.413 + i;
        y[i] = -56.7 - i;
    }

    struct timeval at, bt;

    gettimeofday(&at, 0);
    scaled_sum(r, x, y, a, size);
    gettimeofday(&bt, 0);
    double total = (bt.tv_sec + (bt.tv_usec / 1e6)) - (at.tv_sec + (at.tv_usec / 1e6));
    double mflops = (2 * size) / total / 1e6;

    char text[999];
    strcpy(text, "ScaledSum double, size = ");
    char snumber[10];
    sprintf(snumber, "%d", size);
    strcat(text, snumber);
    strcat(text, "\n");
    strcat(text, "Runtime[sec]: ");
    sprintf(snumber, "%lf", total);
    strcat(text, snumber);
    strcat(text, "\n");
    strcat(text, "MFLOPS: ");
    sprintf(snumber, "%lf", mflops);
    strcat(text, snumber);
    strcat(text, "\n");
    strcat(text, "=========================\n");

    free(r);
    free(x);
    free(y);
    return (*env)->NewStringUTF(env, text);
}
