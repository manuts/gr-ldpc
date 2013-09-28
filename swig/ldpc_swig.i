/* -*- c++ -*- */

#define LDPC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ldpc_swig_doc.i"

%{
#include "ldpc/copy_bb.h"
#include "ldpc/ldpc_encoder_bb.h"
#include "ldpc/ldpc_decoder_bb.h"
#include "ldpc/bsc_bb.h"
#include "ldpc/ldpc_encoder_bf.h"
#include "ldpc/ldpc_decoder_fb.h"
#include "ldpc/lh_detector_fb.h"
%}


%include "ldpc/copy_bb.h"
GR_SWIG_BLOCK_MAGIC2(ldpc, copy_bb);
%include "ldpc/ldpc_encoder_bb.h"
GR_SWIG_BLOCK_MAGIC2(ldpc, ldpc_encoder_bb);
%include "ldpc/ldpc_decoder_bb.h"
GR_SWIG_BLOCK_MAGIC2(ldpc, ldpc_decoder_bb);
%include "ldpc/bsc_bb.h"
GR_SWIG_BLOCK_MAGIC2(ldpc, bsc_bb);
%include "ldpc/ldpc_encoder_bf.h"
GR_SWIG_BLOCK_MAGIC2(ldpc, ldpc_encoder_bf);
%include "ldpc/ldpc_decoder_fb.h"
GR_SWIG_BLOCK_MAGIC2(ldpc, ldpc_decoder_fb);
%include "ldpc/lh_detector_fb.h"
GR_SWIG_BLOCK_MAGIC2(ldpc, lh_detector_fb);
