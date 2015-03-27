/**
 * Yaf Dispatcher
 */
/**
 * @namespace
 */
namespace Yaf;

class Dispatcher
{
    /**
     * Instance of Yaf_Router_Interface
     * @var Yaf_Router
     */
    protected _router = null;
    /**
     * View object
     * @var Yaf_View_Interface
     */
    protected _view = null;
    /**
     * Instance of Yaf_Request_Abstract
     * @var Yaf_Request_Abstract
     */
    protected _request = null;
    /**
     * holds the references to the plugins
     * @var array
     */
    protected _plugins = [];
    /**
     * Singleton instance
     * @var Yaf_Dispatcher
     */
    protected static _instance = null;
    /**
     * Whether or not to enable view.
     * @var boolean
     */
    protected _auto_render = true;
    /**
     * Whether or not to return the response prior to rendering output while in
     * {@link dispatch()}; default is to send headers and render output.
     * @var boolean
     */
    protected _returnResponse = false;
    protected _instantly_flush = false;
    protected _default_module = "";
    protected _default_controller = "";
    protected _default_action = "";
    public function autoRender(flag)
    {
        if !is_bool(flag) {
            return this->_auto_render;
        } else {
            let this->_auto_render = flag;
        }
    }
    
    /**
     * Set the throwExceptions flag and retrieve current status
     *
     * Set whether exceptions encounted in the dispatch loop should be thrown
     * or caught and trapped in the response object.
     *
     * Default behaviour is to trap them in the response object; call this
     * method to have them thrown.
     *
     * Passing no value will return the current value of the flag; passing a
     * boolean true or false value will set the flag and return the current
     * object instance.
     *
     * @param boolean $flag Defaults to null (return flag state)
     * @return boolean|Yaf_Dispatcher when used as a setter,
     * returns object; as a getter, returns boolean
     */
    public function catchException(boolean flag = null)
    {
        if flag !== null {
            g::set("catchException", flag );
            return this;
        }
        
        return g::get("catchException");
    }
    
    /**
     * Enforce singleton; disallow cloning
     *
     * @return void
     */
    protected function __clone()
    {
    }
    
    /**
     * Constructor
     *
     * Instantiate using {@link getInstance()}; dispatcher is a singleton
     * object.
     *
     * @return void
     */
    protected function __construct()
    {
    }
    
    public function disableView() -> void
    {
        let this->_auto_render =  false;
    }
    
    /**
     * Dispatch an HTTP request to a controller/action.
     *
     * @param Yaf_Request_Abstract|null $request
     * @return void|Yaf_Response_Abstract
     */
    public function dispatch(<Request_Abstract> request = null)
    {
        var response, router, plugin, e, view, nested/*, em*/;
    
        /**
         * Instantiate default request object (HTTP version) if none provided
         */
        
        if request == null {
            let request =  this->getRequest();
        } else {
            this->setRequest(request);
        }
        
        if !(request instanceof Request_Abstract) {
            throw new Exception\TypeError("Expect a Yaf_Request_Abstract instance");
        }
        
        if request instanceof Request\Http {
            let response =  new Response\Http();
        } else { 
        
        if request instanceof Request\Simple {
            let response =  new Response\Cli();
        }
        }
        /**
         * Initialize router
         */
        let router =  this->getRouter();
        
        if !request->isRouted() {
            /**
             * Notify plugins of router startup
             */
            for plugin in this->_plugins {
                plugin->routerStartup(request, response);
            }
            /*try {
                //@todo here seems there is 2 type of routes
                router->route(request);
            } catch \Exception, e {
                
                if this->throwException() == true {
                    throw e;
                }
            }*/
            router->route(request);
            this->_fixDefault(request);
            /**
             * Notify plugins of router shutdown
             */
            for plugin in this->_plugins {
                plugin->routerShutdown(request, response);
            }
        } else {
            this->_fixDefault(request);
        }
        let view =  this->initView();
        /**
         * Notify plugins of dispatch loop startup
         */
        for plugin in this->_plugins {
            plugin->dispatchLoopStartup(request, response);
        }
        let nested =  g::iniGet("yaf.forward_limit");
        // Begin dispatch
        try {
            /**
             * Route request to controller/action, if a router is provided
             */
            do {
                /**
                 * Notify plugins of dispatch startup
                 */
                for plugin in this->_plugins {
                    plugin->preDispatch(request, response);
                }
                /**
                 * Dispatch request
                 */
                this->handle(request, response, view);
                this->_fixDefault(request);
                /**
                 * Notify plugins of dispatch completion
                 */
                for plugin in this->_plugins {
                    plugin->postDispatch(request, response);
                }
                let nested--;
            } while (!request->isDispatched() && nested > 0);
            /**
             * Notify plugins of dispatch loop completion
             */
            for plugin in this->_plugins {
                plugin->dispatchLoopShutdown(request, response);
            }
        } catch \Exception, e {
            if this->catchException() {
                //Try load module error controller, do same as Yaf
                
                if request->getModuleName() != this->_default_module {
                   // try {
                        request->setControllerName("Error");
                        request->setActionName("error");
                        request->setParam("exception", e);
                        request->setException(e);
                        this->handle(request, response, view);
                        //auto response
                        response->response();
                        response->clearBody();
                        
                        return false;
                   // } catch \Exception, em {
                    //}
                }
                //Try load default module error controller, do same as Yaf
                //try {
                    request->setModuleName(this->_default_module);
                    request->setControllerName("Error");
                    request->setActionName("error");
                    request->setParam("exception", e);
                    request->setException(e);
                    this->handle(request, response, view);
                    //auto response
                    response->response();
                    response->clearBody();
                    
                    return false;
                //} catch \Exception, em {
                    //Throw original exception
                    
                //    if this->throwException() {
                //        throw e;
                //    } else {
                //        Exception::trigger_error(e->getMessage(), E_USER_ERROR);
                 //   }
                //}
            } else {
                
                if this->throwException() {
                    throw e;
                } else {
                    Exception::trigger_error(e->getMessage(), E_USER_ERROR);
                }
            }
        }
        
        if nested == 0 && !request->isDispatched() {
            throw new Exception\DispatchFailed("The max dispatch nesting " . g::iniGet("yaf.forward_limit") . " was reached");
        }
        
        if this->returnResponse() == false {
            response->response();
            response->clearBody();
        }
        
        return response;
    }
    
    protected function handle(
    <Request_Abstract> request,
    <Response_Abstract> response,
    <View_Interface> view)
    {
        var app, appDir, module, controllerName, className, controller, viewDir, templateDir, action, actionMethod, methodParams, ret, actionName, actionController ;
    
        request->setDispatched(true);
        let app =  this->getApplication();
        let appDir =  app->getAppDirectory();
        
        if appDir == "" {
            throw new Exception\StartupError("Yaf_Dispatcher requires " . "Yaf_Application(which set the application.directory) " . "to be initialized first.");
        }
        let module =  request->getModuleName();
        
        if empty(module) {
            throw new Exception\DispatchFailed("Unexcepted an empty module name");
        }
        
        if !Application::isModuleName(module) {
            throw new Exception\LoadFailed\Module("There is no module " . module);
        }
        let controllerName =  request->getControllerName();
        
        if empty(controllerName) {
            throw new Exception\DispatchFailed("Unexcepted an empty controller name");
        }
        let className =  this->getController(appDir, module, controllerName);
        
        if !className {
            
            return false;
        }
        let controller =  new {className}(request, response, view);
        
        if !(controller instanceof Controller_Abstract) {
            throw new Exception\TypeError("Controller must be an instance of Yaf_Controller_Abstract");
        }
        let viewDir =  view->getScriptPath();
        //template dir might be set from the __construct
        
        if empty(viewDir) {
            let templateDir = "";
            
            if this->_default_module == module {
                let templateDir =  appDir . DIRECTORY_SEPARATOR . Loader::YAF_VIEW_DIRECTORY_NAME;
            } else {
                let templateDir =  appDir . DIRECTORY_SEPARATOR . Loader::YAF_MODULE_DIRECTORY_NAME . DIRECTORY_SEPARATOR . module . DIRECTORY_SEPARATOR . Loader::YAF_VIEW_DIRECTORY_NAME;
            }
            view->setScriptPath(templateDir);
            //unset(templateDir);
        
        }
        let action =  request->getActionName();
        let actionMethod =  action . "Action";
        
        if method_exists(controller, actionMethod) {
            //Get all action method parameters
            let methodParams =  this->getActionParams(className, actionMethod);
            
            if methodParams == null {
                let ret =  call_user_func([controller, actionMethod]);
            } else {
                let ret =  call_user_func_array([controller, actionMethod], this->prepareActionParams(request, methodParams));
            }
            
            if is_bool(ret) && ret == false {
                
                return true;
            }
        } else { 
        let actionName =  this->getAction(appDir, controller, action, module);
        if actionName != null {
            let actionController =  new {actionName}(request, response, view);
            
            if !(actionController instanceof Action_Abstract) {
                throw new Exception\TypeError("Action must be an instance of Yaf_Action_Abstract");
            }
            actionController->setController(controller);
            //check if not in actions vars we have the action
            let actionMethod = "execute";
            
            if method_exists(actionController, actionMethod) {
                //Get all action method parameters
                let methodParams =  this->getActionParams(get_class(actionController), actionMethod);
                let ret =  null;
                
                if methodParams == null {
                    let ret =  call_user_func([actionController, actionMethod]);
                } else {
                    let ret =  call_user_func_array([actionController, actionMethod], this->prepareActionParams(request, methodParams));
                }
                
                if is_bool(ret) && ret == false {
                    
                    return true;
                }
            } else {
                throw new Exception\LoadFailed\Action("There is no method " . actionMethod . " in " . get_class(controller) . "::actions");
            }
        }
         else {
            
            return false;
        }}
        
        if this->_auto_render == true {
            if this->_instantly_flush == true {
                controller->display(action);
            } else {
                let ret =  controller->render(action);
                response->appendBody(ret);
            }
        }
        //let controller =  null;
    }

