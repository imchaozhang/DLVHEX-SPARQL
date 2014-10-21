/**
 * @file SparqlAtom.cpp
 * @author Chao ZHANG
 * @date 04/22/2014 21:09:10
 *
 * @brief Defintion of the Sparql Atom.
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "SparqlAtom.h"
#include <dlvhex2/Registry.h>
#include <dlvhex2/Term.h>

#include <sstream>
#include <iostream>

#include <soprano/Model>
#include <soprano/BackendSetting>
#include <soprano/Backend>
#include <soprano/Soprano>

#include <QtCore/QString>


namespace dlvhex {
    namespace sparql {
        SparqlAtom::SparqlAtom() : PluginAtom("sparql", 1)
  
      {
            //sparql["Prefix","G", "*" "{ ?s, ?p, ?o }" ](S,P,O)
            
            addInputConstant();
            addInputConstant();
            addInputConstant();
            addInputConstant();
            
            //set the maximum output number as 10.
            setOutputArity(10);
        }
        void
        SparqlAtom::retrieve(const Query& query, Answer& answer) throw (PluginError)
        {
            Registry &registry = *getRegistry();
            
            std::string in_prefix;
            
            std::string in_graph;
            
            std::string in_select;
            
            std::string in_option;
            
            std::string query_string;
            
            const Term& s_prefix = registry.terms.getByID(query.input[0]);
            
            const Term& s_graph = registry.terms.getByID(query.input[1]);
            
            const Term& s_select = registry.terms.getByID(query.input[2]);
            
            const Term& s_option = registry.terms.getByID(query.input[3]);
            
            if (!s_prefix.isQuotedString())
            {
                throw PluginError("Wrong input argument type for argument 0");
            }
            
            in_prefix = s_prefix.getUnquotedString();
            
            
            //something you can try here to format the input
//            if(in_prefix.find("prefix",0) == std::string::npos)
//            {
//                throw PluginError("Need to include \"prefix\" in the argument 0");
//            }
            
      
            if (!s_graph.isQuotedString())
            {
                throw PluginError("Wrong input argument type for argument 1");
            }
            
            in_graph = s_graph.getUnquotedString();
            
            
            if (!s_select.isQuotedString())
            {
                throw PluginError("Wrong input argument type for argument 2");
            }
            
            in_select = s_select.getUnquotedString();
            
            
            if (!s_option.isQuotedString())
            {
                throw PluginError("Wrong input argument type for argument 3");
            }
            
            in_option = s_option.getUnquotedString();
            
            
//            std::string::size_type pos = 0; // Must initialize
//            while ( ( pos = in_option.find ("\n",pos) ) != std::string::npos )
//            {
//                in_option.erase( pos, 1 );
//            }
            
            
            
            
            
            
            query_string = in_prefix + " SELECT " + in_select + " WHERE {graph " + in_graph + " " + in_option + "}";
            
            
            const Soprano::Backend* virtBack;
            if( !(virtBack = Soprano::PluginManager::instance()->discoverBackendByName("virtuosobackend")))
               throw PluginError("Database is not open!");
            virtBack->isAvailable();
                
                
            
            Soprano::BackendSettings settings;
            settings << Soprano::BackendSetting(Soprano::BackendOptionHost, "localhost");
            settings << Soprano::BackendSetting(Soprano::BackendOptionPort, "1111");
            settings << Soprano::BackendSetting(Soprano::BackendOptionUsername, "dba");
            settings << Soprano::BackendSetting(Soprano::BackendOptionPassword, "dba");
            
            Soprano::Model* model = virtBack->createModel(settings);
            
            Soprano::QueryResultIterator it = model->executeQuery(QString::fromStdString(query_string), Soprano::Query::queryLanguageFromString("SPARQL"), "SPARQL");

            
            if (it.isBool()) {
                // this should be updated to the ask plugin
                //outStream << (it.boolValue() ? "true" : "false") << endl;
            }
            else if (it.isGraph()) {
                //return printStatementList(it.iterateStatements());
            }
            
            else {
                int cnt = 0;
                while (it.next()) {
                    
                    Tuple out;
                    
                    for(int i = 0; i < it.bindingCount(); i++){
                        
                        std::string ss;
                        
                        if(it.binding(i).isLiteral())
                        {
                            ss = it.binding(i).toString().toStdString();
                            
                            try {
                                int v;
                                v = boost::lexical_cast<int>(ss);
                                Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, ss);
                                out.push_back(registry.storeTerm(term));
                                
                            }
                            catch (boost::bad_lexical_cast& e) {
                                
                                Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, '"' + ss + '"');
                                out.push_back(registry.storeTerm(term));
                            }
                        }
                        
                        else if (it.binding(i).isBlank())
                        {
                            Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, "\"_:\"");
                            out.push_back(registry.storeTerm(term));
                            
                        }
                        
                        else if (it.binding(i).isEmpty())
                        {
                            Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, "emptyNode");
                            out.push_back(registry.storeTerm(term));
                        }
                        
                        else if (it.binding(i).isResource())
                        {
                            ss = it.binding(i).toString().toStdString();
            
                            Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, "\"<" + ss + ">\"");
                            out.push_back(registry.storeTerm(term));
                        }
                        else
                        {
                            ss = it.binding(i).toString().toStdString();
                            
                            Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, "\"" + ss + "\"");
                            out.push_back(registry.storeTerm(term));
                        }
                            
                    
                        
                    } // end of for loop

                
                    answer.get().push_back(out);
                    
                    ++cnt;
                    
                } // end of while loop
            } // end of if - else if - else
        } // end of retrieve function
        
    } // end of sparql
} // end of dlvhex
