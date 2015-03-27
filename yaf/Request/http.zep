/**
 * Yaf Request Http
 */
/**
 * @namespace
 */
namespace Yaf\Request;
use Yaf\Request_Abstract;
class Http extends Request_Abstract
{
    /**
     * Scheme for http
     *
     */
    const SCHEME_HTTP = "http";
    /**
     * Scheme for https
     *
     */
    const SCHEME_HTTPS = "https";
    /**
     * REQUEST_URI
     * @var string;
     */
    protected _requestUri;

    protected _params;
    /**
     * Constructor
     *
     * @param string $requestUri
     * @param string $baseUri
     * @return void
     */
    public function __construct(string requestUri = null, string baseUri = null)
    {
        if requestUri !== null {
            let this->_requestUri = requestUri;
        } else {
            this->setRequestUri();
        }
        
        if baseUri !== null {
            let this->_baseUri = baseUri;
        } else {
            this->setBaseUri();
        }
        //this will set the current method
        this->getMethod();
    }
    
    protected function __clone() -> void
    {
    }
    
    /**
     * Magic method get
     * @param string $key
     * @return mixed
     */
    public function __get(name)
    {
        return this->get(name);
    }
    
    /**
     * Access values contained in the superglobals as public members
     * Order of precedence: 1. GET, 2. POST, 3. COOKIE, 4. SERVER, 5. ENV
     *
     * @param string $name
     * @return mixed
     */
    public function get(string name, string tmpDefault=null)
    {
         if isset this->_params[name]{
            return this->_params[name];
         }elseif isset _GET[name] {
            return _GET[name];
         }elseif isset _POST[name] {
            return _POST[name];
         }elseif isset _COOKIE[name] {
            return _COOKIE[name];
         }elseif  name == "REQUEST_URI" {
            return this->getRequestUri();
         }elseif  name == "PATH_INFO" {
            return this->getPathInfo();
         }elseif isset _SERVER[name] {
            return _SERVER[name];
         //}elseif isset _ENV[name] {
         //   return _ENV[name];
         }else{
            return tmpDefault;
         }
    }

    
    public function __set(name, value) -> void
    {
        throw new Exception("Use setParam to set a parameter of request");
    }
    
    /**
     * Check to see if a property is set
     *
     * @param string $key
     * @return boolean
     */
    public function __isset(string key) -> boolean
    {
        if isset this->_params[key]{
             return true;
          }elseif isset _GET[key] {
             return true;
          }elseif isset _POST[key] {
             return true;
          }elseif isset _COOKIE[key] {
             return true;
          }elseif isset _SERVER[key] {
             return true;
          //}elseif isset _ENV[key] {
          //   return true;
          }else{
             return false;
          }
    }
    
    /**
     * Retrieve a member of the $_GET superglobal
     *
     * If no $name is passed, returns the entire $_GET array.
     *
     * @param string $name
     * @param mixed $default Default value to use if key not found
     * @return mixed Returns null if key does not exist
     */
    public function getQuery(string name = null, tmpDefault = null)
    {
        var get;
        let get = _GET;
        if name === null {
            
            return _GET;
        }
        
        return isset get[name] ? get[name] : tmpDefault;
    }
    
    /**
     * Retrieve a member of the $_POST superglobal
     *
     * If no $name is passed, returns the entire $_POST array.
     *
     * @param string $name
     * @param mixed $default Default value to use if key not found
     * @return mixed Returns null if key does not exist
     */
    public function getPost(string name = null, tmpDefault = null)
    {
        var post;
        let post = _POST;
        if name === null {
            
            return post;
        }
        
        return isset post[name] ? post[name] : tmpDefault;
    }
    
    /**
     * Retrieve a member of the $_COOKIE superglobal
     *
     * If no $name is passed, returns the entire $_COOKIE array.
     *
     * @param string $name
     * @param mixed $default Default value to use if key not found
     * @return mixed Returns null if key does not exist
     */
    public function getCookie(string name = null, tmpDefault = null)
    {
        var cookie;
        let cookie = _COOKIE;
        if name === null {
            
            return cookie;
        }
        
        return isset cookie[name] ? cookie[name] : tmpDefault;
    }
    
