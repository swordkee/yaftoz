/**
 * Yaf router supervar
 *
 */
/**
 * @namespace
 */
namespace Yaf\Route;
use Yaf\Response_Abstract;
use Yaf\Request_Abstract;
class Supervar implements \Yaf\Route_Interface
{
    protected _varName = "";
    /**
     * Class constructor
     *
     */
    public function __construct(varName) -> void
    {
        
        if !is_string(varName) || varName == "" {
            throw new \Yaf\Exception\TypeError("Expects a string super var name");
        } else {
            let this->_varName = varName;
        }
    }
    
    /**
     * Processes a request and sets its controller and action based on a
     * supervar value.
     *
     * @param  Yaf_Request_Abstract
     * @return Yaf_Request_Abstract|boolean
     */
    public function route(<Request_Abstract> request)
    {
        var requestUri, module, controller, action, rest, path, actionPrefer, params, numSegs, i, key, val;
    
        let requestUri =  request->getQuery(this->_varName);
        
        if requestUri == null || requestUri == "" {
            
            return false;
        }
        let module =  null;
        let controller =  null;
        let action =  null;
        let rest =  null;
        let path =  trim(requestUri, \Yaf\Router::URI_DELIMITER);
        
        if path != "" && path != "/" {
            let path =  explode(\Yaf\Router::URI_DELIMITER, path);
            
            if \Yaf\Application::isModuleName(path[0]) {
                let module = path[0];
                array_shift(path);
            }
            
            if count(path) && !empty(path[0]) {
                let controller = path[0];
                array_shift(path);
            }
            
            if count(path) && !empty(path[0]) {
                let action = path[0];
                array_shift(path);
            }
            let rest =  implode(\Yaf\Router::URI_DELIMITER, path);
            let actionPrefer =  \Yaf\G::iniGet("yaf.action_prefer");
            
            if module == null && controller == null && action == null {
                
                if actionPrefer == true {
                    let action = rest;
                } else {
                    let controller = rest;
                }
                let rest =  null;
            } elseif module == null && action == null && rest == null {
                
                if actionPrefer == true {
                    let action = controller;
                    let controller =  null;
                }
            } elseif controller == null && action == null && rest != null {
                let controller = module;
                let action = rest;
                let module =  null;
                let rest =  null;
            } elseif action == null && rest == null {
                let action = controller;
                let controller = module;
                let module =  null;
            } elseif controller == null && action == null {
                let controller = module;
                let action = rest;
                let module =  null;
                let rest =  null;
            } elseif action == null {
                let action = rest;
                let rest =  null;
            }
            
            if module != null {
                request->setModuleName(module);
            }
            
            if controller != null {
                request->setControllerName(controller);
            }
            
            if action != null {
                request->setActionName(action);
            }
            
            let params =  [];
            
            if rest != null && trim(rest) != "" {
                let path =  explode(\Yaf\Router::URI_DELIMITER, rest);
                let numSegs =  count(path);
                if numSegs != 0 {
                    let i = 0;
                    while i < numSegs {
                       let key =  urldecode(path[i]);
                        let val =  isset path[i + 1] ? urldecode(path[i + 1]) : null;
                        let params[key] =  isset params[key] ? array_merge((array) params[key], [val]) : val;
                        let i=i+2;
                    }
                }
                request->setParam(params);
            }
        }
        
        return true;
    }
    
    /**
     * used to create routes on the fly from config
     *
     * @param array $config
     */
    public static function getInstance(array config)
    {
        
        if !is_string(config["varname"]) || config["varname"] == "" {
            
            return null;
        }
        
        return new self(config["varname"]);
    }

}