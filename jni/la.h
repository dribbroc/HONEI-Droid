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
#include <math.h>

struct BMQ1
{
    jsize size;
    jsize root;
    double * ll;
    double * ld;
    double * lu;
    double * dl;
    double * dd;
    double * du;
    double * ul;
    double * ud;
    double * uu;
};

void difference(double * r, double * x, double * y, jsize size);
double dot_product(double * x, double * y, jsize size);
void element_product(double * r, double * x, double * y, jsize size);
double norm_l2_false(double * x, jsize size);
double norm_l2_true(double * x, jsize size);
void product(double * r, double *x, struct BMQ1 bmq1);
void scale(double * r, double * x, double a, jsize size);
void scaled_sum(double * r, double * x, double * y, double a, jsize size);
void scaled_sum3(double * r, double * x, double * y, double * z, jsize size);
void sum(double * r, double * x, double * y, jsize size);
