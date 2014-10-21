/* -*- C++ -*- */
/**
 * @file SparqlPlugin.h
 * @author Chao ZHANG
 * @date 04/22/2014 21:09:10 *
 * @brief Header file for SparqlPlugin
 *
 */
#ifndef _SPARQL_PLUGIN_H
#define _SPARQL_PLUGIN_H

#include <dlvhex2/PluginInterface.h>
#include <dlvhex2/Error.h>



namespace dlvhex {
  namespace sparql {


class SparqlPlugin : public PluginInterface
{

public:
  SparqlPlugin();

  //adding by Chao
  std::vector<PluginAtomPtr> createAtoms(ProgramCtx&) const;
    
};  // class SparqlPlugin



  } // namespace sparql
} // namespace dlvhex


#endif /* _SPARQL_PLUGIN_H */
