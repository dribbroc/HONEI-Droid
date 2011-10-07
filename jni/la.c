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

void copy(double * src, double * dest, jsize size)
{
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        dest[i] = src[i];
    }
}

void scaled_sum(double * r, double * x, double * y, double a, jsize size)
{
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = x[i] + a*y[i];
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
    jsize size = bmq1.size;
    jsize root = bmq1.root;
    jsize i = 0;
    for (i = 0 ; i < size ; ++i)
    {
        r[i] = 0.;
    }

    scaled_sum3(r + root + 1, r + root + 1, bmq1.ll + root + 1, x,            size - root - 1);
    scaled_sum3(r + root,     r + root,     bmq1.ld + root,     x,            size - root);
    scaled_sum3(r + root - 1, r + root - 1, bmq1.lu + root - 1, x,            size - root + 1);
    scaled_sum3(r + 1,        r + 1,        bmq1.dl + 1,        x,            size - 1);
    scaled_sum3(r,            r,            bmq1.dd,            x,            size);
    scaled_sum3(r,            r,            bmq1.du,            x + 1,        size - 1);
    scaled_sum3(r,            r,            bmq1.ul,            x + root - 1, size - root + 1);
    scaled_sum3(r,            r,            bmq1.ud,            x + root,     size - root);
    scaled_sum3(r,            r,            bmq1.uu,            x + root + 1, size - root - 1);
}

void defect(double * r, double * rhs, struct BMQ1 bmq1, double * x)
{
    product(r, bmq1, x);
    difference(r, rhs, r, bmq1.size);
}
