/**
 * Yaf Controller Abstract
 */
/**
 * @namespace
 */
namespace Yaf;

abstract class Controller_Abstract
{
    public actions = null;
    protected _module;
    protected _name = "";
    /**
     * Yaf_Request_Abstract object wrapping the request environment
     * @var Yaf_Request_Abstract
     */
    protected _request = null;
    /**
     * Yaf_Response_Abstract object wrapping the response
     * @var Yaf_Response_Abstract
     */
    protected _response = null;
    /**
     * Array of arguments provided to the constructor, minus the
     * {@link $_request Request object}.
     * @var array
     */
    protected _invokeArgs = [];
    /**
     * View object
     * @var Yaf_View_Interface
     */
    protected _view = null;
    /**
     * Class constructor
     *
     * The request and response objects should be registered with the
     * controller, as should be any additional optional arguments; these will be
     * available via {@link getRequest()}, {@link getResponse()}, and
     * {@link getInvokeArgs()}, respectively.
     *
     * @param Yaf_Request_Abstract $request
     * @param Yaf_Response_Abstract $response
     * @param Yaf_View_Interface $view
     * @param array $invokeArgs Any additional invocation arguments
     * @return void
     */
    public function __construct(<Request_Abstract> request,
      <Response_Abstract> response,
      <View_Interface>view,
      array invokeArgs = [])
    {
        let this->_request = request;
        let this->_response = response;
        let this->_view = view;
        let this->_invokeArgs = invokeArgs;
        let this->_module =  request->getModuleName();
        let this->_name =  get_class(this);
        this->init();
    }
    
    /**
     * Render a view
     *
     * Renders a view. By default, views are found in the view script path as
     * <controller>/<action>.phtml. You may change the script suffix by
     * resetting {@link $viewSuffix}.
     *
     *
     * @see Yaf_Response_Abstract::appendBody()
     * @param  string|null $tpl Defaults to action registered in request object
     * @param  array $parameters  add those variables to the view
     * @return void
     */
    public function display(tpl = null, array parameters = [])
    {
        var view, script;
    
        let view =  this->initView();
        let script =  this->getViewScript(tpl);
        view->display(script, parameters);
    }
    
    /**
     * Forward to another controller/action.
     *
     * It is important to supply the unformatted names, i.e. "article"
     * rather than "ArticleController".  The dispatcher will do the
     * appropriate formatting when the request is received.
     *
     * If only an action name is provided, forwards to that action in this
     * controller.
     *
     * If an action and controller are specified, forwards to that action and
     * controller in this module.
     *
     * Specifying an action, controller, and module is the most specific way to
     * forward.
     *
     * A fourth argument, $params, will be used to set the request parameters.
     * If either the controller or module are unnecessary for forwarding,
     * simply pass null values for them before specifying the parameters.
     *
     * @todo this should be checked again within a test
     * @param string $action
     * @param string $controller
     * @param string $module
     * @param array $args
     * @return void
     */
    public function forward(string module, string controller = null, string action = null, array args = null)
    {
        var request;
    
        let request =  this->getRequest();
        
        if args !== null {
            request->setParams(args);
        }
        
        if controller == null && action == null {
            let action = module;
            let module =  null;
        } else { 
        
        if action == null {
            let action = controller;
            let controller = module;
            let module =  null;
        }
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
        request->setActionName(action)->setDispatched(false);
    }
    
    /**
     * Return a single invocation argument
     *
     * @param string $key
     * @return mixed
     */
    public function getInvokeArg(string key)
    {
        
        if isset this->_invokeArgs[key] {
            
            return this->_invokeArgs[key];
        }
        
        return null;
    }
    
    /**
     * Return the array of constructor arguments (minus the Request object)
     *
     * @return array
     */
    public function getInvokeArgs() -> array
    {
        
        return this->_invokeArgs;
    }
    
    /**
     * return the current module name
     */
    public function getModuleName()
    {
        
        return this->_module;
    }
    
    /**
     * Return the Request object
     *
     * @return Zend_Controller_Request_Abstract
     */
    public function getRequest()
    {
        
        return this->_request;
    }
    
    /**
     * Return the Response object
     *
     * @return Yaf_Response_Abstract
     */
    public function getResponse()
    {
        
        return this->_response;
    }
    
    /**
     * Return the View object
     *
     * @return Yaf_View_Interface
     */
    public function getView()
    {
        
        return this->_view;
    }
    
    public function getViewpath()
    {
        var view;
    
        let view =  this->getView();
        
        return view->getScriptPath();
    }
    
    /**
     * Initialize object
     *
     * Called from {@link __construct()} as final step of object instantiation.
     *
     * @return void
     */
    public function init()
    {
    }
    
    /**
     * Initialize View object
     * @todo this does nothing for now
     *
     * @return Yaf_View_Interface
     */
    public function initView()
    {
        
        return this->_view;
    }
    
    /**
     * Render a view
     *
     * Renders a view. By default, views are found in the view script path as
     * <controller>/<action>.phtml. You may change the script suffix by
     * resetting {@link $viewSuffix}.
     *
     *
     * @see Yaf_Response_Abstract::appendBody()
     * @param  string|null $tpl Defaults to action registered in request object
     * @param  array $parameters  add those variables to the view
     * @return void
     */
    public function render(tpl = null, array parameters = [])
    {
        var view, script;
    
        let view =  this->initView();
        let script =  this->getViewScript(tpl);
        
        return view->render(script, parameters);
    }
    
    /**
     * Redirect to another URL
     *
     * @param string $url
     * @return void
     */
    public function redirect(string url)
    {
        var response;
    
        let response =  this->getResponse();
        response->setRedirect(url);
    }
    
    public function setViewpath(templateDir) -> void
    {
        var view;
    
        let view =  this->getView();
        view->setScriptPath(templateDir);
    }
    
    /**
     * Construct view script path
     *
     * Used by render() and display to determine the path to the view script.
     *
     * @param  string $action Defaults to action registered in request object
     * @return string
     * @throws InvalidArgumentException with bad $action
     */
    protected function getViewScript(string action = null) -> string
    {
        var request, script, controller,tmpAction;

        let request =  this->getRequest();
        if action === null {
            let tmpAction =  request->getActionName();
            let action =  tmpAction;
        } elseif !is_string(action) {
            throw new \InvalidArgumentException("Invalid action for view rendering");
        }

        let action =  str_replace("_", DIRECTORY_SEPARATOR, strtolower(action));
        let script =  action . "." . g::get("view_ext");
        let controller =  request->getControllerName();
        
        if controller != null {
            let controller =  str_replace("_", DIRECTORY_SEPARATOR, strtolower(controller));
        }
        let script =  controller . DIRECTORY_SEPARATOR . script;
        
        return script;
    }

}