/**
 * Yaf Application
 */
/**
 * @namespace
 */
namespace Yaf;

class Application
{
    /**
     * @var Yaf_Config_Abstract
     */
    protected _config = null;
    /**
     *
     * @var Yaf_Dispatcher
     */
    protected _dispatcher = null;
    /**
     *
     * @var Yaf_Application
     */
    protected static _app = null;
    protected _modules = [];
    protected _running = false;
    protected _environ = null;
    protected _options = [];
    protected _errno = 0;
    protected _errmsg = "";
    public function __construct(config, env = null) -> void
    {
        var app, request, loader, tmpNamespace;

        let app =  self::app();

        if !is_null(app) {
            throw new Exception\StartupError("Only one application can be initialized");
        }
        let this->_environ = env;
        //fix default environ

        if this->_environ == null {
            let this->_environ =  g::iniGet("yaf.environ");
        }
        //define Yaf\ENVIRON
        //defined("Yaf\\ENVIRON") or define("Yaf\\ENVIRON", this->_environ);

        let config =  this->_loadConfig(config);

        if config == null || !(config instanceof Config_Abstract) || this->parseOptions(config->toArray()) != true {
            throw new Exception\StartupError("Initialization of application config failed");
        }

        let this->_config = config;
        //request initialization
        let request =  new Request\Http();

        if request == null {
            throw new Exception\StartupError("Initialization of request failed");
        }
        //dispatcher
        let this->_dispatcher =  Dispatcher::getInstance();

        if this->_dispatcher == null || !(this->_dispatcher instanceof Dispatcher) {
            throw new Exception\StartupError("Instantiation of dispatcher failed");
        }
        this->_dispatcher->setRequest(request);
        //loader initialization
        let loader =  Loader::getInstance(
        isset this->_options["local_library"] ? this->_options["local_library"] : "", g::iniGet("yaf.library"));

        if loader == null || !(loader instanceof Loader) {
            throw new Exception\StartupError("Initialization of application auto loader failed");
        }

        if isset this->_options["local_namespace"] && this->_options["local_namespace"] != "" {
            let tmpNamespace =  str_replace([",", " "], [":", ":"], this->_options["local_namespace"]);
            loader->registerLocalNamespace(tmpNamespace);
        }
        let self::_app = this;

        if g::get("throwException") == false {
            set_exception_handler([this, "exceptionHandler"]);
        }
    }

    public function __destruct() -> void
    {
    }

    public function bootstrap()
    {
        var bootstrapClass, bootstrap, loader, tmpClass, classMethods, methodNames, initMethodLength, method;

        let bootstrapClass =  Bootstrap_Abstract::YAF_DEFAULT_BOOTSTRAP;
        if isset this->_options["bootstrap"] {
            let bootstrap = this->_options["bootstrap"];
        } else {
            let bootstrap =  this->getAppDirectory() . DIRECTORY_SEPARATOR . bootstrapClass . "." . g::get("ext");
        }
        let loader =  Loader::getInstance();
        if Loader::import(bootstrap) {

            if !class_exists(bootstrapClass) {
                throw new Exception("Couldn't find class Bootstrap in " . bootstrap);
            } else {
                let bootstrap =  new {bootstrapClass}();

                if !(bootstrap instanceof Bootstrap_Abstract) {
                    throw new Exception("Expect a Yaf_Bootstrap_Abstract instance, " . get_class(bootstrap) . " give ");
                }

                if version_compare(PHP_VERSION, "5.2.6") === -1 {
                    let tmpClass =  new \ReflectionObject(bootstrap);
                    let classMethods =  tmpClass->getMethods();

                    let methodNames =  [];
                    for method in classMethods {
                        let methodNames[] = method->getName();
                    }
                } else {
                    let methodNames =  get_class_methods(bootstrap);
                }
                let initMethodLength =  strlen(Bootstrap_Abstract::YAF_BOOTSTRAP_INITFUNC_PREFIX);
                for method in methodNames {

                    if initMethodLength < strlen(method) && Bootstrap_Abstract::YAF_BOOTSTRAP_INITFUNC_PREFIX === substr(method, 0, initMethodLength) {
                        bootstrap->{method}(this->_dispatcher);
                    }
                }
            }
        } else {
            throw new Exception("Couldn't find bootstrap file " . bootstrap);
        }

        return this;
    }

