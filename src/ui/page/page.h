#pragma once

#include <iostream>
#include "widget/widget.h"

class Page {
public:
	virtual Widget* build() {
		return new Widget();
	};
};
