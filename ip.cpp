/* Copyright 2020 walt@danielwalt.io
 * Author: Daniel Walt
 * NYU Email: dw2789@nyu.edu
 */
#include "ip.h"

address_t::address_t(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    address = (a << 24U) | (b << 16U) | (c << 8U) | d;
}

address_t::address_t(const_ref_t rhs) {
    address = rhs.address;
}

address_t::address_t(r_value rhs) noexcept {
    address = rhs.address;
}

address_t::ref_t address_t::operator=(const_ref_t rhs) {
    address = rhs.address;
    return *this;
}

address_t::ref_t address_t::operator=(const u32& rhs) {
    address = rhs;
    return *this;
}

address_t::ref_t address_t::operator=(r_value rhs) noexcept{
    address = rhs.address;
    return *this;
}


std::string address_t::dot() const {
    std::stringstream ss;
    ss << ((address & 0xFF000000U) >> 24U) << ".";
    ss << ((address & 0x00FF0000U) >> 16U) << ".";
    ss << ((address & 0x0000FF00U) >> 8U) << ".";
    ss <<  (address & 0x000000FFU);
    return ss.str();
}

char address_t::inet_class() const {
    std::string bts = bits().substr(0, 5);
    if (bts[0] == '0') {
        return 'A';
    } else if (bts[1] == '0') {
        return 'B';
    } else if (bts[2] == '0') {
        return 'C';
    } else if (bts[3] == '0') {
        return 'D';
    } else if (bts[4] == '0') {
        return 'E';
    }
    return 'U';
}

IP::IP(int a, int b, int c, int d) {
    host = address_t(a, b, c, d);
    switch (host.inet_class()) {
        case 'A':
            mask = 0xFF000000U;
            break;
        case 'B':
            mask = 0xFFFF0000U;
            break;
        case 'C':
            mask = 0xFFFFFF00U;
            break;
        default:
            mask = 0xFFFFFFF0U;
            break;
    }
    _calc_range();
}

IP::IP(int a, int b, int c, int d, int m) {
    host = address_t(a, b, c, d);
    wildcard = address_t(std::pow(2, 32-m)-1);
    mask = ~wildcard;
    _calc_range();

};

void IP::_calc_range() {
    if (wildcard.address == 0) {
        wildcard = ~mask;
    }
    network = mask & host;
    broadcast = network | wildcard;
    first_host = network + 1;
    last_host = broadcast - 1;
    n_hosts = last_host - first_host + 1;
}
