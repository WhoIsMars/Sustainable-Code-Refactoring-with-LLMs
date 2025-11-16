#include "space_age.h"

namespace space_age {
    space_age::space_age(unsigned long long int seconds) : m_seconds(seconds) {}

    unsigned long long int space_age::seconds() const
    {
        return m_seconds;
    }

    double space_age::on_earth() const
    {
        return m_seconds * 3.168808781402895e-8; // 1.0 / 31557600.0 precomputed
    }

    double space_age::on_mercury() const
    {
        return m_seconds * 1.3154902513227513e-7; // 1.0 / (31557600.0 * 0.2408467) precomputed
    }

    double space_age::on_venus() const
    {
        return m_seconds * 5.150779130434783e-8; // 1.0 / (31557600.0 * 0.61519726) precomputed
    }
    
    double space_age::on_mars() const
    {
        return m_seconds * 1.6848073394495413e-8; // 1.0 / (31557600.0 * 1.8808158) precomputed
    }

    double space_age::on_jupiter() const
    {
        return m_seconds * 2.6717344973751463e-9; // 1.0 / (31557600.0 * 11.862615) precomputed
    }

    double space_age::on_saturn() const
    {
        return m_seconds * 1.0759731284530934e-9; // 1.0 / (31557600.0 * 29.447498) precomputed
    }

    double space_age::on_uranus() const
    {
        return m_seconds * 3.7717537688442107e-10; // 1.0 / (31557600.0 * 84.016846) precomputed
    }

    double space_age::on_neptune() const
    {
        return m_seconds * 1.9226582677165354e-10; // 1.0 / (31557600.0 * 164.79132) precomputed
    }

}