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

#ifndef INCLUDED_LSA_INTERFERENCE_CANCELLATION_CORE_CC_IMPL_H
#define INCLUDED_LSA_INTERFERENCE_CANCELLATION_CORE_CC_IMPL_H

#include <lsa/interference_cancellation_core_cc.h>
#include <list>

namespace gr {
  namespace lsa {

    // helper class to record tags
    class tagObject
    {
      public:
       friend class interference_cancellation_core_cc_impl;
       friend std::ostream & operator<<( std::ostream& out,const tagObject& obj)
       {
         out << "index:"<<obj.d_idx<<" ,msg:"<<obj.d_msg<<std::endl;
         return out;
       }
       tagObject(){d_idx = 0;d_msg = pmt::PMT_NIL;}
       tagObject(const tagObject& obj){d_msg = obj.d_msg;d_idx = obj.d_idx;}
       tagObject(int idx, pmt::pmt_t msg){d_msg = msg;d_idx = idx;}
       ~tagObject(){}
       bool operator >(const tagObject& o1)const {return d_idx>o1.d_idx;}
       bool operator <(const tagObject& o1)const {return d_idx<o1.d_idx;}
       bool operator <=(const tagObject& o1)const {return d_idx<=o1.d_idx;}
       bool operator >=(const tagObject& o1)const {return d_idx>=o1.d_idx;}
       const tagObject& operator* (){return *this;}
       const tagObject& operator -=(int sub){d_idx-=sub; return *this;}
       const tagObject& operator =(const tagObject& obj){
         d_msg = obj.d_msg;
         d_idx = obj.d_idx;
       }
       bool empty()const{return pmt::is_null(d_msg);}
       void reset(){d_idx = 0;d_msg=pmt::PMT_NIL;}
       void set_msg(pmt::pmt_t msg){d_msg = msg;}
       void init_dict(){d_msg = pmt::make_dict();}
       void add_msg(pmt::pmt_t key,pmt::pmt_t value){d_msg = pmt::dict_add(d_msg,key,value);}
       pmt::pmt_t msg()const {return d_msg;}
       void set_idx(int idx){d_idx = idx;}
       int index()const {return d_idx;}
       bool subtract_idx(int sub){
         if(sub>d_idx){
           return false;
         }
         d_idx-=sub;
         return true;
       }
      private:
       int d_idx;
       pmt::pmt_t d_msg;
    };

    class interference_cancellation_core_cc_impl : public interference_cancellation_core_cc
    {
     private:
      gr_complex* d_in_mem;
      gr_complex* d_out_mem;
      int d_in_mem_idx;
      int d_in_mem_size;
      int d_out_mem_idx;
      int d_out_mem_size;
      float* d_phase_mem;
      //float* d_time_mem;
      int d_phase_idx;
      int d_phase_size;

      const int d_mem_cap;
      std::list<tagObject> d_in_tlist;
      std::list<tagObject> d_out_tlist;
      bool d_debug;

     public:
      interference_cancellation_core_cc_impl(bool debug);
      ~interference_cancellation_core_cc_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace lsa
} // namespace gr

#endif /* INCLUDED_LSA_INTERFERENCE_CANCELLATION_CORE_CC_IMPL_H */
