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
#include "cg.h"
#include "bicgstab.h"

#ifdef HONEI_NEON
#include <arm_neon.h>
#warning "NEON is defined"
#endif

#ifdef __ARM_ACLE
#include <arm_acle.h>
#warning "ACLE is defined"
#endif


JNIEXPORT jstring JNICALL
Java_com_honei_HoneiUnittestActivity_runTests(JNIEnv* env, jobject thiz)
{
    char text[50000];
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
            if (r[i] != x[i] + y[i] * a)
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
        float r[size];
        float x[size];
        float y[size];
        float a = 3;
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            r[i] = 4711;
            x[i] = 3.413 + i;
            y[i] = -56.7 - i;
        }
        scaled_sumf(r, x, y, a, size);
        for (i = 0 ; i < size ; ++i)
        {
            if (r[i] != x[i] + y[i] * a)
            {
                strcat(text, "ScaledSumf Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "ScaledSumf Test PASSED!\n");
        }
    }
#ifdef HONEI_NEON
    {
        jsize size = 200;
        float32_t r[size];
        float32_t x[size];
        float32_t y[size];
        float32_t a = 3.f;
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            r[i] = 4711;
            x[i] = 3.413 + i;
            y[i] = -56.7 - i;
        }
        scaled_sumf_NEON(r, x, y, a, size);
        for (i = 0 ; i < size ; ++i)
        {
            if (r[i] != x[i] + y[i] * a)
            {
                strcat(text, "ScaledSumf_NEON Test FAILED!\n");
                char bla[100];
                sprintf(bla, "Index %d : %f , %f \n", i, r[i], x[i] + y[i] * a);
                strcat(text, bla);
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "ScaledSumf_NEON Test PASSED!\n");
        }
    }
