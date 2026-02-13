/****************************************************************************** 
 * Includes 
 ******************************************************************************/

#include "firstorderFilter.h"

/***********************************************************************************************
 * setup()
 *
 * Initializes a first‑order low‑pass filter using the bilinear (Tustin) transform.
 *
 * cutOff : cutoff frequency in rad/sec (ω_c)
 * Ts     : sampling time in seconds
 *
 * Continuous‑time transfer function:
 *        H(s) = ω_c / (s + ω_c)
 *
 * Discrete‑time (Tustin) form:
 *        y[k] = a * (u[k] + u[k-1]) - b * y[k-1]
 *
 * where:
 *        a = (Ts * ω_c) / (Ts * ω_c + 2)
 *        b = (Ts * ω_c - 2) / (Ts * ω_c + 2)
 *
 * Internal states:
 *        _prev_u = u[k-1]
 *        _prev_y = y[k-1]
 ************************************************************************************************/
void firstorderFilter::setup(float cutOff, float Ts)
{
    // Guard against invalid parameters
    if (Ts <= 0 || cutOff <= 0)
        return;

    this->cutOff = cutOff;
    this->Ts = Ts;

    _a = Ts * cutOff / (Ts * cutOff + 2);
    _b = (Ts * cutOff - 2) / (Ts * cutOff + 2);

    _prev_u = 0;
    _prev_y = 0;
}

/************************************************************************************
 * filteredValue()
 *
 * Computes the filtered output for the current input sample u.
 *
 * Implements:
 *        y[k] = a * (u[k] + u[k-1]) - b * y[k-1]
 *
 * Updates internal state for next iteration.
 ************************************************************************************/
float firstorderFilter::filteredValue(float u)
{
    _y = _a * (u + _prev_u) - _b * _prev_y;

    _prev_u = u;
    _prev_y = _y;

    return _y;
}