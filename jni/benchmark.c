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

#include <cpu-features.h>
#include "la.h"

JNIEXPORT jstring JNICALL
Java_com_honei_HoneiBenchmarkActivity_scaledSumBenchmark(JNIEnv* env, jobject thiz)
{
    jsize size = 1000000;
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
    for (i = 0 ; i < 5 ; ++i)
    {
        scaled_sum(r, x, y, a, size);
    }
    gettimeofday(&bt, 0);
    double total = (bt.tv_sec + (bt.tv_usec / 1e6)) - (at.tv_sec + (at.tv_usec / 1e6));
    total /= 5.;
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

JNIEXPORT jstring JNICALL
Java_com_honei_HoneiBenchmarkActivity_scaledSumfBenchmark(JNIEnv* env, jobject thiz)
{
    jsize size = 10000000;
    float * r = (float*) malloc (size * sizeof(float));
    float * x = (float*) malloc (size * sizeof(float));
    float * y = (float*) malloc (size * sizeof(float));
    float a = 3;
    jsize i;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = 4711;
        x[i] = 3.413 + i;
        y[i] = -56.7 - i;
    }

    struct timeval at, bt;

    gettimeofday(&at, 0);
    for (i = 0 ; i < 10 ; ++i)
    {
        scaled_sumf(r, x, y, a, size);
    }
    gettimeofday(&bt, 0);
    double total = (bt.tv_sec + (bt.tv_usec / 1e6)) - (at.tv_sec + (at.tv_usec / 1e6));
    total /= 10.;
    double mflops = (2 * size) / total / 1e6;

    char text[999];
    strcpy(text, "ScaledSumf float, size = ");
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

JNIEXPORT jstring JNICALL
Java_com_honei_HoneiBenchmarkActivity_scaledSumfneonBenchmark(JNIEnv* env, jobject thiz)
{
#ifdef HONEI_NEON

    uint64_t features = android_getCpuFeatures();
    if(!(features & ANDROID_CPU_ARM_FEATURE_NEON == 0))
    {

    jsize size = 10000000;
    float32_t * r = (float32_t*) malloc (size * sizeof(float32_t));
    float32_t * x = (float32_t*) malloc (size * sizeof(float32_t));
    float32_t * y = (float32_t*) malloc (size * sizeof(float32_t));
    float32_t a = 3;
    jsize i;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = 4711;
        x[i] = 3.413 + i;
        y[i] = -56.7 - i;
    }

    struct timeval at, bt;

    gettimeofday(&at, 0);
    for (i = 0 ; i < 10 ; ++i)
    {
        scaled_sumf_NEON(r, x, y, a, size);
    }
    gettimeofday(&bt, 0);
    double total = (bt.tv_sec + (bt.tv_usec / 1e6)) - (at.tv_sec + (at.tv_usec / 1e6));
    total /= 10.;
    double mflops = (2 * size) / total / 1e6;

    char text[999];
    strcpy(text, "ScaledSumfNEON float32_t, size = ");
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
    else
        return (*env)->NewStringUTF(env, "skipping NEON benchmarks...\n");
#endif
    return (*env)->NewStringUTF(env, "skipping NEON benchmarks...\n");
}

JNIEXPORT jstring JNICALL
Java_com_honei_HoneiBenchmarkActivity_dotProductBenchmark(JNIEnv* env, jobject thiz)
{
    jsize size = 1000000;
    double * x = (double*) malloc (size * sizeof(double));
    double * y = (double*) malloc (size * sizeof(double));
    double r;
    jsize i;
    for (i = 0 ; i < size ; ++i)
    {
        x[i] = 3.413 + i;
        y[i] = -56.7 - i;
    }

    struct timeval at, bt;

    gettimeofday(&at, 0);
    for (i = 0 ; i < 5 ; ++i)
    {
        r = dot_product(x, y, size);
    }
    gettimeofday(&bt, 0);
    double total = (bt.tv_sec + (bt.tv_usec / 1e6)) - (at.tv_sec + (at.tv_usec / 1e6));
    total /= 5.;
    double mflops = (2 * size) / total / 1e6;

    char text[999];
    strcpy(text, "DotProduct double, size = ");
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

    free(x);
    free(y);
    return (*env)->NewStringUTF(env, text);
}

JNIEXPORT jstring JNICALL
Java_com_honei_HoneiBenchmarkActivity_productBenchmark(JNIEnv* env, jobject thiz)
{
    // BEWARE! Flops are hardcoded for lvl 9
    jsize size = 263169;

    double * r = (double*) malloc (size * sizeof(double));
    double * x = (double*) malloc (size * sizeof(double));
    double * ll = (double*) malloc (size * sizeof(double));
    double * ld = (double*) malloc (size * sizeof(double));
    double * lu = (double*) malloc (size * sizeof(double));
    double * dl = (double*) malloc (size * sizeof(double));
    double * dd = (double*) malloc (size * sizeof(double));
    double * du = (double*) malloc (size * sizeof(double));
    double * ul = (double*) malloc (size * sizeof(double));
    double * ud = (double*) malloc (size * sizeof(double));
    double * uu = (double*) malloc (size * sizeof(double));
    jsize i;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = 4711;
        x[i] = 3.413 - i;
        ll[i] = i;
        ld[i] = i;
        lu[i] = i;
        dl[i] = i;
        dd[i] = i;
        du[i] = i;
        ul[i] = i;
        ud[i] = i;
        uu[i] = i;
    }
    struct BMQ1 bmq1;
    bmq1.size = size;
    bmq1.root = (jsize) sqrt(size);
    bmq1.ll = ll;
    bmq1.ld = ld;
    bmq1.lu = lu;
    bmq1.dl = dl;
    bmq1.dd = dd;
    bmq1.du = du;
    bmq1.ul = ul;
    bmq1.ud = ud;
    bmq1.uu = uu;

    struct timeval at, bt;

    gettimeofday(&at, 0);
    for (i = 0 ; i < 5 ; ++i)
    {
        product(r, bmq1, x);
    }
    gettimeofday(&bt, 0);
    double total = (bt.tv_sec + (bt.tv_usec / 1e6)) - (at.tv_sec + (at.tv_usec / 1e6));
    total /= 5.;
    double mflops = 4730882 / total / 1e6;

    char text[999];
    strcpy(text, "Q1 BMDV double, size = ");
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
    free(ll);
    free(ld);
    free(lu);
    free(dl);
    free(dd);
    free(du);
    free(ul);
    free(ud);
    free(uu);
    return (*env)->NewStringUTF(env, text);
}
