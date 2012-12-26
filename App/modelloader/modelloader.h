#ifndef __MODELLOADER__
#define __MODELLOADER__

#include "objects/3dmodel.h"
#include <map>

using namespace std;

class xModelProvider {

    map<string,x3DModel*> models;

    public:
        x3DModel* getModel(char *name) {
            map<string, x3DModel*>::iterator model = models.find(name);

            if (model == models.end()) {
                x3DModel* mod = new x3DModel(name);
                models.insert(pair<string,x3DModel*>(name,mod) );
            }
            return (*model).second;
        }




};


#endif
