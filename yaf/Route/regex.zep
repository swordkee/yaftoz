/**
 * Yaf Route Regexp
 */
/**
 * @namespace
 */
namespace Yaf\Route;
use Yaf\Response_Abstract as Response_Abstract;
use Yaf\Request_Abstract as Request_Abstract;
class Regex implements \Yaf\Route_Interface
{
    protected _route = "";
    protected _default = [];
    protected _maps = [];
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
        } elseif !isset config["map"] || empty(config["map"]) {
            return null;
        } else {
            return new self(config["match"], config["route"], config["map"]);
        }
    }
    
    public function __construct(match, route, map, verify = null) -> void
    {
        if !is_string(match) || match == "" {
            throw new \Yaf\Exception\RouterFailed("Expects a string as the first parameter");
        }
        
        if !is_array(route) {
            throw new \Yaf\Exception\RouterFailed("Expects a array as the second parameter");
        }
        
        if !is_array(map) {
            throw new \Yaf\Exception\RouterFailed("Expects a array as the third parameter");
        }
        
        if verify != null && !is_array(verify) {
            throw new \Yaf\Exception\RouterFailed("Expects an array as verify parameter");
        }
        let this->_route = match;
        let this->_default =  (array) route;
        let this->_maps =  (array) map;
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
        var requestUri, baseuri, path, res, values;
        let values=[];
        let requestUri =  request->getRequestUri();
        let baseuri =  request->getBaseUri();
        
        if requestUri != "" && baseuri != "" && stripos(requestUri, baseuri) !== false {
            let path =  substr(requestUri, strlen(baseuri));
        } else {
            let path = requestUri;
        }
        let path =  urldecode(path);
        let res =  preg_match(this->_route, path, values);
        
        if res === 0 {
            
            return false;
        }
        let values =  this->_getMappedValues(values);
        
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
     * Uses user provided map array which consists
     * of index => name parameter mapping. If map is not found,
     * it returns nothing.
     *
     * @param  array   $values Indexed or associative array of values to map
     * @return array   An array of mapped values
     */
    protected function _getMappedValues(array values) -> array
    {
        var tempReturn, key, value, index;
        let tempReturn =  [];
        for key, value in values {
            if is_int(key) {
                if array_key_exists(key, this->_maps) {
                    let index = this->_maps[key];
                    let tempReturn[index] = value;
                }
            } else {
                let tempReturn[key] = value;
            }
        }
        return tempReturn;
    }

}