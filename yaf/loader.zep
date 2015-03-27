/**
 * Yaf loader
 * @todo
 * check if local namespace from application.ini with , as sep would be
 * transformed to :
 *
 */
/**
 * @namespace
 */
namespace Yaf;

class Loader
{
    const YAF_LOADER_RESERVERD = "Yaf_";
    const YAF_LOADER_CONTROLLER = "Controller";
    const YAF_LOADER_MODEL = "Model";
    const YAF_LOADER_PLUGIN = "Plugin";
    //not used yet
    const YAF_LOADER_DAO = "Dao_";
    const YAF_LOADER_SERVICE = "Service_";
    const YAF_LIBRARY_DIRECTORY_NAME = "library";
    const YAF_CONTROLLER_DIRECTORY_NAME = "controllers";
    const YAF_PLUGIN_DIRECTORY_NAME = "plugins";
    const YAF_MODULE_DIRECTORY_NAME = "modules";
    const YAF_VIEW_DIRECTORY_NAME = "views";
    const YAF_MODEL_DIRECTORY_NAME = "models";
    const YAF_DEFAULT_VIEW_EXT = "phtml";
    /**
     * @var Yaf_Loader instance
     */
    protected static _instance;
    /**
     * @var string default library path
     */
    protected _library;
    /**
     * @var string global library path
     */
    protected _globalLibrary;
    /**
     * @var string Namespace of classes within this resource
     */
    protected _localNamespace = "";
    public function internal_autoload(classs, dirs = null)
    {
        var file, dirPath, dir, key;
        bool autoload=false;
        
        if class_exists(classs, autoload) || interface_exists(classs, autoload) {
            return;
        }
        
        if dirs !== null && !is_string(dirs) {
            throw new Exception("Directory argument must be a string");
        }
        
        if dirs == null {
            let dirs =  this->resolveDirectory(classs);
        }
        let file =  this->resolveClass(classs);
        
        if !empty(dirs) {
            // use the autodiscovered path
            let dirPath =  dirname(file);
            let dirs =  explode(PATH_SEPARATOR, dirs);
            for key, dir in dirs {
                
                if dir == "." {
                    let dirs[key] = dirPath;
                } else {
                    let dir =  rtrim(dir, "\\/");
                    let dirs[key] = dir . DIRECTORY_SEPARATOR . dirPath;
                }
            }
            let file =  basename(file);
            
            return self::import(file, dirs);
        } else {
            
            return self::import(file);
        }
    }
    
    /**
     * Attempt to autoload a class
     *
     * @param  string $class
     * @return mixed False if not matched, otherwise result if include operation
     */
    public function autoload(string classs)
    {
        var className, appDir, directory, splAutoLoadIni;
    
        let className = classs;
         bool autoload=false;
        if class_exists(className, autoload) || interface_exists(className, autoload) {
            
            return true;
        }
        
        if strpos(classs, self::YAF_LOADER_RESERVERD) === 0 {
            throw new Exception("You should not use " . self::YAF_LOADER_RESERVERD . " as class name prefix");
        }
        let appDir =  g::get("directory");
        let directory = "";
        
        if this->isCategoryType(classs, self::YAF_LOADER_MODEL) {
            //this is a model
            let directory =  appDir . DIRECTORY_SEPARATOR . self::YAF_MODEL_DIRECTORY_NAME . DIRECTORY_SEPARATOR;
            let classs =  this->resolveCategory(classs, self::YAF_LOADER_MODEL);
        } else {
            
            if this->isCategoryType(classs, self::YAF_LOADER_PLUGIN) {
                //this is a plugin
                let directory =  appDir . DIRECTORY_SEPARATOR . self::YAF_PLUGIN_DIRECTORY_NAME;
                let classs =  this->resolveCategory(classs, self::YAF_LOADER_PLUGIN);
            } else {
                
                if this->isCategoryType(classs, self::YAF_LOADER_CONTROLLER) {
                    //this is a controller
                    let directory =  appDir . DIRECTORY_SEPARATOR . self::YAF_CONTROLLER_DIRECTORY_NAME;
                    let classs =  this->resolveCategory(classs, self::YAF_LOADER_CONTROLLER);
                } else {
                    
                    if this->isCategoryType(classs, self::YAF_LOADER_DAO) || this->isCategoryType(classs, self::YAF_LOADER_SERVICE) {
                        //this is used internally
                        let directory =  appDir . DIRECTORY_SEPARATOR . self::YAF_MODEL_DIRECTORY_NAME;
                    }
                }
            }
        }
        
        if directory != "" && appDir == "" {
            Exception::trigger_error("Couldn't load a framework MVC class without an " . "Yaf_Application initializing ", E_USER_WARNING);
        }
        let splAutoLoadIni =  g::iniGet("yaf.use_spl_autoload");
        
        if this->internal_autoload(classs, directory) {
            
            if !class_exists(className, autoload) && !interface_exists(className, autoload) {
                
                if splAutoLoadIni == false {
                    Exception::trigger_error("Could not find class " . className . " in " . directory, E_USER_ERROR);
                } else {
                    
                    return false;
                }
            }
        } else {
            
            if splAutoLoadIni == false {
                Exception::trigger_error("Could not find script " . (
                directory != "" ? directory : this->resolveDirectory(classs)) . DIRECTORY_SEPARATOR . this->resolveClass(classs), E_USER_WARNING);
            } else {
                
                return false;
            }
        }
        
        return true;
    }
    
