#!/usr/bin/env python
# 
# Copyright 2013 <+YOU OR YOUR COMPANY+>.
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

from gnuradio import gr, gr_unittest, blocks, digital
import ldpc_swig as ldpc
import random, array, copy

class qa_copy_bb (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # set up fg
        blk_len = 100
        encoder = ldpc.copy_bb(blk_len)
        datatpl = array.array('B')
        txdata = ()
        for i in range(blk_len):
            X = random.randint(0, 1)
            if X == 1:
                datatpl.append(1)
                txdata = txdata + (1, )
            else:
                datatpl.append(0)
                txdata = txdata + (0, )
        src = blocks.vector_source_b(datatpl)
        str2vec = blocks.stream_to_vector(1, blk_len)
        vec2str = blocks.vector_to_stream(1, blk_len)
        dst = blocks.vector_sink_b()
        self.tb.connect(src, str2vec, encoder, vec2str, dst)
        self.tb.run ()
        rxtpl = dst.data()
        self.assertTupleEqual(txdata, rxtpl)
        # check data

    def test_002_t (self):
        # set up fg
        fname = "/home/manu/repos/ldpc/gr-ldpc/python/alist-files/96.3.963"
        epsilon = 0.5
        max_iterations = 100
        encoder = ldpc.ldpc_encoder_bf(fname)
        decoder = ldpc.ldpc_decoder_fb(fname, epsilon, max_iterations)
        blk_len = encoder.get_K()
        datatpl = array.array('B')
        txdata = ()
        for i in range(blk_len):
            X = random.randint(0, 1)
            if X == 1:
                datatpl.append(1)
                txdata = txdata + (1, )
            else:
                datatpl.append(0)
                txdata = txdata + (0, )
        src = blocks.vector_source_b(datatpl)
        str2vec = blocks.stream_to_vector(1, blk_len)
        vec2str = blocks.vector_to_stream(1, blk_len)
        dst = blocks.vector_sink_b()
        self.tb.connect(src, str2vec, encoder, decoder, vec2str, dst)
        self.tb.run ()
        rxtpl = dst.data()
        self.assertTupleEqual(txdata, rxtpl)
        # check data

if __name__ == '__main__':
    gr_unittest.run(qa_copy_bb, "qa_copy_bb.xml")
