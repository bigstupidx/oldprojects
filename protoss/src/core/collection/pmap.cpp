// pmap.cpp
// A set of key value pairs
//
// Copyright 2013 Cooee. All rights reserved.
//
// Hongwei Li lihw81@gmail.com
//

#include "pmap.h"

#if defined P_DEBUG

static void pMapTestCompiling()
{
	PMap<pInt32, pInt32> map;
	map.insert(1, 1);
	pInt32 ret = map[1];

	PMap<pInt32, pInt32>::iterator it, ib = map.begin(), ie = map.end();
	for (it = ib; it != ie; ++it)
	{
		pInt32 value = it.value();
	}
}

#endif // !P_DEBUG