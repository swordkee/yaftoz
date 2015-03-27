/**
 *
 * Handle request object ...
 *
 */
/**
 * @namespace
 */
namespace Yaf;

abstract class Request_Abstract
{
    /**
     * Has the action been dispatched?
     * @var boolean
     */
    protected dispatched = false;
    /**
     * Module
     * @var string
     */
    public module;
    /**
     * Controller
     * @var string
     */
    public controller;
    /**
     * Action
     * @var string
     */
    public action;
    /**
     * Method
     * @var string
     */
    public method;
    /**
     * Request parameters
     * @var array
     */
    protected params = [];
    /**
     * request_uri
     * @var string
     */
    protected language;
    /**
     * routed
     * @var string
     */
    protected routed;
    /**
     * base_uri
     * @var string
     */
    protected _baseUri;
    /**
     * exception
     * @var \Exception
     */
    protected _exception;
    /**
     * Retrieve the action name
     *
     * @return string
     */
    public function getActionName() -> string
    {
        
        return this->action;
    }
    
    public function getBaseUri() -> array
    {
    }
    
    /**
     * Retrieve the controller name
     *
     * @return string
     */
    public function getControllerName() -> string
    {
        
        return this->controller;
    }
    
    /**
     * Retrieve a member of the $_ENV superglobal
     *
     * If no $key is passed, returns the entire $_ENV array.
     *
     * @param string $name
     * @param mixed $default Default value to use if key not found
     * @return mixed Returns null if key does not exist
     */
    public function getEnv(string name = null, tmpDefault = null)
    {
        /*var env;
        let env = _ENV;
        if name === null {
            return env;
        }
        return isset env[name] ? env[name] : tmpDefault;*/
        return tmpDefault;
    }
    public function getQuery(string name = null, tmpDefault = null)
    {
        var get;
        let get = _GET;
        if name === null {
            return _GET;
        }
        return isset get[name] ? get[name] : tmpDefault;
    }
    /**
     * Set the exception
     * @todo check if this is OK
     */
    public function setException(<\Exception> exception)
    {
        let this->_exception = exception;
        return this;
    }
    /**
     * Retrieve the exception
     * @todo check if this is OK
     * @return \Exception
     */
    public function getException() -> string
    {
        return this->_exception;
    }
    
    /**
     * Retrieve the language
     * @return string
     */
    public function getLanguage() -> string
    {
        if this->language === null {
            let this->language =  this->getEnv("HTTP_ACCEPT_LANGUAGE");
        }
        
        return this->language;
    }
    
    /**
     * Retrieve the method
     * @return string
     */
    public function getMethod() -> string
    {
        var method, sapiType;
    
        
        if this->method === null {
            let method =  this->getServer("REQUEST_METHOD");
            
            if method {
                let this->method = method;
            } else {
                let sapiType =  php_sapi_name();
                
                if strtolower(sapiType) == "cli" || substr(sapiType, 0, 3) == "cgi" {
                    let this->method = "CLI";
                } else {
                    let this->method = "Unknown";
                }
            }
        }
        
        return this->method;
    }
    
    public function getModuleName()
    {
        
        return this->module;
    }
    
    /**
     * Get an action parameter
     *
     * @param string $key
     * @param mixed $default Default value to use if key not found
     * @return mixed
     */
    public function getParam(name, tmpDefault = null)
    {
        let name =  (string) name;
        
        if isset this->params[name] {
            
            return this->params[name];
        }
        
        return tmpDefault;
    }
    
    /**
     * Get all action parameters
     *
     * @return array
     */
    public function getParams() -> array
    {
        
        return this->params;
    }
    
    public function getRequestUri() -> array
    {
    }
    
    /**
     * Retrieve a member of the $_SERVER superglobal
     *
     * If no $key is passed, returns the entire $_SERVER array.
     *
     * @param string $key
     * @param mixed $default Default value to use if key not found
     * @return mixed Returns null if key does not exist
     */
    public function getServer(name = null, tmpDefault = null)
    {
        var server;
        let server = _SERVER;
        if name === null {
            
            return server;
        }
        
        return isset server[name] ? server[name] : tmpDefault;
    }
    
    public function isCli()
    {
        
        if this->getMethod() == "CLI" {
            
            return true;
        }
        
        return false;
    }
    
