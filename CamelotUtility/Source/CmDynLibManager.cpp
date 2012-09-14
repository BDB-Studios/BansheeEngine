/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2011 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "CmDynLibManager.h"
#include "CmDynLib.h"

namespace CamelotEngine
{
    //-----------------------------------------------------------------------
    template<> DynLibManager* Singleton<DynLibManager>::ms_Singleton = 0;
    DynLibManager* DynLibManager::getSingletonPtr(void)
    {
        return ms_Singleton;
    }
	//-----------------------------------------------------------------------
    DynLibManager& DynLibManager::getSingleton(void)
    {  
        assert( ms_Singleton );  return ( *ms_Singleton );  
    }
    //-----------------------------------------------------------------------
	DynLibManager::DynLibManager()
	{
	}
	//-----------------------------------------------------------------------
    DynLib* DynLibManager::load( const String& filename)
    {
		DynLibList::iterator i = mLibList.find(filename);
		if (i != mLibList.end())
		{
			return i->second;
		}
		else
		{
	        DynLib* pLib = new DynLib(filename);
			pLib->load();        
        	mLibList[filename] = pLib;
	        return pLib;
		}
    }
	//-----------------------------------------------------------------------
	void DynLibManager::unload(DynLib* lib)
	{
		DynLibList::iterator i = mLibList.find(lib->getName());
		if (i != mLibList.end())
		{
			mLibList.erase(i);
		}
		lib->unload();
		delete lib;
	}
	//-----------------------------------------------------------------------
    DynLibManager::~DynLibManager()
    {
        // Unload & delete resources in turn
        for( DynLibList::iterator it = mLibList.begin(); it != mLibList.end(); ++it )
        {
            it->second->unload();
            delete it->second;
        }

        // Empty the list
        mLibList.clear();
    }
}
