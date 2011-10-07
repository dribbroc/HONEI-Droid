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

#include "bicgstab.h"
#include <string.h>

jsize bicgstab_jac(struct BMQ1 A, double * P, double * b, double * x, jsize max_iters, double eps_relative)
{
    jsize used_iters = 0;
    jsize size = A.size;

    double * r = (double*) malloc (size * sizeof(double));
    double * r_tilde = (double*) malloc (size * sizeof(double));
    double * r_tilde_0 = (double*) malloc (size * sizeof(double));
    double * p_tilde = (double*) malloc (size * sizeof(double));
    double * v = (double*) malloc (size * sizeof(double));
    double * v_tilde = (double*) malloc (size * sizeof(double));
    double * s = (double*) malloc (size * sizeof(double));
    double * s_tilde = (double*) malloc (size * sizeof(double));
    double * t = (double*) malloc (size * sizeof(double));
    double * t_tilde = (double*) malloc (size * sizeof(double));


    double defnorm, defnorm_0;
    double defnorm_00 = 1e14;
    unsigned long iter = 0;
    double rho_tilde, rho_tilde_old, alpha_tilde, omega_tilde, beta_tilde, gamma_tilde;
    double nrm_r_tilde_0, nrm_tilde_00;
    int early_exit = 0;
    int restarted = 0;
    int converged = 0;

    do
    {
        defect(r, b, A, x);
        defnorm_0 = norm_l2_false(r, size);
        defnorm = defnorm_0;
        element_product(r_tilde_0, P, r, size);
        nrm_r_tilde_0 = norm_l2_false(r_tilde_0, size);

        if (restarted == 0)
        {
            defnorm_00 = defnorm_0;
            nrm_tilde_00 = nrm_r_tilde_0;
        }
        copy(r_tilde_0, r_tilde, size);
        copy(r_tilde_0, p_tilde, size);
        rho_tilde = dot_product(r_tilde_0, r_tilde_0, size);

        // main BiCGStab loop
        do
        {
            ++used_iters;

            product(v, A, p_tilde);
            element_product(v_tilde, P, v, size);

            gamma_tilde = dot_product(v_tilde, r_tilde_0, size);

            if (fabs(gamma_tilde) < fabs(rho_tilde)*1e-14)
            {
                restarted = 1;
                break;
            }

            alpha_tilde = rho_tilde / gamma_tilde;

            if ((fabs(alpha_tilde) * norm_l2_false(v_tilde, size)) / defnorm < 1e-5)
            {
                restarted = 1;
                //break;
            }

            scaled_sum(s, r, v, -alpha_tilde, size);

            defnorm = norm_l2_false(s, size);
            if (defnorm < eps_relative * defnorm_00)
            {
                scaled_sum(x, x, p_tilde, alpha_tilde, size);

                early_exit = 1;
                converged = 1;
                //std::cout << "Breakpoint 3 (converged)" << std::endl;
                break;
            }
            scaled_sum(s_tilde, r_tilde, v_tilde, -alpha_tilde, size);

            product(t, A, s_tilde);

            element_product(t_tilde, P, t, size);

            gamma_tilde = dot_product(t_tilde, t_tilde, size);
            omega_tilde = dot_product(t_tilde, s_tilde, size);

            if (fabs(gamma_tilde) < fabs(omega_tilde) * 1e-14)
            {
                restarted = 1;
                //std::cout << "Breakpoint 4" << std::endl;
                break;
            }
            omega_tilde = omega_tilde / gamma_tilde;

            scaled_sum(x, x, s_tilde, omega_tilde, size);
            scaled_sum(x, x, p_tilde, alpha_tilde, size);

            scaled_sum(r, s, t, -omega_tilde, size);

            defnorm = norm_l2_false(r, size);
            if (defnorm < eps_relative * defnorm_00)
            {
                converged = 1;
                //std::cout << "Breakpoint 5 (converged)" << std::endl;
                break;
            }

            scaled_sum(r_tilde, s_tilde, t_tilde, -omega_tilde, size);

            rho_tilde_old = rho_tilde;
            rho_tilde = dot_product(r_tilde, r_tilde_0, size);

            beta_tilde = (alpha_tilde / omega_tilde) * (rho_tilde / rho_tilde_old);

            scaled_sum(p_tilde, p_tilde, v_tilde, -omega_tilde, size);
            scale(p_tilde, p_tilde, beta_tilde, size);
            sum(p_tilde, p_tilde, r_tilde, size);

        } while (used_iters <= max_iters);

    } while (converged == 0 && used_iters < max_iters);



    free(r);
    free(r_tilde);
    free(r_tilde_0);
    free(p_tilde);
    free(v);
    free(v_tilde);
    free(s);
    free(s_tilde);
    free(t);
    free(t_tilde);

    return used_iters;
}
