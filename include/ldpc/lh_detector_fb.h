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


#ifndef INCLUDED_LDPC_LH_DETECTOR_FB_H
#define INCLUDED_LDPC_LH_DETECTOR_FB_H

#include <ldpc/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ldpc {

    /*!
     * \brief <+description of block+>
     * \ingroup ldpc
     *
     */
    class LDPC_API lh_detector_fb : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<lh_detector_fb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ldpc::lh_detector_fb.
       *
       * To avoid accidental use of raw pointers, ldpc::lh_detector_fb's
       * constructor is in a private implementation
       * class. ldpc::lh_detector_fb::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace ldpc
} // namespace gr

#endif /* INCLUDED_LDPC_LH_DETECTOR_FB_H */

