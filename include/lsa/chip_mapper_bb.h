/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_LSA_CHIP_MAPPER_BB_H
#define INCLUDED_LSA_CHIP_MAPPER_BB_H

#include <lsa/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace lsa {

    /*!
     * \brief <+description of block+>
     * \ingroup lsa
     *
     */
    class LSA_API chip_mapper_bb : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<chip_mapper_bb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of lsa::chip_mapper_bb.
       *
       * To avoid accidental use of raw pointers, lsa::chip_mapper_bb's
       * constructor is in a private implementation
       * class. lsa::chip_mapper_bb::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace lsa
} // namespace gr

#endif /* INCLUDED_LSA_CHIP_MAPPER_BB_H */

