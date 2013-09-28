#!/usr/bin/env python
# 
# Copyright 2013 IIT Bombay.
# Author: Manu T S
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

import math
import sys

class GF:

    def __init__(self, prime, poly):
        self.prime = prime
        self.mod_poly = poly
        self.dimension = len(self.mod_poly) - 1
        self.q = int(math.pow(self.prime, self.dimension))
        self.exp_2_pol = []
        self.pol_2_exp = [0]*self.q
        self.pol_2_exp[0] = -1*sys.maxint
        self.zero_exp = -1*sys.maxint
        for i in range(1, self.q):
            pol = [0]*i
            pol.pop()
            pol.append(1)
            poly = self.divide_poly(pol)
            ind = 0
            for j in range(len(poly)):
                ind += poly[j]*(self.prime**j)
            self.pol_2_exp[ind] = i - 1
            self.exp_2_pol.append(poly)

    def divide_poly(self, poly):
        if len(poly) >= len(self.mod_poly):
            mul_index = len(poly) - len(self.mod_poly)
            prod = []
            for i in range(mul_index):
                prod.append(0)
            for i in range(mul_index, len(self.mod_poly) + mul_index):
                prod.append(
                (self.mod_poly[i - mul_index]*poly[-1]) % self.prime)
            bal = self.sub_poly(poly, prod)
            return self.divide_poly(bal) 
        else:
            return poly

    def mul_exp(self, exp1, exp2):
        if exp1 == self.zero_exp:
            return exp2
        elif exp2 == self.zero_exp:
            return exp1
        else:
            return ((exp1 + exp2) % (self.q - 1))

    def pol_2_indx(self, poly):
        ind = 0
        for i in range(len(poly)):
            ind += poly[i]*(self.prime**i)
        return ind

    def mul_poly(self, poly1, poly2):
        ind1 = self.pol_2_indx(poly1)
        ind2 = self.pol_2_indx(poly2)
        exp1 = self.pol_2_exp[ind1]
        exp2 = self.pol_2_exp[ind2]
        return self.exp_2_pol[self.mul_exp(exp1, exp2)]

    def div_poly(self, poly1, poly2):
        ind0 = 0
        for i in range(len(poly1)):
            ind0 += poly1[i]*(self.prime**i)
        ind1 = 0
        for i in range(len(poly2)):
            ind1 += poly2[i]*(self.prime**i)
        return self.exp_2_pol[self.div_exp(ind0, ind1)]

    def div_exp(self, exp1, exp2):
        inv_exp2 = m_inv_exp(self, exp2)
        return self.mul_exp(exp1, inv_exp2)

    def m_inv_exp(self, exp):
        return (self.q - 1) - (exp % self.q - 1)

    def add_exp(self, exp1, exp2):
        if exp1 == -1*sys.maxint:
            pol1 = []
        else:
            pol1 = self.exp_2_pol[exp1]
        if exp2 == -1*sys.maxint:
            pol2 = []
        else:
            pol2 = self.exp_2_pol[exp2]
        _sum = self.add_poly(pol1, pol2)
        ind = self.pol_2_indx(_sum)
        return self.pol_2_exp[ind]

    def sub_poly(self, poly1, poly2):
        inv_poly2 = self.a_inv_poly(poly2)
        return self.add_poly(poly1, inv_poly2)

    def add_poly(self, poly1, poly2):
        if len(poly1) >= len(poly2):
            _sum = []
            for i in range(len(poly2)):
                _sum.append((poly1[i] + poly2[i]) % self.prime)
            for i in range(len(poly2), len(poly1)):
                _sum.append(poly1[i])
            if len(_sum) == 0:
                return _sum
            while(_sum[-1] == 0):
                _sum.pop()
                if len(_sum) == 0:
                    break
            return _sum
        else:
            return self.add_poly(poly2, poly1)

    def a_inv_poly(self, poly):
        inv = []
        for i in range(len(poly)):
            inv.append((self.prime - poly[i]) % self.prime)
        return inv

    def a_inv_exp(self, exp):
        poly = self.exp_2_pol[exp]
        inv = self.a_inv_poly(poly)
        ind = self.pol_2_indx(inv)
        return self.pol_2_exp[ind]

    def rs_gen_poly(self, rho):
        gen_poly = [self.a_inv_exp(1), 0]
        comp = 1
        while comp < rho - 2:
            gen_poly = self.rs_gen_add_degree(gen_poly)
            comp += 1
        return gen_poly

    def rs_gen_add_degree(self, pol):
        new_degree = len(pol)
        new_gen = []
        g_0 = self.mul_exp(self.a_inv_exp(new_degree), pol[0])
        new_gen.append(g_0)
        new_comp = self.a_inv_exp(new_degree)
        for i in range(1, new_degree):
            _prdct = self.mul_exp(pol[i], new_comp)
            _sum = self.add_exp(_prdct, pol[i-1])
            new_gen.append(_sum)
        new_gen.append(0)
        return new_gen
