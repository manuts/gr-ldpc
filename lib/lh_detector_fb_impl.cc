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
#include "lh_detector_fb_impl.h"

namespace gr {
  namespace ldpc {

    lh_detector_fb::sptr
    lh_detector_fb::make()
    {
      return gnuradio::get_initial_sptr
        (new lh_detector_fb_impl());
    }

    /*
     * The private constructor
     */
    lh_detector_fb_impl::lh_detector_fb_impl()
      : gr::sync_block("lh_detector_fb",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {}

    /*
     * Our virtual destructor.
     */
    lh_detector_fb_impl::~lh_detector_fb_impl()
    {
    }

    int
    lh_detector_fb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        char *out = (char *) output_items[0];

        // Do <+signal processing+>
        for (int i = 0; i < noutput_items; i++) {
            if (in[i] < 0.0) {
                out[i] = char(1);
            }
            else {
                out[i] = char(0);
            }
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace ldpc */
} /* namespace gr */

