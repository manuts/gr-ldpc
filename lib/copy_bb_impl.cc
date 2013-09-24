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
#include "copy_bb_impl.h"
#include <iostream>

namespace gr {
  namespace ldpc {

    copy_bb::sptr
    copy_bb::make(size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new copy_bb_impl(vlen));
    }

    /*
     * The private constructor
     */
    copy_bb_impl::copy_bb_impl(size_t vlen)
      : gr::sync_block("copy_bb",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)), d_vlen(vlen)
    {
        set_input_signature(gr::io_signature::make(1, 1, sizeof(char) * d_vlen));
        set_output_signature(gr::io_signature::make(1, 1, sizeof(char) * d_vlen));
    }

    /*
     * Our virtual destructor.
     */
    copy_bb_impl::~copy_bb_impl()
    {
    }

    size_t
    copy_bb_impl::get_vlen() {
        return d_vlen;
    }

    int
    copy_bb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        char *out = (char *) output_items[0];

        memcpy(out, in, noutput_items * d_vlen);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace ldpc */
} /* namespace gr */

