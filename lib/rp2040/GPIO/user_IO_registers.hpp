#pragma once

#include <bitfield.hpp>

union STATUS
{
    bitfield<26, 1> interrupt_to_processor;
    bitfield<24, 1> interrupt_from_pad;
    bitfield<19, 1> input_signal_to_peripheral;
    bitfield<17, 1> input_signal_from_pad;
    bitfield<13, 1> output_enable_to_pad;
    bitfield<12, 1> output_enable_from_peripheral;
    bitfield<9, 1> output_signal_to_pad;
    bitfield<8, 1> output_signal_from_peripheral;
};

union CTRL
{
    /* data */
};