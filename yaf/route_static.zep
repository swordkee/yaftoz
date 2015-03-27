/**
 * StaticRoute is used for managing static URIs.
 *
 */
/**
 * @namespace
 */
namespace Yaf;

class Route_Static implements Route_Interface
{
    /**
     * Class constructor
     *
     */
    public function __construct() -> void
    {
    }
    
    /**
     * @todo this method is not used anywhere
     *
     * @param string $uri
     * @return bool
     */
    public function match(string uri) -> bool
    {
        return true;
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
        var requestUri, baseuri, path, module, controller, action, rest, actionPrefer, params,  numSegs, i, key, val;

        let requestUri =  request->getRequestUri();
        let baseuri =  request->getBaseUri();

        if requestUri != "" && baseuri != "" && stripos(requestUri, baseuri) === 0 {
            let path =  substr(requestUri, strlen(baseuri));
        } else {
            let path = requestUri;
        }
        let module =  null;
        let controller =  null;
        let action =  null;
        let rest =  null;
        let path =  trim(path, Router::URI_DELIMITER);

        if path != "" {
            let path =  explode(Router::URI_DELIMITER, path);
            let path =  array_filter(path, "strlen");

            if Application::isModuleName(path[0]) {
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
            let rest =  implode(Router::URI_DELIMITER, path);
            let actionPrefer =  g::iniGet("yaf.action_prefer");

            if (module == null && controller == null && action == null) {
                if (actionPrefer == true) {
                   let action = rest;
                } else {
                   let controller = rest;
                }
                let rest = null;
            } elseif (module == null && action == null && rest == null) {
                if (actionPrefer == true) {
                   let action = controller;
                   let controller = null;
                }
            } elseif (controller == null && action == null && rest != null) {
                let controller = module;
                let action = rest;
                let module = null;
                let rest = null;
            } elseif (action == null && rest == null) {
                let action = controller;
                let controller = module;
                let module = null;
            } elseif (controller == null && action == null) {
                let controller = module;
                let action = rest;
                let module = null;
                let rest = null;
            } elseif (action == null) {
                let action = rest;
                let rest = null;
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
                let path =  explode(Router::URI_DELIMITER, rest);
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
    public function getInstance(array config)
    {
        return new self();
    }

}