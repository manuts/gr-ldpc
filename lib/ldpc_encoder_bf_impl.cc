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
#include "ldpc_encoder_bf_impl.h"

namespace gr {
  namespace ldpc {

    ldpc_encoder_bf::sptr
    ldpc_encoder_bf::make(const char * alist_file)
    {
      return gnuradio::get_initial_sptr
        (new ldpc_encoder_bf_impl(alist_file));
    }

    /*
     * The private constructor
     */
    ldpc_encoder_bf_impl::ldpc_encoder_bf_impl(const char * alist_file)
      : gr::sync_block("ldpc_encoder_bb",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
        d_list.read(alist_file);
        d_code.set_alist(d_list);
        K = d_code.dimension();
        N = d_code.get_N();
        set_input_signature(gr::io_signature::make(1, 1, sizeof(char) * K));
        set_output_signature(gr::io_signature::make(1, 1, sizeof(float) * N));
    }

    /*
     * Our virtual destructor.
     */
    ldpc_encoder_bf_impl::~ldpc_encoder_bf_impl()
    {
    }

    int
    ldpc_encoder_bf_impl::get_K() {
        return K;
    }

    int
    ldpc_encoder_bf_impl::get_N() {
        return N;
    }

    int
    ldpc_encoder_bf_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        float *out = (float *) output_items[0];

        // Do <+signal processing+>
        std::vector<char> data, code;
        data.resize(K);
        for (int j = 0; j < noutput_items; j++) {
            for ( int i = 0; i < K; i++ ) {
                data[i] = in[i + (j*K)];
            }
            code = d_code.encode(data);
            for ( int i = 0; i < N; i++ ) {
                if ( code[i] == char(0) ) {
                    out[i + (j*N)] = 1.0;
                }
                else {
                    out[i + (j*N)] = -1.0;
                }
            }
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace ldpc */
} /* namespace gr */

