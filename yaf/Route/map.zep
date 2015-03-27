/**
 * Yaf Route Map for hash based ajax URL
 */
/**
 * @namespace
 */
namespace Yaf\Route;
use Yaf\Response_Abstract as Response_Abstract;
use Yaf\Request_Abstract as Request_Abstract;
class Map implements \Yaf\Route_Interface
{
    protected _ctlPrefer = false;
    protected _delimiter = "";
    /**
     * Class constructor
     * @param string $module
     * @param string $controller
     * @param string $action
     */
    public function __construct(controller_prefer = false, delimiter = "#!") -> void
    {
        
        if is_bool(controller_prefer) {
            let this->_ctlPrefer = controller_prefer;
        }
        
        if is_string(delimiter) && delimiter != "" {
            let this->_delimiter = delimiter;
        }
    }
    
    /**
     * Processes a request and sets its controller and action.  If
     * no route was possible, default route is set.
     *
     * @param  Yaf_Request_Abstract
     * @return Yaf_Request_Abstract|boolean
     */
    public function route(<Request_Abstract> request)
    {
        var requestUri, baseuri, path, rest, queryStringPos, route, params, numSegs, i, key, val;
    
        let requestUri =  request->getRequestUri();
        let baseuri =  request->getBaseUri();
        
        if requestUri != "" && baseuri != "" && stripos(requestUri, baseuri) === 0 {
            let path =  substr(requestUri, strlen(baseuri));
        } else {
            let path = requestUri;
        }
        let path =  trim(urldecode(path), \Yaf\Router::URI_DELIMITER);
        let rest = "";
        
        if is_string(this->_delimiter) && this->_delimiter != "" {
            let queryStringPos =  strpos(path, this->_delimiter);
            if queryStringPos !== false {
                let rest =  substr(path, queryStringPos + strlen(this->_delimiter), strlen(path) - 1);
                let path =  substr(path, 0, queryStringPos);
            }
        }
        let route = "";
        
        if path != "" && path != "/" {
            let route =  str_replace(\Yaf\Router::URI_DELIMITER, "_", trim(path, \Yaf\Router::URI_DELIMITER));
        }
        
        if route != "" {
            
            if this->_ctlPrefer == true {
                request->setControllerName(route);
            } else {
                request->setActionName(route);
            }
        }
        
        let params =  [];
        
        if rest != null && trim(rest) != "" {
            let path =  explode(\Yaf\Router::URI_DELIMITER, trim(rest, \Yaf\Router::URI_DELIMITER));
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
        
        return true;
    }
    
    /**
     * used to create routes on the fly from config
     *
     * @param array $config
     */
    public static function getInstance(array config)
    {
        var controllerPrefer, delimiter;
    
        let controllerPrefer =  false;
        
        if isset config["controllerPrefer"] && is_bool(config["controllerPrefer"]) {
            let controllerPrefer = config["controllerPrefer"];
        }
        let delimiter = "#!";
        
        if isset config["delimiter"] {
            let delimiter = config["delimiter"];
        }
        
        return new self(controllerPrefer, delimiter);
    }

}