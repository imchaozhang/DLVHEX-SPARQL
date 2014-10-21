/* -*- C++ -*- */
/**
 * @file SparqlPlugin.cpp
 * @author Chao ZHANG
 * @date 04/22/2014 21:09:10
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "SparqlPlugin.h"
#include "SparqlAtom.h"
#include "UpdateAtom.h"



  SparqlPlugin::SparqlPlugin()

  {
    setNameVersion(PACKAGE_TARNAME,SPARQLPLUGIN_VERSION_MAJOR,SPARQLPLUGIN_VERSION_MINOR,SPARQLPLUGIN_VERSION_MICRO);
  }


  
 std::vector<PluginAtomPtr> SparqlPlugin::createAtoms(ProgramCtx&) const
      {
          std::vector<PluginAtomPtr> ret;
          
          // return smart pointer with deleter (i.e., delete code compiled into this plugin)
          ret.push_back(PluginAtomPtr(new SparqlAtom, PluginPtrDeleter<PluginAtom>()));
          ret.push_back(PluginAtomPtr(new UpdateAtom, PluginPtrDeleter<PluginAtom>()));
          
          return ret;
      }
      
SparqlPlugin theSparqlPlugin;


  } // namespace sparql
} // namespace dlvhex

//
// let it be loaded by dlvhex!
//

IMPLEMENT_PLUGINABIVERSIONFUNCTION

// return plain C type s.t. all compilers and linkers will like this code
extern "C"
void * PLUGINIMPORTFUNCTION()
{
	return reinterpret_cast<void*>(& dlvhex::sparql::theSparqlPlugin);
}
