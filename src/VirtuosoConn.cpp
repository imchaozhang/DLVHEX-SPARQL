//
//  virtuosoConn.cpp
//  SPARQLPlugin
//
//  Created by Chao Zhang on 4/22/14.
//  Copyright (c) 2014 Chao Zhang. All rights reserved.
//

#include "virtuosoConn.h"
#include <string>
namespace dlvhex
{
    namespace sparql
    {
        
        void virtuosoConn::init() {
            
            storage_name = "virtuoso";
            results_format = "xml";
            context = DEFAULT_CONTEXT;
            identifier = DEFAULT_IDENTIFIER;
            storage_options = DEFAULT_STORAGE_OPTIONS;
            
            world = librdf_new_world();
            librdf_world_open(world);
            
            options = librdf_new_hash(world, NULL);
            librdf_hash_open(options, NULL, 0, 1, 1, NULL);
            
            librdf_hash_put_strings(options, "contexts", "yes");
            transactions = 1;
            
            
            librdf_hash_from_string(options, storage_options);
            
            
            
            storage = librdf_new_storage_with_options(world, storage_name, identifier, options);
            model = librdf_new_model(world, storage, NULL);
            
            base_uri = NULL;
            statement = NULL;
            
            
            if (transactions)
                librdf_model_transaction_start(model);
            
            stream = NULL;
            iterator = NULL;
            subject = NULL;
            predicate = NULL;
            object = NULL;
            node = NULL;
            r_query = NULL;
            results = NULL;
            query_cmd = NULL;
            context_node = librdf_new_node_from_uri_string(world, (const unsigned char *) context);
        }
        
        void virtuosoConn::print_query_result(librdf_query_results* results_para) {
            
            int i;
            char *name;
            librdf_stream* stream;
            librdf_serializer* serializer;
            const char *query_graph_serializer_syntax_name = "rdfxml";
            
            if (librdf_query_results_is_bindings(results_para)) {
                
                while (!librdf_query_results_finished(results_para)) {
                    
                    for (i = 0; i < librdf_query_results_get_bindings_count(results_para); i++) {
                        librdf_node *value = librdf_query_results_get_binding_value(results_para, i);
                        name = (char*) librdf_query_results_get_binding_name(results_para, i);
                        if (value) {
                            
                            unsigned char* cstr = librdf_node_to_string(value);
                            std::string s;
                            printf("%s", s.append(reinterpret_cast<const char*> (cstr)).c_str());
                            printf(" ");
                            librdf_free_node(value);
                        }
                    }
                    printf("\n");
                    librdf_query_results_next(results_para);
                }
            }
        }
        
        void virtuosoConn::sparql_select(const std::string& in_select,const std::string& in_graph,const std::string& in_option) {
            
            std::string query_string;
            
            //query_string = "Select * Where {graph <http://smarthome.asu.edu> { ?s <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://smarthome.asu.edu/service_ontology#health_problem> . }}";
            
            
            query_string = "SELECT " + in_select + " WHERE {graph " + in_graph + " " + in_option + "}";
            
            query_cmd = query_string.c_str();
            r_query = librdf_new_query(world, (char *) "sparql", NULL, (const unsigned char *) query_cmd, NULL);
            
            if (!(results = librdf_model_query_execute(model, r_query))) {
                
                librdf_free_query(r_query);
                r_query = NULL;
                
            } else {
                print_query_result(results);
                
                librdf_free_query_results(results);
            }
        }
        
        void virtuosoConn::free() {
            librdf_free_query(r_query);
            
            
            if (transactions)
                librdf_model_transaction_commit(model);
            
            librdf_free_node(context_node);
            librdf_free_node(context_node);
            librdf_free_hash(options);
            librdf_free_model(model);
            librdf_free_storage(storage);
            
            librdf_free_world(world);
            
        }
        
        int virtuosoConn::add_triple(const char *s, const char *p, const char *o)
        {
            librdf_node *subject, *predicate, *object;
            librdf_statement* statement=NULL;
            int rc;
            
            if(librdf_heuristic_is_blank_node(s))
                subject=librdf_new_node_from_blank_identifier(world, (const unsigned char *)librdf_heuristic_get_blank_node(s));
            else
                subject=librdf_new_node_from_uri_string(world, (const unsigned char *)s);
            
            predicate=librdf_new_node_from_uri_string(world, (const unsigned char *)p);
            
            if(librdf_heuristic_is_blank_node(o))
                object=librdf_new_node_from_blank_identifier(world, (const unsigned char *)librdf_heuristic_get_blank_node(o));
            else
                object=librdf_new_node_from_uri_string(world, (const unsigned char *)o);
            
            statement=librdf_new_statement(world);
            librdf_statement_set_subject(statement, subject);
            librdf_statement_set_predicate(statement, predicate);
            librdf_statement_set_object(statement, object);
            
            rc=librdf_model_context_add_statement(model, context_node, statement);
            
            librdf_free_statement(statement);
            return rc;
        }
        
        int virtuosoConn::add_triple_typed(const char *s, const char *p, const char *o)
        {
            librdf_node *subject, *predicate, *object;
            librdf_statement* statement=NULL;
            int rc;
            
            if(librdf_heuristic_is_blank_node(s))
                subject=librdf_new_node_from_blank_identifier(world, (const unsigned char *)librdf_heuristic_get_blank_node(s));
            else
                subject=librdf_new_node_from_uri_string(world, (const unsigned char *)s);
            
            predicate=librdf_new_node_from_uri_string(world, (const unsigned char *)p);
            
            if(librdf_heuristic_is_blank_node(o))
                object=librdf_new_node_from_blank_identifier(world, (const unsigned char *)librdf_heuristic_get_blank_node(o));
            else
                object=librdf_new_node_from_literal(world, (const unsigned char *)o, NULL, 0);
            
            statement=librdf_new_statement(world);
            librdf_statement_set_subject(statement, subject);
            librdf_statement_set_predicate(statement, predicate);
            librdf_statement_set_object(statement, object);
            
            rc=librdf_model_context_add_statement(model, context_node, statement);
            
            librdf_free_statement(statement);
            return rc;
        }
        
        
        
        
        virtuosoConn::virtuosoConn() {
            
            init();
        }
        
        virtuosoConn::~virtuosoConn() {
            
            free();
        }
        
    } // sparql
    
} // dlvhex
