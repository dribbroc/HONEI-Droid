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

#include "la.h"
#include <pthread.h>
#define NUM_THREADS 2

void copy(double * src, double * dest, jsize size)
{
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        dest[i] = src[i];
    }
}

struct scaled_sum_thread_data
{
    double * r;
    double * x;
    double * y;
    double a;
    jsize size;
};

void * scaled_sum_thread(void * argument)
{
    jsize i = 0;
    struct scaled_sum_thread_data * data = (struct scaled_sum_thread_data *) argument;
    double * r = data->r;
    double * x = data->x;
    double * y = data->y;
    double a = data->a;
    jsize size = data->size;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = x[i] + a*y[i];
    }
}

void scaled_sum(double * r, double * x, double * y, double a, jsize size)
{
    pthread_t threads[NUM_THREADS];
    struct scaled_sum_thread_data data[NUM_THREADS];
    jsize sizes[NUM_THREADS];
    jsize i = 0;
    for (i = 0 ; i < NUM_THREADS ; ++i)
    {
        sizes[i] = size / NUM_THREADS;
    }
    sizes[NUM_THREADS - 1] += size - ((size / NUM_THREADS) * NUM_THREADS);

    for (i = 0 ; i < NUM_THREADS ; ++i)
    {
        struct scaled_sum_thread_data tdata;
        tdata.r = r;
        tdata.x = x;
        tdata.y = y;
        tdata.a = a;
        tdata.size = sizes[i];
        data[i] = tdata;
        pthread_create(&threads[i], NULL, scaled_sum_thread, (void*) &data[i]);

        r+=sizes[i];
        x+=sizes[i];
        y+=sizes[i];
    }

    for (i = 0 ; i < NUM_THREADS ; ++i)
    {
        pthread_join(threads[i], NULL);
    }
}

void scaled_sum3(double * r, double * x, double * y, double * z, jsize size)
{
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = x[i] + y[i] * z[i];
    }
}

double dot_product(double * x, double * y, jsize size)
{
    double r = 0;
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        r += x[i] * y[i];
    }
    return r;
}

double norm_l2_false(double * x, jsize size)
{
    double r = 0;
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        r += x[i] * x[i];
    }
    return r;
}

double norm_l2_true(double * x, jsize size)
{
    double r = norm_l2_false(x, size);
    return sqrt(r);
}

void sum(double * r, double * x, double * y, jsize size)
{
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = x[i] + y[i];
    }
}

void difference(double * r, double * x, double * y, jsize size)
{
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = x[i] - y[i];
    }
}

void element_product(double * r, double * x, double * y, jsize size)
{
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = x[i] * y[i];
    }
}

void scale(double * r, double * x, double a, jsize size)
{
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = x[i] * a;
    }
}

void product(double * r, struct BMQ1 bmq1, double * x)
{
    jsize index = 0;;
    jsize size = bmq1.size;
    jsize m = bmq1.root;

    //index 0
    r[index] = bmq1.dd[index] * x[index]
        + bmq1.du[index] * x[index + 1]
        + bmq1.ul[index] * x[index + m - 1]
        + bmq1.ud[index] * x[index + m]
        + bmq1.uu[index] * x[index + m + 1];

    //index in [1, root_n -1[
    index = 1;
    for ( ; index < m - 1 ; ++index)
    {
        r[index] = bmq1.dd[index] * x[index]
            + bmq1.dl[index] * x[index - 1]
            + bmq1.du[index] * x[index + 1]
            + bmq1.ul[index] * x[index + m - 1]
            + bmq1.ud[index] * x[index + m]
            + bmq1.uu[index] * x[index + m + 1];
    }

    //index root_n -1
    index = m - 1;
    r[index] = bmq1.dd[index] * x[index]
        + bmq1.lu[index] * x[index - m + 1]
        + bmq1.dl[index] * x[index - 1]
        + bmq1.du[index] * x[index + 1]
        + bmq1.ul[index] * x[index + m - 1]
        + bmq1.ud[index] * x[index + m]
        + bmq1.uu[index] * x[index + m + 1];

    //index root_n
    index = m;
    r[index] = bmq1.dd[index] * x[index]
        + bmq1.lu[index] * x[index - m + 1]
        + bmq1.ld[index] * x[index - m]
        + bmq1.dl[index] * x[index - 1]
        + bmq1.du[index] * x[index + 1]
        + bmq1.ul[index] * x[index + m - 1]
        + bmq1.ud[index] * x[index + m]
        + bmq1.uu[index] * x[index + m + 1];

    //index in [root_n + 1, n - (root_n + 1)[
    index = m + 1;
    for ( ; index < size - m - 1 ; ++index)
    {
        r[index] = bmq1.dd[index] * x[index]
            + bmq1.ll[index] * x[index - m - 1]
            + bmq1.lu[index] * x[index - m + 1]
            + bmq1.ld[index] * x[index - m]
            + bmq1.dl[index] * x[index - 1]
            + bmq1.du[index] * x[index + 1]
            + bmq1.ul[index] * x[index + m - 1]
            + bmq1.ud[index] * x[index + m]
            + bmq1.uu[index] * x[index + m + 1];
    }

    //index n - (root_n + 1)
    index = size - m - 1;
    r[index] = bmq1.dd[index] * x[index]
        + bmq1.ll[index] * x[index - m - 1]
        + bmq1.lu[index] * x[index - m + 1]
        + bmq1.ld[index] * x[index - m]
        + bmq1.dl[index] * x[index - 1]
        + bmq1.du[index] * x[index + 1]
        + bmq1.ul[index] * x[index + m - 1]
        + bmq1.ud[index] * x[index + m];

    //index n - root_n
    index = size - m;
    r[index] = bmq1.dd[index] * x[index]
        + bmq1.ll[index] * x[index - m - 1]
        + bmq1.lu[index] * x[index - m + 1]
        + bmq1.ld[index] * x[index - m]
        + bmq1.dl[index] * x[index - 1]
        + bmq1.du[index] * x[index + 1]
        + bmq1.ul[index] * x[index + m - 1];

    //index in [n - root_n + 1, n -1[
    index = size - m + 1;
    for ( ; index < size - 1 ; ++ index)
    {
        r[index] = bmq1.dd[index] * x[index]
            + bmq1.ll[index] * x[index - m - 1]
            + bmq1.lu[index] * x[index - m + 1]
            + bmq1.ld[index] * x[index - m]
            + bmq1.dl[index] * x[index - 1]
            + bmq1.du[index] * x[index + 1];
    }

    //index n - 1
    index = size - 1;
    r[index] = bmq1.dd[index] * x[index]
        + bmq1.ll[index] * x[index - m - 1]
        + bmq1.lu[index] * x[index - m + 1]
        + bmq1.ld[index] * x[index - m]
        + bmq1.dl[index] * x[index - 1];
}

void defect(double * r, double * rhs, struct BMQ1 bmq1, double * x)
{
    product(r, bmq1, x);
    difference(r, rhs, r, bmq1.size);
}
