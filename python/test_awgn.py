from gnuradio import gr, digital, blocks, analog
import ldpc
import numpy as np
import random, array, copy

class my_tb(gr.top_block):
    def __init__(self, fname, epsilon, max_iterations):
        gr.top_block.__init__(self)

        self.src = blocks.vector_source_b(())
#        self.encoder = ldpc.ldpc_encoder_bf(fname)
#        self.decoder = ldpc.ldpc_decoder_fb(fname, epsilon, max_iterations)
#        self.encoder = ldpc.ldpc_encoder_bb(fname)
#        self.decoder = ldpc.ldpc_decoder_bb(fname, epsilon, max_iterations)
#        self.K = self.encoder.get_K()
#        self.N = self.encoder.get_N()
        self.K = 100
        self.N = 100
        print self.K
        print self.N
        copy = ldpc.copy_bb(self.K)
        self.dst = blocks.vector_sink_b()
        fsink1 = blocks.file_sink(gr.sizeof_char*self.K, "in")
        fsink1.set_unbuffered(False)
        fsink2 = blocks.file_sink(gr.sizeof_char*self.K, "out")
        fsink2.set_unbuffered(False)
#        fsink3 = blocks.file_sink(gr.sizeof_float*1, "encout")
#        fsink3.set_unbuffered(False)
        fsink3 = blocks.file_sink(gr.sizeof_char*self.N, "encout")
        fsink3.set_unbuffered(False)

        inFile = "/home/manu/Downloads/in.flac"
        outFile = "/home/manu/out.flac"
        source = blocks.file_source(gr.sizeof_char*self.K, inFile, False)
        sink = blocks.file_sink(gr.sizeof_char*self.K, outFile)
        unpack2pack = blocks.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
        pack2unpack = blocks.packed_to_unpacked_bb(1, gr.GR_MSB_FIRST)
        rsource= blocks.vector_source_b(map(int, np.random.randint(0x00, 0x02, 1000)), True)


#        str2Kvec = blocks.stream_to_vector(1, self.K)
#        str2Nvec = blocks.stream_to_vector(4, self.N)
#        Kvec2str = blocks.vector_to_stream(1, self.K)
#        Nvec2str = blocks.vector_to_stream(4, self.N)
        str2Kvec = blocks.stream_to_vector(1, self.K)
        str2Nvec = blocks.stream_to_vector(1, self.N)
        Kvec2str = blocks.vector_to_stream(1, self.K)
        Nvec2str = blocks.vector_to_stream(1, self.N)

        self.noise = analog.noise_source_f(analog.GR_GAUSSIAN, epsilon, 0)
        self.adder = blocks.add_vff(1)

        self.connect(source, copy, sink)
#        self.connect(source, pack2unpack, str2Kvec, fsink1)
#        self.connect(str2Kvec, self.encoder, self.decoder, fsink2)
#        self.connect(self.encoder, fsink3)

#        self.connect(self.src, str2Kvec, self.encoder,
#                Nvec2str)
#        self.connect(Nvec2str, (self.adder, 0))
#        self.connect(self.noise, (self.adder, 1))
#        self.connect(self.adder, str2Nvec,
#                self.decoder, Kvec2str, self.dst)

def main():
    fname = "/home/manu/repos/ldpc/gr-ldpc/python/alist-files/96.3.963"
    epsilon = 0.6
    max_iterations = 100
    print "initializing top block"
    tb = my_tb(fname, epsilon, max_iterations)
    tb.start()
    tb.wait()
#    K = tb.K
#    N = tb.N
#    match = 0
#    mismatch = 0
#    datatpl = array.array('B')
#    for i in range(K):
#        datatpl.append(0)
#    f = open('output', 'w')
#    g = open('data', 'w')
#    for i in range(100):
#        txdata = ()
#        for i in range(K):
#            X = random.randint(0, 1)
#            if X == 1:
#                datatpl[i] = 1
#                txdata = txdata + (1, )
#            else:
#                datatpl[i] = 0
#                txdata = txdata + (0, )
#        g.write("tx data\n")
#        g.write(str(datatpl) + "\n")
#        tb.src.set_data(datatpl)
#        tb.run()
#        rx_tpl = tb.dst.data()
#        tb.dst.reset()
#        g.write("rx data\n")
#        g.write(str(rx_tpl) + "\n")
#        if np.array_equal(txdata, rx_tpl):
#            match += 1
#        else:
#            mismatch += 1
#        _str = str(np.array_equal(txdata, rx_tpl))
#        _str = _str + "\t" + str(tb.decoder.get_niterations()) + "\n"
#        f.write(_str)
#        print _str

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass
