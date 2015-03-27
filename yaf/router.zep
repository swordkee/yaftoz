/**
 * Yaf_Router is the standard framework router.
 */
/**
 * @namespace
 */
namespace Yaf;
use Yaf\Request_Abstract;
class Router
{
    /**
     * Array of routes to match against
     *
     * @var array
     */
    protected _routes = [];
    /**
     * Currently matched route
     *
     * @var string
     */
    protected _current = null;
    const URI_DELIMITER = "/";
    const URI_VARIABLE = ":";
    const YAF_DEFAULT_EXT = "php";
    const YAF_ROUTER_DEFAULT_ACTION = "index";
    const YAF_ROUTER_DEFAULT_CONTROLLER = "Index";
    const YAF_ROUTER_DEFAULT_MODULE = "Index";
    public function __construct() -> void
    {
        var defaultRoute;
    
        let defaultRoute =  g::get("default_route");
        
        if defaultRoute != null {
            this->addRoute("_default", this->_getRouteFromArray(defaultRoute));
        } else {
            this->addRoute("_default", new Route_Static());
        }
    }
    
    /**
     * Add route to the route chain
     *
     * @param  string $name Name of the route
     * @param  Yaf_Route_Interface $route Instance of the route
     * @return Yaf_Router
     */
    public function addRoute(string name, <Route_Interface> route)
    {
        let this->_routes[name] = route;
        
        return this;
    }
    
    /**
     *
     * Example INI:
     * routes.archive.type = "simple"
     * routes.archive.module = Index
     * routes.archive.controller = archive
     * routes.archive.action = show
     *
     * routes.news.type = "static"
     * routes.news.route = "news"
     *
     * And finally after you have created a Yaf_Config with above ini:
     * $router = new Yaf_Router();
     * $router->addConfig($config);
     *
     * @param  array|Yaf_Config $config  Configuration object
     * @throws Yaf_Router_Exception
     * @return Yaf_Router
     */
    public function addConfig(config)
    {
        var name, entry, route;
    
        
        if is_array(config) {
            echo "not allowed";
        } else {
            
            if (config instanceof Config_Abstract) {
                let config =  config->toArray();
            } else {
                throw new Exception\RouterFailed("Expecting Array or Yaf_Config_Abstract instance");
            }
        }
        let name =  key(config);
        for entry in config {
            let route =  this->_getRouteFromArray(entry);
            
            if route != null {
                
                if (route instanceof Route_Interface) {
                    this->addRoute(name, route);
                } else {
                    this->addRoute(name, route);
                }
            } else {
                
                if is_string(name) {
                    throw new Exception\RouterFailed("Unable to initialize route named " . name);
                } else {
                    throw new Exception\RouterFailed("Unable to initialize route at index " . name);
                }
            }
            next(config);
            let name =  key(config);
        }
        return this;
    }
    
    /**
     * Get a route from a config instance
     *
     * @param  Yaf_Config_Abstract $info
     * @return Yaf_Route_Interface
     */
    protected function _getRouteFromConfig(<Config_Abstract> info)
    {
        var useNamespace, tmpClass, route, e;
    
        let useNamespace =  g::iniGet("yaf.use_namespace");
        
        if useNamespace {
            let tmpClass =  isset info["type"] ? "\\Yaf\\Route\\" . ucfirst(info["type"]) : "\\Yaf\\Route\\Static";
        } else {
            let tmpClass =  isset info["type"] ? "Yaf_Route_" . ucfirst(info["type"]) : "Yaf_Route_Static";
        }
        try {
            let route =  call_user_func([tmpClass, "getInstance"], info);
        } catch \Exception, e {
            return null;
        }
        return route;
    }
    
    /**
     * Get a route from an array
     *
     * @param  array $info
     * @return Yaf_Route_Interface
     */
    protected function _getRouteFromArray(array info)
    {
        var useNamespace, tmpClass, route, e;
    
        let useNamespace =  g::iniGet("yaf.use_namespace");
        
        if useNamespace {
            let tmpClass =  isset info["type"] ? "\\Yaf\\Route\\" . ucfirst(info["type"]) : "\\Yaf\\Route\\Static";
        } else {
            let tmpClass =  isset info["type"] ? "Yaf_Route_" . ucfirst(info["type"]) : "Yaf_Route_Static";
        }
        try {
            let route =  call_user_func([tmpClass, "getInstance"], info);
        } catch \Exception, e {
            return null;
        }
        
        return route;
    }
    
    /**
     * Retrieve a currently matched route
     *
     * @throws Yaf_Exception_RouterFailed
     * @return Yaf_Route_Interface Route object
     */
    public function getCurrentRoute()
    {
        
        return this->_current;
    }
    
    /**
     * Retrieve a named route
     *
     * @param string $name Name of the route
     * @throws Yaf_Exception_RouterFailed
     * @return Yaf_Route_Interface Route object
     */
    public function getRoute(string name)
    {
        
        if !isset this->_routes[name] {
            
            return null;
        }
        
        return this->_routes[name];
    }
    
    /**
     * Retrieve an array of routes added to the route chain
     *
     * @return array All of the defined routes
     */
    public function getRoutes() -> array
    {
        
        return this->_routes;
    }
    
    /**
     * Find a matching route to the current Request and inject
     * returning values to the Request object.
     *
     * @return bool if there is a valid route
     */
    public function route(<Request_Abstract> request) -> bool
    {
        var routeMatched, name, route, ret;
    
        // Find the matching route
        let routeMatched =  false;
        for name, route in array_reverse(this->_routes, true) {
            let ret =  route->route(request);
            if ret != false {
                let this->_current = name;
                let routeMatched =  true;
                break;
            }
        }
        
        if !routeMatched {
            
            return false;
        } else {
            request->setRouted(true);
            
            return true;
        }
        
        return false;
    }

}