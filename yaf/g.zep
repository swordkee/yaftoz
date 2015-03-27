/**
 * added this class to handle all the global options
 * which are available when yaf.so is loaded
 *
 */
/**
 * @namespace
 */
namespace Yaf;

/**
 * yaf gloab definitions
 */
/*globals_set("Yaf\\VERSION", "2.2.9");
globals_set("Yaf\\ERR\\STARTUP_FAILED", 512);
globals_set("Yaf\\ERR\\ROUTE_FAILED", 513);
globals_set("Yaf\\ERR\\DISPATCH_FAILED", 514);
globals_set("Yaf\\ERR\\AUTOLOAD_FAILED", 520);
globals_set("Yaf\\ERR\\NOTFOUND\\MODULE", 515);
globals_set("Yaf\\ERR\\NOTFOUND\\CONTROLLER", 516);
globals_set("Yaf\\ERR\\NOTFOUND\\ACTION", 517);
globals_set("Yaf\\ERR\\NOTFOUND\\VIEW", 518);
globals_set("Yaf\\ERR\\CALL_FAILED", 519);
globals_set("Yaf\\ERR\\TYPE_ERROR", 521);
*/
class g
{
    protected static _globals;
    //missing globals to check
    //local_namespace
    protected static _ini;

    public function __construct()-> void
    {
        this->getGlobals();
        this->getIni();
    }
    public function getGlobals() -> array
    {
        var globals;

        let globals = self::_globals;

        if globals === null {
            let globals = [
                "throwException" : true,
                "catchException" : false,
                "autoload_started" : 0,
                "configs" : null,
                "directory" : null,
                "local_library" : null,
                "ext" : Router::YAF_DEFAULT_EXT,
                "view_ext" : Loader::YAF_DEFAULT_VIEW_EXT,
                "default_module" : Router::YAF_ROUTER_DEFAULT_MODULE,
                "default_controller" : Router::YAF_ROUTER_DEFAULT_CONTROLLER,
                "default_action" : Router::YAF_ROUTER_DEFAULT_ACTION,
                "bootstrap" : Bootstrap_Abstract::YAF_DEFAULT_BOOTSTRAP,
                "modules" : null,
                "default_route" : null
            ];
            let self::_globals = globals;
        }
        return globals;
    }

    public function getIni() -> array
    {
        var ini;
        let ini = self::_ini;
        if ini === null {
            let ini = [
                "yaf.library" : "",
                "yaf.action_prefer" : false,
                "yaf.lowcase_path" : false,
                "yaf.use_spl_autoload" : false,
                "yaf.forward_limit" : "5",
                "yaf.name_suffix" : true,
                "yaf.name_separator" : "",
                "yaf.cache_config" : false,
                "yaf.st_compatible" : false,
                "yaf.environ" : "product",
                "yaf.use_namespace" : true
            ];
            let self::_ini = ini;
        }
        return ini;
    }
    public static function iniSet(key, value) -> void
    {
        let self::_ini[key] = value;
    }
    
    public static function iniGet(key)
    {
        var iniValue, value;
    
        let iniValue =  ini_get(key);
        if iniValue !== false {
            //we have ini set from php
            
            if iniValue == "0" {
                let value =  false;
            } elseif iniValue == "1" {
                let value =  true;
            } else {
                let value = iniValue;
            }
            self::iniSet(key, value);
            return value;
        } else {
            if isset self::_ini[key] {
                return self::_ini[key];
            }
        }
        return null;
    }
    
    public static function set(key, value) -> void
    {
        let self::_globals[key] = value;
    }
    
    public static function get(key)
    {
        if isset self::_globals[key] {
            
            return self::_globals[key];
        }
        return null;
    }
    
    public static function isAbsolutePath(path)
    {
        if substr(path, 0, 1) == "/" || strpos(path, ":") !== false && strpos(PHP_OS, "WIN") !== FALSE {
            return true;
        } else {
            return false;
        }
    }

}