#endif
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
            if (r[i] != x[i] + y[i] * z[i])
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
    {
        jsize size = 25;
        jsize root = (jsize) sqrt(size);
        double r[size];
        double ref[size];
        double x[size];
        double ll[size];
        double ld[size];
        double lu[size];
        double dl[size];
        double dd[size];
        double du[size];
        double ul[size];
        double ud[size];
        double uu[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            r[i] = 4711;
            x[i] = i;
            ll[i] = i;
            ld[i] = i+2;
            lu[i] = i+4;
            dl[i] = i+6;
            dd[i] = i+8;
            du[i] = i+10;
            ul[i] = i+12;
            ud[i] = i+14;
            uu[i] = i+16;
        }

        ref[0] = 224;
        ref[1] = 305;
        ref[2] = 404;
        ref[3] = 515;
        ref[4] = 638;
        ref[5] = 782;
        ref[6] = 948;
        ref[7] = 1137;
        ref[8] = 1344;
        ref[9] = 1569;
        ref[10] = 1812;
        ref[11] = 2073;
        ref[12] = 2352;
        ref[13] = 2649;
        ref[14] = 2964;
        ref[15] = 3297;
        ref[16] = 3648;
        ref[17] = 4017;
        ref[18] = 4404;
        ref[19] = 3934;
        ref[20] = 3446;
        ref[21] = 2939;
        ref[22] = 3212;
        ref[23] = 3497;
        ref[24] = 2944;

        struct BMQ1 bmq1;
        bmq1.size = size;
        bmq1.root = root;
        bmq1.ll = ll;
        bmq1.ld = ld;
        bmq1.lu = lu;
        bmq1.dl = dl;
        bmq1.dd = dd;
        bmq1.du = du;
        bmq1.ul = ul;
        bmq1.ud = ud;
        bmq1.uu = uu;

        product(r, bmq1, x);
        for (i = 0 ; i < size ; ++i)
        {
            if (r[i] != ref[i])
            {
                strcat(text, "Q1 BMDV Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "Q1 BMDV Test PASSED!\n");
        }
    }
    {
        jsize size = 25;
        jsize root = (jsize) sqrt(size);
        double r[size];
        double b[size];
        double P[size];
        double x[size];
        double jac[size];
        double ll[size];
        double ld[size];
        double lu[size];
        double dl[size];
        double dd[size];
        double du[size];
        double ul[size];
        double ud[size];
        double uu[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            b[i] = i;
            x[i] = 0;
            ll[i] = 0.1;
            ld[i] = 0.2;
            lu[i] = 0.3;
            dl[i] = 0.4;
            dd[i] = 1.01;
            du[i] = 0.4;
            ul[i] = 0.3;
            ud[i] = 0.2;
            uu[i] = 0.1;
            jac[i] = 1. / dd[i];
        }


        struct BMQ1 bmq1;
        bmq1.size = size;
        bmq1.root = root;
        bmq1.ll = ll;
        bmq1.ld = ld;
        bmq1.lu = lu;
        bmq1.dl = dl;
        bmq1.dd = dd;
        bmq1.du = du;
        bmq1.ul = ul;
        bmq1.ud = ud;
        bmq1.uu = uu;

        defect(r, b, bmq1, x);
        double initial_defect = norm_l2_true(r, size);
        jsize used_iters = cg_jac(bmq1, jac, b, x, 1000, 1e-8);
        defect(r, b, bmq1, x);
        double final_defect = norm_l2_true(r, size);

        strcat(text, "CG JAC Test:\n");
        char snumber[20];
        sprintf(snumber, "%e", initial_defect);
        strcat(text, "Initial defect: ");
        strcat(text, snumber);
        strcat(text, "\n");
        sprintf(snumber, "%e", final_defect);
        strcat(text, "Final defect: ");
        strcat(text, snumber);
        strcat(text, "\n");
        sprintf(snumber, "%d", used_iters);
        strcat(text, "Used iters: ");
        strcat(text, snumber);
        strcat(text, "\n");
        for (i = 0 ; i < size ; ++i)
        {
            if (final_defect > initial_defect || used_iters != 25)
            {
                strcat(text, "CG JAC Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "CG JAC Test PASSED!\n");
        }
    }
    {
        jsize size = 25;
        jsize root = (jsize) sqrt(size);
        double r[size];
        double b[size];
        double P[size];
        double x[size];
        double jac[size];
        double ll[size];
        double ld[size];
        double lu[size];
        double dl[size];
        double dd[size];
        double du[size];
        double ul[size];
        double ud[size];
        double uu[size];
        jsize i;
        for (i = 0 ; i < size ; ++i)
        {
            b[i] = i;
            x[i] = 0;
            ll[i] = 0.1;
            ld[i] = 0.2;
            lu[i] = 0.3;
            dl[i] = 0.4;
            dd[i] = 1.01;
            du[i] = 0.4;
            ul[i] = 0.3;
            ud[i] = 0.2;
            uu[i] = 0.1;
            jac[i] = 1. / dd[i];
        }


        struct BMQ1 bmq1;
        bmq1.size = size;
        bmq1.root = root;
        bmq1.ll = ll;
        bmq1.ld = ld;
        bmq1.lu = lu;
        bmq1.dl = dl;
        bmq1.dd = dd;
        bmq1.du = du;
        bmq1.ul = ul;
        bmq1.ud = ud;
        bmq1.uu = uu;

        defect(r, b, bmq1, x);
        double initial_defect = norm_l2_false(r, size);
        jsize used_iters = bicgstab_jac(bmq1, jac, b, x, 1000, 1e-8);
        defect(r, b, bmq1, x);
        double final_defect = norm_l2_false(r, size);

        strcat(text, "BiCGStab JAC Test:\n");
        char snumber[20];
        sprintf(snumber, "%e", initial_defect);
        strcat(text, "Initial defect: ");
        strcat(text, snumber);
        strcat(text, "\n");
        sprintf(snumber, "%e", final_defect);
        strcat(text, "Final defect: ");
        strcat(text, snumber);
        strcat(text, "\n");
        sprintf(snumber, "%d", used_iters);
        strcat(text, "Used iters: ");
        strcat(text, snumber);
        strcat(text, "\n");
        for (i = 0 ; i < size ; ++i)
        {
            if (final_defect > initial_defect || used_iters != 10)
            {
                strcat(text, "BiCGStab JAC Test FAILED!\n");
                ++failed;
                break;
            }
            if (i == size - 1)
                strcat(text, "BiCGStab JAC Test PASSED!\n");
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
