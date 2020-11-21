#include "test.h"

#include "serial/util/fp_convert.h"

void dtoa_serial_fp_convert(double value, char* buffer) {
	buffer[util::fp_convert(value, buffer)] = '\0';
}

REGISTER_TEST(serial_fp_convert);