    /**
     * Start Yaf_Application
     */
    public function run()
    {

        if this->_running == true {
            throw new Exception\StartupError("An application instance already run");
        } else {
            let this->_running =  true;

            return this->_dispatcher->dispatch();
        }
    }

    /**
     * Retrieve application instance
     * @return Yaf_Application
     */
    public static function app()
    {

        return self::$_app;
    }

    /**
     * Retrieve the config instance
     */
    public function getConfig()
    {

        return this->_config;
    }

    /**
     * Get Yaf_Dispatcher instance
     * @return Yaf_Dispatcher
     */
    public function getDispatcher()
    {

        return this->_dispatcher;
    }

    /**
     * Get defined module names
     */
    public function getModules()
    {

        return this->_modules;
    }

    /**
     * Retrieve environment
     */
    public function environ()
    {
        /*var env, fromIni;

        let env =  this->_environ;

        if env == null {
            let fromIni =  ini_get("yaf.environ");

            if fromIni {
                let env = fromIni;
            } else {
                let env = "product";
            }
        }

        return env;*/
        return this->_environ;
    }

    public function execute(args)
    {
        var arguments, callback;

        let arguments =  func_get_args();
        let callback = arguments[0];

        if !is_callable(callback) {
            Exception::trigger_error("First argument is expected to be a valid callback", E_USER_WARNING);
        }
        array_shift(arguments);

        return call_user_func_array(callback, arguments);
    }

    /**
     * Yaf_Application can not be cloned
     */
    protected function __clone() -> void
    {
    }

    /**
     * Yaf_Application can not be serialized
     */
    protected function __sleep() -> void
    {
    }

    /**
     * Yaf_Application can not be deserialized
     */
    protected function __wakeup() -> void
    {
    }

    public function getAppDirectory()
    {

        return g::get("directory");
    }

    public function setAppDirectory(directory)
    {

        if !is_dir(directory) || !g::isAbsolutePath(directory) {

            return false;
        }
        g::set("directory", directory);

        return this;
    }

    /**
     * this was added internally
     * @param string $module
     * @return boolean
     */
    public static function isModuleName(string module) -> boolean
    {
        var app, modules;

        let app =  self::app();

        if app == null {

            return false;
        }
        let modules =  app->getModules();

        if array_search(strtolower(module), array_map("strtolower", modules)) !== false {

            return true;
        }

        return false;
    }

    public function setErrorNo(err) -> void
    {
        let this->_errno = err;
    }

    public function setErrorMsg(msg) -> void
    {
        let this->_errmsg = msg;
    }

    public function clearLastError() -> void
    {
        let this->_errno = 0;
        let this->_errmsg = "";
    }

    public function getLastErrorMsg()
    {

        return this->_errmsg;
    }

    public function getLastErrorNo()
    {

        return this->_errno;
    }

    /**
     * Load configuration file of options
     *
     * @param  string $file
     * @throws Yaf_Exception when invalid configuration file is provided
     * @return array
     */
    protected function _loadConfig(string file) -> array
    {
        var environment, config;

        let environment =  this->environ();

        if is_string(file) {
            let config =  new Config\Ini(file, environment);
        } elseif is_array(file) {
            let config =  new Config\Simple(file);
        //}elseif file instanceof Config_Abstract {
        //  let config = file;
        } else {
            throw new Exception("Invalid options provided; must be location of config file, " . "a config object, or an array");
        }
        return config;
    }
    
