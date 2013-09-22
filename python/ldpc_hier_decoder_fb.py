#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2013 IIT Bombay.
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

from gnuradio import gr, blocks
import ldpc

class ldpc_hier_decoder_fb(gr.hier_block2):
    """
    docstring for block ldpc_hier_decoder_fb
    """
    def __init__(self, alist_file, sigma, max_iterations):
        gr.hier_block2.__init__(self,
            "ldpc_hier_decoder_fb",
            gr.io_signature(1, 1, gr.sizeof_float),  # Input signature
            gr.io_signature(1, 1, gr.sizeof_char)) # Output signature

            # Define blocks and connect them
        decoder = ldpc.ldpc_decoder_fb(alist_file,
                sigma, max_iterations)
        K = decoder.get_K()
        N = decoder.get_N()
        str2Nvec = blocks.stream_to_vector(4, N)
        Kvec2str = blocks.vector_to_stream(1, K)

        self.connect(self, str2Nvec, decoder, Kvec2str, self)
