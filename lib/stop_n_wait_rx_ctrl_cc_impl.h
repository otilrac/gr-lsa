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

#ifndef INCLUDED_LSA_STOP_N_WAIT_RX_CTRL_CC_IMPL_H
#define INCLUDED_LSA_STOP_N_WAIT_RX_CTRL_CC_IMPL_H

#include <lsa/stop_n_wait_rx_ctrl_cc.h>
#include <ctime>

namespace gr {
  namespace lsa {

    #define d_debug false
    #define DEBUG d_debug && std::cout
    
    static int d_valid = 64;
    static unsigned char d_sns_clear[] = {0x00,0xff,0x0f};
    static const pmt::pmt_t d_voe_tag = pmt::intern("voe_tag");

    enum SNSRXSTATE{
      ED_LISTEN,
      ED_SFD,
      ED_DETECT_PU,
      ED_DETECT_SNS,
      ED_SILENT
    };

    class stop_n_wait_rx_ctrl_cc_impl : public stop_n_wait_rx_ctrl_cc
    {
     private:
      const pmt::pmt_t d_out_port;
      const pmt::pmt_t d_src_id;
      gr_complex* d_buf;
      int d_state;
      float d_ed_thres;
      int d_ed_cnt;
      std::vector<gr_complex> d_samples;
      gr_complex d_sample_eng;
      gr::thread::mutex d_mutex;
      bool d_silent_trig;
      std::vector<tag_t> d_tags;
      int d_voe_cnt;
      void tags_handler(int count);
      void enter_listen();
      void enter_silent();
      void enter_sfd();
      void enter_ed_pu();
      void enter_ed_sns();
      void notify_clear();
      void pub_clear();
     public:
      stop_n_wait_rx_ctrl_cc_impl(float ed_thres,const std::vector<gr_complex>& samples);
      ~stop_n_wait_rx_ctrl_cc_impl();
      void set_ed_threshold(float thres);
      float ed_threshold() const;
      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace lsa
} // namespace gr

#endif /* INCLUDED_LSA_STOP_N_WAIT_RX_CTRL_CC_IMPL_H */

