#ifndef firstorderFilter_h
#define firstorderFilter_h

#include "Arduino.h"

/**
 * firstorderFilter
 *
 * Implements a first‑order low‑pass filter using the Tustin (bilinear) transform.
 * Call setup() once, then repeatedly call filteredValue(u) each sample.
 */
class firstorderFilter
{
  public:
    // Initialize filter with cutoff frequency (rad/s) and sampling time (s)
    void setup(float cutOff, float Ts);

    // Compute filtered output for current input sample
    float filteredValue(float u);

  private:
    /************************
     * Filter parameters
     ************************/
    float cutOff;   // cutoff frequency (rad/s)
    float Ts;       // sampling time (s)
    float _a;       // Tustin coefficient
    float _b;       // Tustin coefficient

    /************************
     * Filter states
     ************************/
    float _prev_u;  // previous input u[k-1]
    float _prev_y;  // previous output y[k-1]
    float _y;       // current output y[k]
};

#endif