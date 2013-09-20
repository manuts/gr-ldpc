/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
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
#include "bsc_bb_impl.h"
#include <cstdlib>
#include <time.h>

namespace gr {
  namespace ldpc {

    bsc_bb::sptr
    bsc_bb::make(int vlen, float epsilon)
    {
      return gnuradio::get_initial_sptr
        (new bsc_bb_impl(vlen, epsilon));
    }

    /*
     * The private constructor
     */
    bsc_bb_impl::bsc_bb_impl(int vlen, float epsilon)
      : gr::sync_block("bsc_bb",
              gr::io_signature::make(1, 1, sizeof(char) * vlen),
              gr::io_signature::make(1, 1, sizeof(char) * vlen)), d_vlen(vlen)
    {
        limit = 100000*epsilon;
    }

    /*
     * Our virtual destructor.
     */
    bsc_bb_impl::~bsc_bb_impl()
    {
    }

    int
    bsc_bb_impl::get_nerr() {
        return nerr;
    }

    int
    bsc_bb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        char *out = (char *) output_items[0];

        // Do <+signal processing+>
        srand(time(NULL));
        nerr = 0;
        for ( int i = 0; i < d_vlen; i++ ) {
            X = rand()%100000;
            if ( X > limit ) {
                out[i] = in[i];
            }
            else {
                nerr++;
                if ( in[i] == char(0) ) {
                    out[i] = char(1);
                }
                else {
                    out[i] = char(0);
                }
            }
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace ldpc */
} /* namespace gr */

