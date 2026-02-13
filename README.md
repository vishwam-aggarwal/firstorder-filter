/**

@file README.md

@brief First‑order low‑pass IIR filter using the bilinear (Tustin) transform.



This library implements a lightweight, real‑time‑safe first‑order low‑pass filter.

It was written for Arduino but is fully portable to any C++ environment.



The continuous‑time transfer function is:

 H(s) = ω_c / (s + ω_c)



Using the bilinear (Tustin) transform, the discrete‑time update becomes:



 y[k] = a (u[k] + u[k‑1]) − b y[k‑1]



with:



 a = (Ts * ω_c) / (Ts * ω_c + 2)

 b = (Ts * ω_c − 2) / (Ts * ω_c + 2)



The class stores previous input/output internally and performs only a few

floating‑point operations per sample, making it ideal for embedded control,

robotics, and sensor smoothing. */

firstorderFilter — First‑Order Low‑Pass Filter (Tustin/Bilinear)

@brief Overview

A minimal, stable, first‑order low‑pass IIR filter implemented using the bilinear (Tustin) transform. Designed for Arduino but fully portable to standard C++.

The filter computes:

y[k] = a (u[k] + u[k‑1]) − b y[k‑1]

where a and b are derived from the cutoff frequency (rad/s) and sampling time (s).

@section features Features

First‑order low‑pass IIR filter

Bilinear (Tustin) discretization

No dynamic memory allocation

Stable for all valid cutoff frequencies and sampling times

Guard against invalid parameters (Ts <= 0 or cutOff <= 0)

Suitable for embedded control, robotics, and sensor smoothing

Portable to any C++ project (Arduino not required)

@section usage Usage

Include the library

#include "firstorderFilter.h"

Create and initialize the filter

firstorderFilter lp;

float cutoff_rad = 20.0;   // cutoff frequency in rad/sfloat Ts = 0.001;          // sampling time in seconds

lp.setup(cutoff_rad, Ts);

Filter your signal each loop

float filtered = lp.filteredValue(raw_signal);

@section params Parameter Notes

cutOff is in radians per secondConvert from Hz: cutOff = 2 * PI * f_hz

Ts is in secondsExample: 1 kHz loop → Ts = 0.001

@section numeric Numerical Notes

Tustin discretization preserves stability for all valid parameters.

Very low cutoff frequencies relative to the sampling rate produce slow, integrator‑like behavior (expected for first‑order LPFs).

If Ts <= 0 or cutOff <= 0, initialization is ignored to prevent invalid coefficients.

@section portability Portability

Although written for Arduino, the class uses only basic C++ features. To use it outside Arduino:

Replace #include "Arduino.h" with standard headers (<cmath>, <stdint.h>, etc.)

No other changes are required.

@section refs References

Bilinear Transform (Tustin):https://en.wikipedia.org/wiki/Bilinear_transform

Example derivation of discrete‑time filters:https://spinlab.wpi.edu/courses/ece503_2014/10-3bilinear_transform.pdf