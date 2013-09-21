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


#ifndef INCLUDED_LDPC_LDPC_ENCODER_BF_H
#define INCLUDED_LDPC_LDPC_ENCODER_BF_H

#include <ldpc/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ldpc {

    /*!
     * \brief <+description of block+>
     * \ingroup ldpc
     *
     */
    class LDPC_API ldpc_encoder_bf : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<ldpc_encoder_bf> sptr;
      virtual int get_K() = 0;
      virtual int get_N() = 0;

      /*!
       * \brief Return a shared_ptr to a new instance of ldpc::ldpc_encoder_bf.
       *
       * To avoid accidental use of raw pointers, ldpc::ldpc_encoder_bf's
       * constructor is in a private implementation
       * class. ldpc::ldpc_encoder_bf::make is the public interface for
       * creating new instances.
       */
      static sptr make(const char * alist_file);
    };

  } // namespace ldpc
} // namespace gr

#endif /* INCLUDED_LDPC_LDPC_ENCODER_BF_H */

