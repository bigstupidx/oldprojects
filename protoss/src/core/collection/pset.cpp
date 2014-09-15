// pset.cpp
// A set of unique values.
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pset.h"

#if defined P_DEBUG

static void pSetTestCompiling()
{
	PSet<pInt32> set;
	set.insert(1);

	PSet<pInt32>::iterator it, ib = set.begin(), ie = set.end();
	for (it = ib; it != ie; ++it)
	{
		pInt32 value = *it;
	}
}

#endif // !P_DEBUG