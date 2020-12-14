/* Copyright 2020 walt@danielwalt.io
 * Author: Daniel Walt
 * NYU Email: dw2789@nyu.edu
 *
 */
#ifndef INCLUDE_IP_H_
#define INCLUDE_IP_H_

#include <cstdint>
#include <cmath>
#include <bitset>
#include <string>
#include <sstream>


class address_t {
    typedef address_t val_t;
    typedef address_t& ref_t;
    typedef const address_t& const_ref_t;
    typedef address_t* ptr_t;
    typedef const address_t&& r_value;

    typedef std::bitset<32> octets;
    typedef uint32_t u32;

 public:
    u32 address;

 public:
    address_t() : address(0) {}  // Default
    explicit address_t(u32 a) : address(a) {}
    address_t(u32 a, u32 b, u32 c, u32 d);

    // DESTRUCTOR
    ~address_t() = default;

    // COPY
    address_t(const_ref_t);

    // ASSINGMENT
    ref_t operator=(const_ref_t);
    ref_t operator=(const u32&);

    // MOVE CONSTRUCTOR
    address_t(r_value) noexcept;

    // MOVE ASSIGN
    ref_t operator=(r_value) noexcept;

    // SPECIAL OPERATORS (bitwise)

    val_t operator&(const_ref_t rhs) const {
        return address_t(address & rhs.address);
    }
    val_t operator&(u32 const& rhs) const {
        return address_t(address & rhs);
    }
    val_t operator|(const_ref_t rhs) const {
        return address_t(address | rhs.address);
    }
    val_t operator|(u32 const& rhs) const {
        return address_t(address | rhs);
    }
    val_t operator~() const {return address_t(~address);}


    // Arithmetic Operators
    val_t operator+(u32 const& rhs) const {
        return address_t(address + rhs);
    }

    val_t operator-(u32 const&rhs) const {
        return address_t(address - rhs);
    }

    u32 operator+(const_ref_t rhs) const {
        return address + rhs.address;
    }

    u32 operator-(const_ref_t rhs) const {
        return address - rhs.address;
    }

    // OSTREAM
    friend std::ostream& operator<<(std::ostream& ohs, const_ref_t v) {
        ohs << v.bits();
        ohs << " (" << v.dot() << ")";
        return ohs;
    }

    // Formatters

    char inet_class() const;
    std::string dot() const;
    octets octet() const {return {address};}
    std::string bits() const {return octet().to_string();}
};

class IP {
    typedef IP value_type;
    typedef IP& reference_type;
    typedef IP* pointer_type;

 public:
    address_t host;
    address_t mask;
    address_t wildcard;
    address_t network;
    address_t broadcast;
    address_t first_host;
    address_t last_host;
    uint32_t n_hosts = 0;

 public:
    IP() = default; // Default

    IP(int a, int b, int c, int d);
    IP(int a, int b, int c, int d, int m);

 private:
    void _calc_range();

};


#endif //INCLUDE_IP_H_
