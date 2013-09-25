/* -*- c++ -*- */
/* 
 * Copyright 2013 IIT Bombay.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ldpc_decoder_fb_impl.h"

namespace gr {
  namespace ldpc {

    ldpc_decoder_fb::sptr
    ldpc_decoder_fb::make(const char * alist_file, float sigma, int max_iterations)
    {
      return gnuradio::get_initial_sptr
        (new ldpc_decoder_fb_impl(alist_file, sigma, max_iterations));
    }

    /*
     * The private constructor
     */
    ldpc_decoder_fb_impl::ldpc_decoder_fb_impl(const char * alist_file, float sigma, int max_iterations)
      : gr::sync_block("ldpc_decoder_fb",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
        d_list.read(alist_file);
        d_code.set_alist(d_list);
        d_spa.set_alist_sigma(d_list, sigma);
        K = d_code.dimension();
        N = d_code.get_N();
        d_spa.set_K(K);
        d_spa.set_max_iterations(max_iterations);
        set_input_signature(gr::io_signature::make(1, 1, sizeof(float) * N));
        set_output_signature(gr::io_signature::make(1, 1, sizeof(char) * K));
    }

    /*
     * Our virtual destructor.
     */
    ldpc_decoder_fb_impl::~ldpc_decoder_fb_impl()
    {
    }

    int
    ldpc_decoder_fb_impl::get_K() {
        return K;
    }
    
    int
    ldpc_decoder_fb_impl::get_N() {
        return N;
    }

    int
    ldpc_decoder_fb_impl::get_niterations () {
        return n_iterations;
    }

    int
    ldpc_decoder_fb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        char *out = (char *) output_items[0];

        // Do <+signal processing+>
        std::vector<float> rx;
        std::vector<char> estimate, data;
        rx.resize(N);
        for (int j = 0; j < noutput_items; j++) {
            for ( int i = 0; i < N; i++ ) {
                rx[i] = in[i + (j*N)];
            }
            estimate = d_spa.decode(rx, &n_iterations);
            data = d_code.get_systematic_bits(estimate);
            for ( int i = 0; i < K; i++ ) {
                out[i + (j*K)] = data[i];
            }
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace ldpc */
} /* namespace gr */

