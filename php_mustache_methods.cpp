
#include "php_mustache.hpp"
#include "php_mustache_methods.hpp"

/* {{{ proto void __construct()
   */
PHP_METHOD(Mustache, __construct)
{
  zend_class_entry * _this_ce;
  zval * _this_zval;
  php_obj_Mustache *payload;

  if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, Mustache_ce_ptr) == FAILURE) {
          return;
  }

  _this_zval = getThis();
  _this_ce = Z_OBJCE_P(_this_zval);

  payload = (php_obj_Mustache *) zend_object_store_get_object(_this_zval TSRMLS_CC);
}
/* }}} __construct */

/* {{{ proto string getStartSequence()
   */
PHP_METHOD(Mustache, getStartSequence)
{
  zend_class_entry * _this_ce;
  zval * _this_zval;
  php_obj_Mustache *payload;
  std::string str;

  if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, Mustache_ce_ptr) == FAILURE) {
          return;
  }

  _this_zval = getThis();
  _this_ce = Z_OBJCE_P(_this_zval);

  payload = (php_obj_Mustache *) zend_object_store_get_object(_this_zval TSRMLS_CC);
  
  str = payload->mustache->getStartSequence();
  
  RETURN_STRING(str.c_str(), 1);
}
/* }}} getStartSequence */

/* {{{ proto string getStopSequence()
   */
PHP_METHOD(Mustache, getStopSequence)
{
  zend_class_entry * _this_ce;
  zval * _this_zval;
  php_obj_Mustache *payload;
  std::string str;

  if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, Mustache_ce_ptr) == FAILURE) {
          return;
  }

  _this_zval = getThis();
  _this_ce = Z_OBJCE_P(_this_zval);

  payload = (php_obj_Mustache *) zend_object_store_get_object(_this_zval TSRMLS_CC);
  
  str = payload->mustache->getStopSequence();
  
  RETURN_STRING(str.c_str(), 1);
}
/* }}} getStopSequence */

/* {{{ proto boolean setStartSequence(string str)
   */
PHP_METHOD(Mustache, setStartSequence)
{
  zend_class_entry * _this_ce;
  zval * _this_zval;
  php_obj_Mustache *payload;
  
  char *str;
  long str_len;
  std::string cppstr;

  if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, Mustache_ce_ptr, &str, &str_len) == FAILURE) {
          return;
  }

  _this_zval = getThis();
  _this_ce = Z_OBJCE_P(_this_zval);

  payload = (php_obj_Mustache *) zend_object_store_get_object(_this_zval TSRMLS_CC);
  
  cppstr.assign(str, str_len);
  payload->mustache->setStartSequence(cppstr);
  
  RETURN_TRUE;
}
/* }}} setStartSequence */

/* {{{ proto boolean setStopSequence(string str)
   */
PHP_METHOD(Mustache, setStopSequence)
{
  zend_class_entry * _this_ce;
  zval * _this_zval;
  php_obj_Mustache *payload;
  
  char *str;
  long str_len;
  std::string cppstr;

  if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, Mustache_ce_ptr, &str, &str_len) == FAILURE) {
          return;
  }

  _this_zval = getThis();
  _this_ce = Z_OBJCE_P(_this_zval);

  payload = (php_obj_Mustache *) zend_object_store_get_object(_this_zval TSRMLS_CC);
  
  cppstr.assign(str, str_len);
  payload->mustache->setStopSequence(cppstr);
  
  RETURN_TRUE;
}
/* }}} setStartSequence */

/* {{{ proto array tokenize(string template)
   */
PHP_METHOD(Mustache, tokenize)
{
  zend_class_entry * _this_ce;
  zval * _this_zval;
  php_obj_Mustache *payload;
  
  char * template_str;
  long template_len;
  string * template_str_obj;
  
  MustacheNode * root;

  if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, Mustache_ce_ptr, &template_str, &template_len) == FAILURE) {
          return;
  }

  _this_zval = getThis();
  _this_ce = Z_OBJCE_P(_this_zval);

  payload = (php_obj_Mustache *) zend_object_store_get_object(_this_zval TSRMLS_CC);
  
  template_str_obj = new string(template_str);
  
  root = payload->mustache->tokenize(template_str_obj);
  
  // Convert to PHP array
  mustache_node_to_zval(root, return_value);
  
  // Free internal tokens
  delete root;
}
/* }}} tokenize */

/* {{{ proto string render(string template, array data)
   */