    /**
     * Determine if the request has been dispatched
     *
     * @return boolean
     */
    public function isDispatched() -> boolean
    {
        
        return this->dispatched;
    }
    
    /**
     * Was the request made by GET?
     *
     * @return boolean
     */
    public function isGet() -> boolean
    {
        
        if this->getMethod() == "GET" {
            
            return true;
        }
        
        return false;
    }
    
    /**
     * Was the request made by HEAD?
     *
     * @return boolean
     */
    public function isHead() -> boolean
    {
        
        if this->getMethod() == "HEAD" {
            
            return true;
        }
        
        return false;
    }
    
    /**
     * Was the request made by OPTIONS?
     *
     * @return boolean
     */
    public function isOptions() -> boolean
    {
        
        if this->getMethod() == "OPTIONS" {
            
            return true;
        }
        
        return false;
    }
    
    /**
     * Was the request made by POST?
     *
     * @return boolean
     */
    public function isPost() -> boolean
    {
        
        if this->getMethod() == "POST" {
            
            return true;
        }
        
        return false;
    }
    
    /**
     * Was the request made by PUT?
     *
     * @return boolean
     */
    public function isPut() -> boolean
    {
        
        if this->getMethod() == "PUT" {
            
            return true;
        }
        
        return false;
    }
    
    /**
     * Was the request made by DELETE?
     *
     * @return boolean
     */
    public function isDelete() -> boolean
    {
        
        if this->getMethod() == "DELETE" {
            
            return true;
        }
        
        return false;
    }
    
    /**
     * Is the request a Javascript XMLHttpRequest?
     *
     * Should work with Prototype/Script.aculo.us, possibly others.
     *
     * @return boolean
     */
    public function isXmlHttpRequest() -> boolean
    {
        return  strcasecmp(this->getServer("HTTP_X_REQUESTED_WITH"), "XMLHttpRequest") == 0 ? true : false;
    }
    
    /**
     * Determine if the request has been routed
     *
     * @return boolean
     */
    public function isRouted() -> boolean
    {
        
        return this->routed;
    }
    
    /**
     * Set the action name
     *
     * @param string $value
     * @return Yaf_Request_Abstract
     */
    public function setActionName(action)
    {
        
        if !is_string(action) {
            throw new Request\Exception("Expect a string action name");
        }
        let this->action = action;
        
        if action === null {
            this->setParam("action", action);
        }
        
        return this;
    }
    
    public function setBaseUri(baseUri = null) -> void
    {
    }
    
    /**
     * Set the controller name to use
     *
     * @param string $value
     * @return Yaf_Request_Abstract
     */
    public function setControllerName(controller)
    {
        
        if !is_string(controller) {
            throw new Request\Exception("Expect a string controller name");
        }
        let this->controller = controller;
        
        return this;
    }
    
    public function setDispatched(dispatched = true) -> void
    {
        let this->dispatched = dispatched;
    }
    
    /**
     * Set the module name to use
     *
     * @param string $value
     * @return Yaf_Request_Abstract
     */
    public function setModuleName(module)
    {
        
        if !is_string(module) {
            throw new Request\Exception("Expect a string module name");
        }
        let this->module = module;
        
        return this;
    }
    
    /**
     * Set an action parameter
     *
     * A $value of null will unset the $key if it exists
     *
     * @param string $key
     * @param mixed $value
     * @return Yaf_Request_Abstract
     */
    public function setParam(name, value = null)
    {
        if is_array(name) {
            let this->params =  this->params + name;
        } else {
            let name =  (string) name;
            /*if (null === value) && isset this->_params[name] {
              unset(this->_params[name]);
              } elseif (null !== value) {
              this->_params[name] = value;
              }*/
            let this->params[name] = value;
        }
        
        return this;
    }
    
    /**
     * Unset all user parameters
     *
     * @return Yaf_Request_Abstract
     */
    public function clearParams()
    {
        
        let this->params =  [];
        
        return this;
    }
    
    public function setRequestUri(requestUri = null) -> void
    {
    }
    
    /**
     * Set flag indicating whether or not request has been dispatched
     *
     * @param boolean $flag
     * @return Yaf_Request_Abstract
     */
    public function setRouted(boolean flag = true)
    {
        
        let this->routed =  flag ? true : false;
        
        return this;
    }

}