    protected function isCategoryType(className, category)
    {
        var nameSeparator;
    
        let nameSeparator =  g::iniGet("yaf.name_separator");
        
        if g::iniGet("yaf.name_suffix") == true {
            //we should check at the end of the class name
            
            if category == substr(className, strlen(className) - strlen(category), strlen(category)) {
                
                if nameSeparator == "" || substr(className, strlen(className) - strlen(category) - strlen(nameSeparator), strlen(nameSeparator)) == nameSeparator {
                    
                    return true;
                }
            }
        } else {
            //we check at the begining
            
            if category == substr(className, 0, strlen(category)) {
                
                if nameSeparator == "" || substr(className, strlen(category), strlen(nameSeparator)) == nameSeparator {
                    
                    return true;
                }
            }
        }
    }
    
    protected function resolveCategory(className, category)
    {
        var nameSeparator;
    
        let nameSeparator =  g::iniGet("yaf.name_separator");
        
        if g::iniGet("yaf.name_suffix") == true {
            //we should remove from the end of classname
            
            return substr(className, 0, strlen(className) - strlen(category) - strlen(nameSeparator));
        } else {
            //we should remove from the start of the classname
            
            return substr(className, strlen(category) - strlen(nameSeparator), strlen(className));
        }
    }
    
    protected function resolveDirectory(classs)
    {
        var directory;
    
        
        if this->isLocalName(classs) {
            let directory =  this->_library;
        } else {
            let directory =  this->_globalLibrary;
        }
        
        if directory == "" {
            Exception::trigger_error("Yaf_Loader requires Yaf_Application" . "(which set the library_directory) to be initialized first", E_USER_WARNING);
        }
        
        return directory;
    }
    
    protected function resolveClass(classs)
    {
        var className, file, namespacee, lastNsPos, segments, value, key;
    
        // Autodiscover the path from the class name
        // Implementation is PHP namespace-aware, and based on
        // Framework Interop Group reference implementation:
        // http://groups.google.com/group/php-standards/web/psr-0-final-proposal
        let className =  ltrim(classs, "\\");
        let file = "";
        let namespacee = "";
        let lastNsPos =  strripos(className, "\\");
        if lastNsPos !== false {
            let namespacee =  substr(className, 0, lastNsPos);
            let className =  substr(className, lastNsPos + 1);
            let file =  str_replace("\\", DIRECTORY_SEPARATOR, namespacee) . DIRECTORY_SEPARATOR;
        }
        
        if g::iniGet("yaf.lowcase_path") == true {
            let file =  strtolower(file);
            let segments =  explode("_", className);
            for key, value in segments {
                
                if key != count(segments) - 1 {
                    let value =  strtolower(value);
                }
            }
            let file .= implode(DIRECTORY_SEPARATOR, segments) . "." . g::get("ext");
        } else {
            let file .= str_replace("_", DIRECTORY_SEPARATOR, className) . "." . g::get("ext");
        }
        
        return file;
    }
    
    /**
     * Loads a PHP file.  This is a wrapper for PHP's include() function.
     *
     * $filename must be the complete filename, including any
     * extension such as ".php".  Note that a security check is performed that
     * does not permit extended characters in the filename.  This method is
     * intended for loading Zend Framework files.
     *
     * If $dirs is a string or an array, it will search the directories
     * in the order supplied, and attempt to load the first matching file.
     *
     * If the file was not found in the $dirs, or if no $dirs were specified,
     * it will attempt to load it from PHP's include_path.
     *
     *
     * @param  string        $filename
     * @param  string|array  $dirs - OPTIONAL either a path or array of paths
     *                       to search.
     * @return boolean
     */
    public static function import(string filename, dirs = null) -> boolean
    {
        var loader, incPath;
    
        let loader =  self::getInstance();
        loader->_securityCheck(filename);
        /**
         * Search in provided directories, as well as include_path
         */
        let incPath =  false;
        
        if !empty(dirs) && (is_array(dirs) || is_string(dirs)) {
            
            if is_array(dirs) {
                let dirs =  implode(PATH_SEPARATOR, dirs);
            }
            let incPath =  get_include_path();
            set_include_path(dirs . PATH_SEPARATOR . incPath);
        }
        /**
         * Try finding for the plain filename in the include_path.
         */
         if file_exists(filename) {
             require filename;
         } else {
             return false;
         }
        /**
         * If searching in directories, reset include_path
         */
        
        if incPath {
            set_include_path(incPath);
        }
        
        return true;
    }
    
