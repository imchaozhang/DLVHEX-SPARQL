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


namespace dlvhex {
    namespace sparql {
        SparqlAtom::SparqlAtom() : PluginAtom("sparql", 1)
        {
            //sparql["G", "*" "{ ?s, ?p, ?o }" ](S,P,O)
            
            addInputConstant();
            addInputConstant();
            addInputConstant();
            
            
            setOutputArity(3);
        }
        
        void
        SparqlAtom::map_query_result(librdf_world* world, librdf_model* model, librdf_query_results *results, Answer& answer_para, Registry &registry_para)
        {
            int i;
            char *name;
            librdf_stream* stream;
            librdf_serializer* serializer;
            const char *query_graph_serializer_syntax_name="rdfxml";
            
            if(librdf_query_results_is_bindings(results)) {
                
                while(!librdf_query_results_finished(results)) {
                    
                    Tuple out;
                    
                    for(i=0; i<librdf_query_results_get_bindings_count(results); i++) {
                        
                        librdf_node *value=librdf_query_results_get_binding_value(results, i);
                        
                        name=(char*)librdf_query_results_get_binding_name(results, i);
                        
                        if(value) {
                            
                            unsigned char* cstr = librdf_node_to_string(value);
                            
                            std::string s;
                            
                            s.append(reinterpret_cast<const char*>(cstr));
                            
                            
                            if(s[0] == '\"' && s[s.size()-1] == '\"')
                                
                                s = s.substr(1, s.length() - 2);
                            
                            try {
                                int v;
                                v = boost::lexical_cast<int>(s);
                                Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, s);
                                out.push_back(registry_para.storeTerm(term));
                                
                            }
                            catch (boost::bad_lexical_cast& e) {
                                
                                Term term(ID::MAINKIND_TERM | ID::SUBKIND_TERM_CONSTANT, '"' + s + '"');
                                out.push_back(registry_para.storeTerm(term));
                                
                            }
                            
                            
                            
                            
                            
                            librdf_free_node(value);
                        }
                        
                    }
                    
                    answer_para.get().push_back(out);
                    
                    librdf_query_results_next(results);
                    
                }
            }
        }
        
        
        void
        SparqlAtom::retrieve(const Query& query, Answer& answer) throw (PluginError)
        {
            librdf_world* world;
            librdf_storage *storage;
            librdf_model* model;
            librdf_node *node;
            librdf_node *subject, *predicate, *object;
            librdf_node* context_node=NULL;
            librdf_stream* stream;
            librdf_iterator* iterator;
            librdf_uri *base_uri=NULL;
            librdf_query *r_query;
            librdf_query_results *results;
            librdf_hash *options;
            int count;
            int rc;
            int transactions=0;
            const char* storage_name;
            const char* storage_options;
            const char* context;
            const char* identifier;
            const char* results_format;
            librdf_statement* statement=NULL;
            const char* query_cmd=NULL;
            char* s;
            
            /*
             * Initialize
             */
            storage_name="virtuoso";
            results_format="xml";
            context=DEFAULT_CONTEXT;
            identifier=DEFAULT_IDENTIFIER;
            
            storage_options=DEFAULT_STORAGE_OPTIONS;
            
            
            world=librdf_new_world();
            
            
            librdf_world_open(world);
            
            options=librdf_new_hash(world, NULL);
            librdf_hash_open(options, NULL, 0, 1, 1, NULL);
            
            librdf_hash_put_strings(options, "contexts", "yes");
            transactions=1;
            
            librdf_hash_from_string(options, storage_options);
            
            storage=librdf_new_storage_with_options(world, storage_name, identifier, options);
            
            
            model=librdf_new_model(world, storage, NULL);
            
            if(transactions)
                librdf_model_transaction_start(model);
                
                stream=NULL;
                iterator=NULL;
                subject=NULL;
                predicate=NULL;
                object=NULL;
                node=NULL;
                r_query=NULL;
                results=NULL;
                context_node=librdf_new_node_from_uri_string(world, (const unsigned char *)context);
                
                
                Registry &registry = *getRegistry();
                
                
                
            std::string in_graph;
            
            std::string in_select;
            
            std::string in_option;
            
            std::string query_string;
            
            const Term& s_graph = registry.terms.getByID(query.input[0]);
            
            const Term& s_select = registry.terms.getByID(query.input[1]);
            
            const Term& s_option = registry.terms.getByID(query.input[2]);
            
            
            
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
            
            query_string = "SELECT " + in_select + " WHERE {graph " + in_graph + " " + in_option + "}";
            
            
            //query_string = "SELECT * WHERE {graph <http://red> { ?s ?p ?o }}";
            
            query_cmd = query_string.c_str();
            
            
            r_query=librdf_new_query(world, (char *)"sparql", NULL, (const unsigned char *)query_cmd, NULL);
            
            
            if(!(results=librdf_model_query_execute(model, r_query))) {
                
                throw PluginError("Query mode falied");
                
                librdf_free_query(r_query);
                r_query=NULL;
                
            }
            else {
                map_query_result(world, model, results, answer, registry);
                
                librdf_free_query_results(results);
                
            }
            
            librdf_free_query(r_query);
            
            
            if(transactions)
                librdf_model_transaction_commit(model);
                
                librdf_free_node(context_node);
                librdf_free_node(context_node);
                librdf_free_hash(options);
                librdf_free_model(model);
                librdf_free_storage(storage);
                
                librdf_free_world(world);
                
				
                }
	}
    
}