    /**
     * Retrieve a member of the $_FILES superglobal
     *
     * If no $name is passed, returns the entire $_FILES array.
     *
     * @param string $name
     * @param mixed $default Default value to use if key not found
     * @return mixed Returns null if key does not exist
     */
    public function getFiles(string name = null, tmpDefault = null)
    {
        var files;
        let files = _FILES;
        if name === null {
            
            return files;
        }
        
        return isset files[name] ? files[name] : tmpDefault;
    }
    
    /**
     * Retrieve a member of the $_REQUEST superglobal
     *
     * If no $name is passed, returns the entire $_REQUEST array.
     *
     * @param string $name
     * @param mixed $default Default value to use if key not found
     * @return mixed Returns null if key does not exist
     */
    public function getRequest(string name = null, tmpDefault = null)
    {
        var request;
        let request = _REQUEST;
        if name === null {
            return request;
        }
        
        return isset request[name] ? request[name] : tmpDefault;
    }
    
    /**
     * Returns the REQUEST_URI taking into account
     * platform differences between Apache and IIS
     *
     * @return string
     */
    public function getRequestUri() -> string
    {
        
        if empty(this->_requestUri) {
            this->setRequestUri();
        }
        
        return this->_requestUri;
    }
    public function getPathInfo() -> string
    {}
    /**
     * Everything in REQUEST_URI before PATH_INFO
     * <form action="<?=$baseUrl?>/news/submit" method="POST"/>
     *
     * @return string
     */
    public function getBaseUri() -> string
    {
        
        if this->_baseUri === null {
            this->setBaseUri();
        }
        
        return this->_baseUri;
    }
    
    /**
     * Set the base URL of the request; i.e.,
     * the segment leading to the script name
     *
     * E.g.:
     * - /admin
     * - /myapp
     * - /subdir/index.php
     *
     * Do not use the full URI when providing the base. The following are
     * examples of what not to use:
     * - http://example.com/admin (should be just /admin)
     * - http://example.com/subdir/index.php (should be just /subdir/index.php)
     *
     * If no $baseUrl is provided, attempts to determine the base URL from the
     * environment, using SCRIPT_FILENAME, SCRIPT_NAME, PHP_SELF, and
     * ORIG_SCRIPT_NAME in its determination.
     *
     * @param mixed $baseUrl
     * @return Yaf_Request_Abstract
     */
    public function setBaseUri(baseUri = null)
    {
        var filename, path, file, segs, index, last, pos, seg, requestUri, truncatedRequestUri, basename;
        
        if baseUri !== null && !is_string(baseUri) {
            
            return this;
        }
        
        if baseUri === null {
            
            let filename =  isset _SERVER["SCRIPT_FILENAME"] ? basename(_SERVER["SCRIPT_FILENAME"]) : "";
            
            if isset _SERVER["SCRIPT_NAME"] && basename(_SERVER["SCRIPT_NAME"]) === filename {
                let baseUri = _SERVER["SCRIPT_NAME"];
            } elseif isset _SERVER["PHP_SELF"] && basename(_SERVER["PHP_SELF"]) === filename {
                let baseUri = _SERVER["PHP_SELF"];
            } elseif isset _SERVER["ORIG_SCRIPT_NAME"] && basename(_SERVER["ORIG_SCRIPT_NAME"]) === filename {
                let baseUri = _SERVER["ORIG_SCRIPT_NAME"];
            } else {
                // Backtrack up the script_filename to find the portion matching
                // php_self
                
                let path =  isset _SERVER["PHP_SELF"] ? _SERVER["PHP_SELF"] : "";
                
                let file =  isset _SERVER["SCRIPT_FILENAME"] ? _SERVER["SCRIPT_FILENAME"] : "";
                let segs =  explode("/", trim(file, "/"));
                let segs =  array_reverse(segs);
                let index = 0;
                let last =  count(segs);
                let baseUri = "";
                do {
                    let seg = segs[index];
                    let baseUri =  "/" . seg . baseUri;
                    let index++;
                let pos =  strpos(path, baseUri);
                } while (last > index && pos !== false && pos != 0);
            }
            // Does the baseUrl have anything in common with the request_uri?
            let requestUri =  this->getRequestUri();
            
            if strpos(requestUri, baseUri) === 0 {
                // full $baseUrl matches
                let this->_baseUri = baseUri;
                
                return this;
            }
            
            if strpos(requestUri, dirname(baseUri)) === 0 {
                // directory portion of $baseUrl matches
                let this->_baseUri =  dirname(baseUri);
                
                return this;
            }
            let truncatedRequestUri = requestUri;
            let pos =  strpos(requestUri, "?");
            if pos !== false {
                let truncatedRequestUri =  substr(requestUri, 0, pos);
            }
            let basename =  basename(baseUri);
            
            if empty(basename) || !strpos(truncatedRequestUri, basename) {
                // no match whatsoever; set it blank
                let this->_baseUri = "";
                
                return this;
            }
            // If using mod_rewrite or ISAPI_Rewrite strip the script filename
            // out of baseUrl. $pos !== 0 makes sure it is not matching a value
            // from PATH_INFO or QUERY_STRING
            let pos =  strpos(requestUri, baseUri);
            if strlen(requestUri) >= strlen(baseUri) && (pos !== false && pos !== 0) {
                let baseUri =  substr(requestUri, 0, pos + strlen(baseUri));
            }
        }
        let this->_baseUri = baseUri;
        
        return this;
    }
    
