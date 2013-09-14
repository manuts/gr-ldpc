/* -*- c++ -*- */

#define LDPC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ldpc_swig_doc.i"

%{
#include "ldpc/copy_bb.h"
%}


%include "ldpc/copy_bb.h"
GR_SWIG_BLOCK_MAGIC2(ldpc, copy_bb);
