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

import numpy
import sys

"""
Generation of LDPC matrices based on Reed-Solomon codes [1]
"""

def swap_columns(i, j, M):
    n = M.shape[1]
    I = numpy.zeros(shape=(n, n))
    for k in range(n):
        I[k, k] = 1
    I[i, i] = 0
    I[j, j] = 0
    I[i, j] = 1
    I[j, i] = 1
    return M*I

def swap_index(i, j, index):
    temp = index[0, i]
    index[0, i] = index[0, j]
    index[0, j] = temp
    return index
def add_rows(i, j, M):
    n = M.shape[0]
    I = numpy.zeros(shape=(n, n))
    for k in range(n):
        I[k, k] = 1
    I[j, i] = 1
    return I*M

def regular_check(H, rho, gamma):
    right_regular = True
    left_regular = True
    for i in range(H.shape[0]):
        weight = 0
        for j in range(H.shape[1]):
            weight += H[i, j]
        if weight != rho:
            right_regular = False
    for j in range(H.shape[1]):
        weight = 0
        for i in range(H.shape[0]):
            weight += H[i, j]
        if weight != gamma:
            left_regular = False
    return left_regular, right_regular

def generate_H(rho, gamma, gf):
    q = gf.q
    gen = gf.rs_gen_poly(rho)
    coset_base = []
    exp_matrix = numpy.zeros((gamma*q, rho), dtype = int)
    for i in range(gamma):
        multiplier = i 
        curnt_word = []
        curnt_word.append(gen[0])
        for j in range(1, len(gen)):
            _prdct = gf.mul_exp(gen[j], multiplier)
            _sum = gf.add_exp(_prdct, gen[j - 1])
            curnt_word.append(_sum)
        curnt_word.append(0)
        coset_base.append(curnt_word)
    subspace_base = coset_base[0]
    for i in range(gamma):
        row = i*q
        for j in range(rho):
            exp_matrix[row, j] = coset_base[i][j]
        for k in range(1, q):
            for j in range(rho):
                _prdct = gf.mul_exp(k, subspace_base[j])
                _sum = gf.add_exp(_prdct, coset_base[i][j])
                exp_matrix[row + k, j] = _sum

    H = numpy.zeros((gamma*q, q*rho), dtype = int)
    for row in range(gamma*q):
        for col in range(rho):
            if (exp_matrix[row, col] == -1*sys.maxint):
                H[row, col*q] = 1
            else:
                exp = exp_matrix[row, col]
                H[row, col*q + exp + 1] = 1
    return H

def convert_binary(H):
    n = H.shape[1]
    m = H.shape[0]
    for i in range(m):
        for j in range(n):
            H[i, j] = H[i, j]%2
    return H

def triangulate_H(H):       # TODO There are errors in this routine
    n = H.shape[1]
    m = H.shape[0]
    index = numpy.zeros(shape=(1, n))
    for i in range(n):
        index[0, i] = i
    for i in range(m):
        j = i
        while j < n:
            if H[i, j] == 1:
                print "swapping column ",
                print i, j
                H = swap_columns(i, j, H)
                index = swap_index(i, j, index)
                print H
                print index
                break
            j += 1
        for k in range(i+1, m):
            if H[k, i] == 1:
                print "adding ",
                print i, k
                H = add_rows(i, k, H)
                print H
        H = convert_binary(H)
        print H
    return index, H

"""
References

"A Class of Low-Density Parity-Check Codes Constructed Based on
Reed-Solomon Codes With Two Information Symbols",
Ivana Djurdjevic, Jun Xu, Khaled Abdel-Ghaffer and Shu Lin
IEEE Communications Letters, July 2000.
"""
