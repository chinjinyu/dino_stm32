#pragma once

#include <stdint.h>

const uint8_t ascii_6x8[][6] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // SPACE
    {0x00, 0x00, 0x00, 0x4f, 0x00, 0x00}, // !
    {0x00, 0x00, 0x00, 0x07, 0x00, 0x07}, // "
    {0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14}, // #
    {0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12}, // $
    {0x00, 0x23, 0x13, 0x08, 0x62, 0x61}, // %
    {0x00, 0x36, 0x49, 0x55, 0x22, 0x50}, // &
    {0x00, 0x00, 0x00, 0x05, 0x03, 0x00}, // '
    {0x00, 0x00, 0x1c, 0x22, 0x41, 0x00}, // (
    {0x00, 0x00, 0x41, 0x22, 0x1c, 0x00}, // )
    {0x00, 0x14, 0x08, 0x3e, 0x08, 0x14}, // *
    {0x00, 0x08, 0x08, 0x3e, 0x08, 0x08}, // +
    {0x00, 0x00, 0x00, 0x28, 0x18, 0x00}, // ,
    {0x00, 0x08, 0x08, 0x08, 0x08, 0x08}, // -
    {0x00, 0x00, 0x00, 0x60, 0x60, 0x00}, // .
    {0x00, 0x20, 0x10, 0x08, 0x04, 0x02}, // /
    {0x00, 0x3e, 0x51, 0x49, 0x45, 0x3e}, // 0
    {0x00, 0x00, 0x42, 0x7f, 0x40, 0x40}, // 1
    {0x00, 0x62, 0x51, 0x51, 0x49, 0x46}, // 2
    {0x00, 0x21, 0x41, 0x45, 0x4b, 0x31}, // 3
    {0x00, 0x18, 0x14, 0x12, 0x7f, 0x10}, // 4
    {0x00, 0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x00, 0x3c, 0x4a, 0x49, 0x49, 0x30}, // 6
    {0x00, 0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x00, 0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x00, 0x06, 0x49, 0x49, 0x29, 0x1e}, // 9
    {0x00, 0x00, 0x36, 0x36, 0x00, 0x00}, // :
    {0x00, 0x00, 0x56, 0x36, 0x00, 0x00}, // ;
    {0x00, 0x08, 0x14, 0x22, 0x41, 0x00}, // <
    {0x00, 0x14, 0x14, 0x14, 0x14, 0x14}, // =
    {0x00, 0x00, 0x41, 0x22, 0x14, 0x08}, // >
    {0x00, 0x02, 0x01, 0x51, 0x09, 0x06}, // ?
    {0x00, 0x3e, 0x59, 0x55, 0x79, 0x3e}, // @
    {0x00, 0x7e, 0x11, 0x11, 0x11, 0x7e}, // A
    {0x00, 0x7f, 0x49, 0x49, 0x49, 0x36}, // B
    {0x00, 0x3e, 0x41, 0x41, 0x41, 0x22}, // C
    {0x00, 0x7f, 0x41, 0x41, 0x22, 0x1c}, // D
    {0x00, 0x7f, 0x49, 0x49, 0x49, 0x49}, // E
    {0x00, 0x7f, 0x09, 0x09, 0x09, 0x01}, // F
    {0x00, 0x3e, 0x41, 0x49, 0x49, 0x7a}, // G
    {0x00, 0x7f, 0x08, 0x08, 0x08, 0x7f}, // H
    {0x00, 0x41, 0x7f, 0x41, 0x00, 0x00}, // I
    {0x00, 0x20, 0x40, 0x41, 0x3f, 0x01}, // J
    {0x00, 0x7f, 0x08, 0x14, 0x22, 0x41}, // K
    {0x00, 0x7f, 0x40, 0x40, 0x40, 0x40}, // L
    {0x00, 0x7f, 0x02, 0x0c, 0x02, 0x7f}, // M
    {0x00, 0x7f, 0x04, 0x08, 0x10, 0x7f}, // N
    {0x00, 0x3e, 0x41, 0x41, 0x41, 0x3e}, // O
    {0x00, 0x7f, 0x09, 0x09, 0x09, 0x06}, // P
    {0x00, 0x3e, 0x41, 0x41, 0x41, 0x3e}, // Q
    {0x00, 0x7f, 0x09, 0x19, 0x29, 0x46}, // R
    {0x00, 0x46, 0x49, 0x49, 0x49, 0x31}, // S
    {0x00, 0x01, 0x01, 0x7f, 0x01, 0x01}, // T
    {0x00, 0x3f, 0x40, 0x40, 0x40, 0x3f}, // U
    {0x00, 0x1f, 0x20, 0x40, 0x20, 0x1f}, // V
    {0x00, 0x3f, 0x40, 0x38, 0x40, 0x3f}, // W
    {0x00, 0x63, 0x14, 0x08, 0x14, 0x63}, // X
    {0x00, 0x07, 0x08, 0x70, 0x08, 0x07}, // Y
    {0x00, 0x61, 0x51, 0x49, 0x45, 0x43}, // Z
    {0x00, 0x00, 0x7f, 0x41, 0x41, 0x00}, // [
    {0x00, 0x01, 0x02, 0x08, 0x10, 0x20}, // "\"
    {0x00, 0x00, 0x41, 0x41, 0x7f, 0x00}, // ]
    {0x00, 0x04, 0x02, 0x01, 0x02, 0x04}, // ^
    {0x00, 0x40, 0x40, 0x40, 0x40, 0x40}, // _
    {0x00, 0x00, 0x01, 0x02, 0x04, 0x00}, // `
    {0x00, 0x20, 0x54, 0x54, 0x54, 0x7c}, // a
    {0x00, 0x7f, 0x48, 0x44, 0x44, 0x38}, // b
    {0x00, 0x38, 0x44, 0x44, 0x44, 0x20}, // c
    {0x00, 0x38, 0x44, 0x44, 0x48, 0x7f}, // d
    {0x00, 0x38, 0x54, 0x54, 0x54, 0x18}, // e
    {0x00, 0x08, 0x7e, 0x09, 0x01, 0x02}, // f
    {0x00, 0x0c, 0x52, 0x52, 0x52, 0x3e}, // g
    {0x00, 0x7f, 0x08, 0x04, 0x04, 0x78}, // h
    {0x00, 0x00, 0x44, 0x7d, 0x40, 0x00}, // i
    {0x00, 0x40, 0x40, 0x44, 0x3d, 0x00}, // j
    {0x00, 0x7f, 0x10, 0x28, 0x44, 0x00}, // k
    {0x00, 0x00, 0x41, 0x7e, 0x40, 0x00}, // l
    {0x00, 0x7c, 0x04, 0x18, 0x04, 0x78}, // m
    {0x00, 0x7c, 0x08, 0x04, 0x04, 0x78}, // n
    {0x00, 0x38, 0x44, 0x44, 0x44, 0x38}, // o
    {0x00, 0x7c, 0x14, 0x14, 0x14, 0x08}, // p
    {0x00, 0x08, 0x14, 0x14, 0x14, 0x7c}, // q
    {0x00, 0x7c, 0x08, 0x04, 0x04, 0x08}, // r
    {0x00, 0x48, 0x54, 0x54, 0x54, 0x20}, // s
    {0x00, 0x04, 0x3f, 0x44, 0x44, 0x24}, // t
    {0x00, 0x3c, 0x40, 0x40, 0x20, 0x7e}, // u
    {0x00, 0x1d, 0x20, 0x40, 0x20, 0x1c}, // v
    {0x00, 0x3c, 0x40, 0x30, 0x40, 0x3c}, // w
    {0x00, 0x44, 0x28, 0x10, 0x28, 0x44}, // x
    {0x00, 0x06, 0x48, 0x48, 0x48, 0x3e}, // y
    {0x00, 0x44, 0x64, 0x54, 0x4c, 0x44}, // z
    {0x00, 0x00, 0x08, 0x36, 0x41, 0x00}, // {
    {0x00, 0x00, 0x00, 0x7F, 0x00, 0x00}, // |
    {0x00, 0x00, 0x41, 0x36, 0x08, 0x00}, // }
    {0x00, 0x08, 0x04, 0x04, 0x08, 0x04}, // ~
};