    /**
     * Parse application options
     *
     * @param  array $options
     * @throws Yaf_Exception When no bootstrap path is provided
     * @throws Yaf_Exception When invalid bootstrap information are provided
     * @return Yaf_Application
     */
    protected function parseOptions(array options)
    {
        var modules, module;
    
        
        if !is_array(options) {
            throw new Exception\TypeError("Expected an array of application configure");
        }
        let options =  array_change_key_case(options, CASE_LOWER);
        
        if !isset options["application"] {
            throw new Exception\TypeError("Expected an array of application configure");
        }
        let options = options["application"];
        
        if !empty(options["directory"]) {
            g::set("directory", preg_replace("/" . preg_quote(DIRECTORY_SEPARATOR, "/") . "$/", "", options["directory"]));
        } else {
            throw new Exception\StartupError("Expected a directory entry in application configures");
        }
        
        if !empty(options["ext"]) {
            g::set("ext", options["ext"]);
        }
        
        if !empty(options["bootstrap"]) && is_string(options["bootstrap"]) {
            let this->_options["bootstrap"] = options["bootstrap"];
        }
        
        if !empty(options["library"]) {
            
            if is_string(options["library"]) {
                let this->_options["local_library"] = options["library"];
            } else { 
            
            if is_array(options["library"]) {
                
                if !empty(options["library"]["directory"]) && is_string(options["library"]["directory"]) {
                    let this->_options["local_library"] = options["library"]["directory"];
                }
                
                if !empty(options["library"]["namespace"]) && is_string(options["library"]["namespace"]) {
                    let this->_options["local_namespace"] = options["library"]["namespace"];
                }
            }
            }
        } else {
            let this->_options["local_library"] = g::get("directory") . DIRECTORY_SEPARATOR . Loader::YAF_LIBRARY_DIRECTORY_NAME;
        }
        
        if !empty(options["view"]) && is_array(options["view"]) && !empty(options["view"]["ext"]) && is_string(options["view"]["ext"]) {
            g::set("view_ext", options["view"]["ext"]);
        }
        
        if !empty(options["baseUri"]) && is_string(options["baseUri"]) {
            let this->_options["baseUri"] = options["baseUri"];
        } else {
            let this->_options["baseUri"] = _SERVER["PHP_SELF"];
        }
        
        if !empty(options["dispatcher"]) && is_array(options["dispatcher"]) {
            
            if !empty(options["dispatcher"]["defaultModule"]) && is_string(options["dispatcher"]["defaultModule"]) {
                g::set("default_module", options["dispatcher"]["defaultModule"]);
            } else {
                g::set("default_module", Router::YAF_ROUTER_DEFAULT_MODULE);
            }
            
            if !empty(options["dispatcher"]["defaultController"]) && is_string(options["dispatcher"]["defaultController"]) {
                g::set("default_controller", options["dispatcher"]["defaultController"]);
            } else {
                g::set("default_controller", Router::YAF_ROUTER_DEFAULT_CONTROLLER);
            }
            
            if !empty(options["dispatcher"]["defaultAction"]) && is_string(options["dispatcher"]["defaultAction"]) {
                g::set("default_action", options["dispatcher"]["defaultAction"]);
            } else {
                g::set("default_action", Router::YAF_ROUTER_DEFAULT_ACTION);
            }
            
            if isset options["dispatcher"]["throwException"] {
                g::set("throwException", (bool) options["dispatcher"]["throwException"]);
            }
            
            if isset options["dispatcher"]["catchException"] {
                g::set("catchException", (bool) options["dispatcher"]["catchException"]);
            }
            
            if isset options["dispatcher"]["defaultRoute"] && is_array(options["dispatcher"]["defaultRoute"]) {
                g::set("default_route", options["dispatcher"]["defaultRoute"]);
            }
        } else {
            g::set("default_module", Router::YAF_ROUTER_DEFAULT_MODULE);
            g::set("default_controller", Router::YAF_ROUTER_DEFAULT_CONTROLLER);
            g::set("default_action", Router::YAF_ROUTER_DEFAULT_ACTION);
            let this->_options["throwException"] = true;
            let this->_options["catchException"] = true;
        }
        
        if !empty(options["modules"]) && is_string(options["modules"]) {
            let modules =  preg_split("/,/", options["modules"]);
            for module in modules {
                let this->_modules[] = trim(module);
            }
        }
        
        if empty(this->_modules) {
            let this->_modules[] = g::get("default_module");
        }
        
        return true;
    }
    
    public function exceptionHandler(<\Exception> e) -> void
    {
        //the exception is registered
        echo PHP_EOL . "Exception throught App - " . e->getMessage();
    }

}