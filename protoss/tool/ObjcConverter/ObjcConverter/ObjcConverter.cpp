// ObjcConverter.cpp : 定义控制台应用程序的入口点。
//

#include "loaderobj.h"
#include "encoder.h"
#include "modeldata.h"
#include "macro.h"

int main(int argc, char* argv[])
{
    LoaderObj *loader = new LoaderObj();
    loader->loadFile("test.obj");
    ModelData data;
    loader->cloneData(data);
	delete loader;

    Encoder *encoder = new Encoder();
    // FIXME: set data should clone, but here is not.
    encoder->setData(data); 
    encoder->saveFile("test.objc");

	data.dispose();
	
	return 0;
}