    protected function getAction(appDir, <Controller_Abstract> controller, action, module)
    {
        var nameSeparator, actionPath, actionUpper, tmpClassname, actionDir;
    
        let nameSeparator =  g::iniGet("yaf.name_separator");
        
        if is_array(controller->actions) {
            
            if isset controller->actions[action] {
                let actionPath =  appDir . DIRECTORY_SEPARATOR . controller->actions[action];
                
                if Loader::import(actionPath) {
                    let actionUpper =  this->_formatName(action);
                    
                    if g::iniGet("yaf.name_suffix") == true {
                        let tmpClassname =  actionUpper . nameSeparator . "Action";
                    } else {
                        let tmpClassname =  "Action" . nameSeparator . actionUpper;
                    }
                    
                    if !class_exists(tmpClassname, false) {
                        throw new Exception\LoadFailed\Action("Could not find action " . tmpClassname . " in " . actionPath);
                    }
                    
                    return tmpClassname;
                } else {
                    throw new Exception\LoadFailed\Action("Could not find action script " . actionPath);
                }
            } else {
                throw new Exception\LoadFailed\Action("There is no method " . action . "Action in " . get_class(controller) . "::actions");
            }
        } else {
            
            if g::iniGet("yaf.st_compatible") {
                let actionDir = "";
                
                if this->_default_module == module {
                    let actionDir =  appDir . DIRECTORY_SEPARATOR . "actions";
                } else {
                    let actionDir =  appDir . DIRECTORY_SEPARATOR . "modules" . DIRECTORY_SEPARATOR . module . DIRECTORY_SEPARATOR . "actions";
                }
                let actionUpper =  this->_formatName(action);
                
                if g::iniGet("yaf.name_suffix") == true {
                    let tmpClassname =  actionUpper . nameSeparator . "Action";
                } else {
                    let tmpClassname =  "Action" . nameSeparator . actionUpper;
                }
                
                if !class_exists(tmpClassname, false) {
                    
                    if !Loader::getInstance()->internal_autoload(actionUpper, actionDir) {
                        throw new Exception\LoadFailed\Action("Could not find action script " . actionDir);
                    }
                }
                
                if !class_exists(tmpClassname, false) {
                    throw new Exception\LoadFailed\LoadFailed("Could not find class " . tmpClassname . " in action script " . actionDir);
                }
                
                return tmpClassname;
            } else {
                throw new Exception\LoadFailed\Action("There is no method " . action . "Action in " . get_class(controller));
            }
        }
        
        return null;
    }

    protected function prepareActionParams(request, methodParams)
    {
        var data, params, param, name;
    
        
        let data =  [];
        // It will sent to the action
        let params =  request->getParams();
        for param in methodParams {
            let name =  param->getName();
            
            if param->isOptional() {
                // If there is no data to send, use the default
                
                let data[name] =  !empty(params[name]) ? params[name] : param->getDefaultValue();
            } elseif empty(params[name]) {
                // The parameter cannot be empty as defined
                throw new Exception("Parameter: " . name . " cannot be empty");
            } else {
                let data[name] = params[name];
            }
        }
        
        return data;
    }
    
    protected function getActionParams(className, action)
    {
        var funcRef, paramsRef;
    
        let funcRef =  new \ReflectionMethod(className, action);
        let paramsRef =  funcRef->getParameters();
        
        return paramsRef;
    }
    
    protected function getController(appDir, module, controller)
    {
        var controllerDir, nameSeparator, classname;
    
        let controllerDir = "";
        
        if this->_default_module == module {
            let controllerDir =  appDir . DIRECTORY_SEPARATOR . Loader::YAF_CONTROLLER_DIRECTORY_NAME;
        } else {
            let controllerDir =  appDir . DIRECTORY_SEPARATOR . Loader::YAF_MODULE_DIRECTORY_NAME . DIRECTORY_SEPARATOR . module . DIRECTORY_SEPARATOR . Loader::YAF_CONTROLLER_DIRECTORY_NAME;
        }
        let nameSeparator =  g::iniGet("yaf.name_separator");
        
        if g::iniGet("yaf.name_suffix") == true {
            let classname =  controller . nameSeparator . "Controller";
        } else {
            let classname =  "Controller" . nameSeparator . controller;
        }
        
        if !class_exists(classname, false) {
            
            if !Loader::getInstance()->internal_autoload(controller, controllerDir) {
                throw new Exception\LoadFailed\Controller("Could not find controller script " . controllerDir . DIRECTORY_SEPARATOR . str_replace("_", DIRECTORY_SEPARATOR, controller) . "." . g::get("ext"));
            }
        }
        
        if !class_exists(classname, false) {
            throw new Exception\LoadFailed\LoadFailed("Could not find class " . classname . " in controller script " . controllerDir);
        }
        
        return classname;
    }
    
    protected function _fixDefault(<Request_Abstract> request) -> void
    {
        var module, controller, action;
    
        let module =  request->getModuleName();
        
        if empty(module) || !is_string(module) {
            request->setModuleName(this->_default_module);
        } else {
            request->setModuleName(ucfirst(module));
        }
        let controller =  request->getControllerName();
        
        if empty(controller) || !is_string(controller) {
            request->setControllerName(this->_default_controller);
        } else {
            request->setControllerName(this->_formatName(controller));
        }
        let action =  request->getActionName();
        
        if empty(action) || !is_string(action) {
            request->setActionName(this->_default_action);
        } else {
            request->setActionName(strtolower(action));
        }
    }
    
    protected function _formatName(unformatted)
    {
        var segments, segment, key;
    
        // we have namespace
        let segments =  explode("\\", unformatted);
        
        if segments && count(segments) > 1 {
            for key, segment in segments {
                let segment =  preg_replace("/[^a-z0-9 ]/", "", strtolower(segment));
                let segments[key] = str_replace(" ", "", ucwords(segment));
            }
            
            return implode("\\", segments);
        }
        //we have _
        let segments =  explode("_", unformatted);
        
        if segments {
            for key, segment in segments {
                let segment =  preg_replace("/[^a-z0-9 ]/", "", strtolower(segment));
                let segments[key] = str_replace(" ", "", ucwords(segment));
            }
            
            return implode("_", segments);
        }
    }
    
    public function enableView() -> void
    {
        let this->_auto_render =  true;
    }
    
    public function flushInstantly(flag)
    {
        
        if !is_bool(flag) {
            return this->_instantly_flush;
        } else {
            let this->_instantly_flush = flag;
        }
        
        return this;
    }
    
    /**
     * returns the application
     *
     * @return Yaf_Application
     */
    public function getApplication()
    {
        
        return Application::app();
    }
    
