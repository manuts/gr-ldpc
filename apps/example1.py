#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Example1
# Author: Manu T S
# Generated: Wed Sep 25 11:14:24 2013
##################################################

from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import ldpc
import wx

class example1(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Example1")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.sigma = sigma = 0.3
        self.samp_rate = samp_rate = 32000
        self.max_iterations = max_iterations = 50
        self.alist_file = alist_file = "/home/manu/repos/ldpc/gr-ldpc/python/alist-files"

        ##################################################
        # Blocks
        ##################################################
        self.ldpc_ldpc_hier_encoder_bf_1 = ldpc.ldpc_hier_encoder_bf(alist_file)
        self.ldpc_ldpc_hier_decoder_fb_0 = ldpc.ldpc_hier_decoder_fb(alist_file, sigma, max_iterations)
        self.digital_chunks_to_symbols_xx_0 = digital.chunks_to_symbols_bf(([1.0, -1.0]), 2)
        self.blocks_unpacked_to_packed_xx_0 = blocks.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
        self.blocks_packed_to_unpacked_xx_0 = blocks.packed_to_unpacked_bb(1, gr.GR_MSB_FIRST)
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, "/home/manu/Downloads/in.flac", False)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, "/home/manu/Downloads/out")
        self.blocks_file_sink_0.set_unbuffered(False)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_file_source_0, 0), (self.blocks_packed_to_unpacked_xx_0, 0))
        self.connect((self.ldpc_ldpc_hier_decoder_fb_0, 0), (self.blocks_unpacked_to_packed_xx_0, 0))
        self.connect((self.blocks_unpacked_to_packed_xx_0, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.ldpc_ldpc_hier_decoder_fb_0, 0))
        self.connect((self.blocks_packed_to_unpacked_xx_0, 0), (self.ldpc_ldpc_hier_encoder_bf_1, 0))
        self.connect((self.ldpc_ldpc_hier_encoder_bf_1, 0), (self.digital_chunks_to_symbols_xx_0, 0))


# QT sink close method reimplementation

    def get_sigma(self):
        return self.sigma

    def set_sigma(self, sigma):
        self.sigma = sigma

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_max_iterations(self):
        return self.max_iterations

    def set_max_iterations(self, max_iterations):
        self.max_iterations = max_iterations

    def get_alist_file(self):
        return self.alist_file

    def set_alist_file(self, alist_file):
        self.alist_file = alist_file

if __name__ == '__main__':
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = example1()
    tb.Start(True)
    tb.Wait()

