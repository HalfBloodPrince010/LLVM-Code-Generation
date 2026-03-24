// REQUIRES : asahi-registered-target

// RUN : %clang_cc1 -triple asahi -Wall -Werror -verify %s

int too_few_smul(short a) {
    // expected-error@+1 {{too few arguments to function call, expected 2, have 1}}
    return __builtin_asahi_widening_smul(a);
}