#include "test.h"

#include "dragonbox/include/dragonbox/dragonbox_to_chars.h"

void dtoa_dragonbox(double value, char* buffer) {
	jkj::dragonbox::to_chars(value, buffer);
}

REGISTER_TEST(dragonbox);
