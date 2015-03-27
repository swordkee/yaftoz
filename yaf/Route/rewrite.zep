/**
 * Yaf Route Rewrite
 */
/**
 * @namespace
 */
namespace Yaf\Route;
use Yaf\Request_Abstract as Request_Abstract;
class Rewrite implements \Yaf\Route_Interface
{
    protected _route = "";
    protected _default = [];
    protected _verify = null;
    /**
     * Instantiates route based on passed Yaf_Config_Abstract structure
     *
     * @param array $config Configuration object
     */
    public static function getInstance(array config)
    {
        if !isset config["match"] || !is_string(config["match"]) {
            return null;
        } elseif !isset config["route"] || empty(config["route"]) {
            return null;
        } else {
            return new self(config["match"], config["route"]);
        }
    }
    
    public function __construct(match, route, verify = null) -> void
    {
        
        if !is_string(match) || match == "" {
            throw new \Yaf\Exception\TypeError("Expects a string as the first parameter");
        }
        
        if !is_array(route) {
            throw new \Yaf\Exception\TypeError("Expects an array as the second parameter");
        }
        
        if verify != null && !is_array(verify) {
            throw new \Yaf\Exception\TypeError("Expects an array as third parameter");
        }
        let this->_route = match;
        let this->_default =  (array) route;
        let this->_verify = verify;
    }
    
    /**
     * Matches a user submitted path with a previously defined route.
     * Assigns and returns an array of defaults on a successful match.
     *
     * @param  string $path Path used to match against this routing map
     * @return array|false  An array of assigned values or a false on a mismatch
     */
    public function route(<Request_Abstract> request)
    {
        var requestUri, baseuri, path, values;
    
        let requestUri =  request->getRequestUri();
        let baseuri =  request->getBaseUri();
        
        if requestUri != "" && baseuri != "" && stripos(requestUri, baseuri) !== false {
            let path =  substr(requestUri, strlen(baseuri));
        } else {
            let path = requestUri;
        }
        let path =  trim(urldecode(path), \Yaf\Router::URI_DELIMITER);
        let values =  this->_match(path);
        
        if values == null {
            
            return false;
        }
        
        if isset this->_default["module"] {
            request->setModuleName(this->_default["module"]);
        }
        
        if isset this->_default["controller"] {
            request->setControllerName(this->_default["controller"]);
        }
        
        if isset this->_default["action"] {
            request->setActionName(this->_default["action"]);
        }
        request->setParam(values);
        
        return true;
    }
    
    /**
     * @todo this method can be write differently with (P< style match
     * Matches a user submitted path with parts defined by a map. Assigns and
     * returns an array of variables on a successful match.
     *
     * @param string $path Path used to match against this routing map
     * @return array|false An array of assigned values or a false on a mismatch
     */
    protected function _match(string path)
    {
        var staticCount, pathStaticCount, values, matchedPath, parts, variables, wildcardData, name, part, pos, pathMatch, count, i, varr, pathPart, tmpReturn;
    
        let staticCount = 0;
        let pathStaticCount = 0;
        
        let values =  [];
        let matchedPath = "";
        
        let parts =  [];
        
        let variables =  [];
        
        let wildcardData =  [];
        
        if this->_route !== "" {
            for pos, part in explode(\Yaf\Router::URI_DELIMITER, trim(this->_route, \Yaf\Router::URI_DELIMITER)) {
                
                if substr(part, 0, 1) == \Yaf\Router::URI_VARIABLE && substr(part, 1, 1) != \Yaf\Router::URI_VARIABLE {
                    let name =  substr(part, 1);
                    let parts[pos] = null;
                    let variables[pos] = name;
                } else {
                    
                    if substr(part, 0, 1) == \Yaf\Router::URI_VARIABLE {
                        let part =  substr(part, 1);
                    }
                    let parts[pos] = part;
                    
                    if part !== "*" {
                        let staticCount++;
                    }
                }
            }
        }
        
        if path !== "" {
            let pathMatch =  explode(\Yaf\Router::URI_DELIMITER, path);
            for pos, pathPart in pathMatch {
                // Path is longer than a route, it's not a match
                
                if !array_key_exists(pos, parts) {
                    
                    return false;
                }
                let matchedPath .= pathPart . \Yaf\Router::URI_DELIMITER;
                // If it's a wildcard, get the rest of URL as
                // wildcard data and stop matching
                
                if parts[pos] == "*" {
                    let count =  count(pathMatch);
                    let i = pos;
                    while i < count {
                       let varr =  urldecode(pathMatch[i]);
                       if !isset wildcardData[varr] && !isset this->_default[varr] && !isset values[varr] {

                           let wildcardData[varr] =  isset pathMatch[i + 1] ? urldecode(pathMatch[i + 1]) : null;
                       }
                        let i += 2;
                    }
                    let matchedPath =  implode(\Yaf\Router::URI_DELIMITER, pathMatch);
                    break;
                }
                
                let name =  isset variables[pos] ? variables[pos] : null;
                let pathPart =  urldecode(pathPart);
                let part = parts[pos];
                
                if substr(part, 0, 2) === "@@" {
                    let part =  substr(part, 1);
                }
                // If it's a static part, match directly
                
                if name === null && part != pathPart {
                    
                    return false;
                }
                // If it's a variable with requirement,
                // match a regex. If not - everything matches
                
                if part !== null && !preg_match(part . "#^" . "$#" . "iu", pathPart) {
                    
                    return false;
                }
                // If it's a variable store it's value for later
                
                if name !== null {
                    let values[name] = pathPart;
                } else {
                    let pathStaticCount++;
                }
            }
        }
        // Check if all static mappings have been matched
        
        if staticCount != pathStaticCount {
            
            return false;
        }
        let tmpReturn =  values + wildcardData;
        // Check if all map variables have been initialized
        for varr in variables {
            
            if !array_key_exists(varr, tmpReturn) {
                return false;
            //} elseif tmpReturn[varr] == "" || tmpReturn[varr] === null {
                // Empty variable? Replace with the default value.
            //    let tmpReturn[varr] = this->_default[varr];
            }
        }
        
        if values == null && wildcardData == null && staticCount != 0 {
            let tmpReturn =  tmpReturn + this->_default;
        }
        
        return tmpReturn;
    }

}