    /**
     * Ensure that filename does not contain exploits
     *
     * @param  string $filename
     * @return void
     * @throws Yaf_Exception
     */
    protected function _securityCheck(string filename)
    {
        /**
         * Security check
         */
        
        if preg_match("/[^a-z0-9\\/\\\\_.:-]/i", filename) {
            throw new Exception("Security check: Illegal character in filename");
        }
    }
    
    public function clearLocalNamespace() -> void
    {
        let this->_localNamespace = "";
    }
    
    /**
     * not possible to clone
     */
    protected function __clone() -> void
    {
    }
    
    /**
     * Constructor
     *
     * @param
     * @return void
     */
    public function __construct()
    {
    }
    
    /**
     * Retrieve singleton instance
     *
     * @return Yaf_Loader
     */
    public static function getInstance(library = null, globalLibrary = null)
    {
        var instance;
    
        
        if self::_instance === null {
            let self::_instance =  new self();
            let instance =  self::_instance;
            
            if library != null {
                instance->setLibraryPath(library, false);
            }
            
            if globalLibrary != null {
                instance->setLibraryPath(globalLibrary, true);
            } else {
                
                if library != null {
                    instance->setLibraryPath(library, true);
                }
            }
            
            if phpversion() >= "5.3" {
                spl_autoload_register([instance, "autoload"], true, false);
            } else {
                spl_autoload_register([instance, "autoload"], true);
            }
        } else {
            let instance =  self::_instance;
            
            if library != null {
                instance->setLibraryPath(library, false);
            }
            
            if globalLibrary != null {
                instance->setLibraryPath(globalLibrary, true);
            }
        }
        
        return self::_instance;
    }
    
    /**
     * Get base path to this set of resources
     *
     * @return string
     */
    public function getLibraryPath(isGlobal = false) -> string
    {
        
        if isGlobal == true {
            
            return this->_globalLibrary;
        } else {
            
            return this->_library;
        }
    }
    
    /**
     * Get namespace this autoloader handles
     *
     * @return string
     */
    public function getLocalNamespace() -> string
    {
        
        return this->_localNamespace;
    }
    
    public function isLocalName(className)
    {
        var namespaces, prefix, pos, classs, prefixes;
    
        let namespaces =  this->getLocalNamespace();
        
        if namespaces == null {
            
            return false;
        }
        let className =  ltrim(className, "\\");
        let prefix = "";
        let pos =  strpos(className, "_");
        if pos !== false {
            let prefix =  substr(className, 0, pos);
            let classs =  substr(className, pos + 1);
        } else {
            let pos =  strpos(className, "\\");
            if pos !== false {
                let prefix =  substr(className, 0, pos);
                let classs =  substr(className, pos + 1);
            }
        }
        
        if prefix == "" {
            
            return false;
        }
        let prefixes =  explode(PATH_SEPARATOR, namespaces);
        
        if in_array(prefix, prefixes) {
            
            return true;
        }
        
        return false;
    }
    
    /**
     * register a namespace for the loader
     *
     * @param  string|array $namespace
     * * @throws Yaf_Exception if namespace is not string or array
     */
    public function registerLocalNamespace(namespacee) -> void
    {
        var directorySeparator, value;
    
        
        if !is_string(namespacee) && !is_array(namespacee) {
            throw new Exception("Invalid parameters provided, must be a string, or an array");
        }
        let directorySeparator =  PATH_SEPARATOR;
        
        if is_string(namespacee) {
            
            if this->_localNamespace == "" {
                let this->_localNamespace .= directorySeparator;
            }
            let this->_localNamespace .= (string) namespacee . directorySeparator;
        } else { 
        
        if is_array(namespacee) {
            
            if this->_localNamespace == "" {
                let this->_localNamespace .= directorySeparator;
            }
            for value in namespacee {
                let this->_localNamespace .= value . directorySeparator;
            }
        }
        }
    }
    
    /**
     * Set base path for this set of resources
     *
     * @param  string $path
     * @return void
     */
    public function setLibraryPath(string path, isGlobal = false)
    {
        if isGlobal == true {
            let this->_globalLibrary =  (string) path;
        } else {
            let this->_library =  (string) path;
        }
    }
    
    protected function __sleep() -> void
    {
    }
    
    protected function __wakeup() -> void
    {
    }

}