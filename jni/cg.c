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

#include "cg.h"
#include <string.h>

jsize cg_jac(struct BMQ1 A, double * P, double * b, double * x, jsize max_iters, double eps_relative)
{
    jsize used_iters = 0;
    jsize size = A.size;

    double * p = (double*) malloc (size * sizeof(double));
    double * r = (double*) malloc (size * sizeof(double));
    double * v = (double*) malloc (size * sizeof(double));
    double * z = (double*) malloc (size * sizeof(double));
    double alpha, alpha_new, lambda, initial_defect, current_defect, temp;

    defect(r, b, A, x);
    element_product(p, P, r, size);

    initial_defect = norm_l2_true(r, size);

    alpha_new = dot_product(r, p, size);

    while (used_iters < max_iters)
    {
        product(v, A, p);
        temp = dot_product(v, p, size);
        lambda = alpha_new / temp;
        ++used_iters;
        scaled_sum(x, x, p, lambda, size);
        scaled_sum(r, r, v, -lambda, size);

        current_defect = norm_l2_true(r, size);
        if (current_defect < eps_relative * initial_defect)
        {
            break;
        }
        if (current_defect < eps_relative)
        {
            break;
        }
        if(used_iters == max_iters)
        {
            break;
        }

        element_product(z, P, r, size);
        alpha = alpha_new;
        alpha_new = dot_product(r, z, size);
        scale(p, p, alpha_new / alpha, size);
        sum(p, p, z, size);
    }

    free(p);
    free(r);
    free(v);
    free(z);

    return used_iters;
}