    /**
     * Set the REQUEST_URI on which the instance operates
     *
     * If no request URI is passed, uses the value in $_SERVER['REQUEST_URI'],
     * $_SERVER['HTTP_X_REWRITE_URL'],
     * or $_SERVER['ORIG_PATH_INFO'] + $_SERVER['QUERY_STRING'].
     *
     * @param string $requestUri
     * @return Yaf_Request_Http
     */
    public function setRequestUri(requestUri = null)
    {
        var schemeAndHttpHost = "";
    
        
        if requestUri === null {
          if fetch requestUri, _SERVER["HTTP_X_REWRITE_URL"] {
                // check this first so IIS will catch
                 let this->_requestUri = requestUri;
            } elseif isset _SERVER["IIS_WasUrlRewritten"] && _SERVER["IIS_WasUrlRewritten"] == "1" && isset _SERVER["UNENCODED_URL"] && _SERVER["UNENCODED_URL"] != "" {
                let this->_requestUri = _SERVER["UNENCODED_URL"];
            } elseif isset _SERVER["REQUEST_URI"] {
                let this->_requestUri = _SERVER["REQUEST_URI"];
                // Http proxy reqs setup request uri with
                // scheme and host [and port] + the url path, only use url path
                let schemeAndHttpHost =  this->getScheme() . "://" . this->getHttpHost();
                
                if strpos(requestUri, schemeAndHttpHost) === 0 {
                    let this->_requestUri =  substr(requestUri, strlen(schemeAndHttpHost));
                }
            } elseif isset _SERVER["ORIG_PATH_INFO"] {
                // IIS 5.0, PHP as CGI
                let this->_requestUri = _SERVER["ORIG_PATH_INFO"];
                
                if !empty(_SERVER["QUERY_STRING"]) {
                    let this->_requestUri .= "?" . _SERVER["QUERY_STRING"];
                }
            } else {
                
                return this;
            }
        } elseif !is_string(requestUri) {
            return this;
        } else {
        }
        let this->_requestUri = requestUri;
        
        return this;
    }
    
    //new methods which had to be added
    /**
     * Get the request URI scheme
     *
     * @return string
     */
    public function getScheme()
    {
        
        return 
        this->getServer("HTTPS") == "on" ? self::SCHEME_HTTPS : self::SCHEME_HTTP;
    }
    
    /**
     * Get the HTTP host.
     *
     * "Host" ":" host [ ":" port ] ; Section 3.2.2
     * Note the HTTP Host header is not the same as the URI host.
     * It includes the port while the URI host doesn't.
     *
     * @return string
     */
    public function getHttpHost() -> string
    {
        var host, scheme, name, port;
    
        let host =  this->getServer("HTTP_HOST");
        
        if !empty(host) {
            
            return host;
        }
        let scheme =  this->getScheme();
        let name =  this->getServer("SERVER_NAME");
        let port =  this->getServer("SERVER_PORT");

        if name === null {
            
            return "";
        } elseif scheme == self::SCHEME_HTTP && port == 80 || scheme == self::SCHEME_HTTPS && port == 443 {
            return name;
        } else {
            return name . ":" . port;
        }
    }

}