    /**
     * Singleton instance
     *
     * @return Yaf_Dispatcher
     */
    public static function getInstance()
    {
        if self::_instance === null {
            let self::_instance =  new self();
            self::_instance->setDefaultAction(g::get("default_action"));
            self::_instance->setDefaultController(g::get("default_controller"));
            self::_instance->setDefaultModule(g::get("default_module"));
            //let self::_instance[_router] = new Router();
            //let self::_instance->_router = new Router();
        }
        
        return self::_instance;
    }
    
    /**
     * Return the request object.
     *
     * @return null|Yaf_Request_Abstract
     */
    public function getRequest()
    {
        
        return this->_request;
    }
    
    /**
     * Return the router object.
     * @return Yaf_Router
     */
    public function getRouter()
    {
        
        return this->_router;
    }
    
    public function initView(templates_dir = null, options = [])
    {
        if this->_view == null {
            let this->_view =  new View\Simple(templates_dir, options);
        }
        
        return this->_view;
    }
    
    /**
     * Register a plugin.
     *
     * @param  Yaf_Plugin_Abstract $plugin
     * @return Yaf_Dispatcher
     */
    public function registerPlugin(<Plugin_Abstract> plugin)
    {
        let this->_plugins[] = plugin;
        
        return this;
    }
    
    /**
     * Set whether {@link dispatch()} should return the response without first
     * rendering output. By default, output is rendered and dispatch() returns
     * nothing.
     *
     * @param boolean $flag
     * @return boolean|Yaf_Dispatcher Used as a setter,
     * returns object; as a getter, returns boolean
     */
    public function returnResponse(boolean flag = null)
    {
        if flag === true {
            let this->_returnResponse =  true;
            return this;
        } elseif flag === false {
            let this->_returnResponse =  false;
            return this;
        }
        
        return this->_returnResponse;
    }
    
    /**
     * Set the default action
     *
     * @param string $action
     * @return Yaf_Dispatcher
     */
    public function setDefaultAction(string action)
    {
        let this->_default_action =  (string) action;
        
        return this;
    }
    
    /**
     * Set the default controller
     *
     * @param string $controller
     * @return Yaf_Dispatcher
     */
    public function setDefaultController(string controller)
    {
        let this->_default_controller =  ucfirst((string) controller);
        
        return this;
    }
    
    /**
     * Set the default module name
     *
     * @param string $module
     * @return Yaf_Dispatcher
     */
    public function setDefaultModule(string module)
    {
        if Application::isModuleName(module) || strtolower(module) == "index" {
            let this->_default_module =  ucfirst((string) module);
        }
        return this;
    }
    
    public function setErrorHandler(callback, error_types = "E_ALL") -> void
    {
        set_error_handler(callback, error_types);
    }
    
    /**
     * Set the request object.
     * @param Yaf_Request_Abstract $request
     * @return Yaf_Dispatcher
     */
    public function setRequest(<Request_Abstract> request)
    {
        let this->_request = request;
        
        return this;
    }
    
    /**
     * Set the view object.
     *
     * @param Yaf_View_Interface $view
     * @return Yaf_Dispatcher
     */
    public function setView(<View_Interface> view)
    {
        let this->_view = view;
        
        return this;
    }
    
    /**
     * Enforce singleton; disallow serialization
     *
     * @return void
     */
    protected function __sleep()
    {
    }
    
    /**
     * Set the throwExceptions flag and retrieve current status
     *
     * Set whether exceptions encounted in the dispatch loop should be thrown
     * or caught and trapped in the response object.
     *
     * Default behaviour is to trap them in the response object; call this
     * method to have them thrown.
     *
     * Passing no value will return the current value of the flag; passing a
     * boolean true or false value will set the flag and return the current
     * object instance.
     *
     * @param boolean $flag Defaults to null (return flag state)
     * @return boolean|Yaf_Dispatcher Used as a setter,
     *     returns object; as a getter, returns boolean
     */
    public function throwException(boolean flag = null)
    {
        
        if flag !== null {
            g::set("throwException",  flag);
            
            return this;
        }
        
        return g::get("throwException");
    }
    
    /**
     * Enforce singleton; disallow serialization
     *
     * @return void
     */
    protected function __wakeup()
    {
    }

}