PHP_METHOD(Mustache, render)
{
  zend_class_entry * _this_ce;
  zval * _this_zval;
  php_obj_Mustache *payload;
  
  char * template_str;
  long template_len;
  
  zval * data = NULL;
  HashTable * data_hash = NULL;
  
  string * template_str_obj;
  MustacheData * template_data;
  string * return_str;

  if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Osa/", &_this_zval, Mustache_ce_ptr, &template_str, &template_len, &data) == FAILURE) {
          return;
  }

  _this_zval = getThis();
  _this_ce = Z_OBJCE_P(_this_zval);

  payload = (php_obj_Mustache *) zend_object_store_get_object(_this_zval TSRMLS_CC);
  
  // Prepare template string
  template_str_obj = new string(template_str);
  
  // Prepare template data
  template_data = new MustacheData();
  mustache_data_from_zval(template_data, data);
  
  // Render template
  return_str = payload->mustache->render(template_str_obj, template_data);
  
  // Free template data
  delete template_data;
  
  RETURN_STRING(return_str->c_str(), 0); // Do reallocate
  //RETURN_STRINGL(return_str, return_len, 0); // Do not reallocate
}
/* }}} render */

void mustache_data_from_zval(MustacheData * node, zval * current)
{
  HashTable * data_hash = NULL;
  HashPosition data_pointer = NULL;
  zval **data_entry = NULL;
  long data_count;
  
  int key_type;
  char * key_str;
  uint key_len;
  ulong key_nindex;
  string * ckey;
  
  MustacheData * child = NULL;
  
  switch( Z_TYPE_P(current) ) {
      case IS_LONG:
      case IS_DOUBLE:
      case IS_STRING:
        convert_to_string(current);
        node->type = MUSTACHE_DATA_STRING;
        node->val = new string(Z_STRVAL_P(current)); // Z_STRLEN_P(current)
        //cout << *node->val << endl;
        break;
      case IS_ARRAY: // START IS_ARRAY -----------------------------------------
        node->type = MUSTACHE_DATA_NONE;
        
        data_hash = HASH_OF(current);
        data_count = zend_hash_num_elements(data_hash);
        zend_hash_internal_pointer_reset_ex(data_hash, &data_pointer);
        while( zend_hash_get_current_data_ex(data_hash, (void**) &data_entry, &data_pointer) == SUCCESS ) {
          // Get current key
          key_type = zend_hash_get_current_key_ex(data_hash, &key_str, &key_len, &key_nindex, true, &data_pointer);
          // Check key type
          if( key_type == HASH_KEY_IS_LONG ) {
            //cout << key_nindex << endl;
            if( node->type == MUSTACHE_DATA_NONE ) {
              node->type = MUSTACHE_DATA_LIST;
            } else if( node->type != MUSTACHE_DATA_LIST ) {
              php_error(E_WARNING, "Mixed numeric and associative arrays are not supported");
              return; // EXIT
            }
          } else {
            //cout << key_str << endl;
            if( node->type == MUSTACHE_DATA_NONE ) {
              node->type = MUSTACHE_DATA_MAP;
            } else if( node->type != MUSTACHE_DATA_MAP ) {
              php_error(E_WARNING, "Mixed numeric and associative arrays are not supported");
              return; // EXIT
            }
          }
          
          // Process value
          child = new MustacheData();
          mustache_data_from_zval(child, *data_entry);
          
          // Store value
          if( node->type == MUSTACHE_DATA_LIST ) {
            node->children.push_back(child);
          } else if( node->type == MUSTACHE_DATA_MAP ) {
            ckey = new string(key_str);
            node->data.insert(pair<string,MustacheData*>(*ckey,child));
          } else {
            // Whoops
            delete child;
            child = NULL;
          }
          zend_hash_move_forward_ex(data_hash, &data_pointer);
        }
  
        break; // END IS_ARRAY -------------------------------------------------
    default:
      php_error(E_WARNING, "Invalid data type");
      break;
  }
}

void mustache_node_to_zval(MustacheNode * node, zval * current)
{
  array_init(current);
  
  // Basic data
  add_assoc_long(current, "type", node->type);
  add_assoc_long(current, "flags", node->flags);
  if( NULL != node->data && node->data->length() > 0 ) {
    add_assoc_stringl(current, "data", (char *) node->data->c_str(), node->data->length(), 1);
  }
  
  // Children
  if( node->children.size() > 0 ) {
    zval * children;
    ALLOC_INIT_ZVAL(children);
    array_init(children);
    
    list<MustacheNode *>::iterator it;
    for ( it = node->children.begin() ; it != node->children.end(); it++ ) {
      zval * child;
      ALLOC_INIT_ZVAL(child);
      mustache_node_to_zval(*it, child);
      add_next_index_zval(children, child);
    }
    
    add_assoc_zval(current, "children", children);
  }
}