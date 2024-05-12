#include "complex.h"

HDSP::complex_f32_t HDSP::cadd(complex_f32_t a, complex_f32_t b) { return complex_f32_t{ a.re + b.re, a.im + b.im }; }
HDSP::complex_f32_t HDSP::csub(complex_f32_t a, complex_f32_t b) { return complex_f32_t{ a.re - b.re, a.im - b.im }; }
HDSP::complex_f32_t HDSP::cmul(complex_f32_t a, complex_f32_t b) { return complex_f32_t{ a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re }; }
HDSP::complex_f32_t HDSP::cmulreal(complex_f32_t a, float b) { return complex_f32_t{ a.re * b, a.im * b }; }

HDSP::complex_f64_t HDSP::cadd64(complex_f64_t a, complex_f64_t b) { return complex_f64_t{ a.re + b.re, a.im + b.im }; }
HDSP::complex_f64_t HDSP::csub64(complex_f64_t a, complex_f64_t b) { return complex_f64_t{ a.re - b.re, a.im - b.im }; }
HDSP::complex_f64_t HDSP::cmul64(complex_f64_t a, complex_f64_t b) { return complex_f64_t{ a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re }; }
HDSP::complex_f64_t HDSP::cmulreal64(complex_f64_t a, double b) { return complex_f64_t{ a.re * b, a.im * b }; }